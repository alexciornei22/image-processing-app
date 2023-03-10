#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bmp_header.h"

#define COMM_LEN 20
#define PATH_LEN 100
#define BYTE_SIZE 8

/* coordonatele unui punct din bitmap
(linia - x, coloana - y) */
typedef struct {
    int x, y;
} point;

// date necesare ale pen-ului pentru trasarea unei linii
typedef struct {
    point A, B;  // punctele intre care se deseneaza linia
    unsigned int color;  // culoarea penului
    int width;  // latimea penului
} pen_info;

// date necesare pentru realizarea operatiei de fill
typedef struct {
    point start_point;  // punctul de la care incepe fill-ul
    unsigned int start_color;  // culoarea punctul de start
    unsigned int color;  // culoarea de umplere
    unsigned int width;  // latimea bitmap-ului
    unsigned int height;  // inaltimea bitmap-ului
} fill_info;

void edit(bmp_fileheader *fh, bmp_infoheader *ih, unsigned int ***bitmap);
void save(bmp_fileheader fh, bmp_infoheader ih, unsigned int **bitmap);
void insert(bmp_fileheader fh, bmp_infoheader ih, unsigned int **bitmap);
void set(pen_info *pen, fill_info *fill_data);
void draw(pen_info pen, unsigned int **bitmap, bmp_infoheader ih);

// deseneaza linie
void draw_line(pen_info pen, unsigned int **bitmap, bmp_infoheader ih);
// deseneaza triunghi
void draw_tri(pen_info pen, unsigned int **bitmap, bmp_infoheader ih);
// deseneaza dreptunghi
void draw_rect(pen_info pen, unsigned int **bitmap, bmp_infoheader ih);

// fill recursiv
void fill(fill_info *fill_data, unsigned int **bitmap);
