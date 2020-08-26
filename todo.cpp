#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;


struct paircustom
{
	string first;
	std::vector<string> second;


};

int main() {
	std::vector<paircustom> v1;
	v1.emplace_back("create", vector<string>{"32132", "454", "1323"});
	v1.emplace_back("assign", vector<string>{"6456", "34325", "134"});
	v1.emplace_back("reachsrc", vector<string>{"775", "4365", "886"});

	std::cout << v1.size() << "\n";

	return 0;
}