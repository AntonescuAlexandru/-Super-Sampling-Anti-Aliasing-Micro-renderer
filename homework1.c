#include "homework1.h"

int num_threads;
int resolution;

void *threadFunction(void *var)
{
    threadFunctionParams params = *(threadFunctionParams *)var;
    image *im = params.im;
    int threadID = params.threadID;
    int intervalSize = ceil((float)resolution / num_threads);
    int low = threadID * intervalSize;
    int high = fmin((threadID + 1) * intervalSize, resolution);

    int i, j;
    double pixelL;
    pixelL = 100.f / resolution;
    double sa2b2 = sqrt(5.f);
    double distance;
    double x, y;

    for (i = low; i < high; i++)
    {
        for (j = 0; j < resolution; j++)
        {
            x = j * pixelL + pixelL / 2.f;
            y = 100.f - i * pixelL - pixelL / 2.f;
            distance = abs((-1.f) * x + 2.f * y) / sa2b2;
            if (distance < 3.f)
            {
                im->map[i * resolution + j] = BLACK;
            }
            else
            {
                im->map[i * resolution + j] = WHITE;
            }
        }
    }
}

void initialize(image *im) {
    im->map = calloc(resolution * resolution, sizeof(char));
}

void render(image *im) {
    int i;
    pthread_t tid[num_threads];
    int thread_id[num_threads];
    for (i = 0; i < num_threads; i++)
    {
        thread_id[i] = i;
    }

    threadFunctionParams params[num_threads];

    for (i = 0; i < num_threads; i++)
    {
        params[i].threadID = thread_id[i];
        params[i].im = im;
        pthread_create(&(tid[i]), NULL, threadFunction, &params[i]);
    }

    for (i = 0; i < num_threads; i++)
    {
        pthread_join(tid[i], NULL);
    }
}

void writeData(const char * fileName, image *img) {
    FILE *f;
    f = fopen(fileName, "wb");
    fwrite("P5", sizeof(char), 2, f);
    fwrite("\n", sizeof(char), 1, f);
    fprintf(f, "%hu %hu\n", resolution, resolution);
    fprintf(f, "255\n");

    
    fwrite(img->map, sizeof(char), resolution * resolution, f);
    
    free(img->map);
    fclose(f);

}

