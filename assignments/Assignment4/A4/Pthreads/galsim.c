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
double* Fx;
double* Fy;
int n_threads;

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
        d->p[i].velocity_x += dt*Fx[i]/(d->p[i].mass);
        d->p[i].velocity_y += dt*Fy[i]/(d->p[i].mass);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 7) {
        printf("Wrong amount of input arguments: should be 6 \n");
        return 0;
    }
    N = atoi(argv[1]);
    char *filename = argv[2];
    const int nsteps = atoi(argv[3]);
    dt = atof(argv[4]);
    int graphics = atoi(argv[5]);
    n_threads = atoi(argv[6]);

    graphics += 0; //annoying warning
    G = 100.0/N;

    Particle* particles = malloc(sizeof(Particle)*N);
    FILE *file;
    

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    size_t dummy = fread(particles, sizeof(Particle), N, file);
    
    dummy += 0; // again, annoying warning
    fclose(file);

    Data* data = malloc(sizeof(Data)*n_threads);


    int chunk_size = N / n_threads;
    int extra_particles = N % n_threads;
    int start_index = 0;
    for (int i = 0; i < n_threads; i++) {
        data[i].p = particles;

        int thread_chunk = chunk_size + (i < extra_particles ? 1 : 0);

        data[i].start = start_index;
        data[i].stop = start_index + thread_chunk;

        start_index += thread_chunk;
    }

    pthread_t threads[n_threads];
    Fx = malloc(sizeof(double)*N);
    Fy = malloc(sizeof(double)*N);
    
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
        for (int j = 0; j < N; j++) //need to update 
        {
            particles[j].pos_x += dt*(particles[j].velocity_x);
            particles[j].pos_y += dt*(particles[j].velocity_y);
        }
        
    }
    
    free(Fx);
    free(Fy);
    free(data);

    FILE *outputFile; 
    outputFile = fopen("result.gal", "wb");

    if (outputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(particles, sizeof(Particle), N, outputFile);
    fclose(outputFile);

    free(particles);
    
    return 0;
}