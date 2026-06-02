#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
#include "objetos.h"

typedef struct No {
    Objeto objeto;
    struct No* proximo;
} No;

No* lista;

No*  criarNo(Objeto obj);
void inserir(Objeto obj);
void remover(Objeto obj);
void buscar(Objeto obj);
void limpar();

#endif
