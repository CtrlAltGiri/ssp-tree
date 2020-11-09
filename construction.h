#include <iostream>
#include "processing.h"

void TreeConstruction(int n, vector<table> &mainTable, vector<vector<int>> &data, node *root){

    // Iterate through the dataset.
    for(int i = 0; i < n; i++){

        if(i == 7){
            cout << "Break here";
        }

        //cout << i << ' ' << flush;

        // Add to the table and rearrange data[i]
        addCountTable(mainTable, data[i]);

        // Rearrange the tree
        rearrangeTree(mainTable, data[i], root);

        // Insert into the tree
        insertTree(mainTable, data[i], root);

        if(i % 100 == 0)
            cout << i << endl << flush;
    }
}

void TreeDeletion(node* root){
}
