#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDER 20 
#define MAX_PAGES 1000

typedef struct {
    int page_id;                    // ID unico desta pagina
    int num_keys;                   // Numero de chaves ocupadas
    int is_leaf;                    
    int keys[2 * MAX_ORDER - 1];    
    int children[2 * MAX_ORDER];    // IDs dos filhos
} BTreeNode;

// Metadados da arvore em RAM
typedef struct {
    int root_id;    // ID da pagina da raiz (-1 se vazia)
    int t;          // Grau minimo
} BTree;

// Simulacao do disco
extern BTreeNode* disk[MAX_PAGES];
extern int NUM_PAGES;       // Numero de paginas usadas
extern int CONTA_LEITURA;   // Contador de leituras
extern int CONTA_ESCRITA;   // Contador de escritas

BTree* create_tree(int t);
BTreeNode* create_node(int is_leaf);

// Leitura de linha com INSERT x ou SEARCH x
int ler_comando_insert_search(char* linha, int* valor);

// Identifica comando isolado (modo escrita)
int identificar_comando(char* cmd);

// Escrita no arquivo
void EscreverInsert(FILE* f, int valor);
void EscreverSearch(FILE* f, int valor);

// OPERACOES DE DISCO
BTreeNode* disk_read(int node_id);
void disk_write(int node_id);
int create_node_in_disk(int is_leaf);

// BUSCA
int btree_search(BTree* tree, int node_id, int key);

// INSERCAO
void btree_split_child(int parent_id, int index, int t);
void btree_insert_nonfull(int node_id, int key, int t);
void btree_insert(BTree* tree, int key);

// IMPRESSAO
void imprimir_arvore(int node_id, int nivel);

#endif