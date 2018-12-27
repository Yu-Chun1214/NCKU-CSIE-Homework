#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Node * NodePointer;
struct Node{
    int val;
    NodePointer next;
};

typedef struct Node Node;

int RandomInt(int m){
    return (rand()%m);
}

NodePointer nodeConstructor(int num){
    NodePointer newNode = (NodePointer)malloc(sizeof(Node));
    newNode->val = num;
    newNode->next = NULL;
    return newNode;
}

NodePointer createRandomList(int amounts,int m){
    if(amounts){
        NodePointer np;
        NodePointer iterator;
        iterator = np = nodeConstructor(-1);
        for(int i = 0; i < amounts; i++){
            iterator->next = nodeConstructor(RandomInt(m));
            iterator = iterator->next;
        }
        return np;
    }
    return NULL;
}

void Show(NodePointer head){
    NodePointer iterator = head->next;
    while(iterator){
        printf("%6d ",iterator->val);
        iterator = iterator->next;
    }
    printf("\n");
}

void Insertion(NodePointer node1, NodePointer node2) // node1->next will be insert after node2
{
    // if(node1 == node2) return;
    NodePointer temp = NULL;
    if(node2->next)
        temp = node2->next;
    node2->next = node1->next;
    node1->next = node2->next->next;
    node2->next->next = temp;
}

int NodeCmpr(void * v_node1, void * v_node2){
    return ((NodePointer)v_node1)->next->val < ((NodePointer)v_node2)->val;
}

void * NodeIterator(void * node){
    NodePointer Next = ((NodePointer)node)->next;
    return (void *)Next;
}

void nodeInsertion(void * v_node1,void* v_node2){
    // Insertion((NodePointer)node1,(NodePointer)node2);
    NodePointer node2 = (NodePointer)v_node2;
    NodePointer node1 = (NodePointer)v_node1;
    NodePointer temp ;
    temp = node2->next;
    node2->next = node1->next;
    node1->next = node2->next->next;
    node2->next->next = temp;
}

void quickSort(void * list,unsigned int size, int cmpr(void * , void *),void operation(void * , void *),void * iterator(void *)){
    void * pivot = iterator(list);
    void * iter = pivot;
    int i;
    int new_size = 0;
    if(size > 1){
        for(i = 0; i < size - 1; i++){
            if(cmpr(iter,pivot)){
                operation(iter,list);
                ++new_size;
            }else  iter = iterator(iter);
        }
        quickSort(list,new_size,cmpr,operation,iterator);
        quickSort(pivot,size-1-new_size,cmpr,operation,iterator);
    }else return;
}

void nodeQuickSort(NodePointer head,unsigned int size){
    NodePointer pivot = head->next;
    NodePointer iter = pivot;
    NodePointer temp;
    int new_size = 0;
    if(size > 1){
        for(int i = 0;i < size - 1; i++){
            if(iter->next->val < pivot->val){
                temp = head->next;
                head->next = iter->next;
                iter->next = head->next->next;
                head->next->next = temp;
                ++new_size;
            }else iter = iter->next;
        }
        nodeQuickSort(head,new_size);
        nodeQuickSort(pivot,size - 1 - new_size);
    }
}

int main(int argc,char const *argv[]){
    int num = atoi(argv[1]);
    srand(atoi(argv[3]));
    NodePointer head = createRandomList(num,atoi(argv[2]));
    NodePointer test = head;
    // printf("Original SLL:");
    // Show(head);
    float time_1 = clock();
    // quickSort(head,num,NodeCmpr,nodeInsertion,NodeIterator);
    nodeQuickSort(head,num);
    float time_2 = clock();
    printf("time consume : %f\n",(time_2 - time_1)/CLOCKS_PER_SEC);
    // printf("Sorted SLL:");
    // Show(head);
}
