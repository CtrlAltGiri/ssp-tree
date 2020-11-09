#include <iostream>
#include "dataInput.h"
#include "mining.h"

using namespace std;

int main(){

    // Read data
    vector<vector<int>> data;
    read_record(data);

    unsigned int n=1000, freqThreshold=10, rareThreshold=5;

    // INPUT TAKEN.
    /*cout << "Enter the number of rows: ";
    cin >> n;

    cout << "Enter the frequent item threshold: ";
    cin >> freqThreshold;

    cout << "Enter the rare item threshold: ";
    cin >> rareThreshold;
    */

    // Initializing
    vector<table> mainTable;
    node root = {-1, 0, {}, NULL};

    // Iterate through the dataset.
    for(int i = 0; i < n; i++){

        if(i == 7){
            cout << "Break here";
        }

        //cout << i << ' ' << flush;

        // Add to the table and rearrange data[i]
        addCountTable(mainTable, data[i]);

        // Rearrange the tree
        rearrangeTree(mainTable, data[i], &root);

        // Insert into the tree
        insertTree(mainTable, data[i], &root);

        if(i % 100 == 0)
            cout << i << endl << flush;
    }

    mineSSPTree(mainTable, root, freqThreshold, rareThreshold);
}
