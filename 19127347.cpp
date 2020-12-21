//#include<iostream>
//#include<vector>
//#include<fstream>
//#include<string>
//#include<algorithm>
//
//using namespace std;
//
//struct Company
//{
//	string name;
//	string profit_tax;
//	string address;
//};//
//
//vector<Company> readData(string filename){
//	string s;
//	ifstream readData;
//	vector<Company>data;
//	Company a;
//
//	readData.open(filename);
//	while (getline(readData, s)){
//		a.name = s.substr(0, s.find('|'));
//		s.erase(0, s.find('|') + 1);
//		a.profit_tax = s.substr(0, s.find('|'));
//		s.erase(0, s.find('|'));
//		a.address = s.substr(1);
//		data.push_back(a);
//	}
//
//	readData.close();
//	return data;
//}
//
//long long getTheModulo(long long number, long long i, long long m) {
//	long long temp = 1;
//	while (i > 0) {
//		temp = (temp * number) % m;
//		i--;
//	}
//	return temp;
//}
//
//long long HashString(string company_name){
//	long long m = pow(10, 9) + 9;
//	
//	while (company_name.length() > 20) company_name = company_name.substr(1);
//
//	long long name_hashed = 0;
//	for (int i = 0; i < company_name.length(); i++) {
//		name_hashed += company_name[i] * getTheModulo(31, i, m);
//		name_hashed %= m;
//	}
//	
//	return name_hashed;
//}
//
//Company* CreateHashTable(vector<Company> list_company) {
//	Company* hash_table = new Company[2000];
//	
//	for (int i = 1; i < list_company.size(); i++) {
//		if (hash_table[HashString(list_company[i].name) % 2000].name == "")
//			hash_table[HashString(list_company[i].name) % 2000] = list_company[i];
//		else {
//			int j = i;
//			while (hash_table[HashString(list_company[j].name) % 2000].name != "") {
//				j++;
//				if (j >= 2000) j -= 2000;
//			} hash_table[j] = list_company[i];
//		}
//	}
//
//	return hash_table;
//}
//
//Company* Search(Company* hash_table, string company_name) {
//	if (HashString(hash_table[HashString(company_name) % 2000].name) == HashString(company_name))
//		return &hash_table[HashString(company_name) % 2000];
//	else return NULL;
//}
//
//int main(){
//
//	vector<Company> a = readData("MST.txt");
//	/*for (auto i : a)
//		cout << HashString(i.name) << " " << i.profit_tax << " " << i.address << endl << endl << endl;*/
//
//	Company* b = CreateHashTable(a);
//
//	/*for (int i = 0; i < 2000; i++) {
//		if (b[i].name != "")
//			cout << "( " << i << " )"<< b[i].name << " " << b[i].address << " " << b[i].profit_tax << endl;
//	}*/
//
//	Company* c = Search(b, "CONG TY TNHH BEE VIET NA");
//	if(c)
//		cout << c->name << " " << c->address << " " << c->profit_tax;
//
//	return 1;
//}