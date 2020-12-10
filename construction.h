#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "constructHeaderTable.h"
#include "constructTree.h"

#define FILENAME "./data/data.csv"

void TreeConstruction(int n, vector<table> &mainTable, node *root){

    cout << endl << "TREE CONSTRUCTION IN PROGRESS..." << endl;

    fstream fin(FILENAME, ios::in);
	string line;
	int index = 0;
    vector<int> transaction;

    // Iterate through the dataset
    while(getline(fin, line) && index < n){

        transaction.clear();
        index++;
        stringstream ss(line);
        string temp;
        char delim = ',';
        while (std::getline(ss, temp, delim)) {
            if(!temp.size()){
                break;
            }
            transaction.push_back(stoi(temp));
        }

        // Add to the table and rearrange transaction
        addCountTable(mainTable, transaction);

        // Rearrange the tree
        rearrangeTree(mainTable, transaction, root);

        // Insert into the tree
        insertTree(mainTable, transaction, root);

        if(index % 100 == 0)
            cout << index << ", "<< flush;
    }


    cout << n << endl << "TREE CONSTRUCTION COMPLETE..." << endl;
}

void TreeDeletion(node* root){
}
