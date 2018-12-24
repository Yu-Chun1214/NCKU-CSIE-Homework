#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node * nodePointer;
struct Node{
    int value;
    nodePointer link;
};

typedef nodePointer * listPointer;
typedef struct Node Node;

nodePointer Constructor(int i);
void Destructor(nodePointer trash);
void Insertion(nodePointer node1, nodePointer node2); // node1->link whill be inserted after node2
listPointer createRandomChain(int amounts);
void showLinkedList(listPointer);


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

listPointer createRandomChain(int amounts){
    listPointer start;
    nodePointer current = Constructor(0);
    *start = current;
    for(int i = 1; i <amounts; i++){
        current->link = Constructor(i);
        current = current->link;
    }
    return start;
}

void showLinkedList(listPointer header){
    nodePointer current = *header;
    while(current){
        printf("%d ",current->value);
        current = current->link;
    }
    printf("\n");
}

void * pivot_selection(void * v_chain,unsigned int size){
    nodePointer chain = (nodePointer)v_chain;
    nodePointer iterator = chain;
    for(int i = 0; i < size-1;i++) iterator = iterator->link;
    return (void *) iterator;
}

void quickSort(void * chain,unsigned int size, int cmpr(void *,void *),void insertion(void *, void *),void * pivot_selection(void * chain,unsigned int size)){
    void * pivot = pivot_selection(chain,size - 1); // select which node you want to be the pivot
    // void * before_pivot = pivot_selection(chain,size - 1);
    void * iterator;
    int i = 0; void * first_swap,* current = chain;
    for(i = 0; i < size; i++){
        if(cmpr(current,pivot)){
            first_swap = current;
            insertion(current,NULL);
        }
    }
}

int cmpr(void * v_node1, void * v_node2){
    nodePointer node1 = (nodePointer)v_node1;
    nodePointer node2 = (nodePointer)v_node2;
    if(node1->value > node2->link->value) return 1;
    return 0;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    // nodePointer chain;
    nodePointer current;
    listPointer chain;
    printf("showLinkedList\n");
    showLinkedList(chain);
    current = chain;
    current = (nodePointer)pivot_selection((void *)chain,3);
    printf("current->value = %d\n",current->value);
    Insertion(chain,current);
    showLinkedList(chain);
    return 0;
}
