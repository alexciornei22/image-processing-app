#include "utils.h"

int main() {
    bmp_fileheader fileheader;
    bmp_infoheader infoheader;
    unsigned int **bitmap = NULL;
    infoheader.height = 0;

    pen_info pen;
    fill_info fill_data;

    // command - memoreaza comenzile citite de la tastatura
    char *command = calloc(COMM_LEN, sizeof(char));
    scanf("%s", command);

    // termina atunci cand se citeste "quit"
    while (command[0] != 'q') {
        switch (command[0]) {
            case 's':
                if (command[1] == 'a') {  // save
                    save(fileheader, infoheader, bitmap);
                } else {  // set
                    set(&pen, &fill_data);
                }
                break;
            case 'e':  // edit
                edit(&fileheader, &infoheader, &bitmap);
                break;
            case 'i':  // insert
                insert(fileheader, infoheader, bitmap);
                break;
            case 'd':  // draw
                draw(pen, bitmap, infoheader);
                break;
            case 'f':  // fill
                scanf("%d", &fill_data.start_point.y);
                scanf("%d", &fill_data.start_point.x);

                fill_data.height = infoheader.height;
                fill_data.width = infoheader.width;

                int i = fill_data.start_point.x;
                int j = fill_data.start_point.y;
                fill_data.start_color = bitmap[i][j];
                fill(&fill_data, bitmap);
                break;
            default:
                break;
        }

        scanf("%s", command);
    }

    // dezalocarea memoriei
    free(command);
    for (unsigned int i = 0; i < infoheader.height; ++i) {
        free(bitmap[i]);
    }
    free(bitmap);

    return 0;
}
