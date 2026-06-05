#ifndef SELECAO_H
#define SELECAO_H
#include "objetos.h"

int selecionaPonto(Ponto ponto, float mx, float my);
int selecionaLinha(Linha linha,float mx, float my);
int selecionaPoligono(Poligono poligono, float mx, float my);
Objeto* selecionaObjetos(float mx, float my);

#endif

