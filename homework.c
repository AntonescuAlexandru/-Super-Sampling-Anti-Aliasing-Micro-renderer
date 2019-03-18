#include "homework.h"

int num_threads;
int resize_factor;
int gaussianKernel[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

void readInput(const char * fileName, image *img) {
    FILE *f;
    char garbage[4];
    f = fopen(fileName, "rb");
    fread(&img->type, sizeof(char), 2, f);
    fread(&garbage, sizeof(char), 1, f);
    
    fscanf(f, "%hu %hu\n", &img->width, &img->height);
    fscanf(f, "%hu\n", &img->valSize);

    if(strncmp(img->type, "P6", 2) == 0){
        img->rgb = calloc(img->width * img->height * 3, sizeof(char));
        fread(img->rgb, sizeof(char), img->width * img->height * 3, f);
    } else {
        img->grayScale = calloc(img->width * img->height, sizeof(char));
        fread(img->grayScale, sizeof(char), img->width * img->height, f);
    }
    fclose(f);
}

void writeData(const char * fileName, image *img) {
    FILE *f;
    f = fopen(fileName, "wb");
    fwrite(&img->type, sizeof(char), 2, f);
    fwrite("\n", sizeof(char), 1, f);
    fprintf(f, "%hu %hu\n", img->width, img->height);
    fprintf(f, "%hu\n", img->valSize);
    
    if(strncmp(img->type, "P6", 2) == 0) {
        fwrite(img->rgb, sizeof(char), img->width * img->height * 3, f);
    } else {
        fwrite(img->grayScale, sizeof(char), img->width * img->height, f);
    }
    
    fclose(f);
}

void* threadFunction(void *var) {   
    threadFunctionParams params = *(threadFunctionParams*) var;
    image *in = params.in;
    image *out = params.out;
    int threadID = params.threadID;
    int intervalSize = ceil((float)out->height / num_threads);
    int low = threadID * intervalSize;
    int high = fmin((threadID + 1) * intervalSize, out->height);
        
    int i,j,k,p;    
    for (i = low; i < high; i++) {
        for (j = 0; j < out->width; j++) {
            unsigned int sum = 0;
            unsigned int sumRgb[3];
            sumRgb[0] = 0;
            sumRgb[1] = 0;
            sumRgb[2] = 0;

            int pos = i * resize_factor * in->width + j * resize_factor;
            for (k = 0; k < resize_factor; k++) {
                for (p = 0; p < resize_factor; p++) {
                    if (strncmp(out->type, "P6", 2) == 0) {
                        if(resize_factor != 3) {
                            sumRgb[0] += in->rgb[pos + k * in->width + p].r;
                            sumRgb[1] += in->rgb[pos + k * in->width + p].g;
                            sumRgb[2] += in->rgb[pos + k * in->width + p].b;
                        } else {
                            sumRgb[0] += in->rgb[pos + k * in->width + p].r * gaussianKernel[k * 3 + p];
                            sumRgb[1] += in->rgb[pos + k * in->width + p].g * gaussianKernel[k * 3 + p];
                            sumRgb[2] += in->rgb[pos + k * in->width + p].b * gaussianKernel[k * 3 + p];
                        }
                    }
                    else {
                        if (resize_factor != 3) {
                            sum += in->grayScale[pos + k * in->width + p];
                        } else {
                            sum += in->grayScale[pos + k * in->width + p] * gaussianKernel[k * 3 + p];
                        }
                    }
                }
            }
            if (strncmp(out->type, "P6", 2) == 0) {
                if (resize_factor != 3) {
                    sumRgb[0] = sumRgb[0] / (resize_factor * resize_factor);
                    sumRgb[1] = sumRgb[1] / (resize_factor * resize_factor);
                    sumRgb[2] = sumRgb[2] / (resize_factor * resize_factor);
                } else {
                    sumRgb[0] = sumRgb[0] / 16;
                    sumRgb[1] = sumRgb[1] / 16;
                    sumRgb[2] = sumRgb[2] / 16;
                }
                out->rgb[i * out->width + j].r = sumRgb[0];
                out->rgb[i * out->width + j].g = sumRgb[1];
                out->rgb[i * out->width + j].b = sumRgb[2];
            }
            else {
                if (resize_factor != 3) {
                    sum = sum / (resize_factor * resize_factor);
                } else {
                    sum = sum / 16;
                }
                    out->grayScale[i * out->width + j] = sum;
            }
        }
    }
}

void resize(image *in, image * out) { 
    int i;
    out->width = in->width / resize_factor;
    out->height = in->height / resize_factor;
    memcpy(out->type, in->type, 2);
    out->valSize = in->valSize;
    
    if (strncmp(out->type, "P6", 2) == 0) {
        out->rgb = calloc(out->width * out->height * 3, sizeof(char));
    } else {
        out->grayScale = calloc(out->width * out->height, sizeof(char));
    }

    pthread_t tid[num_threads];
    int thread_id[num_threads];
    for (i = 0; i < num_threads; i++){
        thread_id[i] = i;
    }
    
    threadFunctionParams params[num_threads];

    for (i = 0; i < num_threads; i++) {
        params[i].threadID = thread_id[i];
        params[i].in = in;
        params[i].out = out;
        pthread_create(&(tid[i]), NULL, threadFunction, &params[i]);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(tid[i], NULL);
    }
}