#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string badchars = "!@#$%^&*()<>,.?/:;\"[]{}\\|_=+`~";

bool isbadchar(char c) {
	for (const char& badc : badchars) {
		if (c == badc) {return true;}
	}
	return false;
}
void error(string s) {
	throw runtime_error(s);
}

// Replace any bad chars in s with whitespace
void remove_badchars(string& s) {
	for (char& c : s) {
		if (isbadchar(c)) {
			c = ' ';
		}
	}
}

int main() 
try {

	cout << "Enter a file name.\n";
	string fname;
	cin >> fname;
	ifstream source {fname};
	if (!source) {error("Bad filename.");}
	ofstream dict {"dictionary.txt"};

	vector<string> words;
	for (string line; getline(source, line);) {
		remove_badchars(line);
		istringstream iss {line};
		for (string word; iss >> word;) {
			words.push_back(word);
		}
	}

	sort(words.begin(), words.end());
	for (int i; i < words.size(); ++i) {
		if (i == 0 || words[i] != words[i-1]) {
			dict << words[i] << endl;
		}
	}

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}