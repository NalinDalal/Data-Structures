#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *reverseList(ListNode *head) {

    ListNode *prev = NULL;
    ListNode *curr = head;

    while (curr != NULL) {
      ListNode *forward = curr->next;
      curr->next = prev;
      prev = curr;
      curr = forward;
    }
    return prev;
  }
};

int main(){
  cout<<"Intialised LL:"<<endl;
  ListNode ll;
  ll.ListNode(3):3;
  ll.ListNode(4,3):4,3.next();

  Solution sol;
  sol.ListNode(ll);
  
  cin.get();
}
