#include <stdlib.h>
#include "quickhull.h"

float distanciaOrientada(Ponto p, Ponto q, Ponto r) {
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

void findHull(Ponto *set, int tam, Ponto p, Ponto q, Ponto *vetSaida, int *idx) {
    if (tam <= 0) {
        return;
    }
    int idxMaisDistante = 0;
    float maiorDist = distanciaOrientada(p, q, set[0]);
    for (int i = 1; i < tam; i++) {
        float d = distanciaOrientada(p, q, set[i]);
        if (d > maiorDist) {
            maiorDist = d;
            idxMaisDistante = i;
        }
    }
    Ponto c = set[idxMaisDistante];
    Ponto *s0 = (Ponto *) malloc(tam * sizeof(Ponto));
    Ponto *s1 = (Ponto *) malloc(tam * sizeof(Ponto));
    int n0 = 0, n1 = 0;
    for (int i = 0; i < tam; i++) {
        if (i == idxMaisDistante) {
            continue;
        }
        Ponto r = set[i];
        if (distanciaOrientada(p, c, r) > 0) {
            s0[n0++] = r;
        } else if (distanciaOrientada(c, q, r) > 0) {
            s1[n1++] = r;
        }
    }
    findHull(s0, n0, p, c, vetSaida, idx);
    vetSaida[(*idx)++] = c;
    findHull(s1, n1, c, q, vetSaida, idx);
    free(s0);
    free(s1);
}

int quickHull(Ponto *pontos, int n, Ponto *vetSaida) {
    if (n < 3) {
        for (int i = 0; i < n; i++) {
            vetSaida[i] = pontos[i];
        }
        return n;
    }
    int idxMin = 0, idxMax = 0;
    for (int i = 1; i < n; i++) {
        if (pontos[i].x < pontos[idxMin].x) idxMin = i;
        if (pontos[i].x > pontos[idxMax].x) idxMax = i;
    }
    Ponto a = pontos[idxMin];
    Ponto b = pontos[idxMax];
    Ponto *acima = (Ponto *) malloc(n * sizeof(Ponto));
    Ponto *abaixo = (Ponto *) malloc(n * sizeof(Ponto));
    int nAcima = 0, nAbaixo = 0;
    for (int i = 0; i < n; i++) {
        if (i == idxMin || i == idxMax) {
            continue;
        }
        float d = distanciaOrientada(a, b, pontos[i]);
        if (d > 0) {
            acima[nAcima++] = pontos[i];
        } else if (d < 0) {
            abaixo[nAbaixo++] = pontos[i];
        }
    }
    int idx = 0;
    vetSaida[idx++] = a;
    findHull(acima, nAcima, a, b, vetSaida, &idx);
    vetSaida[idx++] = b;
    findHull(abaixo, nAbaixo, b, a, vetSaida, &idx);
    free(acima);
    free(abaixo);

    return idx;
}

void converterParaConvexo(Objeto* objetoSelecionado) {
    if (objetoSelecionado == NULL || objetoSelecionado->tipo != POLIGONO) return;

    int n = objetoSelecionado->poligono.total;
    if (n < 3) return;

    Ponto* saida = (Ponto*) malloc(n * sizeof(Ponto));
    int totalSaida = quickHull(objetoSelecionado->poligono.pontos, n, saida);

    if (totalSaida >= 3) {
        free(objetoSelecionado->poligono.pontos);
        objetoSelecionado->poligono.pontos = saida;
        objetoSelecionado->poligono.total = totalSaida;
    } else {
        free(saida);
    }
}
