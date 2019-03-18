#ifndef HOMEWORK_H1
#define HOMEWORK_H1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define WHITE 255
#define BLACK 0

typedef struct {
    unsigned char *map;
} __attribute__((packed)) image;

typedef struct {
    image *im;
    int threadID;
} __attribute__((packed)) threadFunctionParams;

void initialize(image *im);
void render(image *im);
void writeData(const char * fileName, image *img);

#endif /* HOMEWORK_H1 */