#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} __attribute__((packed)) rgbStruct;

typedef struct {
    unsigned char type[2];
    unsigned short width;
    unsigned short height;
    unsigned short valSize;
    unsigned char *grayScale;
    rgbStruct *rgb;
} __attribute__((packed)) image;

typedef struct{
    image *in;
    image *out;
    int threadID;
} __attribute__((packed)) threadFunctionParams;

void readInput(const char * fileName, image *img);

void writeData(const char * fileName, image *img);

void resize(image *in, image * out);

#endif /* HOMEWORK_H */