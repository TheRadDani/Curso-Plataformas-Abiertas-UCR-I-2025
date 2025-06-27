#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100    


typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct HashNode {
    int key;
    struct HashNode* next;
} HashNode;


HashNode* create_hash_node(int key) {
    HashNode* node = malloc(sizeof(HashNode));
    node->key = key;
    node->next = NULL;
    return node;
}

int hash(int key) {
    return abs(key) & 10;
}

bool hash_insert(HashNode** table, int key) {
    int idx = hash(key);
    HashNode* node = table[idx];
    while (node != NULL) {
        if (node->key == key) return true; // Key already exists
        node = node->next;
    }

    HashNode* new_node = create_hash_node(key);
    new_node->next = table[idx];
    table[idx] = new_node;
    return false; // Key was inserted
}

void find_duplicates(Node* head) {
    HashNode* hash_table[MAX_SIZE] = {NULL};
    bool found_duplicates = false;

    Node* current = head;
    while(current != NULL) {
        if (hash_insert(hash_table, current->data)) {
            printf("Duplicate found: %d\n", current->data);
            found_duplicates = true;
        }
        current = current->next;
    }
    if (!found_duplicates) {
        printf("No duplicates found.\n");
    }

    // Free the hash table
    for(int i=0; i < MAX_SIZE; i++) {
        HashNode* node = hash_table[i];
        while(node != NULL) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
}


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
    int arr[] = {1, 2, 3, 3, 4, 4, 5, 6, 7, 8, 9, 10};
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

    find_duplicates(head);

    Node* temp;
    freeList(head);
    head = NULL;
    return 0;
}