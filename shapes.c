#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Funkce pro kreslení čáry.
void drawLine(Image *image, int x1, int y1, int x2, int y2, Color color)
{
    // Vypočet rozdílů souřadnic X a Y pro určení délky a směru čáry.
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // Určení směru kreslení čáry. Když je x1 menší než x2, čára se bude kreslit zleva doprava a naopak.
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1; // Totéž pro osu Y.

    // Proměnná pro sledování chyby při kreslení.
    int err = dx - dy;

    // Cyklus pro kreslení čáry. Pokračuje, dokud nedojde k poslednímu bodu čáry.
    while (1)
    {
        // Zkontroluje, jestli je bod (x1, y1) v rámci hranic obrázku.
        if (x1 >= 0 && x1 < image->width && y1 >= 0 && y1 < image->height)
        {
            // Výpočet indexu pixelu v poli pixelů.
            int index = y1 * image->width + x1;

            // Výpočet barvy pixelu s ohledem na alfa kanál.
            float alpha = (float)color.a / 255.0f;
            image->pixels[index].r = alpha * color.r + (1.0 - alpha) * image->pixels[index].r;
            image->pixels[index].g = alpha * color.g + (1.0 - alpha) * image->pixels[index].g;
            image->pixels[index].b = alpha * color.b + (1.0 - alpha) * image->pixels[index].b;
            image->pixels[index].a = 255; // Nastavení alfa kanálu na neprůhledný.
        }
        else
        {
            // Pokud je bod mimo obrázek, vypíšeme chybovou hlášku.
            printf("Pixel (%d,%d) zasahuje mimo obrázek :(\n", x1, y1);
        }

        // Podmínka pro ukončení cyklu, když dojdeme k poslednímu bodu čáry.
        if (x1 == x2 && y1 == y2)
            break;

        // Výpočet a aktualizace chyby pro Bresenhamův algoritmus čáry.
        // Zdroj: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// Funkce pro kreslení obdélníku.
void drawRectangle(Image *image, int x, int y, int width, int height, Color color)
{
    // Nejdřív zkontrolujeme, jestli celý obdélník bude uvnitř obrázku.
    if (x < 0 || y < 0 || x + width > image->width || y + height > image->height)
    {
        // Pokud ne, vypíšeme chybovou hlášku a funkci ukončíme.
        printf("Obdélník zasahuje mimo obrázek :(\n");
        return;
    }

    // Cyklus pro vykreslení obdélníku. Projde všechny pixely v oblasti obdélníku.
    for (int i = y; i < y + height; ++i) // Od horního levého y po spodní pravý y
    {
        for (int j = x; j < x + width; ++j) // Od horního levého x po spodní pravý x
        {
            // Vypočítáme index pixelu v poli pixelů obrázku.
            int index = i * image->width + j;

            // Vypočítáme efektivní barvu pixelu s ohledem na alfa kanál.
            float alpha = color.a / 255.0;
            image->pixels[index].r = alpha * color.r + (1.0 - alpha) * image->pixels[index].r;
            image->pixels[index].g = alpha * color.g + (1.0 - alpha) * image->pixels[index].g;
            image->pixels[index].b = alpha * color.b + (1.0 - alpha) * image->pixels[index].b;
            image->pixels[index].a = 255; // Nastavení alfa kanálu na neprůhledný.
        }
    }
}

// Funkce pro vykreslení jednoho pixelu na obrázek, kterou využívá funkce pro kreslení kolečka.
void putPixel(Image *image, int x, int y, Color color)
{
    // Nejdřív zkontrolujeme, jestli je pixel uvnitř hranic obrázku.
    if (x >= 0 && x < image->width && y >= 0 && y < image->height)
    {
        // Vypočítáme index pixelu v poli pixelů obrázku.
        int index = y * image->width + x;

        // Vypočítáme efektivní barvu pixelu s ohledem na alfa kanál.
        float alpha = (float)color.a / 255.0f;
        image->pixels[index].r = alpha * color.r + (1.0 - alpha) * image->pixels[index].r;
        image->pixels[index].g = alpha * color.g + (1.0 - alpha) * image->pixels[index].g;
        image->pixels[index].b = alpha * color.b + (1.0 - alpha) * image->pixels[index].b;
        image->pixels[index].a = 255; // Nastavení alfa kanálu na neprůhledný.
    }
    // Pokud je pixel mimo obrázek, nic se neděje.
}

// Funkce pro kreslení kruhu na obrázek.
void drawCircle(Image *image, int cx, int cy, int radius, Color color)
{
    // Základní proměnné pro algoritmus kreslení kruhu.
    int x = radius;
    int y = 0;
    int err = 0;

    // Cyklus pro kreslení kruhu.
    // Používá Bresenhamův algoritmus kruhu.
    // Zdroj: https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

    while (x >= y)
    {
        // Kreslí osm segmentů kruhu najednou (pro využití symetrie)
        // Viz. animace algoritmu na wiki stránce:
        // Zdroj: https://en.wikipedia.org/wiki/Midpoint_circle_algorithm#/media/File:Midpoint_circle_algorithm_animation_(radius_23).gif
        // Vykreslování probíhá 8 směry - na každé ze 4 stran kruhu do dvou stran.

        putPixel(image, cx + x, cy + y, color);
        putPixel(image, cx + y, cy + x, color);
        putPixel(image, cx - y, cy + x, color);
        putPixel(image, cx - x, cy + y, color);
        putPixel(image, cx - x, cy - y, color);
        putPixel(image, cx - y, cy - x, color);
        putPixel(image, cx + y, cy - x, color);
        putPixel(image, cx + x, cy - y, color);

        // Aktualizace proměnných pro Midpoint (Bresenham) algoritmus.
        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        else
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

// Funkce pro kreslení rovnostranného trojúhelníku.
void drawTriangle(Image *image, int x, int y, int side, Color color)
{
    // Nejdříve vypočítáme výšku trojúhelníku. Pro rovnostranný trojúhelník je to (sqrt(3)/2) * délka strany.
    float height = (sqrt(3) / 2) * side;

    // Vypočteme pozice tří vrcholů trojúhelníku.
    // Vrchol 1 bude přímo nad středem (x, y).
    int x1 = x;
    int y1 = y - (int)(height / 2);

    // Vrchol 2 bude doleva a dolů od středu.
    int x2 = x - (side / 2);
    int y2 = y + (int)(height / 2);

    // Vrchol 3 bude doprava a dolů od středu.
    int x3 = x + (side / 2);
    int y3 = y + (int)(height / 2);

    // Nakreslíme tři strany trojúhelníku:

    // Čára od vrcholu 1 k vrcholu 2.
    drawLine(image, x1, y1, x2, y2, color);
    // Čára od vrcholu 2 k vrcholu 3.
    drawLine(image, x2, y2, x3, y3, color);
    // Čára od vrcholu 3 zpatky k vrcholu 1.
    drawLine(image, x3, y3, x1, y1, color);
}

// Funkce pro kreslení otočeného obdélníku.
void drawRotatedRectangle(Image *image, double angle, int cx, int cy, int width, int height, Color color)
{
    // Nejprve převedeme úhel z stupňů na radiány pro funkce sin a cos.
    double radians = angle * M_PI / 180.0;

    // Vypočteme poloviny šířky a výšky, abychom našli rohy obdélníku.
    int halfWidth = width / 2;
    int halfHeight = height / 2;

    // Definujeme počáteční pozice rohů obdélníku před rotací.
    int cornersX[4] = {cx - halfWidth, cx + halfWidth, cx + halfWidth, cx - halfWidth};
    int cornersY[4] = {cy - halfHeight, cy - halfHeight, cy + halfHeight, cy + halfHeight};

    // Vytvoříme pole pro uložení pozic rotovaných rohů.
    int rotatedX[4];
    int rotatedY[4];

    // Projdeme všechny čtyři rohy a aplikujeme na ně rotační transformaci.
    for (int i = 0; i < 4; i++)
    {
        // Aplikujeme 2D rotační transformaci na každý roh (ze zadání).
        // Otáčíme kolem středu (cx, cy).
        rotatedX[i] = (int)((cornersX[i] - cx) * cos(radians) - (cornersY[i] - cy) * sin(radians) + cx);
        rotatedY[i] = (int)((cornersX[i] - cx) * sin(radians) + (cornersY[i] - cy) * cos(radians) + cy);
    }

    // Nakreslíme čáry mezi novými rotovanými rohy.
    // Vytvoříme tak obdélník, jehož rohy jsou na nově vypočítaných pozicích.
    for (int i = 0; i < 4; i++)
    {
        drawLine(image, rotatedX[i], rotatedY[i], rotatedX[(i + 1) % 4], rotatedY[(i + 1) % 4], color);
    }
}