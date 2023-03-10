#include "utils.h"

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// umplerea patratului de latura width din jurul unui pixel principal (point P)
void fill_rect(pen_info pen, unsigned **bitmap, bmp_infoheader ih, point P) {
    for (int i = P.x - (pen.width / 2); i <= P.x + (pen.width / 2); ++i) {
        for (int j = P.y - (pen.width / 2); j <= P.y + (pen.width / 2); ++j) {
            if (i >= 0 && j >= 0 && i < ih.height && j < ih.width) {
                bitmap[i][j] = pen.color;
            }

            if (j >= ih.width) {
                break;  // stop daca iese din limitele bitmap-ului
            }
            if (j < 0) {
                j = -1;  // sare peste pixelii
            }
        }

        if (i >= ih.height) {
            break;
        }
        if (i < 0) {
            i = -1;
        }
    }
}

void draw_line(pen_info pen, unsigned int **bitmap, bmp_infoheader ih) {
    point A = pen.A;
    point B = pen.B;
    point current_point;  // pixelul principal curent
    unsigned int max_interval = 0;

    /* determinarea intervalului maxim
    (x max - x min) sau (y max - y min) */
    max_interval = abs(A.x - B.x);
    if (max_interval < abs(A.y - B.y)) {
        max_interval = abs(A.y - B.y);
    }

    /* determina coordonatele pixelilor principali
    si umple patratele din jurul acestora */
    if (max_interval == abs(A.x - B.x)) {  // intervalul maxim e pe axa x
        int minn = min(A.x, B.x);
        int maxx = max(A.x, B.x);

        for (int i = minn; i <= maxx; ++i) {
            current_point.x = i;
            current_point.y = (i - A.x) * (B.y - A.y) + A.y * (B.x - A.x);
            current_point.y /= (B.x - A.x);
            fill_rect(pen, bitmap, ih, current_point);
        }
    } else {  // intervalul maxim e pe axa y
        int minn = min(A.y, B.y);
        int maxx = max(A.y, B.y);

        for (int i = minn; i <= maxx; ++i) {
            current_point.y = i;
            current_point.x = (i - A.y) * (B.x - A.x) + A.x * (B.y - A.y);
            current_point.x /= (B.y - A.y);
            fill_rect(pen, bitmap, ih, current_point);
        }
    }
}

void draw_tri(pen_info pen, unsigned int **bitmap, bmp_infoheader ih) {
    point A, B, C;  // punctele triunghiului
    scanf("%d%d", &A.y, &A.x);
    scanf("%d%d", &B.y, &B.x);
    scanf("%d%d", &C.y, &C.x);

    // deseneaza laturile triunghiului
    pen.A = A, pen.B = B;
    draw_line(pen, bitmap, ih);
    pen.A = A, pen.B = C;
    draw_line(pen, bitmap, ih);
    pen.A = B, pen.B = C;
    draw_line(pen, bitmap, ih);
}

void draw_rect(pen_info pen, unsigned int **bitmap, bmp_infoheader ih) {
    point A, B, C, D;  // punctele dreptunghiului
    int rect_width = 0, rect_height = 0;
    scanf("%d%d", &A.y, &A.x);
    scanf("%d%d", &rect_width, &rect_height);

    // afla coordonatele celorlalte puncte
    B.x = A.x, B.y = A.y + rect_width;
    C.x = A.x + rect_height, C.y = A.y;
    D.x = A.x + rect_height, D.y = A.y + rect_width;

    // deseneaza laturile dreptunghiului
    pen.A = A, pen.B = B;
    draw_line(pen, bitmap, ih);
    pen.A = A, pen.B = C;
    draw_line(pen, bitmap, ih);
    pen.A = B, pen.B = D;
    draw_line(pen, bitmap, ih);
    pen.A = C, pen.B = D;
    draw_line(pen, bitmap, ih);
}
