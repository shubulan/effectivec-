#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <list>
using namespace std;
class PhoneNumber{
public:
	PhoneNumber(const string& num = "0", string na = "0", string ar = "0") : 
														number(num),
														nation(na),
														area(ar)
	{}
	string number;
	string nation;
	string area;
};
class ABEntry1{
public:
	ABEntry1(const string& name, const string& address,
			const list<PhoneNumber>& phones);
private:
	string theName;
	string theAddress;
	list<PhoneNumber> thePhones;
	int numTimesConsulted;
};
class ABEntry2{
public:
	ABEntry2(const string& name, const string& address,
			const list<PhoneNumber>& phones);
private:
	string theName;
	string theAddress;
	list<PhoneNumber> thePhones;
	int numTimesConsulted;
};
// 构造函数的写法:赋值
ABEntry1::ABEntry1(const string& name, const string& address,
			const list<PhoneNumber>& phones){
	theName = name;
	theAddress = address;
	thePhones = phones;
	numTimesConsulted = 0;
}
// 构造函数的写法:初始化
ABEntry2::ABEntry2(const string& name, const string& address,
			const list<PhoneNumber>& phones) : theName(name),
											   theAddress(address),
												thePhones(phones),
												numTimesConsulted(0)
{
}
int main() {
	int TESTNUM = 10000;
	vector<ABEntry1> ab1;
	vector<ABEntry2> ab2;
	long long start = clock();
	for (int i = 0; i < TESTNUM; i++) {
		ABEntry1 temp("江户川柯南", "东京米花町5丁目毛利侦探事务所", {PhoneNumber("55441355335", "0081", "3"),
		                                                              PhoneNumber("58798493135", "0081", "3")});
		ab1.push_back(temp);
	}
	long long end = clock();
	for (int i = 0; i < TESTNUM; i++) {
		ABEntry2 temp("江户川柯南", "东京米花町5丁目毛利侦探事务所", {PhoneNumber("55441355335", "0081", "3"),
		                                                              PhoneNumber("58798493135", "0081", "3")});
		ab2.push_back(temp);
	}
	long long end2 = clock();
	cout << (end - start)   << endl;
	cout << (end2 - end)  << endl;
	
	return 0;
}