#include <iostream>
#include <fstream>
#include <vector>
#include <dos.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
vector<char> readfile(int n, ifstream& FILE, int size)
{
	switch (n)
	{
	case 0:
	{
		char arr[100000];
		FILE >> arr;
		vector<char> way;
		for (int i = 0; arr[i] > 64 && arr[i] < 123; i++)
			way.push_back(arr[i]);
		return way;
	}
	case 1:
	{
		char num[3];
		FILE >> num[0];
		FILE >> num[1];
		FILE >> num[2];
		vector<char> nmk;
		nmk.push_back(num[0]);
		nmk.push_back(num[1]);
		nmk.push_back(num[2]);
		return nmk;
	}
	case 2:
	{
		char k;
		vector<char> k_vector;
		while (size != 0)
		{
			FILE >> k;
			k_vector.push_back(k);
			size--;
		}

		return k_vector;
	}
	case 3:
	{
		vector<char> ar;
		char buff;
		FILE >> buff;
		while (buff != '|')
		{
			ar.push_back(buff);
			FILE >> buff;
		}
		//ar.pop_back();
		return ar;
	}
	case 4:
	{
		char num[4];
		FILE >> num[0];
		FILE >> num[1];
		FILE >> num[2];
		FILE >> num[3];
		vector<char> nmk;
		nmk.push_back(num[0]);
		nmk.push_back(num[1]);
		nmk.push_back(num[2]);
		nmk.push_back(num[3]);
		return nmk;
	}
	}
}
/*if (dictionary.size() < n)
		{
			bool t = false;
			for (int u = 0;u < dictionary.size();u++)
			{
				if (dictionary[u] == data[i])
				{
					t = true;
					break;
				}
			}
			if (t == false)
				dictionary.push_back(data[i]);
		}*/
