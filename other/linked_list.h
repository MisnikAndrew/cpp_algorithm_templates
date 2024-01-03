#include <bits/stdc++.h>

/*
API
makeList(m) - create linked list from vector m and return pointer to its head
fromNode(l) - return vector of values of linked list with head l
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

ListNode* makeList(vector<int>& m) {
    int a = m.size();
    ListNode* head = new ListNode(0);
    ListNode* tail = head;
    for (int i = 0; i < a; ++i) {
        tail->val = m[i];
        ListNode* next = new ListNode(0);
        if (i + 1 < a) {
            tail->next = next;
            tail = tail->next;
        }
    }
    return head;
}

vector <int> fromNode(ListNode* l) {
    vector <int> ans;
    ListNode* cur = l;
    while (cur) {
        ans.push_back(cur->val);
        cur = cur->next;
    }
    return ans;
}