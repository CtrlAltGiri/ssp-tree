#include <iostream>
#include <algorithm>
#include <climits>
#include <unordered_set>

int indexOfInTable(vector<table> &mainTable, int item_no){
    for(int i = 0; i < mainTable.size(); i++){
        if(mainTable[i].item_no == item_no){
            return i;
        }
    }
    return INT_MAX;
}

void addCountTable(vector<table> &mainTable, vector<int> &transaction){

    int flag;
    for(int i = 0; i < transaction.size(); i++){
        flag = 0;
        for(int j = 0; j < mainTable.size(); j++){
            if(transaction[i] == mainTable[j].item_no){
                mainTable[j].count++;
                flag = 1;
                break;
            }
        }
        if(!flag){
            mainTable.push_back({transaction[i], 1, NULL});
        }
    }

    sort(mainTable.begin(), mainTable.end(), [](const table &a, const table &b){
        return a.count > b.count;
    });

    vector<pair<int,int>> tempStruct;
    for(int i = 0; i < transaction.size(); i++){
        tempStruct.push_back(make_pair(transaction[i], indexOfInTable(mainTable, transaction[i])));
    }

    sort(tempStruct.begin(), tempStruct.end(), [](const pair<int,int> &a, const pair<int,int> &b){
        return a.second < b.second;   // index in the table must be greater.
    });

    transaction.clear();
    for(int i = 0; i < tempStruct.size(); i++){
        transaction.push_back(tempStruct[i].first);
    }
}
