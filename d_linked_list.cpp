#include<iostream>

using namespace std;

struct d_NODE {
	int key;
	d_NODE* pNext;
	d_NODE* pPrev;
};

struct d_List {
	d_NODE* pHead;
	d_NODE* pTail;
};

d_NODE* createNode(int data) {
	d_NODE* pnode = new d_NODE;
	if (!pnode) return NULL;

	pnode->key = data;
	pnode->pNext = NULL;
	pnode->pPrev = NULL;

	return pnode;
}

d_List* init() {
	d_List* pl = new d_List;
	if (!pl) return NULL;

	pl->pHead = NULL;
	pl->pTail = NULL;

	return pl;
}

void addFront(d_List*& pl, d_NODE* pnode) {
	if (!pnode) return;
	if (pl->pHead == NULL) {
		pl->pHead = pnode;
		pl->pTail = pnode;
		pl->pHead->pNext = pl->pTail;
		pl->pTail->pPrev = pl->pHead;
		pl->pTail->pNext = NULL;
		pl->pHead->pPrev = NULL;
	}
	else {
		pnode->pNext = pl->pHead;
		pl->pHead->pPrev = pnode;
		pl->pHead = pnode;
	}
}

void addBack(d_List*& pl, d_NODE* pnode) {
	if (!pnode) return;
	if (pl->pHead == NULL) {
		pl->pHead = pnode;
		pl->pTail = pnode;
		pl->pHead->pNext = pl->pTail;
		pl->pTail->pPrev = pl->pHead;
		pl->pTail->pNext = NULL;
		pl->pHead->pPrev = NULL;
	}
	else {
		pnode->pPrev = pl->pTail;
		pl->pTail->pNext = pnode;
		pl->pTail = pnode;
	}
}

void addBeforeGivenNode(d_List*& pl, d_NODE* pnode_base, d_NODE* pnode_wanna_add) {
	if (pnode_base == pl->pHead) addFront(pl, pnode_wanna_add);
	else {
		pnode_wanna_add->pPrev = pnode_base->pPrev;
		pnode_base->pPrev->pNext = pnode_wanna_add;

		pnode_wanna_add->pNext = pnode_base;
		pnode_base->pPrev = pnode_wanna_add;
	}
}

void addAfterGivenNode(d_List*& pl, d_NODE* pnode_base, d_NODE* pnode_wanna_add) {
	if (pnode_base == pl->pTail) addBack(pl, pnode_wanna_add);
	else {
		pnode_wanna_add->pNext = pnode_base->pNext;
		pnode_base->pNext->pPrev = pnode_wanna_add;

		pnode_wanna_add->pPrev = pnode_base;
		pnode_base->pNext = pnode_wanna_add;
	}
}

void removeFront(d_List*& pl) {
	d_NODE* pnode = pl->pHead;
	pl->pHead = pl->pHead->pNext;
	delete pnode;
	pl->pHead->pPrev = NULL;
	pnode = NULL;
}

void removeBack(d_List*& pl) {
	d_NODE* pnode = pl->pTail;
	pl->pTail = pl->pTail->pPrev;
	delete pnode;
	pl->pTail->pNext = NULL;
	pnode = NULL;
}

void removeFirstNodeWithGivenValue(d_List*& pl, int key) {
	if (pl->pHead->key == key) removeFront(pl);
	else if (pl->pTail->key == key) removeBack(pl);
	else {
		for (auto i = pl->pHead->pNext; i != pl->pTail; i = i->pNext) {
			if (i->key == key) {
				auto temp = i;
				i->pPrev->pNext = i->pNext;
				i->pNext->pPrev = i->pPrev;
				delete temp;
				temp = NULL;
				break;
			}
		}
	}
}

int main() {
	d_List* pl = init();
	d_NODE* pn = createNode(3333);
	addBack(pl, pn);
	addBack(pl, pn);
	addBack(pl, pn);
	/*addAfterGivenNode(pl, pl->pHead, pn);
	removeFirstNodeWithGivenValue(pl, 3333);
	d_NODE* pn2 = createNode(3333);
	addAfterGivenNode(pl, pl->pHead, pn2);*/
	d_NODE* pnode = pl->pHead;
	while (pnode != NULL) {
		cout << pnode->key << " ";
		pnode = pnode->pNext;
	}
	return 1;
}