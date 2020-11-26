#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
#include "includes/utils.h"
#include "construction.h"

void mineSSPTree(vector<table> &headerTable, node *root, unsigned int freqThreshold, unsigned int rareThreshold, unsigned int rows){

    int freqRows = (rows * freqThreshold) / 100;
    int rareRows = (rows * rareThreshold) / 100;
    map<vector<int>, int> freqSet;

    // MINING THE SSP TREE.
    if(root){

        // Iterating through header table
        for(auto i : headerTable){

            int currentItemNo = i.item_no;
            // Construction of conditional SSP.
            if(i.count > freqRows){

                // ADD IT TO THE FREQUENT ITEMSETS
                freqSet[{i.item_no}] = i.count;

                // All paths, each vector has one path.
                vector<pair<vector<node*>, int>> allValues;
                vector<node*> tempValues;

                // Step 1: Get all the things in a vector
                node* currentNode = i.nodeLink;
                unsigned int currentItemCount = i.count;

                do{
                    tempValues.clear();
                    node* tempNode = currentNode;
                    while(tempNode -> parent != root){
                        tempValues.push_back(tempNode -> parent);
                        tempNode = tempNode -> parent;
                    }
                    if(!tempValues.empty()){
                        allValues.push_back(make_pair(tempValues, currentNode -> count));
                    }
                    currentNode = currentNode -> nodeLink;

                }while(currentNode);

                // Step 2: Find all combinations
                map<vector<int>, int> combinations;
                for(int i = 0; i < allValues.size(); i++){
                    for(int j = 1; j <= allValues[i].first.size(); j++){
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

                        // ADDING THE HEADER TABLE ELEMENT TO THE LIST AS WELL.
                        vector<int> currentFreqSet;
                        currentFreqSet.insert(currentFreqSet.end(), x.first.begin(), x.first.end());
                        currentFreqSet.push_back(currentItemNo);
                        sort(currentFreqSet.begin(), currentFreqSet.end());

                        // THE COUNT OF THE ITEMSET
                        freqSet[currentFreqSet] = x.second;
                    }
                }
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
