#include "utils.h"

void insert(bmp_fileheader fh, bmp_infoheader ih, unsigned int **bitmap) {
    char *path = calloc(PATH_LEN, sizeof(char));
    unsigned int x = 0, y = 0;  // coordonatele de la care incepe inserarea

    scanf("%s", path);
    scanf("%u%u", &y, &x);
    FILE *ins_img = fopen(path, "rb");

    unsigned int ins_offset = 0;  // offset-ul imaginii de inserat
    unsigned int ins_width = 0;  // latimea imaginii de inserat
    unsigned int ins_height = 0;  // inaltimea imaginii de inserat

    // citirea datelor din imaginea ce trebuie inserata
    fseek(ins_img, 2 * (sizeof(char) + sizeof(unsigned int)), SEEK_SET);
    fread(&ins_offset, sizeof(unsigned int), 1, ins_img);
    fseek(ins_img, sizeof(unsigned int), SEEK_CUR);
    fread(&ins_width, sizeof(unsigned int), 1, ins_img);
    fread(&ins_height, sizeof(unsigned int), 1, ins_img);

    // citirea bitmap-ului imaginii inserate
    unsigned int **ins_bitmap = calloc(ins_height, sizeof(unsigned int *));
    fseek(ins_img, ins_offset, SEEK_SET);
    for (unsigned int i = 0; i < ins_height; ++i) {
        ins_bitmap[i] = calloc(ins_width, sizeof(unsigned int));
        for (unsigned int j = 0; j < ins_width; ++j) {
            fread(&ins_bitmap[i][j], 3, 1, ins_img);
        }
        fseek(ins_img, ins_width % 4, SEEK_CUR);
    }

    // coordonatele punctului curent din ins_img
    unsigned int ins_x = 0, ins_y = 0;
    for (unsigned int i = x; ins_x < ins_height && i < ih.height; ++i) {
        for (unsigned int j = y; ins_y < ins_width && j < ih.width; ++j) {
            bitmap[i][j] = ins_bitmap[ins_x][ins_y];
            ins_y++;
        }
        ins_y = 0;
        ins_x++;
    }

    // dezalocarea imaginii de inserat
    for (unsigned int i = 0; i < ins_height; ++i) {
        free(ins_bitmap[i]);
    }
    free(ins_bitmap);
    free(path);
    fclose(ins_img);
}

void set(pen_info *pen, fill_info *fill_data) {
    char *set_comm = calloc(COMM_LEN, sizeof(char));
    scanf("%s", set_comm);

    if (set_comm[0] == 'd') {  // cazul "set draw_color"
        unsigned int R = 0, G = 0, B = 0;
        scanf("%u%u%u", &R, &G, &B);

        pen->color = B;
        pen->color += (G << BYTE_SIZE * sizeof(char));
        pen->color += (R << BYTE_SIZE * sizeof(short));
        fill_data->color = pen->color;
    } else {  // cazul "set line_width"
        scanf("%d", &pen->width);
    }

    free(set_comm);
}

void draw(pen_info pen, unsigned int **bitmap, bmp_infoheader ih) {
    char *draw_comm = calloc(COMM_LEN, sizeof(char));
    scanf("%s", draw_comm);

    switch (draw_comm[0]) {
        case 'l':  // cazul "draw line"
            scanf("%d%d", &pen.A.y, &pen.A.x);
            scanf("%d%d", &pen.B.y, &pen.B.x);

            draw_line(pen, bitmap, ih);
            break;
        case 'r':  // cazul "draw rectangle"
            draw_rect(pen, bitmap, ih);
            break;
        case 't':  // cazul "draw triangle"
            draw_tri(pen, bitmap, ih);
            break;

        default:
            break;
    }

    free(draw_comm);
}

void fill(fill_info *fill_data, unsigned int **bitmap) {
    int lin = fill_data->start_point.x;  // linia curenta
    int col = fill_data->start_point.y;  // coloana curenta

    if (lin >= 0 && col >= 0 && lin < fill_data->height
    && col < fill_data->width && bitmap[lin][col] == fill_data->start_color) {
        // modifica pixelul in culoarea setata
        bitmap[lin][col] = fill_data->color;

        // trece la pixelul de sus
        fill_data->start_point.x = lin + 1;
        fill_data->start_point.y = col;
        fill(fill_data, bitmap);

        // trece la pixelul de jos
        fill_data->start_point.x = lin - 1;
        fill_data->start_point.y = col;
        fill(fill_data, bitmap);

        // trece la pixelul din dreapta
        fill_data->start_point.x = lin;
        fill_data->start_point.y = col + 1;
        fill(fill_data, bitmap);

        // trece la pixelul din stanga
        fill_data->start_point.x = lin;
        fill_data->start_point.y = col - 1;
        fill(fill_data, bitmap);
    }
}
