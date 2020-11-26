#include <iostream>
#include <map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "structures.h"

void allCombinations(vector<node*> &arr, int size, int reqLen, int start, int currLen, vector<bool> check, map<vector<int>, int> &combinations, unsigned int addCount){

	if(currLen > reqLen){
		return;
	}

 	if (currLen == reqLen){
		unordered_set<int> tempSet;
		for(int i = 0; i < size; i++){
			if(check[i]){
				tempSet.insert(arr[i] -> item_no);
			}
		}
		if(!tempSet.empty()){

			vector<int> finalItemSet(tempSet.size());
			copy(tempSet.begin(), tempSet.end(), finalItemSet.begin());
			combinations[finalItemSet] += addCount;
		}
		return;
	}

	if (start == size){
		return;
	}

	// For every index we have two options.
	// First is, we select it, means put true in check[] and increment currLen and start.
	check[start] = true;
	allCombinations(arr, size, reqLen, start + 1, currLen + 1, check, combinations, addCount);
	// Second is, we don't select it, means put false in check[] and only start incremented.
	check[start] = false;
	allCombinations(arr, size, reqLen, start + 1, currLen, check, combinations, addCount);
}
