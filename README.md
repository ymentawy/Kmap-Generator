# Kmap-Generator
A C++ Project that generates the Karnaugh map of a certain minterms
1-	Problem definition:

K-Maps are one of the most efficient ways to simplify Boolean functions. The problem that this project solves is using programming to simplify the functions using K-Maps

2-	Used Algorisms:

The Algorithm that this project uses is the Quine McCluskey Method (QMC). The Algorithm simply starts by listing all the minterms of the function in a table, let it be called table 1. The next step is generating table 2 that contains the prime implicant(s) from the minterms. The last step is to generate the simplified essential prime implicants from table 2 in table 3. At the end of the algorithm, Table 1 contains the minterms, Table 2 contains the prime Implicants, and Table 3 contains the simplified essential prime implicants. 

3-	Class(es) used in the algorithm:

One class is created for the algorithm to contain the K-Maps and make operation on them.

The K-Map header file contains the class members and the used functions which go as follows:

A-	Class Members:

-	A variable “n” to store the number of variables.
-	A variable “size” to store the size of the K-Map.
-	A vector of integers “map” to store the position of the minterms on the map.
-	A vector of integers “minterms” to store the minterms.
-	A vector of integer vectors “v2” that contains the binary representation of the decimal numbers in 2 bits.
-	A vector of integer vectors “v3” that contains the binary representation of the decimal numbers in 3 bits.









B-	Class Functions:

-	A default constructor “Kmap” that initializes the members.
-	A constructor that sets the number of variables to a specific value” Kmap(n).”
-	A function “add_terms (int i)” that adds the minters to the map by taking the decimal value “i” of the minterm.
-	A function “set_n (int x)” that sets the number of variables of the map.
-	A function “print_map (fstream file)” that prints the map.
-	A function “erasemap()” that clears the map.
-	A function “generate_function ()” that generates the simplified Boolean function of the map.

4-	Codes:

A-	Default constructor:

Kmap::Kmap()
{
	n = 0;
	size = 0;
}

B-	Overloaded constructor:

Kmap::Kmap(int s)
{
	n = s;
	size = pow(2, n);
	map.resize(size);
	for (int i = 0; i < size; i++)
		map[i] = 0;
	
}

C-	The function that clears the map:

void Kmap::erasemap()
{
	n = 0;
	size = 0;
	map.clear();
	map.resize(0);
}

D-	The function that generates the simplified Boolean function:

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
			//table contains the simplified terms of table 3
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

E-	The function that adds minterms to the map:

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
			
F-	The function that sets the number of variables of the map:

void Kmap::set_n(int x)
{
	n = x;
	size = pow(2, n);
	map.resize(size);
	minterms.clear();
	for (int i = 0; i < size; i++)
		map[i] = 0;
}

G-	The function that prints the map to the command prompt:

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

H-	The function that prints the map in a text file:

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


5-	Algorithm explanation:

-	The main function in the Algorithm is the “generate_function()” function that generate the simplified Boolean function. 
-	Steps for Quine McCluskey Method:
1.	Arrange the given minterms according to the number of ones present in their binary representation in ascending order.
2.	Take the minterms from the continuous group if there is only a one-bit change to make their pair, in the vector “temps.” 
3.	Place the ‘5‘number where there is a bit change accordingly and keep the remaining bits the same. The vector “temps4” contains the unpaired minterms.

4.	Repeat steps 2 to 3 until we get all prime implicants (when all the bits present in the table are different). They are present in “temps3.”
5.	Make a prime implicant table that consists of the prime implicants (obtained minterms) as rows and the given minterms (given in problem) as columns. They are present in the vector “temps3.”
6.	Make an essential prime implicant table that consists of the prime implicants (obtained minterms) as rows and the given minterms (given in problem) as columns. They are present in the vector “table.”
