#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<sstream>

#define FILENAME "./data/data.csv"

using namespace std;

struct node{
    int item_no;
    int count;
    vector<node*> link;
};

struct table{
    int item_no;
    int count;
    node* link;
};

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



int main(){
    vector<table> mainTable;

    // Read data
    vector<vector<int>> data;
    read_record(data);

    // Start Processing

}
