#include "Kmap.h"

Kmap::Kmap()
{
	n = 0;
	size = 0;
}

Kmap::Kmap(int s)
{
	n = s;
	size = pow(2, n);
	map.resize(size);
	for (int i = 0; i < size; i++)
		map[i] = 0;
	
}

void Kmap::erasemap()
{
	n = 0;
	size = 0;
	map.clear();
	map.resize(0);
}

string Kmap::generate_function()
{
	string out;
	vector<int> mins;
	mins = this->minterms;
	int count = 0;
	vector<vector<vector<int>>> t1;
	if (this->n == 2) {
		if (mins.size() == 4) {
			out += "F = 1";
		}
		else if (mins.size() == 0) {
			out += "F = 0";
		}
		else {
			vector<vector<int>> temps;
			t1.resize(3);
			for (int i = 0; i < mins.size(); i++) {
				switch (mins[i]) {
				case 0:t1[0].push_back(v2[0]);
					break;
				case 1:t1[1].push_back(v2[1]);
					break;
				case 2:t1[1].push_back(v2[2]);
					break;
				case 3:t1[2].push_back(v2[3]);
					break;
				}
			}
			for (int i = 0; i < t1.size() - 1; i++)
				if (t1[i].size() != 0)
					for (int j = 0; j < t1[i].size(); j++)
						if (t1[i + 1].size() != 0)
							for (int k = 0; k < t1[i + 1].size(); k++)
								if (t1[i][j].size() != 0)
									for (int p = 0; p < t1[i][j].size(); p++) {
										if (t1[i][j][p] != t1[i + 1][k][p])
											count++;
										if (count == 1)
											temps.push_back({ i,j,k,p });
										count = 0;
									}
			if (temps.size() == 0) {
				for (int i = 0; i < mins.size(); i++) {
					if (i == 0) {
						out += "F = ";
					}
					else {
						out += " + ";
					}
					switch (mins[i]) {
					case 0: {
						out += "A'B'";				
					}
						break;
					case 1: {
						out += "A'B";
					}
						break;
					case 2:	{
						out += "AB'";
					}
						break;
					case 3: {
						out += "AB";
					}
						break;
					}
				}
			}
			else {
				for (int i = 0; i < temps.size(); i++) {
					if (i == 0) {
						out += "F = ";
					}
					else {
						out += "+";
					}
					if (temps[i][3] == 0) {
						if (t1[temps[i][0]][temps[i][1]][1] == 0) {
							out += "B'";
						}
						else {
							out += "B";
						}
					}
					else if (temps[i][3] == 1) {
						if (t1[temps[i][0]][temps[i][1]][0] == 0) {
							out += "A'";
						}
						else {
							out += "A";
						}
					}
				}
			}
		}
	}
	else if (this->n == 3) {
		if (mins.size() == 8) {
			out += "F = 1";
		}
		else if (mins.size() == 0) {
			out += "F = 0";
		}
		else {
			vector<vector<int>> temps;
			vector<vector<int >> temps5;
			t1.resize(4);
			for (int i = 0; i < mins.size(); i++) {
				switch (mins[i]) {
				case 0:t1[0].push_back(v3[0]);
					break;
				case 1:t1[1].push_back(v3[1]);
					break;
				case 2:t1[1].push_back(v3[2]);
					break;
				case 3:t1[2].push_back(v3[3]);
					break;
				case 4:t1[1].push_back(v3[4]);
					break;
				case 5:t1[2].push_back(v3[5]);
					break;
				case 6:t1[2].push_back(v3[6]);
					break;
				case 7:t1[3].push_back(v3[7]);
					break;
				}
			}
			for (int i = 0; i < t1.size() - 1; i++)
				if (t1[i].size() != 0)
					for (int j = 0; j < t1[i].size(); j++)
						if (t1[i + 1].size() != 0)
							for (int k = 0; k < t1[i + 1].size(); k++) {
								if (t1[i][j].size() != 0)
									for (int p = 0; p < t1[i][j].size(); p++) {
										if (t1[i][j][p] != t1[i + 1][k][p])
											count++;
									}
								if (count == 1) {
									temps.push_back(t1[i][j]);
									temps.push_back(t1[i + 1][k]);
									count = 0;
								}
								else {
									temps5.push_back(t1[i][j]);
									temps5.push_back(t1[i + 1][k]);
								}
							}
			int h = temps.size();
			vector<vector<int>> temps4;
			for (int i = 0; i < temps5.size(); i++) {
				for (int j = 0; j < temps.size(); j++) {
					if (temps5[i][0] == temps[j][0] && temps5[i][1] == temps[j][1] && temps5[i][2] == temps[j][2]) {
						h--;
					}
				}
				if (h == temps.size()) {
					temps4.push_back(temps5[i]);
				}
				h = temps.size();
			}
			vector<vector<int>> temps1;
			for (int i = 0; i < temps.size(); i += 2) {
				if (temps[i][0] != temps[i + 1][0]) {
					temps[i][0] = 5;
					temps1.push_back(temps[i]);
				}
				else if (temps[i][1] != temps[i + 1][1]) {
					temps[i][1] = 5;
					temps1.push_back(temps[i]);
				}
				else if (temps[i][2] != temps[i + 1][2]) {
					temps[i][2] = 5;
					temps1.push_back(temps[i]);
				}
			}
			count = 0;
			int u = 5;
			vector<vector<int>> temps2;
			set<int> position;
			vector<int> p;
			vector<vector<int>> table2;
			table2 = temps1;
			for (int i = 0; i < temps1.size(); i++)
				for (int j = i + 1; j < temps1.size(); j++) {
					for (int k = 0; k < 3; k++) {
						if (temps1[i][k] != temps1[j][k]) {
							count++;
							u = k;
						}
					}
					if (count == 1) {
						table2[i][u] = 5;
						temps2.push_back(table2[i]);
						position.insert(i);
						position.insert(j);
					}
					count = 0;
					u = 5;
				}
			vector<vector<int>> table;
			for (int i = 0; i < temps2.size(); i++)
				for (int j = i + 1; j < temps2.size(); j++) {
					for (int k = 0; k < 3; k++) {
						if (temps2[i][k] == temps2[j][k]) {
							count++;
						}
					}
					if (count == 3 && temps2[i][0] != 8) {
						table.push_back(temps2[i]);
						temps2[j][0] = 8;
					}
					count = 0;
				}
			for (int const& position : position)
			{
				p.push_back(position);
			}
			for (int i = 0; i < p.size(); i++) {
				table2[p[i]][0] = 8;
			}
			vector<vector<int>> temps3;
			for (int i = 0; i < table2.size(); i++) {
				if (table2[i][0] != 8)
					temps3.push_back(table2[i]);
			}
			//temps3 contains the terms that were not used in the simplification to table3
			bool flag = false;
			for (int i = 0; i < table.size(); i++) {
				flag = true;
				if (i == 0) {
					out += "F = ";
				}
				for (int j = 0; j < table[i].size(); j++) {
					if (table[i][j] == 0 && j == 0) {
						out += "A'";
					}
					else if (table[i][j] == 1 && j == 0) {
						out += "A";
					}
					else if (table[i][j] == 0 && j == 1) {
						out += "B'";
					}
					else if (table[i][j] == 1 && j == 1) {
						out += "B";
					}
					else if (table[i][j] == 0 && j == 2) {
						out += "C'";
					}
					else if (table[i][j] == 1 && j == 2) {
						out += "C";
					}
				}
				if (i != table.size() - 1 || temps3.size() != 0) {
					out += " + ";
				}
			}
			for (int i = 0; i < temps3.size(); i++) {
				if (!flag && i == 0) {
					out += "F = ";
				}
				for (int j = 0; j < temps3[i].size(); j++) {
					if (temps3[i][j] == 0 && j == 0) {
						out += "A'";
					}
					else if (temps3[i][j] == 1 && j == 0) {
						out += "A";
					}
					else if (temps3[i][j] == 0 && j == 1) {
						out += "B'";
					}
					else if (temps3[i][j] == 1 && j == 1) {
						out += "B";
					}
					else if (temps3[i][j] == 0 && j == 2) {
						out += "C'";
					}
					else if (temps3[i][j] == 1 && j == 2) {
						out += "C";
					}
				}
				if (i != temps3.size() - 1 || temps4.size() != 0) {
					out += " + ";
				}
			}
			for (int i = 0; i < temps4.size(); i++) {
				if (table.size() == 0 && temps3.size() == 0 && i == 0) {
					out += "F = ";
				}
				for (int j = 0; j < temps4[i].size(); j++) {
					if (temps4[i][j] == 0 && j == 0) {
						out += "A'";
					}
					else if (temps4[i][j] == 1 && j == 0) {
						out += "A";
					}
					else if (temps4[i][j] == 0 && j == 1) {
						out += "B'";
					}
					else if (temps4[i][j] == 1 && j == 1) {
						out += "B";
					}
					else if (temps4[i][j] == 0 && j == 2) {
						out += "C'";
					}
					else if (temps4[i][j] == 1 && j == 2) {
						out += "C";
					}
				}
				if (i != temps4.size() - 1) {
					out += " + ";
				}
			}
		}
	}
	return out;
}

