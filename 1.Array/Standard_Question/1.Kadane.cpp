/*
Aim:To find non empty subarray with largest Sum😒
Time Complexity:O(n^2)-by the brute method

assign 1st element to max sum
i->starting pointer;j->another starting pointer

now suppose we want that left pointer doesn't crosses the right pointer
ultimately the Window grows
*/
#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::max;
//brute method
//O(n^2)
int bruteForce(vector<int>& nums){
	int maxSum=nums[0];
	for (int i=0;i<nums.size();i++){
		int curSum=0;
		for(int j=i;j<nums.size();j++){
			curSum+=nums[j];
			maxSum=max(maxSum,curSum);
		}
	}
	return maxSum;
}

int main(){
	bruteForce();
	std::cin.get();
}