#include <stdlib.h>
#include <stdio.h>

#include "objetos.h"

Objeto criaPonto(float x, float y){
    Objeto obj;
    obj.tipo = PONTO;
    obj.ponto.x = x;
    obj.ponto.y = y;
    return obj;
}
Objeto criaLinha(float x1, float y1, float x2, float y2){
    Objeto obj;
    obj.tipo = LINHA;
    obj.linha.ponto_a.x = x1;
    obj.linha.ponto_a.y = y1;
    obj.linha.ponto_b.x = x2;
    obj.linha.ponto_b.y = y2;
    return obj;
}

// essa função cria um vetor de pontos clicados dentro de um objeto do tipo POLIGONO,
// assim fazendo uma cópia própria deles na memória que está sendo alocada dinamicamente,
// isso para que o polígono exista de forma independente enquanto estiver nessa lista.
// no fim, a função retorna o objeto para ele ser inserido na lista encadeada.

Objeto criaPoligono(Ponto* pontos, int quant) {
    Objeto obj;
    obj.tipo = POLIGONO;
    obj.poligono.total = quant;
    obj.poligono.pontos = (Ponto*)malloc(sizeof(Ponto) * quant);
    for (int i = 0; i < quant; i++) {
        obj.poligono.pontos[i] = pontos[i];
    }
    return obj;
}
