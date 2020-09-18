#include <fstream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

#define FILENAME "./data/data.csv"

using namespace std;

void read_record(vector<vector<int>> &res)
{
	fstream fin(FILENAME, ios::in);
	string line;

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
