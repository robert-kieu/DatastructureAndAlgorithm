#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 4
#define MIN 2

struct NODE {
	int count;
	int elements[MAX + 1];
	NODE* ptrs[MAX + 1]{ NULL };
};

NODE* proot;

NODE* createNode(int data, NODE* pnode, int way) {
	NODE* ptemp = new NODE;

	ptemp->elements[1] = data;
	ptemp->count = 1;
	ptemp->ptrs[0] = proot;
	ptemp->ptrs[1] = pnode;
	
	return ptemp;
}

void addValueToNode(int data, int pos, NODE* pnode, NODE* pnode2) {
	int i = pnode->count;
	while (i > pos) {
		pnode->elements[i + 1] = pnode->elements[i];
		pnode->ptrs[i + 1] = pnode->ptrs[i];
		i--;
	}
	pnode->elements[i + 1] = data;
	pnode->ptrs[i + 1] = pnode2;
	pnode->count++;
}

void splitNode(int data, int* Val, int pos, NODE* pnode, NODE* pnode2, NODE** pnode3) {
	int m = 0;
	if (pos > MIN) m = MIN + 1;
	else m = MIN;

	*pnode3 = new NODE;
	int i = m + 1;
	while (i <= MAX) {
		(*pnode3)->elements[i - m] = pnode->elements[i];
		(*pnode3)->ptrs[i - m] = pnode->ptrs[i];
		i++;
	}
	pnode->count = m;
	(*pnode3)->count = MAX - m;

	if (pos <= MIN) addValueToNode(data, pos, pnode, pnode2);
	else addValueToNode(data, pos - m, *pnode3, pnode2);
	*Val = pnode->elements[pnode->count];
	(*pnode3)->ptrs[0] = pnode->ptrs[pnode->count];
	--pnode->count;
}

bool setValueInNode(int data, int* Val, NODE* pnode, NODE** pnode2) {
	if (!pnode) {
		*Val = data;
		*pnode2 = NULL;
		return true;
	}

	int pos;
	if (data < pnode->elements[1]) pos = 0;
	else {
		pos = pnode->count;
		while (data < pnode->elements[pos] && pos > 1) pos--;
		if (data == pnode->elements[pos]) return false;
	}
	if (setValueInNode(data, Val, pnode->ptrs[pos], pnode2)) {
		if (pnode->count < MAX) addValueToNode(*Val, pos, pnode, *pnode2);
		else {
			splitNode(*Val, Val, pos, pnode, *pnode2, pnode2);
			return true;
		}
	}
	return false;
}

void insertNode(int data) {
	int i;
	NODE* pnode;

	int check = setValueInNode(data, &i, proot, &pnode);
	if (check) proot = createNode(i, pnode, 0);
}

void traversal(NODE* pnode) {
	if (pnode) {
		int i;
		for (i = 0; i < pnode->count; i++) {
			traversal(pnode->ptrs[i]);
			cout << pnode->elements[i + 1] << " ";
		} traversal(pnode->ptrs[i]);
	}
}

void coppyNode(NODE* pnode, int pos) {
	NODE* ptemp = pnode->ptrs[pos];

	while (ptemp->ptrs[0]) ptemp = ptemp->ptrs[0];
	pnode->elements[pos] = ptemp->elements[1];
}

void removeValue(NODE* pnode, int pos) {
	int i = pos + 1;
	while (i <= pnode->count) {
		pnode->elements[i - 1] = pnode->elements[i];
		pnode->ptrs[i - 1] = pnode->ptrs[i];
		i++;
	} --pnode->count;
}

void shiftDownRight(NODE* pnode, int pos) {
	NODE* ptemp = pnode->ptrs[pos];
	int i = ptemp->count;

	while (i > 0) {
		ptemp->elements[i + 1] = ptemp->elements[i];
		ptemp->ptrs[i + 1] = ptemp->ptrs[i];
	}
	ptemp->elements[1] = pnode->elements[pos];
	ptemp->ptrs[1] = ptemp->ptrs[0];
	++ptemp->count;

	ptemp = pnode->ptrs[pos - 1];
	pnode->elements[pos] = ptemp->elements[ptemp->count];
	pnode->ptrs[pos] = ptemp->ptrs[ptemp->count];
	--ptemp->count;
}

void shiftDownLeft(NODE* pnode, int pos) {
	int i = 1;
	NODE* ptemp = pnode->ptrs[pos - 1];

	++ptemp->count;
	ptemp->elements[ptemp->count] = pnode->elements[pos];
	ptemp->ptrs[ptemp->count] = pnode->ptrs[pos]->ptrs[0];

	ptemp = pnode->ptrs[pos];
	pnode->elements[pos] = ptemp->elements[1];
	ptemp->ptrs[0] = ptemp->ptrs[1];
	--ptemp->count;

	while (i <= ptemp->count) {
		ptemp->elements[i] = ptemp->elements[i + 1];
		ptemp->ptrs[i] = ptemp->ptrs[i + 1];
		i++;
	}
}

