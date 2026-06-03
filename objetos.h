#ifndef OBJETOS_H
#define OBJETOS_H

typedef struct{
    float x;
    float y;
}Ponto;

typedef struct{
    Ponto ponto_a;
    Ponto ponto_b;
}Linha;

typedef struct{
    Ponto* pontos;
    int total;
}Poligono;

typedef enum{
    PONTO,
    LINHA,
    POLIGONO
}TipoObjeto;

typedef struct{
    TipoObjeto tipo;
    union{
        Ponto ponto;
        Linha linha;
        Poligono poligono;
    };
}Objeto;

Objeto criaPonto(float x, float y);
Objeto criaLinha(float x1, float y1, float x2, float y2);
Objeto criaPoligono(Ponto* pontos, int quant);


#endif
