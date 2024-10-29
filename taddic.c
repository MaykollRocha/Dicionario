#include "taddic.h"

Dic criaDic() {
    return criaLista();
}

Dic adDic(Dic d, t_chave k, t_dado valor) {
    t_item novo_item = (t_item)malloc(sizeof(struct item_dic));
    if (novo_item == NULL) {
        perror("Erro ao alocar memória para o item do dicionário");
        exit(EXIT_FAILURE);
    }

    novo_item->key = strdup(k);
    novo_item->valor = valor;

    return appendLista(d, novo_item);
}

int lenDic(Dic d) {
    return lenLista(d);
}

t_dado dadoDic(Dic d, t_chave k) {
    int tamanho = lenLista(d);
    for (int i = 0; i < tamanho; i++) {
        t_item item = (t_item)dadoLista(d, i);
        if (strcmp(item->key, k) == 0) {
            return item->valor;
        }
    }

    return NULL; // Chave não encontrada
}

t_dado removeDic(Dic d, t_chave k) {
    int tamanho = lenLista(d);
    for (int i = 0; i < tamanho; i++) {
        t_item item = (t_item)dadoLista(d, i);
        if (strcmp(item->key, k) == 0) {
            removeLista(d, i);
            t_dado valor = item->valor;
            free(item->key);
            free(item);
            return valor;
        }
    }

    return NULL; // Chave não encontrada
}

Lista keysDic(Dic d) {
    int tamanho = lenLista(d);
    Lista chaves = criaLista();

    for (int i = 0; i < tamanho; i++) {
        t_item item = (t_item)dadoLista(d, i);
        chaves = appendLista(chaves, item->key);
    }

    return chaves;
}

int inDic(Dic d, t_chave k) {
    int tamanho = lenLista(d);
    for (int i = 0; i < tamanho; i++) {
        t_item item = (t_item)dadoLista(d, i);
        if (strcmp(item->key, k) == 0) {
            return 1; // Chave encontrada
        }
    }

    return 0; // Chave não encontrada
}

void print_estats(Dic d) {
    printf("Estatísticas do Dicionário:\n");
    printf("Número de itens: %d\n", lenLista(d));
}
