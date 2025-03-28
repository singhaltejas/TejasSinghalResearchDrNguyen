#include <iostream>
#include <string>
using namespace std;

class LinkedListNode {
public:
    int val;
    LinkedListNode* next;

    LinkedListNode(int val = 0, LinkedListNode* next = nullptr) : val(val), next(next) {} 
};


class FirstNFibonacci {       
public:        
    LinkedListNode* head;  
    int LinkedListLength;  

    FirstNFibonacci(int N) {
        LinkedListLength = N;
        if (N <= 0) {
            head = nullptr;
            return;
        }

        head = new LinkedListNode(0);
        if (N == 1) return;

        LinkedListNode* second = new LinkedListNode(1);
        head->next = second;

        LinkedListNode* prev1 = second; // 1 step before the current
        LinkedListNode* prev2 = head;   // 2 steps before the current

        for (int i = 2; i < N; i++) {
            LinkedListNode* newNode = new LinkedListNode(prev1->val + prev2->val);
            prev1->next = newNode; 
            prev2 = prev1; 
            prev1 = newNode; 
        }
    }

    void print(int k) {
        if (!head) {
            cout << "Empty list!" << endl;
            return;
        }
        
        cout << "The first " << k << " nodes of the linked list are:" << endl;
        LinkedListNode* curr = head;
        int count = 0;

        while (curr != nullptr && count < k) {
            cout << curr->val << endl;
            curr = curr->next;
            count++;
        }
    }

    FirstNFibonacci* deep_clone() {
        if (!head) return new FirstNFibonacci(0); 

        FirstNFibonacci* clone = new FirstNFibonacci(0);
        clone->LinkedListLength = this->LinkedListLength;

        LinkedListNode* cloneHead = new LinkedListNode(head->val);
        clone->head = cloneHead;

        LinkedListNode* currOld = head->next;
        LinkedListNode* currNew = cloneHead;

        while (currOld) {
            LinkedListNode* newNode = new LinkedListNode(currOld->val);
            currNew->next = newNode;

            currOld = currOld->next;
            currNew = newNode;
        }

        return clone;
    }

    ~FirstNFibonacci() {
        LinkedListNode* curr = head;
        while (curr) {
            LinkedListNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

int main() {
    FirstNFibonacci myObj(6);  // Create original linked list
    myObj.print(99);
    return 0;
}



