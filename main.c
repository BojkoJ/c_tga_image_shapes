#include "./image.h"
#include "./shapes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    // Parsování argumentů příkazové řádky.
    char *outputFilename = NULL;
    int width = 0, height = 0;

    // Projdeme všechny argumenty a uložíme si hodnoty pro šířku, výšku a název souboru.
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "--output") == 0)
        {
            outputFilename = argv[i + 1];
        }
        else if (strcmp(argv[i], "--width") == 0)
        {
            width = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--height") == 0)
        {
            height = atoi(argv[i + 1]);
        }
    }

    // Ověření, že byly argumenty zadány správně.
    if (outputFilename == NULL || width <= 0 || height <= 0)
    {
        fprintf(stderr, "Error: Invalid arguments\n");
        return EXIT_FAILURE;
    }

    // Inicializace obrázku s danou šířkou a výškou.
    Image image;
    initializeImage(&image, width, height);

    // Zpracování příkazů od uživatele.
    char line[256]; // Předpokládáme maximální délku řádku 255 znaků.
    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        char command[20];
        int values[9];
        if (sscanf(line, "%s", command) == 1)
        {
            if (strcmp(command, "line") == 0)
            {
                if (sscanf(line, "%s %d,%d,%d,%d,%d,%d,%d,%d",
                           command, &values[0], &values[1], &values[2], &values[3],
                           &values[4], &values[5], &values[6], &values[7]) == 9)
                {
                    drawLine(&image, values[0], values[1], values[2], values[3],
                             (Color){values[4], values[5], values[6], values[7]});
                }
                else
                {
                    fprintf(stderr, "Error: Invalid command for line\n");
                    freeImage(&image);
                    return EXIT_FAILURE;
                }
            }
            else if (strcmp(command, "rectangle") == 0)
            {
                if (sscanf(line, "%s %d,%d,%d,%d,%d,%d,%d,%d",
                           command, &values[0], &values[1], &values[2], &values[3],
                           &values[4], &values[5], &values[6], &values[7]) == 9)
                {
                    drawRectangle(&image, values[0], values[1], values[2], values[3],
                                  (Color){values[4], values[5], values[6], values[7]});
                }
                else
                {
                    fprintf(stderr, "Error: Invalid command for rectangle\n");
                    freeImage(&image);
                    return EXIT_FAILURE;
                }
            }
            else if (strcmp(command, "circle") == 0)
            {
                if (sscanf(line, "%s %d,%d,%d,%d,%d,%d,%d",
                           command, &values[0], &values[1], &values[2], &values[3],
                           &values[4], &values[5], &values[6]) == 8)
                {
                    drawCircle(&image, values[0], values[1], values[2],
                               (Color){values[3], values[4], values[5], values[6]});
                }
                else
                {
                    fprintf(stderr, "Error: Invalid command for circle\n");
                    freeImage(&image);
                    return EXIT_FAILURE;
                }
            }
            else if (strcmp(command, "triangle") == 0)
            {
                if (sscanf(line, "%s %d,%d,%d,%d,%d,%d,%d",
                           command, &values[0], &values[1], &values[2], &values[3],
                           &values[4], &values[5], &values[6]) == 8)
                {
                    drawTriangle(&image, values[0], values[1], values[2],
                                 (Color){values[3], values[4], values[5], values[6]});
                }
                else
                {
                    fprintf(stderr, "Error: Invalid command for triangle\n");
                    freeImage(&image);
                    return EXIT_FAILURE;
                }
            }
            else if (strcmp(command, "rotated-rectangle") == 0)
            {
                if (sscanf(line, "%s %d,%d,%d,%d,%d,%d,%d,%d,%d",
                           command, &values[0], &values[1], &values[2], &values[3],
                           &values[4], &values[5], &values[6], &values[7], &values[8]) == 10)
                {
                    drawRotatedRectangle(&image, values[0], values[1], values[2], values[3], values[4],
                                         (Color){values[5], values[6], values[7], values[8]});
                }
                else
                {
                    fprintf(stderr, "Chyba: špatné parametry pro otočený obdélník\n");
                    freeImage(&image);
                    return EXIT_FAILURE;
                }
            }
            else if (strcmp(command, "save") == 0)
            {
                saveImage(&image, outputFilename);
            }
            else if (strcmp(command, "exit") == 0)
            {
                saveImage(&image, outputFilename);
                freeImage(&image);
                return EXIT_SUCCESS;
            }
        }
        else
        {
            printf("Chyba: špatný příkaz\n");
            freeImage(&image);
            return EXIT_FAILURE;
        }
    }

    // Po dokončení všech operací uvolníme paměť a ukončíme program.
    freeImage(&image);
    return EXIT_SUCCESS;
}