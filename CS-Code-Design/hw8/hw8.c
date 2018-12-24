#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node * nodePointer;
struct Node{
    int value;
    nodePointer link;
};

typedef struct Node Node;

nodePointer Constructor(int i);
void Destructor(nodePointer trash);
void Insertion(nodePointer node1, nodePointer node2); // node1->link whill be inserted after node2
nodePointer createRandomChain(int amounts);
void showLinkedList(nodePointer  header);


nodePointer Constructor(int i){
    nodePointer newNode;
    newNode = (nodePointer)malloc(sizeof(Node));
    newNode->value = i;
    newNode->link = NULL;
    return newNode;
}

void Destructor(nodePointer trash){
    free(trash);
}

void Insertion(nodePointer node1, nodePointer node2){
    /*
    parameter node1 can't be the trail of linked list
    if node1 is the trail of the linked list, node1->link is NULL pointer
    the function of inserting NULL pointer in the linked list is not provided!
    */
    nodePointer temp = NULL;
    if(node2->link)
        temp = node2->link;
    node2->link = node1->link;
    node1->link = node2->link->link;
    node2->link->link = temp;
}

nodePointer createRandomChain(int amounts){
    Node headerNode;
    nodePointer currentNode;
    currentNode = &headerNode;
    for(int i = 0; i < amounts; i++){
        currentNode->link = Constructor(i);
        currentNode = currentNode->link;
    }
    return headerNode.link;
}

void showLinkedList(nodePointer  header){
    nodePointer current = header;
    while(current){
        printf("%d ",current->value);
        current = current->link;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    nodePointer chain;
    nodePointer current;
    current = chain;
    chain = createRandomChain(5);
    printf("showLinkedList\n");
    showLinkedList(chain);
    current = chain;
    for(int i = 0; i < 3; i++){
        current = current->link;
    }
    printf("current->value = %d\n",current->value);
    Insertion(current,chain);
    showLinkedList(chain);
    return 0;
}
