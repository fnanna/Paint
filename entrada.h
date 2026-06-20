#ifndef ENTRADA_H
#define ENTRADA_H

typedef enum{
    CRIAR_PONTO,
    CRIAR_LINHA_P1,
    CRIAR_LINHA_P2,
    CRIAR_POLIGONO,
    SELECAO,
    DELETAR,
}Estado;

void mouseClick(int botao, int state, int x, int y);
void teclado(unsigned char key, int x, int y);

#endif
