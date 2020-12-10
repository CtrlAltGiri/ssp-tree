#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include "includes/utils.h"
#include "construction.h"

unsigned int memUsageCheck(node*);
void mineSSPTree(vector<table> &headerTable, node *root, unsigned int freqThreshold, unsigned int rareThreshold, unsigned int rows, double constructionTime){

    clock_t startMining = clock();
    int freqRows = (rows * freqThreshold) / 100;
    int rareRows = (rows * rareThreshold) / 100;
    map<vector<int>, int> freqSet, rareSet;

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

                    // Frequent itemsets
                    if(x.second >= freqRows){
                        vector<int> currentFreqSet;
                        currentFreqSet.insert(currentFreqSet.end(), x.first.begin(), x.first.end());
                        currentFreqSet.push_back(currentItemNo);
                        sort(currentFreqSet.begin(), currentFreqSet.end());

                        freqSet[currentFreqSet] = x.second;
                    }

                    // Rare itemsets
                    else if(x.second >= rareRows){
                        vector<int> currentRareSet;
                        currentRareSet.insert(currentRareSet.end(), x.first.begin(), x.first.end());
                        currentRareSet.push_back(currentItemNo);
                        sort(currentRareSet.begin(), currentRareSet.end());

                        rareSet[currentRareSet] = x.second;
                    }
                }
            }
        }
    }

    clock_t endMining = clock();
    double miningTime = ((double) (endMining - startMining)) / CLOCKS_PER_SEC;

    ofstream frequentItemSetsFile, rareItemSetsFile;
    frequentItemSetsFile.open("./output/frequentItemSets.txt");
    rareItemSetsFile.open("./output/rareItemSets.txt");

    for(auto x : freqSet){
        for(auto item : x.first){
            frequentItemSetsFile << item << ",";
        }
        frequentItemSetsFile << "COUNT=" << x.second << endl;
    }

    for(auto x : rareSet){
        for(auto item : x.first){
            rareItemSetsFile << item << ",";
        }
        rareItemSetsFile << "COUNT=" << x.second << endl;
    }

    cout << endl << "STATISTICS" << endl << endl;
    cout << "Frequent Item Sets: " << freqSet.size()
         << endl << "Rare Item Sets: " << rareSet.size() << endl << endl;

    cout << "Time taken to construct tree: " << constructionTime << endl;
    cout << "Time taken to mine: " << miningTime << endl;
    cout << "Total time taken: " << (constructionTime + miningTime) << endl << endl;

    unsigned int sspTreeMemUsage = memUsageCheck(root);
    unsigned int headerTableMemUsage =  headerTable.size() * sizeof(table);
    cout << "SSP Tree Memory Usage: " << sspTreeMemUsage << endl;
    cout << "Header Table Memory Usage: " << headerTableMemUsage << endl;
    cout << "Total Memory Usage: " << sspTreeMemUsage + headerTableMemUsage << endl << endl;

    cout << "Frequent and Rare itemsets are stored in output folder" << endl << endl;
}

unsigned int memUsageCheck(node* root){

    if(!root){
        return 0;
    }

    unsigned int nodeTotal = sizeof(*root);
    for(int i = 0; i < (root -> child).size(); i++){
        nodeTotal += memUsageCheck((root -> child)[i]);
    }

    return nodeTotal;
}