int dka(ifstream& FILE)
{
	vector<char> arr = readfile(0, FILE, 0);
	int size = arr.size();
	int n, m, k;
	char* data = (char*)calloc(size + 1, sizeof(char));
	for (int i = 0; i < size; i++)
	{
		data[i] = arr[i];
	}
	vector<char> nmk = readfile(1, FILE, 0);
	char tmp = nmk[0], tmp2 = nmk[1], tmp3 = nmk[2];
	n = atoi(&tmp);
	m = atoi(&tmp2);
	k = atoi(&tmp3);

	vector<char> z = readfile(2, FILE, k);
	int* _k = new int[k];
	for (int i = 0; i < k; i++)
	{
		char p = z[i];
		_k[i] = atoi(&p);
	}

	vector<char> state = readfile(3, FILE, 0);/*
	vector<int> res(state.size());
	transform(state.begin(), state.end(), res.begin(), [](char s) { return atoi(&s); });*/
	if (state.size() / 3 > m)
		return 1;
	vector<char> dictionary;
	int current_state = 1;
	int a = -1;
	for (int i = 0; data[i]!=0; i++)
	{
		for (int z = 0; z < state.size(); z++)
		{
			if (z > 1)
			{
				char p = state[z - 2];
				a = atoi(&p);
			}

			if (data[i] == state[z] && (current_state) == a)
			{
				bool find = false;
				for (int i = 0; i < dictionary.size(); i++)
				{
					if (dictionary[i] == current_state)
						find = true;
				}
				if (find == false)
					dictionary.push_back(current_state);
				char p = state[z - 1];
				a = atoi(&p);
				current_state = a;
				if (dictionary.size() > n)
				{
					cout << "rejects";
					return 0;
				}
				break;
			}
		}
	}
	for (int i = 0; i < k; i++)
	{
		if (current_state == _k[i])
			cout << "accepts";
	}

	cout << endl;
}
int nka(ifstream& FILE)
{
	vector<char> arr = readfile(0, FILE, 0);
	int size = arr.size();
	int n, m, k;
	char* data = (char*)calloc(size + 1, sizeof(char));
	for (int i = 0; i < size; i++)
	{
		data[i] = arr[i];
	}
	vector<char> nmk = readfile(1, FILE, 0);
	char tmp = nmk[0], tmp2 = nmk[1], tmp3 = nmk[2];
	n = atoi(&tmp);
	m = atoi(&tmp2);
	k = atoi(&tmp3);
	
	vector<char> z = readfile(2, FILE, k);
	int* _k = new int[k];
	for (int i = 0; i < k; i++)
	{
		char p = z[i];
		_k[i] = atoi(&p);
	}

	vector<char> state = readfile(3, FILE, 0);
	if (state.size() / 3 > m)
		return 1;
	vector<char> dictionary;
	vector<int> current_state;
	current_state.push_back(1);
	int a = -1;
	vector<int> buff;
	for (int i = 0; data[i]!=0; i++)
	{
		for (int s = 0, z = 0; s < current_state.size(); s++)
		{
			for (int num_state = 0; z < state.size(); z++)
			{
				if (z > 1 && (z + 1) % 3 == 0)
				{
					char p = state[z - 2];
					a = atoi(&p);
				}

				if (data[i] == state[z] && (current_state[s]) == a)
				{
					bool find = false;
					for (int i = 0; i < dictionary.size(); i++)
					{
						if (dictionary[i] == current_state[s])
							find = true;
					}
					if (find == false)
						dictionary.push_back(current_state[s]);
					if (num_state > 0)
					{
						char p = state[z - 1];
						a = atoi(&p);
						current_state.push_back(a);
					}
					else
					{
						char p = state[z - 1];
						a = atoi(&p);
						buff.push_back(a);
					}

					if (dictionary.size() > n)
					{
						cout << "rejects";
						return 1;
					}
					num_state++;
				}
			}
			if (z == state.size())
			{
				for (int s = 0; s < buff.size(); s++)
				{
					current_state[s] = buff[s];
				}
			}
			buff.clear();
		}
	}
	for (int q = 0; q < current_state.size(); q++)
	{
		for (int i = 0; i < k; i++)
		{
			if (current_state[q] == _k[i])
				cout << "accepts";
		}
	}
	cout << endl;
}
int findWordsNKA(ifstream& FILE)
{
	int n, m, k;
	vector<char> nmk = readfile(1, FILE, 0);
	char tmp = nmk[0], tmp2 = nmk[1], tmp3 = nmk[2];
	n = atoi(&tmp);
	m = atoi(&tmp2);
	k = atoi(&tmp3);
	vector<char> z = readfile(2, FILE, k);
	int* _k = new int[k];
	for (int i = 0; i < k; i++)
	{
		char p = z[i];
		_k[i] = atoi(&p) + 48;
	}

	vector<char> state = readfile(3, FILE, 0);
	vector<vector<char>> myresults;
	int answerNum = 0;
	myresults.resize(1);
	myresults[0].push_back(49);
	bool exit = false;
	while (exit == false)
	{
		for (int i = 0, kk = 0; i < myresults.size(); i++)
		{
			for (int z = 0; z < myresults[i].size(); z++)
			{
				for (int y = 0; y < k; y++)
				{
					if (myresults[i][z] == _k[y])
					{
						kk++;
					}
				}
			}
			if (kk == myresults.size() || answerNum == -1)
				exit = true;
		}
		for (int y = 0; y < myresults.size(); y++)
		{
			if (myresults[y].size() > 3)
				for (int r = 0, size = myresults[y].size() - 3; r < size; r++)
				{
					for (int c = 0; c < myresults[y].size() - 1; c++)
					{
						if (myresults[y].at(c) == myresults[y].at(c + 1))
						{
							//if (myresults[y].at(myresults[y].size() - 2) == myresults[y].at(r) && myresults[y].back() == myresults[y].at(r + 1))
							{
								if (myresults[y].at(r + 1) != myresults[y].at(r))
									answerNum = -1;
								auto iter = myresults.begin() + y;
								myresults.erase(iter);
								size = 0;
								if (y != 0)
								{
									y--;
								}
							}
						}
					}
				}
		}
		for (int y = 0; y < myresults.size(); y++)
		{
			int z = INT_MAX;
			if (myresults.size() != 0)
			{
				z = myresults[y].back();
			}
			bool findend = false;
			for (int q = 0;q < k;q++)
			{
				if (_k[q] == z)
				{
					findend = true;
				}
			}
			if (findend == false)
			{
				for (int i = 0, k = 0; i < state.size(); i += 3)
				{
					if (k > 0)
					{
						if (state[i] == z)
						{
							vector<char> tmp = myresults[y];
							tmp.pop_back();
							tmp.push_back(state[i + 1]);
							myresults.push_back(tmp);
							k++;
						}
					}
					else if (state[i] == z)
					{
						myresults[y].push_back(state[i + 1]);
						k++;
					}
				}
			}
			char next = myresults[y].back();
			bool findexit = false;
			for (int i = 0; i < k; i++)
			{
				if (z == _k[i])
				{
					findexit = true;
				}
			}
			if (next == z&&findexit == false)
			{
				auto iter = myresults.begin() + y;
				myresults.erase(iter);
			}
		}
	}
	vector<int> sizetmp;
	vector<vector<char>> tmp_1;
	for (int i = 0; i < myresults.size(); i++)
	{
		for (int y = 0;y < myresults[i].size();y++)
		{
			for (int t = 0;t < k;t++)
			{
				if (_k[t] == state[i])
				{
					vector<char> tmp = myresults[i];
					tmp_1.push_back(tmp);
					sizetmp.push_back(tmp.size());
				}
			}
		}
	}

	while (sizetmp.size() != 0)
	{
		for (int y = 0; y < tmp_1.size(); y++)
		{
			int z = INT_MAX;
			if (tmp_1.size() != 0)
			{
				z = tmp_1[y].back();
			}
			char pastsiuze = sizetmp[y];
			for (int i = 0, k = 0; i < state.size(); i += 3)
			{
				if (k > 0)
				{
					if (state[i] == z)
					{
						vector<char> tmp = tmp_1[y];
						tmp.pop_back();
						tmp.push_back(state[i + 1]);
						tmp_1.push_back(tmp);
						sizetmp.push_back(tmp_1.size());
						k++;
					}
				}
				else if (state[i] == z)
				{
					tmp_1[y].push_back(state[i + 1]);
					sizetmp[y] += 1;
					k++;
				}
			}
			if (pastsiuze == sizetmp[y])
			{
				auto iter = tmp_1.begin() + y;
				tmp_1.erase(iter);
				auto iter2 = sizetmp.begin() + y;
				sizetmp.erase(iter2);
			}
		}
		for (int y = 0; y < tmp_1.size(); y++)
		{
			if (tmp_1[y].size() > 3)
				for (int r = 0, size = tmp_1[y].size() - 3; r < size; r++)
				{
					if (tmp_1[y].at(tmp_1[y].size() - 2) == tmp_1[y].at(r) && tmp_1[y].back() == tmp_1[y].at(r + 1))
					{
						auto iter = tmp_1.begin() + y;
						tmp_1.erase(iter);
						auto iter2 = sizetmp.begin() + y;
						sizetmp.erase(iter2);
						size = 0;
						if (y != 0)
						{
							y--;
						}
						answerNum = -1;
					}
				}
		}
	}
	if (answerNum != -1)
	{
		answerNum = myresults.size();
	}
	int check = INT_MAX;
	for (int i = 0; i < myresults.size(); i++)
	{
		for (int y = 0; y < myresults[i].size(); y++)
		{
			for (int r = 0; r < k; r++)
			{
				if (myresults[i][y] == _k[r])
				{
					check = 0;
				}
			}
		}
	}
	if (check == INT_MAX)
	{
		answerNum = 0;
	}
	cout << answerNum << endl;
	return 0;
}

