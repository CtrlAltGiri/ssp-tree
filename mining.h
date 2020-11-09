#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "includes/utils.h"
#include "construction.h"

void mineSSPTree(vector<table> &headerTable, node *root, unsigned int freqThreshold, unsigned int rareThreshold, unsigned int rows){

    int freqRows = (rows * freqThreshold) / 100;
    int rareRows = (rows * rareThreshold) / 100;
    map<vector<int>, int> freqSet;

    // MINING THE SSP TREE.
    if(root){

        vector<table> secondaryTable;
        node secondaryRoot = {-1, 0, {}, NULL};

        // Iterating through header table
        for(auto i : headerTable){

            // Construction of conditional SSP.
            if(i.count > freqRows){

                // All paths, each vector has one path.
                vector<pair<vector<node*>, int>> allValues;
                vector<node*> tempValues;

                // Step 1: Get all the things in a vector
                node* currentNode = i.nodeLink;
                do{
                    node* tempNode = currentNode;
                    while(tempNode -> parent != root){
                        tempValues.push_back(tempNode -> parent);
                        tempNode = tempNode -> parent;
                    }

                    allValues.push_back(make_pair(tempValues, currentNode -> count));
                    currentNode = currentNode -> nodeLink;

                }while(currentNode);

                // Find all combinations
                map<vector<int>, int> combinations;
                for(int i = 0; i < allValues.size(); i++){
                    for(int j = 0; j < allValues[i].first.size(); j++){
                        vector<bool> tempBools(allValues[i].first.size(), false);
                        allCombinations(
                            allValues[i].first, allValues[i].first.size(),
                            j, 0, 0, tempBools, combinations, allValues[i].second
                        );
                    }
                }

                // For each combination, check frequent.
                for(auto x : combinations){
                    if(x.second > freqRows){
                        freqSet[x.first] = x.second;
                    }
                }

                // REMOVE UNWANTED BLOCKS OF MEMORY?
                vector<table>().swap(secondaryTable);
                TreeDeletion(&secondaryRoot);
            }
        }
    }

    for(auto x : freqSet){
        for(auto item : x.first){
            cout << item << ",";
        }
        cout << "COUNT=" << x.second;
        cout << endl;
    }

    // MAYBE DELETE ROOT AND ALL HERE?

}
