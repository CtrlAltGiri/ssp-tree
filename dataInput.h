#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

void read_all_records(vector<vector<int>> &res)
{
	string FILENAME = "./data/data.csv";
	fstream fin(FILENAME, ios::in);
	string line;
	int index = 0;

    while(getline(fin, line))
    {
        stringstream ss(line);
        string temp;
        vector<int> words;
        char delim = ',';
        while (std::getline(ss, temp, delim)) {
            if(!temp.size()){
                break;
            }
            words.push_back(stoi(temp));
        }
        res.push_back(words);
	}
}
