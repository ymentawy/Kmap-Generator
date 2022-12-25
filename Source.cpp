#include<iostream>
#include <fstream>
#include<string>
#include<vector>
#include<sstream>
#include "Kmap.h"
using namespace std;
int main() {
	fstream myfile;
	string line;
	vector<string> input;
	string out;
	int n = 1;
	ofstream ofile;
	myfile.open("input.txt", ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			input.push_back(line);
		}
		myfile.close();
	}
	else
		cout << "Fail\n";
	vector<Kmap> maps;
	Kmap map;
	int N = stoi(input[0]);
	int x = 0, mint = 0, minp = 0;
	stringstream str;
	for (int i = 1; i <= N; i++) {
		str << input[i].at(0);
		str >> x;
		str.clear();
		str << input[i].at(1);
		str >> mint;
		str.clear();
		map.set_n(x);
		for (int j = 0; j < mint; j++) {
			str << input[i].at(j + 2);
			str >> minp;
			str.clear();
			map.add_terms(minp);
			str.clear();
		}
		maps.push_back(map);
		map.erasemap();
	}
	ofile.open("output.txt", ios::out);
	if (ofile.is_open()) {
		for (int i = 0; i < maps.size(); i++) {
			ofile << n << "\n";
			n++;
			maps[i].print_map(ofile);
			out = maps[i].generate_function();
			ofile << out << "\n";
		}
		ofile.close();
	}
	/*
	Kmap m(3);
	m.add_terms(0);
	m.add_terms(2);
	m.add_terms(5);
	string out = m.generate_function();
	cout << out << "\n";
	*/
	return 0;
}
