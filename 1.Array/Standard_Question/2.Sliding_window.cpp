/*
-[]Check if array contain pair of duplicate value
-[]2 duplicate number further than k position from each other, i.e.
	arr[i]=arr[j];abs(i-j)<=k;
-[]O(n*k)
*/
#include <iostream>
#include <unordered_set>
#include <algorithm>

using std::vector;
using std::unordered_set;
using std::min;

bool closeDuplicateBruteforce(vector<int>& nums,int k){
	int size=static_cast<int>(nums.size());
	for(int L=0;L<size;L++){
		for(int R=L+1;R<min(size,L+k);R++){
			if(nums[L]==nums[R])
				return true;
		}
	}
return false;
}
