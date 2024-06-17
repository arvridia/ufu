#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 1000000 // Tamanho da tabela de hash

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *table[TABLE_SIZE];
} HashTable;

HashTable *createHashTable() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

unsigned int hash(int value) {
    return (unsigned int)(value % TABLE_SIZE);
}

void insert(HashTable *hashTable, int value) {
    unsigned int index = hash(value);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

bool search(HashTable *hashTable, int value) {
    unsigned int index = hash(value);
    Node *current = hashTable->table[index];
    while (current != NULL) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int main() {
    FILE *file = fopen("numeros.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    HashTable *hashTable = createHashTable();
    int num;
    int uniqueCount = 0;

    while (fscanf(file, "%d", &num) != EOF) {
        if (!search(hashTable, num)) {
            insert(hashTable, num);
            uniqueCount++;
        }
    }

    fclose(file);

    printf("Número de valores únicos: %d\n", uniqueCount);

    return 0;
}