#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
#include "objetos.h"

typedef struct No {
    Objeto objeto;
    struct No* proximo;
} No;

No*  criarNo(Objeto obj);
void inserirLista(Objeto obj);
void removerLista(Objeto obj);
void buscarLista(Objeto obj);
void limparLista();

#endif
