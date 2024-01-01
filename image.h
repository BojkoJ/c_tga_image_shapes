#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

// Definice typu byte jako neznaménkový 8-bitový char (používá se pro data pixelů)
typedef unsigned char byte;

// Struktura reprezentující barvu pixelu
typedef struct
{
    byte r; // Červená složka
    byte g; // Zelená složka
    byte b; // Modrá složka
    byte a; // Alfa kanál (průhlednost)
} Color;

// Struktura reprezentující obrázek
typedef struct
{
    int width;     // Šířka obrázku v pixelech
    int height;    // Výška obrázku v pixelech
    Color *pixels; // Pole pixelů (každý pixel má svou barvu)
} Image;

// Funkce pro inicializaci obrázku
void initializeImage(Image *image, int width, int height);

// Funkce pro vykreslení jednoho pixelu (můžete přidat do shapes.h, pokud chcete)
void putPixel(Image *image, int x, int y, Color color);

// Funkce pro uložení obrázku do souboru
void saveImage(const Image *image, const char *filename);

// Funkce pro uvolnění paměti obrázku
void freeImage(Image *image);

#endif
