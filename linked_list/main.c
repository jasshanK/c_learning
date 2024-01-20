// building a linked list 
// what functions would I need? 
// i need something to create the nodes 
// i need something to delete the nodes 

// what is a node? 
// a node is just data + the location of the next node 
// node1(data + location of node2)
//
//
// we dont use linkedlist in embedded systems
// HEAP -> implemented by glibc
// malloc and free
// P1: somebody needs to implement malloc and free
// P2: when im allocating at RUN TIME, what happens if I run out of space?
// knowledge at COMPILE TIME 
// linked list is just dynamic memory allocation 
// -> how much memory I am using, before I even run the program
// RUN TIME ERROR 
//  issues with, code logic, off by 1 (indexing by 1 extra), segmentation fault, recurrsion errors
// stack oveflow 
// COMPILE TIME ERROR
//  syntax issues 
//
//  compile an embedded program 
//  usually there is a table at the bottom, showing you how much memory your program will use

#include <stdlib.h>
#include <stdio.h>

//node
// singley linked list
struct Node {
    int data;
    struct Node* next_node;
    //struct Node* prev_node;
};

// node2<->node3

// linked list has a 
// start, and end
// WHAT IS THE ENDDDDD

// only creates nodes
struct Node* createNode(int data);
// only adds nodes, HINT: how do I know when I'm at the end of the list?
// appendNode CALLS createNode
void appendNode(struct Node* head, int data); 
// how do I remove stuff from the heap?
void deleteNodes(struct Node* head);
void printNode(struct Node* head);

// modify createNode, so you can add more than one node
// you SHOULD MAKE MORE FUNCTION
// createNode = ONLY CREATES NODES
// deleteNode = ONLY DELETES NODES
// appendNode = ONLY ADDS NODES
int main() {
    printf("size: %d\n", sizeof(struct Node));
    struct Node* head = createNode(1);

    appendNode(head, 2);
    appendNode(head, 3);
    appendNode(head, 4);
    appendNode(head, 5);
    appendNode(head, 6);

    printNode(head);

   // appendNode(head, 5);
   // appendNode(head, 6);

    printNode(head);

    int array[5] = {0, 0, 0, 0, 0};
    // 1 2 3 4 5 
    // 2 3 4 5 6
    // 3 4 5 6 7
    // 
    // 1 2 3 4 5
    // 6 2 3 4 5
    // 6 7 3 4 5
    // just increase the size of the array
    // int array[n];
    //

    // ring buffer -> circular queue
    // STACK = LIFO 
    // QUEUE = FIFO 
    //
    // 1->2->3->4->5->1
    // how do I represent something "circular"?
    // MATH
    // index 0-4 
    // index 5-9
    // index 10-14
    // index = index % 5
    //
    // REFEREE SYSTEM MODULE SENDING DATA 
    // [send send send] send
    // start and end of the ring buffer
    //
    // give you guys a super long string 
    // count how many times a certain string appears in that string
    // USE A RING BUFFER
    //
    // stack, heap 
    // dyanmic allocation 
    // compile time runtime 
    // linkedlist ring buffer 
    // stack queue heap (data structure)
    // CS2040C/CS2040 -> did not take this
    // they dont understand HARDWARE -> imo very bad
    // LINEAR TIME, EXPONENTIAL 
    // O(n) O(n^2)
    return 0;
}

// creation of node needs to live past exit of function
struct Node* createNode(int data) { // definition
    // void* -> void pointer
    // whats so special about them? 
    // type casting 
    // python type casting -> int(4.0)
    // c type casting -> (int) 4.0
    //
    size_t size_of_struct_node = sizeof(struct Node);
    // explicit vs implicit
    //struct Node* p_new_node = malloc(size_of_struct_node);
    /*struct Node* p_new_node;
    p_new_node = malloc(size_of_struct_node);*/

    struct Node* p_new_node = (struct Node*) malloc(size_of_struct_node);

    (*p_new_node).data = data;
    //(*p_new_node).next_node = NULL;
    p_new_node->next_node = NULL;

    return p_new_node;
};

void appendNode(struct Node* head, int data) {
    struct Node* current_node = head;
    struct Node* new_node = createNode(data);

    while(1) {
        // if current node is pointing to nothing (NULL), its the last node in the list
        if (current_node->next_node == NULL) {
            current_node->next_node = new_node;

            break;
        }

        current_node = current_node->next_node;
    }
}

void printNode(struct Node* head) {
    struct Node* current_node = head;

    while(1) {
        printf("%d ", (*current_node).data);

        // exit condition; I like putting them on top 
        if ((*current_node).next_node == NULL) {
            break;
        }

        current_node = current_node->next_node;
    }

    printf("\n"); // (almost) same as pressing enter
} 

void deleteNodes(struct Node* head) {
    // start at the head 
    // move to the next node 
    // I want to clear what's behind me
    // shifting the head
    // node1 = head
    // node2 = head, delete node1
    // nodeN = head, delete node(N-1)
    struct Node* current_head = head;
    struct Node* temp;
    
    while(1) {
        if ((*current_head).next_node == NULL) {
            free(current_head);
            break;
        }

        temp = current_head->next_node;

        free(current_head);

        current_head = temp;
    }
}
