#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;


int main(int argc, char *argv[])
{
    // int a = 1;
    // int b = 2;
    // int c = 3;

    // create list assign NULL value to create list empty
    node *list = NULL;

    // // create node at location n assign space of node size
    // node *n = mallco(sizefo(node));

    // // go to pointer n number and assign value of a
    // *n.number = a;

    // // assign end of list to null so its not GARBAGE value
    // *n.next = NULL;

    // // connect node to root
    // list = n;

    // // create node at location n assign space of node size
    // node *n = mallco(sizefo(node));

    // // go to pointer n number and assign value of a
    // *n.number = b;

    // // assign new node next to list (list is a pointer to 1st node.)
    // // if this opperation is not done here new created node will be orphanted. - week5 vid 01:05
    // *n.next = list;

    // list = n;


    // int a = 1;
    // int b = 2;
    // int c = 3;
    // n.number = a;


    for (int i = 1; i < argc; i ++)
    {
        // for number from command line
        int num = atoi(argv[i]);

        // create node assign allocate memory
        node *node_ = malloc(sizeof(node));
        if (node_ == NULL)
        {
            // memory leak if error occure on 1 < i < argc
            // free list func
            return 1;
        }

        // assign number to node.
        node_->number = num;

        // // set list to node
        // list = node_;

        // clear from GARBAGE end of list
        node_->next = NULL;

        // set current node next to point to list
        node_->next = list;

        // set list to node
        list = node_;
    }

    // iterate thru list require extra pointer
    node *temp = list;
    // until end of list
    while (temp != NULL)
    {
        printf("%i -> ", temp->number);
        temp = temp->next;
    }
    printf("NULL\n");

    // free memory
    temp = list;
    for (temp = list; temp != NULL; temp= next )// temp = temp->next
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    }

    // last two cold be in 1 loop

}