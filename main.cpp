#include<iostream>
#include<vector>
using namespace std;

struct node{
    int item_no;
    int count;
    vector<node*> link;
};

struct table{
    int item_no;
    int count;
    node* link;
};

int main(){

    vector<table> mainTable;
    

}