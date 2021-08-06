#include <iostream>
using namespace std;
class Point1{
	int x, y;
};
struct Point2{
	int x, y;
};

int main() {
    Point1 p1;
	Point2 p2;
	cout << *((int *)(&p1))  << " "
	     << *((int *)((&p1) + 4)) << endl;
	cout << p2.x << " "
	     << p2.y << endl;
	return 0;
}