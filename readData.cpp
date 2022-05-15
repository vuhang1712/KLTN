#include "readData.h"

void readFile(string inFile, int* s, int* v, vector<int>* k, vector<vector<int>>* y, vector<vector<int>>* delta) {
	cout << "Reading file " << inFile << endl;

	string filename(inFile);
	ifstream input_file(inFile);

	if (!input_file.is_open()) {
		cerr << "Could not open the file " << filename << endl;
	}

	int d;
	vector<int> value;
	while (!input_file.eof())
	{
		input_file >> d;
		value.push_back(d);
	}

	*s = value[0];
	*v = value[1];
	int index = 2;

	for (int i = 0; i < *s; i++)
	{
		k->push_back(value[index]);
		index++;
	}

	for (int i = 0; i < *v; i++)
	{
		vector<int> temp;
		for (int j = 0; j < *v; j++)
		{
			temp.push_back(value[index]);
			index++;
		}
		y->push_back(temp);
	}

	for (int i = 0; i < *s; i++)
	{
		vector<int> temp;
		for (int j = 0; j < *v; j++)
		{
			temp.push_back(value[index]);
			index++;
		}
		delta->push_back(temp);
	}

	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 6; j++)
	//	{
	//		cout << delta[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	input_file.close();
}