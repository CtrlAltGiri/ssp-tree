#include <iostream>
#include "dataInput.h"
#include "processing.h"

using namespace std;

int main(){

    // Read data
    vector<vector<int>> data;
    read_record(data);

    int n;
    cout << "Enter the number of rows: ";
    cin >> n;

    // Initializing
    vector<table> mainTable;
    node root = {-1, 0, {}, NULL};

    // Iterate through the dataset.
    for(int i = 0; i < n; i++){

        //if(i == 380){
        //    cout << "Break here";
        //}

        // Add to the table and rearrange data[i]
        addCountTable(mainTable, data[i]);
        // Rearrange the tree
        rearrangeTree(mainTable, data[i], &root);
        // Insert into the tree
        insertTree(mainTable, data[i], &root);
        if(i % 100 == 0)
            cout << i << endl << flush;
    }

    /*for(int k = 0; k < mainTable.size(); k++){
        cout << mainTable[k].item_no << ' ' << mainTable[k].count << endl;
    }*/
}
