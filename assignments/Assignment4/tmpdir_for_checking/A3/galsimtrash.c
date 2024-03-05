#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define epsilon 1e-3
double G;
double dt;
int N;
int n_threads;
int chunk;
double* Fx;
double* Fy;

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

typedef struct {
    double pos_x; 
    double pos_y; 
    double mass;
    double velocity_x; 
    double velocity_y;
    double brightness;
} Particle;

typedef struct{
    Particle *p;
    int start;
    int stop;
} Data;


void* step(void* data){
    Data *d = (Data *) data;
    for (int i = d->start; i < d->stop; i++) {
        double mg = -G * d->p[i].mass;
        for (int j = 0; j < i; j++) {
            double rx = d->p[i].pos_x - d->p[j].pos_x; 
            double ry = d->p[i].pos_y - d->p[j].pos_y;
            double r = sqrt(rx * rx + ry * ry) + epsilon;
            double unit = mg*(d->p[j].mass) / (r*r*r);

            Fx[i] += rx * unit;
            Fy[i] += ry * unit;
        }
        for (int j = i+1; j < N; j++) {
            double rx = d->p[i].pos_x - d->p[j].pos_x; 
            double ry = d->p[i].pos_y - d->p[j].pos_y;
            double r = sqrt(rx * rx + ry * ry) + epsilon;
            double unit = mg*(d->p[j].mass) / (r*r*r);

            Fx[i] += rx * unit;
            Fy[i] += ry * unit;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 6) {
        printf("Wrong amount of input arguments: should be 5 \n");
        return 0;
    }
    
    N = atoi(argv[1]);
    char *filename = argv[2];
    const int nsteps = atoi(argv[3]);
    dt = atof(argv[4]);
    int graphics = atoi(argv[5]);

    graphics += 0; //annoying warning
    G = 100.0/N;

    Particle* particles = malloc(sizeof(Particle)*N);
    FILE *file;

    double start, end;
    
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    size_t dummy = fread(particles, sizeof(Particle), N, file);
    
    dummy += 0; // again, annoying warning
    fclose(file);

    int n_threads = 10;
    
    Data* data = malloc(sizeof(Data)*n_threads);
    chunk = N/n_threads;
    for (int i = 0; i < n_threads; i++)
    {
        data[i].p = particles;
        data[i].start = i*chunk;
        data[i].stop = (i+1)*chunk;
    }
    pthread_t threads[n_threads];
    Fx = malloc(sizeof(double)*N);
    Fy = malloc(sizeof(double)*N);
    double* massInv = malloc(sizeof(double)*N);

    for (int i = 0; i < N; i++)
    {
        massInv[i] = 1/particles[i].mass;
    }
    
    start = get_wall_seconds();
    for(int i = 0; i<nsteps; i++){ 
        
        for (int j = 0; j < N; j++)
        {
            Fx[j] = 0; //initialization
            Fy[j] = 0;
        }
        
        for (int j = 0; j < n_threads; j++)
        {
            pthread_create(&threads[j], NULL, step, (void *) &data[j]);
        }
        for (int j = 0; j < n_threads; j++)
        {
            pthread_join(threads[j], NULL);
        }
        for (int j = 0; j < N; j++) //test som fan
        {
            particles[j].pos_x += dt*(particles[j].velocity_x);
            particles[j].pos_y += dt*(particles[j].velocity_y);
        }
    }
    end = get_wall_seconds();
    free(Fx);
    free(Fy);
    free(data);
    free(massInv);

    FILE *outputFile; 
    outputFile = fopen("result.gal", "wb");

    if (outputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(particles, sizeof(Particle), N, outputFile);
    fclose(outputFile);

    free(particles);
    
    printf("Time: %lf s\n", end-start);
    
    return 0;
}
