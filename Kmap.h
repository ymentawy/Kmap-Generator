#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<fstream>
using namespace std;
class Kmap
{
public:
	int n, size;
	vector<int> map;
	vector<int> minterms;
	vector<vector<int>> v2{ {0,0},{0,1},{1,0},{1,1} };
	vector<vector<int>> v3{ {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
	Kmap();
	Kmap(int s);
	void add_terms(int i);
	void set_n(int x);
	void print_maps();
	void print_map(ofstream& file);
	void erasemap();
	string generate_function();
};

