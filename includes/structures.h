#include<iostream>
#include<vector>

struct node{
    int item_no;
    unsigned int count;
    std::vector<node*> child;
    node* parent;
    node* nodeLink;
};

struct table{
    int item_no;
    unsigned int count;
    node* nodeLink;
};
