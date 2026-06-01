#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include "objetos.h"

typedef struct No {
    Objeto objeto;
    struct No* proximo;
} No;

No*  criarNo(Objeto obj);
void inserir(No** lista, Objeto obj);
void remover(No** lista, Objeto obj);
void buscar(No* lista,Objeto obj);
void limpar(No** lista);

#endif
