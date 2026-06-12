
#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H
#include "objetos.h"

typedef float Matriz[3][3];

void MatrizCopiar(Matriz dst, const Matriz src);

void MatrizIdentidade(Matriz m);

void MatrizMultiplicacao(Matriz resultado, const Matriz a, const Matriz b);

Ponto MatrizAplicarPonto(const Matriz m, Ponto p);

void matTranslacao(Matriz m, float tx, float ty);

void matRotacao(Matriz m, float angulo_graus);

void matEscala(Matriz m, float sx, float sy);

void matReflexaoX(Matriz m);

void matReflexaoY(Matriz m);

void matCisalhamentoH(Matriz m, float shx);

void matCisalhamentoV(Matriz m, float shy);

void transladar(Objeto* obj, float dx, float dy);

void rotacionar(Objeto* obj, float angulo_graus);

void escalar(Objeto* obj, float sx, float sy);

void refletirX(Objeto* obj);

void refletirY(Objeto* obj);

void cisalharH(Objeto* obj, float shx);

void cisalharV(Objeto* obj, float shy);

Ponto calcularCentro(const Objeto* obj);

#endif

