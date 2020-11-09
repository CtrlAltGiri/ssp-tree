// Function to test if any path has same child links
bool testFunc(node *x, node *y, node *z){

    if(x -> item_no != 6){
        return false;
    }
    unordered_set <node*> s;

    for(int i = 0; i < (x -> child).size(); i++){
        s.insert((x -> child)[i]);
    }

    x = y;
    for(int i = 0; i < (x -> child).size(); i++){
        if(s.find((x -> child)[i]) != s.end()){
            return true;
        }
        else{
            s.insert((x -> child)[i]);
        }
    }

    x = z;
    for(int i = 0; i < (x -> child).size(); i++){
        if(s.find((x -> child)[i]) != s.end()){
            return true;
        }
        else{
            s.insert((x -> child)[i]);
        }
    }

    return false;
}
