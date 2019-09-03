#include <bits/stdc++.h>

#define ALPHABET_SIZE 26
using namespace std;


struct trie_node {

	struct trie_node* child[ALPHABET_SIZE];
	bool isEnd;
	string meaning;
};

/**
This function initializes the new trie node with null values of the children
*/
struct trie_node* newTrieNode();

/**
This function inserts a string 
*/
void insert(string s);

/**

*/
void check(string s);

struct trie_node* newTrieNode() {

	struct  trie_node* node = new trie_node();
	node->isEnd = false;
	for (int i = 0; i < ALPHABET_SIZE; ++i)
	{
		node->child[i] = NULL;
	}
	node->meaning = "";
	return node;
}

void insert(string s, string key,struct trie_node* root) {

	int l = s.length();
	struct trie_node* current = root;
	for(int i = 0; i < l; ++i) {
		int i_node = s[i] - (int)'a';

		if(current->child[i_node] == NULL)
			current->child[i_node] = newTrieNode();

		current = current->child[i_node];
	}

	current->isEnd = true;
	current->meaning = key;
}

string getMeaning(string s, struct trie_node* root) {

	int l = s.length();
	struct trie_node* current = root;
	for(int i = 0; i < l; ++i) {
		int i_node = s[i] - (int)'a';
		if(current->child[i_node] == NULL)
			return "Not Found";

		current = current->child[i_node];
	}

	if(current->isEnd)
		return current->meaning;


	return "Not Found";
}

void read_file(string filename, struct trie_node* root){

	ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		string key;
		while(getline(file,key,','))
		{
            transform(key.begin(), key.end(), key.begin(), ::tolower);;
			string val;
			getline(file,val);
			insert(key,val, root);
		}
		file.close();
	}
}

int main(int argc, char const *argv[]) {

	struct trie_node* root = newTrieNode();

	read_file(argv[1], root);

	string s;
	cin >> s;

	cout << getMeaning(s, root) << endl;


}