void findWordsLengthNKAandDKA(ifstream& FILE)
{
	int n, m, k, l;
	vector<char> nmk = readfile(4, FILE, 0);
	char tmp = nmk[0], tmp2 = nmk[1], tmp3 = nmk[2], tmp4 = nmk[3];
	n = atoi(&tmp);
	m = atoi(&tmp2);
	k = atoi(&tmp3);
	l = atoi(&tmp4);
	vector<char> z = readfile(2, FILE, k);
	int* _k = new int[k];
	for (int i = 0; i < k; i++)
	{
		char p = z[i];
		_k[i] = atoi(&p) + 48;
	}

	vector<char> state = readfile(3, FILE, 0);
	vector<vector<char>> myresults;
	int answerNum = 0;
	myresults.resize(1);
	myresults[0].push_back(49);
	bool exit = false;
	vector<int> sizemyresults;
	sizemyresults.push_back(myresults.size());
	while (exit == false)
	{
		for (int i = 0, kk = 0; i < myresults.size(); i++)
		{
			for (int z = 0; z < myresults[i].size(); z++)
			{
				for (int y = 0; y < k; y++)
				{
					if (myresults[i][z] == _k[y])
					{
						kk++;
					}
				}
			}
			if (kk == myresults.size() || answerNum == -1)
				exit = true;
		}
		for (int y = 0; y < myresults.size(); y++)
		{
			if (myresults[y].size() > 3)
				for (int r = 0, size = myresults[y].size() - 3; r < size; r++)
				{
					if (myresults[y].at(myresults[y].size() - 2) == myresults[y].at(r) && myresults[y].back() == myresults[y].at(r + 1))
					{
						auto iter = myresults.begin() + y;
						myresults.erase(iter);
						size = 0;
						if (y != 0)
						{
							y--;
						}
						answerNum = -1;
					}
				}
		}
		for (int y = 0; y < myresults.size(); y++)
		{
			int z = INT_MAX;
			if (myresults.size() != 0)
			{
				z = myresults[y].back();
			}
			bool findend = false;
			for (int q = 0;q < k;q++)
			{
				if (_k[q] == z)
				{
					findend = true;
				}
			}
			if (findend == false)
			{
				char pastsiuze = sizemyresults[y];
				for (int i = 0, k = 0; i < state.size(); i += 3)
				{
					if (k > 0)
					{
						if (state[i] == z)
						{
							vector<char> tmp = myresults[y];
							tmp.pop_back();
							tmp.push_back(state[i + 1]);
							myresults.push_back(tmp);
							sizemyresults.push_back(myresults.size());
							k++;
						}
					}
					else if (state[i] == z)
					{
						if (myresults[y].size() <= l)
						{
							myresults[y].push_back(state[i + 1]);
							sizemyresults[y] += 1;
							k++;
						}
					}
				}
				if (pastsiuze == sizemyresults[y])
				{
					auto iter = myresults.begin() + y;
					myresults.erase(iter);
					auto iter2 = sizemyresults.begin() + y;
					sizemyresults.erase(iter2);
				}
			}
		}
	}
	vector<int> sizetmp;
	vector<vector<char>> tmp_1;
	for (int i = 0; i < myresults.size(); i++)
	{
		for (int y = 0;y < myresults[i].size();y++)
		{
			for (int t = 0;t < k;t++)
			{
				if (_k[t] == state[i])
				{
					vector<char> tmp = myresults[i];
					tmp_1.push_back(tmp);
					sizetmp.push_back(tmp.size());
				}
			}
		}
	}

	while (sizetmp.size() != 0)
	{
		for (int y = 0; y < tmp_1.size(); y++)
		{
			int z = INT_MAX;
			if (tmp_1.size() != 0)
			{
				z = tmp_1[y].back();
			}
			char pastsiuze = sizetmp[y];
			for (int i = 0, k = 0; i < state.size(); i += 3)
			{
				if (k > 0)
				{
					if (state[i] == z)
					{
						vector<char> tmp = tmp_1[y];
						tmp.pop_back();
						tmp.push_back(state[i + 1]);
						tmp_1.push_back(tmp);
						sizetmp.push_back(tmp_1.size());
						k++;
					}
				}
				else if (state[i] == z)
				{
					tmp_1[y].push_back(state[i + 1]);
					sizetmp[y] += 1;
					k++;
				}
			}
			if (pastsiuze == sizetmp[y])
			{
				auto iter = tmp_1.begin() + y;
				tmp_1.erase(iter);
				auto iter2 = sizetmp.begin() + y;
				sizetmp.erase(iter2);
			}
		}
		for (int y = 0; y < tmp_1.size(); y++)
		{
			if (tmp_1[y].size() > 3)
				for (int r = 0, size = tmp_1[y].size() - 3; r < size; r++)
				{
					if (tmp_1[y].at(tmp_1[y].size() - 2) == tmp_1[y].at(r) && tmp_1[y].back() == tmp_1[y].at(r + 1))
					{
						auto iter = tmp_1.begin() + y;
						tmp_1.erase(iter);
						auto iter2 = sizetmp.begin() + y;
						sizetmp.erase(iter2);
						size = 0;
						if (y != 0)
						{
							y--;
						}
						answerNum = -1;
					}
				}
		}
	}
	if (answerNum != -1)
	{
		answerNum = myresults.size();
	}
	cout << answerNum << endl;
}

