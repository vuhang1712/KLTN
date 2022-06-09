#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vector"
#include <map>
#include "readData.h"
#include "Model.h"
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
	int s;
	int v;
	vector<int> k;
	vector<vector<int>> a;
	vector<vector<int>> delta;
	srand(time(NULL));

	//string inputFilePath = "reserver_intance_2_4_1.txt";
	//string inputFilePath = "reserver_intance_4_6_1.txt";
	//string inputFilePath = "reserver_intance_4_36_1.txt";
	//readFile(inputFilePath, &s, &v, &k, &a, &delta);

	cout << "Nhap so loai: ";
	cin >> s;

	cout << "Nhap so dinh: ";
	cin >> v;

	//Ma tran k
	k.resize(s);

	for (int i = 0; i < s; i++)
	{
		k[i] = rand() % v + 1;
		k[i] = min(2, k[i]);
	}

	cout << "Ma tran k" << endl;
	for (int i = 0; i < s; i++)
	{
		cout << k[i] << " ";
	}

	//Ma tran a
	a.resize(v);
	for (int i = 0; i < v; ++i)
		a[i].resize(v);

	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			a[i][j] = 0;
		}
	}

	for (int i = 0; i < v; i++)
	{
		if ((i < (v - 1)) && ((i + 1) % ((int)sqrt(v)) != 0))
		{
			a[i][i + 1] = 1;
		}

		if ((i > 0) && (i % ((int)sqrt(v)) != 0))
		{
			a[i][i - 1] = 1;
		}

		if (i > sqrt(v) - 1)
		{
			a[i][i - sqrt(v)] = 1;
		}

		if (i < v - sqrt(v))
		{
			a[i][i + sqrt(v)] = 1;
		}
	}

	cout << "\nMa tran a" << endl;
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	//Ma tran delta
	delta.resize(s);
	for (int i = 0; i < s; ++i)
		delta[i].resize(v);

	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < v; j++)
		{
			delta[i][j] = rand() % 2;
		}
	}

	cout << "Ma tran delta" << endl;
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < v; j++)
		{
			cout << delta[i][j] << " ";
		}
		cout << endl;
	}

	Model(s, v, k, a, delta);

	return 0;
}