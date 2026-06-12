#include "transformacoes.h"
#include <math.h>
#include <string.h>
#define DEG2RAD(g) ((g) * 3.14159265358979f / 180.0f)


void MatrizCopiar(Matriz dst, const Matriz src) {
    memcpy(dst, src, sizeof(Matriz));
}


void MatrizIdentidade(Matriz m) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                m[i][j] = 1;
            } else {
                m[i][j] = 0;
            }
        }
    }
}


void MatrizMultiplicacao(Matriz resultado, const Matriz a, const Matriz b) {
    int i, j, k;
    Matriz tmp;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            tmp[i][j] = 0;
        }
    }

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            for (k = 0; k < 3; k++){
                tmp[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    MatrizCopiar(resultado, tmp);
}


Ponto MatrizAplicarPonto(const Matriz m, Ponto p) {
    Ponto resultado;
    resultado.x = m[0][0]*p.x + m[0][1]*p.y + m[0][2];
    resultado.y = m[1][0]*p.x + m[1][1]*p.y + m[1][2];
    return resultado;
}


void matTranslacao(Matriz m, float tx, float ty) {
    MatrizIdentidade(m);
    m[0][2] = tx;
    m[1][2] = ty;
}


void matRotacao(Matriz m, float angulo_graus) {
    float rad = DEG2RAD(angulo_graus);
    float cos   = cosf(rad);
    float sen   = sinf(rad);

    MatrizIdentidade(m);
    m[0][0] =  cos;   m[0][1] = -sen;
    m[1][0] =  sen;   m[1][1] =  cos;
}


void matEscala(Matriz m, float sx, float sy) {
    MatrizIdentidade(m);
    m[0][0] = sx;
    m[1][1] = sy;
}


void matReflexaoX(Matriz m) {
    MatrizIdentidade(m);
    m[1][1] = -1;
}


void matReflexaoY(Matriz m) {
    MatrizIdentidade(m);
    m[0][0] = -1;
}


void matCisalhamentoH(Matriz m, float shx) {
    MatrizIdentidade(m);
    m[0][1] = shx;
}


void matCisalhamentoV(Matriz m, float shy) {
    MatrizIdentidade(m);
    m[1][0] = shy;
}


static void aplicarMatrizObjeto(Objeto* obj, const Matriz m) {
    int i;
    switch (obj->tipo) {

        case PONTO:
            obj->ponto = MatrizAplicarPonto(m, obj->ponto);
            break;

        case LINHA:
            obj->linha.ponto_a = MatrizAplicarPonto(m, obj->linha.ponto_a);
            obj->linha.ponto_b = MatrizAplicarPonto(m, obj->linha.ponto_b);
            break;

        case POLIGONO:
            for (i = 0; i < obj->poligono.total; i++)
                obj->poligono.pontos[i] = MatrizAplicarPonto(m, obj->poligono.pontos[i]);
            break;
    }
}


Ponto calcularCentro(const Objeto* obj) {
    Ponto centro = {0, 0};
    int i;
    switch (obj->tipo) {
        case PONTO:
            centro = obj->ponto;
            break;

        case LINHA:
            centro.x = (obj->linha.ponto_a.x + obj->linha.ponto_b.x) / 2;
            centro.y = (obj->linha.ponto_a.y + obj->linha.ponto_b.y) / 2;
            break;

        case POLIGONO:
            for (i = 0; i < obj->poligono.total; i++) {
                centro.x += obj->poligono.pontos[i].x;
                centro.y += obj->poligono.pontos[i].y;
            }
            if (obj->poligono.total > 0) {
                centro.x /= obj->poligono.total;
                centro.y /= obj->poligono.total;
            }
            break;
    }
    return centro;
}


void transladar(Objeto* obj, float dx, float dy) {
    Matriz T;
    matTranslacao(T, dx, dy);
    aplicarMatrizObjeto(obj, T);
}


void rotacionar(Objeto* obj, float angulo_graus) {
    Matriz MatrizIda, MatrizVolta, R, tmp, M;
    Ponto c;

    if (obj->tipo == PONTO) {
        matRotacao(R, angulo_graus);
        aplicarMatrizObjeto(obj, R);
        return;
    }

    c = calcularCentro(obj);

    matTranslacao(MatrizIda,   -c.x, -c.y);
    matRotacao(R,          angulo_graus);
    matTranslacao(MatrizVolta,  c.x,  c.y);
    MatrizMultiplicacao(tmp, R,      MatrizIda);
    MatrizMultiplicacao(M,   MatrizVolta, tmp);
    aplicarMatrizObjeto(obj, M);
}


void escalar(Objeto* obj, float sx, float sy) {
    Matriz MatrizIda, MatrizVolta, S, tmp, M;
    Ponto c;

    if (obj->tipo == PONTO) {
        return;
    }

    c = calcularCentro(obj);

    matTranslacao(MatrizIda,  -c.x, -c.y);
    matEscala(S,          sx,   sy);
    matTranslacao(MatrizVolta,  c.x,  c.y);
    MatrizMultiplicacao(tmp, S,      MatrizIda);
    MatrizMultiplicacao(M,   MatrizVolta, tmp);
    aplicarMatrizObjeto(obj, M);
}


void refletirX(Objeto* obj) {
    Matriz MatrizIda, MatrizVolta, Rx, tmp, M;
    Ponto c = calcularCentro(obj);

    matTranslacao(MatrizIda,  -c.x, -c.y);
    matReflexaoX(Rx);
    matTranslacao(MatrizVolta,  c.x,  c.y);
    MatrizMultiplicacao(tmp, Rx,     MatrizIda);
    MatrizMultiplicacao(M,   MatrizVolta, tmp);
    aplicarMatrizObjeto(obj, M);
}


void refletirY(Objeto* obj) {
    Matriz MatrizIda, MatrizVolta, Ry, tmp, M;
    Ponto c = calcularCentro(obj);

    matTranslacao(MatrizIda,  -c.x, -c.y);
    matReflexaoY(Ry);
    matTranslacao(MatrizVolta,  c.x,  c.y);
    MatrizMultiplicacao(tmp, Ry,     MatrizIda);
    MatrizMultiplicacao(M,   MatrizVolta, tmp);
    aplicarMatrizObjeto(obj, M);
}


void cisalharH(Objeto* obj, float shx) {
    Matriz MatrizIda, MatrizVolta, C, tmp, M;
    Ponto c = calcularCentro(obj);

    matTranslacao(MatrizIda,   -c.x, -c.y);
    matCisalhamentoH(C,    shx);
    matTranslacao(MatrizVolta,  c.x,  c.y);
    MatrizMultiplicacao(tmp, C,      MatrizIda);
    MatrizMultiplicacao(M,   MatrizVolta, tmp);
    aplicarMatrizObjeto(obj, M);
}


void cisalharV(Objeto* obj, float shy) {
    Matriz MatrizIda, MatrizVolta, C, tmp, M;
    Ponto c = calcularCentro(obj);

    matTranslacao(MatrizIda,   -c.x, -c.y);
    matCisalhamentoV(C,    shy);
    matTranslacao(MatrizVolta,  c.x,  c.y);
    MatrizMultiplicacao(tmp, C,      MatrizIda);
    MatrizMultiplicacao(M,   MatrizVolta, tmp);
    aplicarMatrizObjeto(obj, M);
}

