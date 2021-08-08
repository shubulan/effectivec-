#ifndef __FileSystem__H__
#define  __FileSystem__H__
#include <string>
using namespace std;
/*class FileSystem{
public:
	FileSystem(const string nm = "Windows", size_t nd = 5) : name(nm), numDisk(nd){}
	size_t numDisks() const { return numDisk;}
	string FSName() const { return name; }
private:
	string name;
	size_t numDisk;
	
};
extern FileSystem tfs;*/
class FileSystem{
public:
	FileSystem(const string nm = "Windows", size_t nd = 5) : name(nm), numDisk(nd){}
	size_t numDisks() const { return numDisk;}
	string FSName() const { return name; }
private:
	string name;
	size_t numDisk;
};
inline FileSystem& tfs() {
	static FileSystem tfs;
	return tfs;
}

#endif