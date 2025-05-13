#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


void append(Node **head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
int main() {
    Node* head = NULL;
    append(&head, 8);
    append(&head, 5);
    append(&head, 3);
    printList(head);
    // Free the linked list
    Node* temp;
    freeList(head);
    head = NULL;
    return 0;
}