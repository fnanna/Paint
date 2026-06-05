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
    } else if (atual->objeto.tipo == LINHA) {
            if (selecionaLinha(atual->objeto.linha, mx, my))
                return &atual->objeto;
        }
        atual = atual->proximo;
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

int codificacao(float px, float py, float xmin, float xmax, float ymin, float ymax) {
    int codigo = 0;
    if (px < xmin) {
        codigo |= 1;
    }
    if (px > xmax){
        codigo |= 2;
    }
    if (py < ymin) {
        codigo |= 4;
    }
    if (py > ymax) {
        codigo |= 8;
    }
    return codigo;
}


int selecionaLinha(Linha linha,float mx, float my){
    float xmin = mx - T;
    float xmax = mx + T;
    float ymin = my - T;
    float ymax = my + T;
    float x0 = linha.ponto_a.x;
    float y0 = linha.ponto_a.y;
    float x1 = linha.ponto_b.x;
    float y1 = linha.ponto_b.y;
    while (1) {
        int cod0 = codificacao(x0, y0, xmin, xmax, ymin, ymax);
        int cod1 = codificacao(x1, y1, xmin, xmax, ymin, ymax);
        if ((cod0 | cod1) == 0){
            return 1;
        }
        if (cod0 & cod1){
            return 0;
        }
        int cod;
        if (cod0 != 0) {
            cod = cod0;
        } else {
            cod = cod1;
        }
        float x, y;
        if (cod & 1) {
            y = y0 + (xmin - x0) * (y1 - y0) / (x1 - x0);
            x = xmin;
        } else if (cod & 2) {
            y = y0 + (xmax - x0) * (y1 - y0) / (x1 - x0);
            x = xmax;
        } else if (cod & 4) {
            x = x0 + (ymin - y0) * (x1 - x0) / (y1 - y0);
            y = ymin;
        } else {
            x = x0 + (ymax - y0) * (x1 - x0) / (y1 - y0);
            y = ymax;
        }
        if (cod == cod0) {
            x0 = x; y0 = y;
        } else {
            x1 = x; y1 = y;
        }
    }
}
