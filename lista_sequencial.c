#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} ListaSequencial;

ListaSequencial create_list() {
    ListaSequencial list;
    list.size = 0;
    return list;
}

int is_empty(ListaSequencial *list) {
    return list->size == 0;
}

int is_full(ListaSequencial *list) {
    return list->size == MAX_SIZE;
}

int get_size(ListaSequencial *list) {
    return list->size;
}

int insert_element(ListaSequencial *list, int posicao, int value) {
    if (posicao < 1 || posicao > list->size + 1 || is_full(list)) {
        return -1;
    }
    for (int i = list->size - 1; i >= posicao - 1; i--) {
        list->data[i + 1] = list->data[i];
    }
    list->data[posicao - 1] = value;
    list->size++;
    return 0;
}

int remove_element(ListaSequencial *list, int posicao) {
    if (posicao < 1 || posicao > list->size) { 
        return -1; 
    }

    for (int i = posicao - 1; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->size--; 
    return 0; 
}


int get_element(ListaSequencial *list, int posicao, int *value) {
    if (posicao < 1 || posicao > list->size) {
        return -1;
    }
    *value = list->data[posicao - 1];
    return 0;
}

int set_element(ListaSequencial *list, int posicao, int value) {
    if (posicao < 1 || posicao > list->size) {
        return -1;
    }
    list->data[posicao - 1] = value;
    return 0;
}

int main() {

    // Criando e verificando se a lista está vazia
    ListaSequencial list = create_list();
    printf("Teste 1: Nova lista esta vazia: %s\n", is_empty(&list) ? "Passou" : "Falhou");

    // Insere um elemento (10) na posição 1 e verifica sucesso
    int result = insert_element(&list, 1, 10);
    printf("Teste 2: Inserir em lista vazia na posicao 1: %s\n", result == 0 ? "Passou" : "Falhou");
    printf("Tamanho apos insercao: %d (esperado 1)\n", get_size(&list));

    // Obtém o elemento na posição 1 e verifica se é 10
    int value;
    result = get_element(&list, 1, &value);
    printf("Teste 3: Obter elemento na posicao 1: %s (valor=%d, esperado 10)\n", result == 0 && value == 10 ? "Passou" : "Falhou", value);

    // Insere 20 na posição 1 (empurrando o 10 para a posição 2)
    result = insert_element(&list, 1, 20);
    printf("Teste 4: Inserir na posicao 1 (tamanho 1 -> 2): %s\n", result == 0 ? "Passou" : "Falhou");
    get_element(&list, 1, &value);
    printf("Elemento na posicao 1 agora eh 20: %s\n", value == 20 ? "Passou" : "Falhou");
    get_element(&list, 2, &value);
    printf("Elemento na posicao 2 eh 10: %s\n", value == 10 ? "Passou" : "Falhou");

    // Inserção no final da lista
    result = insert_element(&list, 3, 30);
    printf("Teste 5: Inserir no final (posicao 3): %s\n", result == 0 ? "Passou" : "Falhou");
    printf("Tamanho agora: %d (esperado 3)\n", get_size(&list));
    get_element(&list, 1, &value);
    printf("Elemento na posicao 1 agora eh 20: %s\n", value == 20 ? "Passou" : "Falhou");
    get_element(&list, 2, &value);
    printf("Elemento na posicao 2 eh 10: %s\n", value == 10 ? "Passou" : "Falhou");
    get_element(&list, 3, &value);
    printf("Elemento na posicao 3 eh 30: %s\n", value == 30 ? "Passou" : "Falhou");

    // Remover um elemento do meio
    result = remove_element(&list, 2);
    printf("Teste 6: Remover da posicao 2: %s\n", result == 0 ? "Passou" : "Falhou");
    get_element(&list, 1, &value);
    printf("Elemento 1 eh 20: %s\n", value == 20 ? "Passou" : "Falhou");
    get_element(&list, 2, &value);
    printf("Elemento 2 eh 30: %s\n", value == 30 ? "Passou" : "Falhou");
    printf("Tamanho apos remocao: %d (esperado 2)\n", get_size(&list));

    // Tentativa de inserção em posição inválida (0)
    result = insert_element(&list, 0, 5);
    printf("Teste 7: Inserir na posicao 0: %s (deve falhar)\n", result == -1 ? "Falhou" : "Passou");

    // Tentativa de inserção em posição maior que o tamanho atual
    result = insert_element(&list, 4, 5);
    printf("Teste 8: Inserir na posicao 4 com tamanho 2: %s (deve falhar)\n", result == -1 ? "Falhou" : "Passou");

    // Inserção no meio
    insert_element(&list, 2, 15);
    printf("Teste 9: Inserir 15 na posicao 2: %s\n", get_element(&list, 2, &value) == 0 && value == 15 ? "Passou" : "Falhou");

    // Reinicializa a lista antes do Teste 10
    while (!is_empty(&list)) {
        remove_element(&list, 1);
    }
    insert_element(&list, 1, 20);
    insert_element(&list, 2, 10);
    insert_element(&list, 3, 30);

    // Teste 10: Remover elemento na posição 2
    remove_element(&list, 2);
    printf("Teste 10: Remover elemento na posicao 2: %s\n", get_element(&list, 2, &value) == 0 && value == 30 ? "Passou" : "Falhou");

    // Reinicializa a lista antes do Teste 11
    while (!is_empty(&list)) {
        remove_element(&list, 1);
    }
    insert_element(&list, 1, 20);
    insert_element(&list, 2, 10);
    insert_element(&list, 3, 30);

    // Teste 11: Inserir e remover 50 na posição 2
    insert_element(&list, 2, 50);
    remove_element(&list, 2);
    printf("Teste 11: Inserir e remover 50 na posicao 2: %s\n", get_element(&list, 2, &value) == 0 && value == 10 ? "Passou" : "Falhou");

    // Teste de inserções repetidas no meio
    insert_element(&list, 2, 5);
    insert_element(&list, 2, 15);
    insert_element(&list, 2, 25);
    printf("Teste 12: Inserir 5, 15, 25 sucessivamente na posicao 2: %s\n", 
        get_element(&list, 2, &value) == 0 && value == 25 &&
        get_element(&list, 3, &value) == 0 && value == 15 &&
        get_element(&list, 4, &value) == 0 && value == 5 ? "Passou" : "Falhou");

    // Preencher a lista até a capacidade máxima
    while (!is_empty(&list)) {
    remove_element(&list, 1);
    }
    for (int i = 1; i <= MAX_SIZE; i++) {  // Começa em 1, não em 3
        insert_element(&list, i, i * 10);
    }
    printf("Teste 13: Lista preenchida ate MAX_SIZE: tamanho %d (esperado %d)\n", get_size(&list), MAX_SIZE);

    // Tentativa de inserir em lista cheia
    if (get_size(&list) == MAX_SIZE) {
        result = insert_element(&list, MAX_SIZE + 1, 1000);
        printf("Teste 14: Inserir com lista cheia: %s\n", result == -1 ? "Passou" : "Falhou");
    } else {
        printf("Teste 14: Lista nao esta cheia. Teste ignorado.\n");
    }

    // Esvaziando a lista completamente
    if (get_size(&list) == MAX_SIZE) {
        for (int i = 1; i <= MAX_SIZE; i++) {
            remove_element(&list, 1);
        }
        printf("Teste 15: Remover todos elementos: tamanho 0? %s\n", is_empty(&list) ? "Passou" : "Falhou");
    } else {
        printf("Teste 15: Lista nao esta cheia. Teste ignorado.\n");
    }
    return 0;
}