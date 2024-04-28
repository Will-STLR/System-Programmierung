#include <stdio.h>
#include <stdlib.h>

// TODO: structs, global variables, etc.
struct Node {
    int value;
    struct Node* next;
};
typedef struct Node Node;

 typedef  Node {
    int value;
    struct Node* next;
}Node;

static Node* head = NULL;

int insertElement(int value) {
    // TODO: implement me!
    Node* check = head;

    if (value < 0) {
        return -1;
    }

    if(check == NULL) {
        Node* newNode;
        newNode = (Node*)malloc(sizeof(*newNode));
        //Fehlerbehandlung
        if(newNode == NULL) {
            return -1;
        }

        head = newNode;
        head->value = value;
        head->next = NULL;
        return value;
    }

    while(check->value != value) {
        if((*check).next == NULL) {

            Node* newNode;
            newNode = (Node*)malloc(sizeof(*newNode));
            //Fehlerbehandlung
            if(newNode == NULL) {
                return -1;
            }

            (*newNode).next = (*check).next;
            (*check).next = newNode;
            (*newNode).value = value;
            return value;
        }
        check = (*check).next;
    }
    return -1;
}

int removeElement(void) {
    // TODO: implement me!
    if(head == NULL) {
        return -1;
    }

    Node* newHead = (*head).next;
    int res = head->value;
    free(head);
    head = newHead;
    return res;
}

static void printList(void) {
    Node* current = head;
    printf("[");
    while (current != NULL) {
        printf("%d", (*current).value);
        if(current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]");
}

int main (int argc, char* argv[]) {
    printf("insert 47: %d\n", insertElement(47));
    printf("insert 11: %d\n", insertElement(11));
    printf("insert 23: %d\n", insertElement(23));
    printf("insert 11: %d\n", insertElement(11));

    printf("remove: %d\n", removeElement());
    printf("remove: %d\n", removeElement());
    printList();

    // TODO: add more tests
    printf("insert -2: %d\n", insertElement(-2));

    exit(EXIT_SUCCESS);
}
