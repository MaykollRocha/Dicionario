#include "tadlista.h"

Lista criaLista() {
    t_cabec *cabec = (t_cabec *)malloc(sizeof(t_cabec));
    cabec->tam = 0;
    cabec->cursor_ndx = -1;
    cabec->cursor_ptr = NULL;
    cabec->prim = NULL;
    cabec->ult = NULL;
    return cabec;
}

// Fun��o para adicionar um novo elemento no final da lista
Lista appendLista(Lista l, t_dado dado) {
    t_noh novoNoh = (t_noh)malloc(sizeof(struct tipo_noh));
    novoNoh->dado = dado;
    novoNoh->prox = NULL;

    if (l->tam == 0) {
        // Lista vazia
        novoNoh->ant = NULL;
        l->prim = novoNoh;
        l->ult = novoNoh;
    } else {
        // Lista n�o vazia
        novoNoh->ant = l->ult;
        l->ult->prox = novoNoh;
        l->ult = novoNoh;
    }

    l->tam++;
    return l;
}

// Fun��o para obter o tamanho da lista
int lenLista(Lista l) {
    return l->tam;
}

// Fun��o para obter o dado em uma determinada posi��o da lista
t_dado dadoLista(Lista l, int pos) {
    if (pos < 0 || pos >= l->tam) {
        return NULL; // Posi��o inv�lida
    }

    t_noh atual = l->prim;
    for (int i = 0; i < pos; i++) {
        atual = atual->prox;
    }

    l->cursor_ndx = pos;
    l->cursor_ptr = atual;

    return atual->dado;
}

// Fun��o para inserir um novo elemento em uma posi��o espec�fica da lista
Lista insereLista(Lista l, t_dado dado, int pos) {
    if (pos < 0 || pos > l->tam) {
        return l; // Posi��o inv�lida
    }

    t_noh novoNoh = (t_noh)malloc(sizeof(struct tipo_noh));
    novoNoh->dado = dado;

    if (pos == 0) {
        // Inser��o no in�cio
        novoNoh->ant = NULL;
        novoNoh->prox = l->prim;
        l->prim->ant = novoNoh;
        l->prim = novoNoh;
    } else if (pos == l->tam) {
        // Inser��o no final
        novoNoh->ant = l->ult;
        novoNoh->prox = NULL;
        l->ult->prox = novoNoh;
        l->ult = novoNoh;
    } else {
        // Inser��o no meio
        t_noh atual = l->prim;
        for (int i = 0; i < pos - 1; i++) {
            atual = atual->prox;
        }

        novoNoh->ant = atual;
        novoNoh->prox = atual->prox;
        atual->prox->ant = novoNoh;
        atual->prox = novoNoh;
    }

    l->tam++;
    return l;
}

// Fun��o para remover um elemento em uma posi��o espec�fica da lista
t_dado removeLista(Lista l, int pos) {
    if (pos < 0 || pos >= l->tam) {
        return NULL; // Posi��o inv�lida
    }

    t_noh removido;
    t_dado valorRemovido;

    if (pos == 0) {
        // Remo��o do in�cio
        removido = l->prim;
        valorRemovido = removido->dado;

        l->prim = removido->prox;
        if (l->prim != NULL) {
            l->prim->ant = NULL;
        }

        free(removido);
    } else if (pos == l->tam - 1) {
        // Remo��o do final
        removido = l->ult;
        valorRemovido = removido->dado;

        l->ult = removido->ant;
        l->ult->prox = NULL;

        free(removido);
    } else {
        // Remo��o do meio
        t_noh atual = l->prim;
        for (int i = 0; i < pos; i++) {
            atual = atual->prox;
        }

        removido = atual;
        valorRemovido = removido->dado;

        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;

        free(removido);
    }

    l->tam--;
    return valorRemovido;
}

// Fun��o para destruir a lista, liberando mem�ria
Lista destroiLista(Lista l) {
    while (l->tam > 0) {
        removeLista(l, 0);
    }

    free(l);
    return NULL;
}
