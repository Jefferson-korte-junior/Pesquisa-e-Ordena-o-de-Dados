#include "function.h"


// Definicao das variaveis globais (simulacao do disco)
BTreeNode* disk[MAX_PAGES];
int NUM_PAGES = 0;
int CONTA_LEITURA = 0;
int CONTA_ESCRITA = 0;

// Cria a arvore B com grau minimo t
// Validacoes: t deve estar entre 2 e MAX_ORDER
// Retorna ponteiro para a arvore ou NULL se parametros invalidos
BTree* create_tree(int t) {
    if (t > MAX_ORDER) {
        printf("Erro: O grau t (%d) excede o limite (%d).\n", t, MAX_ORDER);
        return NULL;
    }
    if (t < 2) {
        printf("Erro: O grau t deve ser no minimo 2.\n");
        return NULL;
    }

    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->t = t;
    tree->root_id = -1;

    return tree;
}

// Cria um novo nó em memoria nao salva no disco ainda
BTreeNode* create_node(int is_leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));

    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->page_id = -1;

    for (int i = 0; i < 2 * MAX_ORDER - 1; i++)
        node->keys[i] = -1;

    for (int i = 0; i < 2 * MAX_ORDER; i++)
        node->children[i] = -1;

    return node;
}

// Comando INSERT ou SEARCH do arquivo
int ler_comando_insert_search(char* linha, int* valor) {
    char comando[20];

    if (sscanf(linha, "%19s %d", comando, valor) == 2) {
        if (strcmp(comando, "INSERT") == 0) return 1;
        if (strcmp(comando, "SEARCH") == 0) return 2;
    }
    return -1;
}

// Identifica comando inserido pelo usuario (modo escrita)
int identificar_comando(char* cmd) {
    if (strcmp(cmd, "INSERT") == 0) return 1;
    if (strcmp(cmd, "SEARCH") == 0) return 2;
    return 0;
}

// Escreve comando INSERT no arquivo operacoes.txt
void EscreverInsert(FILE* f, int valor) {
    fprintf(f, "\nINSERT %d", valor);
}

void EscreverSearch(FILE* f, int valor) {
    fprintf(f, "\nSEARCH %d", valor);
}

// Le um no do disco simulado
// Incrementa CONTA_LEITURA para registro de I/O
BTreeNode* disk_read(int node_id) {
    if (node_id == -1) return NULL;
    CONTA_LEITURA++;
    return disk[node_id];
}

// Registra escrita de um no no disco simulado
// Incrementa CONTA_ESCRITA para contabilizar operacoes I/O
void disk_write(int node_id) {
    if (node_id != -1) {
        CONTA_ESCRITA++;
    }
}

// Cria e aloca um novo no no disco simulado
// Incrementa CONTA_ESCRITA automaticamente ao criar
int create_node_in_disk(int is_leaf) {
    BTreeNode* node = create_node(is_leaf);
    
    node->page_id = NUM_PAGES;
    disk[NUM_PAGES] = node;
    NUM_PAGES++;
    CONTA_ESCRITA++;
    return node->page_id;
}

// Realiza busca binaria no no atual e desce recursivamente para o filho apropriado
int btree_search(BTree* tree, int node_id, int key) {
    BTreeNode* node = disk_read(node_id);
    if (node == NULL) return 0;

    int i = 0;

    while (i < node->num_keys && key > node->keys[i])
        i++;

    if (i < node->num_keys && key == node->keys[i])
        return 1;

    if (node->is_leaf)
        return 0;

    return btree_search(tree, node->children[i], key);
}

void btree_split_child(int parent_id, int index, int t) {
    BTreeNode* parent = disk_read(parent_id);
    int full_child_id = parent->children[index];
    BTreeNode* full_child = disk_read(full_child_id);
    int new_child_id = create_node_in_disk(full_child->is_leaf);
    BTreeNode* new_child = disk[new_child_id];

    new_child->num_keys = t - 1;

    for (int j = 0; j < t - 1; j++)
        new_child->keys[j] = full_child->keys[j + t];

    if (!full_child->is_leaf) {
        for (int j = 0; j < t; j++)
            new_child->children[j] = full_child->children[j + t];
    }

    full_child->num_keys = t - 1;

    for (int j = parent->num_keys; j >= index + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[index + 1] = new_child_id;

    for (int j = parent->num_keys - 1; j >= index; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[index] = full_child->keys[t - 1];

    parent->num_keys++;

    disk_write(parent_id);
    disk_write(full_child_id);
}

// Insere chave recursivamente em um no que nao esta cheio
// Se interno: desce para filho apropriado, divide se necessario
void btree_insert_nonfull(int node_id, int key, int t) {
    BTreeNode* node = disk_read(node_id);
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->num_keys++;
        disk_write(node_id);
    }
    else {
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        int child_id = node->children[i];
        BTreeNode* child = disk_read(child_id);

        if (child->num_keys == 2 * t - 1) {
            btree_split_child(node_id, i, t);
            node = disk_read(node_id);
            if (key > node->keys[i])
                i++;
        }

        btree_insert_nonfull(node->children[i], key, t);
    }
}

void btree_insert(BTree* tree, int key) {
    if (tree->root_id == -1) {
        int root_id = create_node_in_disk(1);
        BTreeNode* root = disk[root_id];
        root->keys[0] = key;
        root->num_keys = 1;
        tree->root_id = root_id;
        disk_write(root_id);
        return;
    }

    BTreeNode* root = disk_read(tree->root_id);

    if (root->num_keys == 2 * tree->t - 1) {
        int new_root_id = create_node_in_disk(0);
        BTreeNode* new_root = disk[new_root_id];
        new_root->children[0] = tree->root_id;

        btree_split_child(new_root_id, 0, tree->t);

        int i = 0;
        new_root = disk_read(new_root_id);
        if (key > new_root->keys[0])
            i = 1;

        btree_insert_nonfull(new_root->children[i], key, tree->t);

        tree->root_id = new_root_id;
        disk_write(new_root_id);
    }
    else {
        btree_insert_nonfull(tree->root_id, key, tree->t);
    }
}

// Funcao para imprimir a arvore em ordem hierarquica
void imprimir_arvore(int node_id, int nivel) {
    BTreeNode* node = disk_read(node_id);
    if (node == NULL) return;

    for (int i = 0; i < nivel * 4; i++)
        printf(" ");
    
    printf("Nivel %d: ", nivel);
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d ", node->keys[i]);
    }
    printf("\n");

    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            if (node->children[i] != -1) {
                imprimir_arvore(node->children[i], nivel + 1);
            }
        }
    }
}