// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

vector<string> split_string(string);

typedef struct Node {
	Node *children[26];
	int	characterCount;
	bool isEndOfWord;
} Node;

Node *create(int size)
{
	Node *root = new Node;

	for (int i = 0; i < 26; i++)
	{
		root->children[i] = NULL;
	}
	root->characterCount = size;
	root->isEndOfWord = false;

	return root;
}

void insert(Node* root, string key)
{
	Node* node = root;
	for (int i = 0; i < key.size(); i++)
	{
		int index = key[i] - 'a';
		if (node->children[index] == NULL)
		{
			node->children[index] = create(1);
		}
		else
		{
			node->children[index]->characterCount++;
		}
		node = node->children[index];
	}
	node->isEndOfWord = true;
}

int search(Node* root, string key)
{
	Node* node = root;
	for (int i = 0; i < key.size(); i++)
	{
		int index = key[i] - 'a';
		if (node->children[index] == NULL)
			return 0;

		node = node->children[index];
	}

	return node->characterCount;
}


int main()
{
	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	Node *root = create(0);
	vector<int> counter;
	for (int n_itr = 0; n_itr < n; n_itr++) {
		string opContact_temp;
		getline(cin, opContact_temp);

		vector<string> opContact = split_string(opContact_temp);

		string op = opContact[0];

		string contact = opContact[1];
		if (op == "add")
		{
			insert(root, contact);
		}
		else if (op == "find")
		{
			counter.push_back(search(root, contact));
		}
	}
	
	for (int i = 0; i < counter.size(); i++)
	{
		cout << counter[i] << endl;;
	}
	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}


