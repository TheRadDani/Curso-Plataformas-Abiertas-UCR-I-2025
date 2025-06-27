#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void append(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
         return;
    }

    Node* current = *head;
    while(current->next != NULL) current = current->next;
    current->next = new_node;
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
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_val = 10;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            printf("Error: Value %d exceeds maximum allowed value of %d\n", arr[i], max_val);
            return 1;
        }
        append(&head, arr[i]);
    }

    printf("Linked List: ");
    printList(head);

    Node* temp;
    freeList(head);
    head = NULL;
    return 0;
}