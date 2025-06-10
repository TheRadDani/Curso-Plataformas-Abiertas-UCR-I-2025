#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable{
    int size;
    HashNode** buckets;
} HashTable;


int hash(int key, int size) {
    return key % size;
}

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (HashNode**)malloc(size * sizeof(HashNode*));
    for(int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// Insert a key-value pair into the hash table
void insert(HashTable* table, int key, int value) {
    int index = hash(key, table->size);
    HashNode* current = table->buckets[index];

    // Check if the key already exists
    while(current != NULL) {
        if(current->key == key) {
            current->value = value; // Update the value if key already exists
            return;
        }
        current = current->next;
    }

    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

int lookup(HashTable* table, int key) {
    int index = hash(key, table->size);
    HashNode* current = table->buckets[index];

    while(current!=NULL) {
        if(current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Key not found
}

void delete(HashTable* table, int key) {
    int index = hash(key, table->size);
    HashNode* current = table->buckets[index];
    HashNode* prev = NULL;

    while(current != NULL) {
        if(current->key == key) {
            if(prev == NULL) {
                table->buckets[index] = current->next; // Remove the first node
            } else {
                prev->next = current->next; // Remove the node from the list
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void freeHashTable(HashTable* table) {
    for(int i = 0; i < table->size; i++) {
        HashNode* current = table->buckets[i];
        while(current !=NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int main() {
    HashTable* table = createHashTable(10);
    insert(table, 1, 100);
    insert(table, 2, 200);
    insert(table, 11, 110); // Collision with key 1
    insert(table, 12, 120); // Collision with key 2
    printf("Value for key 1: %d\n", lookup(table, 1));
    printf("Value for key 2: %d\n", lookup(table, 2));
    printf("Value for key 11: %d\n", lookup(table, 11));
    printf("Value for key 1: %d\n", lookup(table, 1));
    printf("Value for key 12: %d\n", lookup(table, 12));

    delete(table, 1);
    printf("Value for key 1 after deletion: %d\n", lookup(table, 1));
   
    int key = lookup(table, 10000);
    if (key == -1){
        printf("Key 10000 not found\n");
    } else {
        printf("Key 10000 found\n");
    }

    freeHashTable(table);
    return 0;
}