void merge(NODE* pnode, int pos) {
	int i = 1;
	NODE* p1 = pnode->ptrs[pos], * p2 = pnode->ptrs[pos - 1];

	++p2->count;
	p2->elements[p2->count] = pnode->elements[pos];
	p2->ptrs[p2->count] = pnode->ptrs[0];

	while (i <= p1->count) {
		++p2->count;
		p2->elements[p2->count] = p1->elements[i];
		p2->ptrs[p2->count] = p1->ptrs[i];
		i++;
	}

	i = pos;
	while (i < pnode->count) {
		pnode->elements[i] = pnode->elements[i + 1];
		pnode->ptrs[i] = pnode->ptrs[i + 1];
		i++;
	}
	--pnode->count;
	free(p1);
}

void adjust(NODE* pnode, int pos) {
	if (!pos) {
		if (pnode->ptrs[1]->count > MIN) shiftDownLeft(pnode, 1);
		else merge(pnode, 1);
	}
	else {
		if (pnode->count != pos) {
			if (pnode->ptrs[pos - 1]->count > MIN) shiftDownRight(pnode, pos);
			else {
				if (pnode->ptrs[pos + 1]->count > MIN) shiftDownLeft(pnode, pos + 1);
				else merge(pnode, pos);
			}
		}
		else {
			if (pnode->ptrs[pos - 1]->count > MIN) shiftDownRight(pnode, pos);
			else merge(pnode, pos);
		}
	}
}

int delVal(int key, NODE* pnode) {
	int pos, check = 0;
	if (pnode) {
		if (key < pnode->elements[1]) {
			pos = 0;
			check = 0;
		}
		else {
			for (pos = pnode->count; key < pnode->elements[pos] && pos > 1; pos--);
			if (key == pnode->elements[pos]) check = 1;
			else check = 0;
		}
		if (check) {
			if (pnode->ptrs[pos - 1]) {
				coppyNode(pnode, pos);
				check = delVal(pnode->elements[pos], pnode->ptrs[pos]);
			}
			else removeValue(pnode, pos);
		}
		else check = delVal(key, pnode->ptrs[pos]);

		if (pnode->ptrs[pos])
			if (pnode->ptrs[pos]->count < MIN)
				adjust(pnode, pos);
	}
	return check;
}

void remove(int key, NODE* pnode) {
	NODE* ptemp = new NODE;
	if (!delVal(key, pnode)) return;
	else {
		if (pnode->count == 0) {
			ptemp = pnode;
			pnode = pnode->ptrs[0];
			free(ptemp);
		}
	}
	proot = pnode;
}

bool search(int key, int* pos, NODE* pnode) {
	if (!pnode) return false;
	if (key < pnode->elements[1]) *pos = 0;
	else {
		for (*pos = pnode->count; key < pnode->elements[*pos] && *pos > 1; (*pos)--);
		if (key == pnode->elements[*pos]) return true;
	}
	search(key, pos, pnode->ptrs[*pos]);
}

int height(NODE* pnode)
{
	int h = 0;
	if (!pnode) return 0;
	++h;
	h += height(pnode->ptrs[0]);
	return h;
}

void printGivenLevel(NODE* pnode, int level){
	if (!pnode) return;
	else if (level == 1)
		for (int i = 1; i <= pnode->count; i++) cout << pnode->elements[i] << " ";
	else if (level > 1)
		for (int i = 0; i <= pnode->count; i++)
			printGivenLevel(pnode->ptrs[i], level - 1);
}

void LevelOrder(NODE* pnode) {
	int h = height(pnode);
	for (int i = 1; i <= h; i++) printGivenLevel(pnode, i);
}

bool isBTree(NODE* pnode, int i) {
	if (i > MAX || pnode->ptrs[0] == NULL) return true;

	if (height(pnode->ptrs[0]) != height(pnode->ptrs[i])) return false;
	else return(pnode, i + 1);
}

int main() {
	int choice;
	cout << "\n1. insert element";
	cout << "\n2. remove element";
	cout << "\n3. search element";
	cout << "\n4. traversal";
	cout << "\n5. level order";
	cout << "\n6. is Btree";
	cout << "\n0. exit";
	
	while (true) {
		cout << "\n>> "; cin >> choice;

		switch (choice) {
		case 1: {
			int key;
			cout << "\nkey : "; cin >> key;
			insertNode(key);
			break;
		}
		case 2: {
			int key;
			cout << "\nkey : "; cin >> key;
			remove(key, proot);
			break;
		}
		case 3: {
			int key;
			cout << "\nkey : "; cin >> key;
			if (search(key, &key, proot)) cout << "\nelement found";
			else cout << "\nelement not found";
			break;
		}
		case 4: {
			cout << endl;
			traversal(proot);
			break;
		}
		case 5: {
			cout << endl;
			LevelOrder(proot);
			break;
		}
		case 6: {
			if (isBTree(proot, 1)) cout << " yes ";
			else cout << " no ";
			break;
		}
		case 0:
			return 1;
		}
	}
}
