#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texturas.h"
#include <stdio.h>

GLuint carregarTextura(const char* caminho, int* largura, int* altura) {
    int canais;
    unsigned char* dados = stbi_load(caminho, largura, altura, &canais, 4); // 4 = força RGBA

    if (dados == NULL) {
        printf("Erro ao carregar textura: %s\n", caminho);
        return 0;
    }

    GLuint textura;
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *largura, *altura,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, dados);

    stbi_image_free(dados);  // libera a memória da imagem (a textura já está na GPU)
    return textura;
}
