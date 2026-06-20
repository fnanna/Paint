#ifndef INTERFACE_H
#define INTERFACE_H

#include "entrada.h"

typedef struct {
    float x1, y1, x2, y2;
    Estado estado;
} BotaoGui;

void carregarGui(void);
void desenhaGui(void);
int verificarCliqueGui(float mx, float my);

#endif
