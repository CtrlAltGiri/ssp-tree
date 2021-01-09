#include <iostream>
#include <ctime>
#include "dataInput.h"
#include "mining.h"

using namespace std;

int main(){

    unsigned int n = 0, freqThreshold = 0, rareThreshold = 0;

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
    TreeConstruction(n, mainTable, &root);
    endConstruction = clock();
    double constructionTime = ((double) (endConstruction - startConstruction)) / CLOCKS_PER_SEC;

    // Tree Mining
    mineSSPTree(mainTable, &root, freqThreshold, rareThreshold, n, constructionTime);

    char changedFile = 'Y';
    while(changedFile == 'Y' || changedFile == 'y'){
        cout << "Initial Tree Construction and Mining Complete." << endl << "Enter Y if you have modified file and you wish to repeat process: ";
        cin >> changedFile;

        if(changedFile == 'Y' || changedFile == 'y'){
            cout << "Done bruv." << endl;
        }
    }
}
