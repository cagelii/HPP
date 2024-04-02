#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define epsilon 1e-3

typedef struct {
    double pos_x; 
    double pos_y; 
    double mass;
    double velocity_x; 
    double velocity_y;
    double brightness;
} Particle;

void simulation(double G, int N, Particle *p, double dt, int timesteps){
    double* Fx=malloc(sizeof(double)*N);
    double* Fy=malloc(sizeof(double)*N);
    for (int k = 0; k<timesteps; k++){
        for (int i = 0; i < N; i++)
        {
            Fx[i] = 0; //initialization
            Fy[i] = 0;
        }
        for (int i = 0; i < N; i++) {
            double mg = -G * p[i].mass;

            double tempFx = 0;
            double tempFy = 0;

            double tempPx = p[i].pos_x;
            double tempPy = p[i].pos_y;

            for (int j = i + 1; j < N; j++) {
                double rx = tempPx - p[j].pos_x; 
                double ry = tempPy - p[j].pos_y;
                double r = sqrt(rx * rx + ry * ry) + epsilon;
                double unit = mg*p[j].mass / (r*r*r);

                tempFx += rx * unit;
                tempFy += ry * unit;

                Fx[j] -= rx * unit;
                Fy[j] -= ry * unit;
            }
            Fx[i] += tempFx;
            Fy[i] += tempFy;

            p[i].velocity_x += dt*Fx[i]/p[i].mass;
            p[i].velocity_y += dt*Fy[i]/p[i].mass;
            
            p[i].pos_x += dt*p[i].velocity_x;
            p[i].pos_y += dt*p[i].velocity_y;
        }
    }
    free(Fx); 
    free(Fy);
}

int main(int argc, char *argv[]){
    if (argc != 6) {
        printf("Wrong amount of input arguments: should be 5 \n");
        return 0;
    }
    const int N = atoi(argv[1]);
    char *filename = argv[2];
    const int nsteps = atoi(argv[3]);
    const double dt = atof(argv[4]);
    int graphics = atoi(argv[5]);

    graphics += 0; //annoying warning
    const double G = 100.0/N;

    Particle particles[N];
    FILE *file;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    size_t dummy = fread(particles, sizeof(Particle), N, file);
    dummy += 0; // again, annoying warning
    fclose(file);
    
    simulation(G, N, particles, dt, nsteps);
    
    FILE *outputFile; 
    outputFile = fopen("result.gal", "wb");
    if (outputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(particles, sizeof(Particle), N, outputFile);
    fclose(outputFile);

    return 0;
}