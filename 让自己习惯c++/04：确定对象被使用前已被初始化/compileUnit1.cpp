#include <string>
#include <iostream>
#include "FileSystem.h"
using namespace std;
//想在本文件使用tfs
class Directory{
public:
	Directory(const string nm = "root");
	string Name() const {return name;}
	size_t Disks() const {return disks;}
	string FSBelong() const {return fsbelong;}
private:
	size_t disks;
	string name;
	string fsbelong;
};
Directory::Directory(const string nm) : name(nm){
	//使用了compileUnit中的tfs
	//disks = tfs.numDisks();
	disks = tfs().numDisks();
	//fsbelong = tfs.FSName();
	fsbelong = tfs().FSName();
}

int main() {
	Directory s;
	cout << "name: " << s.Name() << endl
		<< "disks: " << s.Disks() << endl
		<< "FSBelong: " << s.FSBelong() << endl;
	return 0;
}