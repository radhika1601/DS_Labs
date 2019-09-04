#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;



class WordTrie
{
	public:

		bool makes_sense;
		string meaning;
		WordTrie *childArr[26];

		WordTrie()
		{
			this->makes_sense=false;
			for (int i = 0; i < 26; ++i)
			{
				this->childArr[i]=NULL;
			}
		}

		WordTrie** address_child(char character)
		{
			if(character < 97 || character > 122)
			{
				return NULL;
			}
			else
			{
				return &(this->childArr[character%97]);
			}
		}

		WordTrie* get_child_with_char(char character)
		{
			if(character < 97 || character > 122)
			{
				return NULL;
			}
			else
			{
				return this->childArr[character%97];
			}
		}
};


class WordDict
{
    private:
        void StrToL(string &str)
        {
            for (int i = 0; i < str.length(); ++i)
            {
                str[i]=(char)tolower((int)str[i]);
            }
        }
	public:
		WordTrie* root;

		WordDict()
		{
			this->root = new WordTrie();
		}

		void insert(string key,string meaning)
		{
			WordTrie* it = this->root;
			for (int i = 0; i < key.length(); ++i)
			{
				char currChar = key.at(i);
				if (it->get_child_with_char(currChar) == NULL)
				{
					*(it->address_child(currChar)) = new WordTrie();
				}

				it = it->get_child_with_char(currChar);
			}
			it->makes_sense = true;
			it->meaning = meaning;
		}

		string retrieveMeaning(string key)
		{
            StrToL(key);
			WordTrie* it = this->root;
			for (int i = 0; it != NULL && i < key.length(); ++i)
			{
				char currChar= key.at(i);
				it = it->get_child_with_char(currChar);
			}

			if (it == NULL || it->makes_sense == false)
			{
				return "Incharacterid Word";
			}
			else
			{
				return it->meaning;
			}
		}

        void insert_from_file(string filename)
		{
			ifstream f;
			f.open(filename);
			if (f.is_open())
			{
				string key;
				while(getline(file,key,','))
				{
                    StrToL(key);
					string character;
					getline(file,character);
					this->insert(key,character);
				}
				f.close();
			}
		}

};

