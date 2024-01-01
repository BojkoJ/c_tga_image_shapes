#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

// Definice typu byte jako neznaménkový 8-bitový char (používá se pro data pixelů)
typedef unsigned char byte;

// Struktura reprezentující hlavičku TGA souboru
typedef struct
{
    byte id_length;      // Délka ID pole (obvykle 0)
    byte color_map_type; // Typ palety barev (0 pro bez palety)
    byte image_type;     // Typ obrázku (např. 2 pro nekomprimovaný RGB)
    byte color_map[5];   // Informace o paletě barev (většinou se nepoužívá)
    byte x_origin[2];    // Pozice X počátku obrázku
    byte y_origin[2];    // Pozice Y počátku obrázku
    byte width[2];       // Šířka obrázku v pixelech
    byte height[2];      // Výška obrázku v pixelech
    byte depth;          // Počet bitů na pixel (např. 32 pro RGBA)
    byte descriptor;     // Popisovač obrázku (např. bitová orientace)
} TGAHeader;

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

// Tato funkce inicializuje obrázek s danou šířkou a výškou.
void initializeImage(Image *image, int width, int height)
{
    // Nastaví šířku a výšku obrázku podle zadaných hodnot.
    image->width = width;
    image->height = height;

    // Alokuje paměť pro pixely obrázku, každý pixel má barvu, takže se násobí počet pixelů velikostí struktury Color.
    image->pixels = (Color *)malloc(width * height * sizeof(Color));

    // Kontrola, jestli se paměť podařilo alokovat. Když ne, vypíše chybu a ukončí program.
    if (image->pixels == NULL)
    {
        printf("Alokace selhala :(\n");
        exit(1);
    }

    // Kontrolní výraz pro ověření, že pixel není NULL.
    assert(image->pixels);

    /* Inicializace všech pixelů na černou barvu. Každý pixel je nastaven na (0,0,0).*/

    for (int i = 0; i < width * height; ++i)
    {
        image->pixels[i] = (Color){0, 0, 0, 255};
    }
}

// Tato funkce inicializuje obrázek s danou šířkou a výškou.
void saveImage(Image *image, const char *filename)
{
    // Otevřeme soubor pro zápis v binárním módu.
    FILE *file = fopen(filename, "wb");
    assert(file); // Ujistíme se, že se soubor podařilo otevřít.

    // Vytvoříme hlavičku TGA souboru s potřebnými informacemi o obrázku.
    TGAHeader header = {
        .id_length = 0,      // Bez dodatečného ID pole.
        .color_map_type = 0, // Bez mapy barev.
        .image_type = 2,     // Typ obrázku: nekomprimovaný true-color.

        // Šířka obrázku rozdělená na dva 8bitové části (little-endian format):
        .width = {
            (byte)(image->width & 0xFF),       // Nižší bajt (LSB - Least Significant Byte) šířky
            (byte)((image->width >> 8) & 0xFF) // Vyšší bajt (MSB - Most Significant Byte) šířky
        },

        // Výška obrázku rozdělená na dva 8bitové části (little-endian format):
        .height = {
            (byte)(image->height & 0xFF),       // Nižší bajt (LSB) výšky
            (byte)((image->height >> 8) & 0xFF) // Vyšší bajt (MSB) výšky
        },

        .depth = 32,       // Počet bitů na pixel: 32 pro RGBA.
        .descriptor = 0x20 // Pořadí pixelů: od horního levého rohu.
    };

    // Zapisujeme hlavičku do souboru.
    fwrite(&header, sizeof(TGAHeader), 1, file);

    // Zapisujeme data pixelů do souboru.
    fwrite(image->pixels, sizeof(Color), image->width * image->height, file);

    // Zavřeme soubor.
    fclose(file);
}

// Funkce pro uvolnění paměti obrázku.
void freeImage(Image *image)
{
    // Uvolníme paměť alokovanou pro pixely obrázku.
    free(image->pixels);
}