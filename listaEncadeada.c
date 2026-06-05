#include <stdlib.h>
#include <stdio.h>
#include "listaEncadeada.h"

No* lista = NULL;

No* criarNo(Objeto obj) {
    No* novo = (No*)malloc(sizeof(No));
    novo->objeto = obj;
    novo->proximo = NULL;
    return novo;
}

void inserirLista(Objeto obj) {
    No* novo = criarNo(obj);
    novo->proximo = lista;
    lista = novo;
}

void removerLista(Objeto obj) {
    No* atual = lista;
    No* anterior = NULL;
    while (atual != NULL) {
        int igual = 0;
        if (atual->objeto.tipo == obj.tipo) {
            if (obj.tipo == PONTO) {
                igual = (atual->objeto.ponto.x == obj.ponto.x &&
                         atual->objeto.ponto.y == obj.ponto.y);
            } else if (obj.tipo == LINHA) {
                igual = (atual->objeto.linha.ponto_a.x == obj.linha.ponto_a.x &&
                         atual->objeto.linha.ponto_a.y == obj.linha.ponto_a.y &&
                         atual->objeto.linha.ponto_b.x == obj.linha.ponto_b.x &&
                         atual->objeto.linha.ponto_b.y == obj.linha.ponto_b.y);
            }
        }
        if (igual) {
            if (anterior == NULL)
                lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            if (atual->objeto.tipo == POLIGONO && atual->objeto.poligono.pontos)
                free(atual->objeto.poligono.pontos);

            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }
}

void buscarLista(Objeto obj) {
    No* atual = lista;
    int indice = 0;
    while (atual != NULL) {
        if (atual->objeto.tipo == obj.tipo)
            printf("objeto encontrado\n");
        atual = atual->proximo;
        indice++;
    }
}

void limparLista() {
    No* atual = lista;
    while (atual != NULL) {
        No* prox = atual->proximo;
        if (atual->objeto.tipo == POLIGONO && atual->objeto.poligono.pontos)
            free(atual->objeto.poligono.pontos);
        free(atual);
        atual = prox;
    }
    lista = NULL;
}
