#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string badchars = "!@#$%^&*()<>,.?/:;\"[]{}\\|_=+`~";
const string badchars_standalone = "-'";

void error(string s) {
	throw runtime_error(s);
}

bool isbadchar(char c) {
	for (const char& badc : badchars) {
		if (c == badc) {return true;}
	}
	return false;
}

bool isbadstr(string s) {
	for (const char& badc : badchars_standalone) {
		if (s == string(1, badc)) {return true;}
	}
	return false;
}

void remove_badchars(string& s) {
	for (char& c : s) {
		if (isbadchar(c)) {
			c = ' ';
		}
	}
}

void tolower(string& s) {
	for (char& c : s) {
		c = tolower(c);
	}
}

// Populate vector words with every word from input file source
// Ignore bad characters and words
void populate(vector<string>& words, ifstream& source) {
	for (string line; getline(source, line);) {
		remove_badchars(line);
		istringstream iss {line};
		for (string word; iss >> word;) {
			tolower(word);
			if (!isbadstr(word)) {
				words.push_back(word);
			}
		}
	}
}

// Write out words vector
// Sort and remove duplicates when writing to create dictionary
void write_dict(vector<string>& words, ofstream& dict) {
	sort(words.begin(), words.end());
	for (int i; i < words.size(); ++i) {
		if (i == 0 || words[i] != words[i-1]) {
			dict << words[i] << endl;
		}
	}
}

int main() 
try {

	// File handling
	cout << "Enter a file name.\n";
	string fname;
	cin >> fname;
	ifstream source {fname};
	if (!source) {error("Bad filename.");}
	ofstream dict {"dictionary.txt"};

	// Input
	vector<string> words;
	populate(words, source);
	write_dict(words, dict);

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}