void Kmap::add_terms(int i) {
	if (n == 2) {
		if (map[i] == 0 && i >= 0) {
			map[i] = 1;
			minterms.push_back(i);
		}
	}
	else if (n == 3) {
		if (i >= 0) {
			switch (i) {
			case 0: {
				if (map[0] == 0) {
					map[0] = 1;
					minterms.push_back(0);
				}
			}
				  break;
			case 1: 
			{
				if (map[1] == 0) {
					map[1] = 1;
					minterms.push_back(1);
				}
			}
				  break;
			case 2: 
			{
				if (map[3] == 0) {
					map[3] = 1;
					minterms.push_back(2);
				}
			}
				  break;
			case 3: 
			{
				if (map[2] == 0) {
					map[2] = 1;
					minterms.push_back(3);
				}
			}
				  break;
			case 4: 
			{
				if (map[4] == 0) {
					map[4] = 1;
					minterms.push_back(4);
				}
			}
				  break;
			case 5: 
			{
				if (map[5] == 0) {
					map[5] = 1;
					minterms.push_back(5);
				}
			}
				  break;
			case 6: 
			{
				if (map[7] == 0) {
					map[7] = 1;
					minterms.push_back(6);
				}
			}
				  break;
			case 7: 
			{
				if (map[6] == 0) {
					map[6] = 1;
					minterms.push_back(7);
				}
			}
				  break;
			}
		}
	}
}
			

void Kmap::set_n(int x)
{
	n = x;
	size = pow(2, n);
	map.resize(size);
	minterms.clear();
	for (int i = 0; i < size; i++)
		map[i] = 0;
}

void Kmap::print_maps() {
	cout << "K-map = \n";
	if (n == 2) {
		for (int i = 0; i < size; i++) {
			if (i == 2)
				cout << "\n";
			cout << map[i] << " ";
		}
		cout << "\n";
	}
	else if (n == 3) {
		for (int i = 0; i < size; i++) {
			if (i == 4)
				cout << "\n";
			cout << map[i] << " ";
		}
		cout << "\n";
	}
}

void Kmap::print_map(ofstream& file)
{
	file << "K-map = \n";
	if (n == 2) {
		for (int i = 0; i < size; i++) {
			if (i == 2)
				file << "\n";
			file << map[i] << " ";
		}
		file << "\n";
	}
	else if (n == 3) {
		for (int i = 0; i < size; i++) {
			if (i == 4)
				file << "\n";
			file << map[i] << " ";
		}
		file << "\n";
	}
}
