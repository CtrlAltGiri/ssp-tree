#include <iostream>
#include <ctime>
#include "dataInput.h"
#include "mining.h"

using namespace std;

int main(){

    // Read data
    vector<vector<int>> data;
    read_record(data);

    unsigned int n=1000, freqThreshold=0, rareThreshold=0;

    // INPUT TAKEN.
    cout << "Enter the number of rows: ";
    cin >> n;

    cout << "Enter the frequent item threshold (percentage): ";
    cin >> freqThreshold;

    cout << "Enter the rare item threshold (percentage): ";
    cin >> rareThreshold;


    // Initializing
    vector<table> mainTable;
    node root = {-1, 0, {}, NULL};

    // Tree construction
    clock_t startConstruction = clock(), endConstruction;
    TreeConstruction(n, mainTable, data, &root);
    endConstruction = clock();
    double constructionTime = ((double) (endConstruction - startConstruction)) / CLOCKS_PER_SEC;

    mineSSPTree(mainTable, &root, freqThreshold, rareThreshold, n, constructionTime);
}
