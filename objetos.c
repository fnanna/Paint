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
Objeto criaPoligono(){

}