bool match(vector<int>  statesecond, vector<int>  statefirst, int min, int* P, int* D)
{
	for (int i = 0; i < min; i++)
		if (statesecond[i] != statefirst[i])
			return false;
	return true;
}
void isomorphism(ifstream& FILE)
{
	int n, m, k;
	vector<char> nmk = readfile(1, FILE, 0);
	char tmp = nmk[0], tmp2 = nmk[1], tmp3 = nmk[2];
	n = atoi(&tmp);
	m = atoi(&tmp2);
	k = atoi(&tmp3);
	vector<char> z = readfile(2, FILE, k);
	int* _k = new int[k];
	for (int i = 0; i < k; i++)
	{
		char p = z[i];
		_k[i] = atoi(&p) + 48;
	}

	vector<char> state = readfile(3, FILE, 0);
	vector<vector<char>> statesecond;
	vector<vector<char>> statefirst;
	vector<char> tmp_state;
	char memory[4];
	for (int i = 0, findseconddata = 0, notcalc = 0;i < state.size();i++)
	{
		if (state.size() > i + 3) {
			memory[0] = state[i];
			memory[1] = state[i + 1];
			memory[2] = state[i + 2];
			memory[3] = state[i + 3];
		}

		for (int i = 0;i < 4;i++)
		{
			if (memory[i] >= 48 && memory[i] <= 57)
			{
				findseconddata++;
			}
		}

		if (findseconddata == 4)
		{
			notcalc++;
			memory[0] = 0;
			memory[1] = 0;
			memory[2] = 0;
			memory[3] = 0;
			i += 4;
		}
		if (state[i] >= 48 && state[i] <= 57)
		{
			tmp_state.push_back(state[i]);
			if (tmp_state.size() - 2 == 0)
			{
				if (notcalc > 0)
					statesecond.push_back(tmp_state);
				else if (notcalc == 0)
					statefirst.push_back(tmp_state);
				tmp_state.clear();
			}
		}

		findseconddata = 0;
	}
	int sizemin = 0;
	if (statefirst.size() > statesecond.size())
		sizemin = statesecond.size();
	else
		sizemin = statefirst.size();
	int* data = new int[sizemin * 2 + 1];
	for (int i = 0;i < sizemin * 2;i++)
	{
		data[i] = i;
	}
	data[sizemin] = '\0';
	int* D = new int[sizemin * 2];
	for (int i = 0; i < sizemin * 2; i++)
	{
		D[i] = i % 2;
	}

	int num = 0;
	vector<int> data1;
	for (int i = 0; i < statefirst.size(); i++)
	{
		for (int z = 0; z < statefirst[i].size(); z++)
		{
			data1.push_back(statefirst[i][z]);
		}
	}
	vector<int> data2;
	for (int i = 0; i < statesecond.size(); i++)
	{
		for (int z = 0; z < statesecond[i].size(); z++)
		{
			data2.push_back(statesecond[i][z]);
		}
	}
	do
	{
		if (match(data1, data2, sizemin * 2, data, D))
		{
			cout << "true" << " ";
		}
	} while (next_permutation(data1.begin(), data1.end()));
	delete[] data;
}
void equal(ifstream& FILE)
{
	vector<char> state = readfile(3, FILE, 0);
	vector<vector<char>> statesecond;
	vector<vector<char>> statefirst;
	vector<char> endfirst;
	vector<char> endsecond;
	for (int i = 0, findseconddata = 0, notcalc = 0;true; )
	{
		vector<char> tmp(3);
		if (state.size() > i + 2) {
			tmp[0] = state[i];
			tmp[1] = state[i + 1];
			tmp[2] = state[i + 2];
		}
		i += 3;

		for (int i = 0;i < 3;i++)
		{
			if (tmp[i] >= 48 && tmp[i] <= 57)
			{
				findseconddata++;
			}
		}
		if (findseconddata == 3)
		{
			notcalc++;

			for (int r = i;r < i + (tmp[2] - 48);r++)
			{
				if (notcalc == 1)
					endfirst.push_back(state[r]);
				else
					endsecond.push_back(state[r]);
			}
			i += (tmp[2] - 48);
		}
		tmp[0] = state[i];
		tmp[1] = state[i + 1];
		tmp[2] = state[i + 2];
		if (notcalc > 1)
			statesecond.push_back(tmp);
		else if (notcalc == 1)
			statefirst.push_back(tmp);

		if (i + 3 >= state.size())
		{
			break;
		}
		findseconddata = 0;
	}
	statefirst.pop_back();
	vector<char> allstepfirst;
	for (int y = 0;y < statefirst.size();y++)
	{
		if (allstepfirst.empty())
			allstepfirst.push_back(statefirst.at(y).at(2));
		else
			for (int t = 0;t < allstepfirst.size();t++)
				if (allstepfirst.at(t) == statefirst.at(y).at(2))
					break;
				else
					allstepfirst.push_back(statefirst.at(y).at(2));
	}
	
	char** datafirst = new char*[allstepfirst.size()+1];
	for (int e = 0;e < allstepfirst.size()+1;e++)
		datafirst[e] = new char[statefirst.size()+1];
	for (int e = 1;e < allstepfirst.size() + 1;e++)
		datafirst[0][e] = allstepfirst[e - 1];
	vector<char> allstepsecond;
	for (int y = 0;y < statesecond.size();y++)
	{
		if (allstepsecond.empty())
			allstepsecond.push_back(statesecond.at(y).at(2));
		else
			for (int t = 0;t < allstepsecond.size();t++)
				if (allstepsecond.at(t) == statesecond.at(y).at(2))
					break;
				else
					allstepsecond.push_back(statesecond.at(y).at(2));
	}
	char** datasecond = new char*[allstepsecond.size()+1];
	for (int e = 0;e < allstepsecond.size()+1;e++)
		datasecond[e] = new char[statefirst.size() + 1];
	for (int e = 1;e < allstepsecond.size() + 1;e++)
		datasecond[0][e] = allstepsecond[e - 1];
}
void main()
{
	ifstream FILE1("text.txt");
	nka(FILE1);
	dka(FILE1);
	findWordsNKA(FILE1);
	findWordsLengthNKAandDKA(FILE1);
	findWordsLengthNKAandDKA(FILE1);
	isomorphism(FILE1);
	equal(FILE1);
	//findWordsLengthNKA();
}