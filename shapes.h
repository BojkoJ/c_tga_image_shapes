#ifndef SHAPES_H
#define SHAPES_H

#include "image.h"

// Funkce pro kreslení čáry
void drawLine(Image *image, int x1, int y1, int x2, int y2, Color color);

// Funkce pro kreslení obdélníku
void drawRectangle(Image *image, int x, int y, int width, int height, Color color);

// Funkce pro kreslení kruhu
void drawCircle(Image *image, int x, int y, int radius, Color color);

// Funkce pro kreslení rovnostranného trojúhelníku
void drawTriangle(Image *image, int x, int y, int side, Color color);

// Funkce pro kreslení otočeného obdélníku
void drawRotatedRectangle(Image *image, double angle, int x, int y, int width, int height, Color color);

#endif