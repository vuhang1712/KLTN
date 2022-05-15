#include <iostream>
#include "vector"
#include <map>
#include "readData.h"
#include "Model.h"

using namespace std;

int main(int argc, char** argv) {
	int s = 0;
	int v = 0;
	vector<int> k;
	vector<vector<int>> y;
	vector<vector<int>> delta;
	string inputFilePath = "reserver_intance_5_6_1.txt";

	readFile(inputFilePath, &s, &v, &k, &y, &delta);
	Model(s, v, k, y, delta);

	return 0;
}