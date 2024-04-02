#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
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

void* step(Particle* p){
    #pragma omp parallel for num_threads(n_threads)
    for (int i = 0; i < N; i++) {
        double mg = -G * p[i].mass;
        double tempFx = 0;
        double tempFy = 0;
        for (int j = 0; j < i; j++) {
            double rx = p[i].pos_x - p[j].pos_x; 
            double ry = p[i].pos_y - p[j].pos_y;
            double r = sqrt(rx * rx + ry * ry) + epsilon;
            double unit = mg*(p[j].mass) / (r*r*r);

            tempFx += rx * unit;
            tempFy += ry * unit;
        }
        for (int j = i+1; j < N; j++) {
            double rx = p[i].pos_x - p[j].pos_x; 
            double ry = p[i].pos_y - p[j].pos_y;
            double r = sqrt(rx * rx + ry * ry) + epsilon;
            double unit = mg*(p[j].mass) / (r*r*r);

            tempFx += rx * unit;
            tempFy += ry * unit;
        }
        Fx[i] = tempFx;
        Fy[i] = tempFy;
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

    printf("%f\n",particles[0].pos_x);

    Fx = malloc(sizeof(double)*N);
    Fy = malloc(sizeof(double)*N);

    
    for(int i = 0; i<nsteps; i++){ 
        for (int j = 0; j < N; j++)
        {
            Fx[j] = 0; //initialization
            Fy[j] = 0;
        }
        step(particles);
        for (int j = 0; j < N; j++) //test som fan
        {
            particles[j].velocity_x += dt*Fx[j]/(particles[j].mass);
            particles[j].velocity_y += dt*Fy[j]/(particles[j].mass);

            particles[j].pos_x += dt*(particles[j].velocity_x);
            particles[j].pos_y += dt*(particles[j].velocity_y);
        }
        
    }
    printf("%f\n",particles[0].pos_x);

    free(Fx);
    free(Fy);

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