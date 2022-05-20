#include <stdio.h>
#include <stdlib.h>
struct node
{
    int a;
};

typedef struct node node1;
typedef node1 *Node;

int main()
{
    node1 **x;
    x = (node1 **)malloc(sizeof(node1 *));

    // lookUpTable->slots = (List*)malloc(slotsNum*sizeof(List));

    // (*x)->a = 1;
    // printf("%d", (*x)->a);

    // node1 y;
    // y.a = 2;
    // printf("%d\n", y.a);
    printf("Heello");
    // printf("\n");
}