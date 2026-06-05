#include <stdlib.h>
#include <stdio.h>

#include "objetos.h"
#include "listaEncadeada.h"

#define T 6

extern No* lista;

int selecionaPonto(Ponto ponto, float mx, float my){
    if (mx<=ponto.x+T && mx>= ponto.x - T){
        if(my<=ponto.y+T && my >= ponto.y-T){
            return 1;
        }
    }
    return 0;
}

Objeto* selecionaObjetos(float mx, float my){
    No* atual = lista;
    while (atual != NULL){
        if (atual->objeto.tipo==PONTO){
            if(selecionaPonto(atual->objeto.ponto,mx,my)){
                return &atual->objeto;
            }
        }
        atual = atual->proximo;
    }
    return NULL;
}
