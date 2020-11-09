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











/*
STEP 2: REARRANGE TREE
*/


void attachNewNodeLink(int val, node* newLink, vector<table> &mainTable, bool replace = false, node* oldLink = NULL){

    // First off, find the index
    int index = indexOfInTable(mainTable, val);

    // IF new entry to table, just add it to the table.
    if(!mainTable[index].nodeLink){
        mainTable[index].nodeLink = newLink;
    }

    // If already present in the table, move until it is NULL and
    // add it to the end of the nodeLinks
    else{

        node* temp = mainTable[index].nodeLink;
        if(!replace){
            while(temp -> nodeLink){
                temp = temp -> nodeLink;
            }
            temp -> nodeLink = newLink;
        }
        else{
            // possibility of endless loop?
            if(temp == oldLink){
                mainTable[index].nodeLink = oldLink -> nodeLink;
            }
            else{
                // Find the old Link and you're going to delete it, so move the
                // nodeLink of the previous one to the one after oldLink
                while(temp -> nodeLink != oldLink){
                    temp = temp -> nodeLink;
                }
                temp -> nodeLink = oldLink -> nodeLink;
            }
        }
    }
}


void exchange(node *x, node *y, node *z, int i, int j){

    if(y-> count > z -> count){
        node *newNode = new node;
        newNode -> item_no = y -> item_no;
        newNode -> count = (y -> count) - (z -> count);

        newNode -> nodeLink = y -> nodeLink;
        y -> nodeLink = newNode;

        for(int k = 0; k < (y -> child).size(); k++){
            if(k == j){
                continue;
            }
            (newNode -> child).push_back((y -> child)[k]);

            // new parent update
            ((newNode -> child)[(newNode -> child).size() - 1]) -> parent = newNode;
        }

        // You should clear it here because you don't want it to be added
        // outside as well.
        (y -> child).clear();

        // parent addition
        newNode -> parent = x;

        // Make this newNode as another child of x (sibling of y)
        (x -> child).push_back(newNode);
    }

    // swap y and z

    // remove z
    if(!(y -> child).empty())
        (y -> child).erase((y -> child).begin() + j);
    vector<node*> tempChildren = y -> child;
    (y -> child).clear();

    int k;
    for(k = 0; k < (z -> child).size(); k++){
        (y -> child).push_back((z -> child)[k]);

        // update new parent
        (y -> child)[k] -> parent = y;
    }

    // clear all children of z initially
    (z -> child).clear();
    // first child is y
    (z -> child).push_back(y);

    for(k = 0; k < tempChildren.size(); k++){
        (z -> child).push_back(tempChildren[k]);

        // update new parent
        (z -> child)[k] -> parent = z;
    }

    y -> count = z -> count;
    // do i have to do something to z -> count as well?

    // parent addition
    y -> parent = z;
    z -> parent = x;
    (x -> child)[i] = z;
}

void merge(node* x, int index, vector<table> &mainTable){

    node* target_node = (x -> child)[index];
    int target_item = target_node -> item_no;

    for(int i = 0; i < (x -> child).size(); i++){

        node *match_sibling = (x -> child)[i];
        if(match_sibling -> item_no == target_item && i != index){

            // if there is another z item, merge all their stuff together.
            for(int j = 0; j < (match_sibling -> child).size(); j++){
                (target_node -> child).push_back((match_sibling -> child)[j]);

                // parent update
                (target_node -> child)[j] -> parent = target_node;
            }

            target_node -> count += match_sibling -> count;

            // NO NEED TO DDO target_node -> nodeLink = match_sibling -> oldLink
            // Below one is enough.

            // also nodeLink from table to this match_sibling needs to be updated.
            attachNewNodeLink(match_sibling -> item_no, target_node, mainTable, true, match_sibling);

            (x -> child).erase((x -> child).begin() + i);
            delete match_sibling;
            break;
        }
    }
}

void rearrangeTree(vector<table> &mainTable, vector<int> &transaction, node *root){

    if(root == NULL){
        return;
    }

    node *x = root;
    for(int i = 0; i < (x -> child).size(); i++){
        node *y = (x -> child)[i];
        rearrangeTree(mainTable, transaction, y);
        int y_index = indexOfInTable(mainTable, y -> item_no);
        int y_support = mainTable[y_index].count;

        for(int j = 0; j < (y -> child).size(); j++){
            node *z = (y -> child)[j];
            int z_index = indexOfInTable(mainTable, z -> item_no);
            int z_support = mainTable[z_index].count;

            if(z_support > y_support){

                exchange(x, y, z, i, j);

                merge(x, i, mainTable);
                // come through this path again DFS.
                // since z and y are swapped now, come again.
                i--;
                break;
            }

        }
    }
}















/*
STEP 3 : INSERTING NODES INTO THE TREE.
*/
void insertTree(vector<table> &mainTable, vector<int> &transaction, node *root){
    node *x = root;
    node *matched_child;
    vector<pair<int, node*>> nodeLinkCache;

    for(int i = 0; i < transaction.size(); i++){

        int found = 0;
        for(int j = 0; j < (x -> child).size(); j++){
            matched_child = (x -> child)[j];
            if(matched_child -> item_no == transaction[i]){
                matched_child -> count++;
                found = 1;
                break;
            }
        }

        if(!found){
            node *newNode = new node;
            newNode -> count = 1;
            newNode -> item_no = transaction[i];
            newNode -> nodeLink = NULL;
            newNode -> parent = x;

            (x -> child).push_back(newNode);
            matched_child = newNode;

            // ONLY HAVE TO ADD LINK WHEN NEW NODE IS INSERTED.
            nodeLinkCache.push_back(make_pair(transaction[i], matched_child));
        }

        x = matched_child;
    }

    // MAKE THE NODE_LINKS VALID NOW.
    for(int i = 0; i < nodeLinkCache.size(); i++){
        attachNewNodeLink(nodeLinkCache[i].first, nodeLinkCache[i].second, mainTable);
    }
}
