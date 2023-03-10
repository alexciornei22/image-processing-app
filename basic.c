#include "utils.h"

void edit(bmp_fileheader *fh, bmp_infoheader *ih, unsigned int ***bitmap) {
    char *path = calloc(PATH_LEN, sizeof(char));  // calea fisierului imagine
    scanf("%s", path);
    FILE *img = fopen(path, "rb");

    // citirea header-ului
    fread(fh, sizeof(bmp_fileheader), 1, img);
    fread(ih, sizeof(bmp_infoheader), 1, img);

    // alocarea dinamica a bitmap-ului
    *bitmap = calloc(ih->height, sizeof(unsigned int *));
    for (unsigned int i = 0; i < ih->height; ++i) {
        (*bitmap)[i] = calloc(ih->width, sizeof(unsigned int));
    }

    // citirea bitmap-ului din imagine
    for (unsigned int i = 0; i < ih->height; ++i) {
        for (unsigned int j = 0; j < ih->width; ++j) {
            fread(&(*bitmap)[i][j], 3, 1, img);
        }
        // ignora octetii de padding, daca e cazul
        fseek(img, ih->width % 4, SEEK_CUR);
    }

    free(path);
    fclose(img);
}

void save(bmp_fileheader fh, bmp_infoheader ih, unsigned int **bitmap) {
    char *path = calloc(PATH_LEN, sizeof(char));  // calea fisierului imagine
    scanf("%s", path);
    FILE *img = fopen(path, "wb");

    // scrierea header-ului
    fwrite(&fh, sizeof(bmp_fileheader), 1, img);
    fwrite(&ih, sizeof(bmp_infoheader), 1, img);

    // scrierea bitmap-ului
    unsigned int x = 0;
    for (int i = 0; i < ih.height; ++i) {
        for (int j = 0; j < ih.width; ++j) {
            fwrite(&bitmap[i][j], 3, 1, img);
        }
        // scrie 0 pe octetii de padding, daca e cazul
        fwrite(&x, ih.width % 4, 1, img);
    }

    free(path);
    fclose(img);
}
