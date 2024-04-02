#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quadtree.h"
#include <sys/time.h>

#define SYMPLECTIC_EULER 0 // 1 compiles symplectic euler time integration, 0 compiles velocity verlet

double get_wall_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * 1.0e-6;
}

int main(){
    const int N = 3;
    const double G = 100.0/N;
    const float thetamax = 0;
    const double T = 2e-2;
    const int timesteps = 2e1;
    const double dt = T/timesteps;
    
    int threads = 1;

    double start, end, total = 0; // timings

    // char file_path[50];
    // snprintf(file_path, sizeof(file_path), "input_data/ellipse_N_%0*d.gal", 5, N);

    char *file_path = "input_data/sun_and_planets_N_3.gal";

    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return 1;
    }

    Particle particles[N];
    
    int dummy = fread(particles, sizeof(Particle), N, file); dummy += 0;
    fclose(file);
    double a[N][2];

    #if SYMPLECTIC_EULER 
    for (int i = 0; i < timesteps; i++){
        Node* root = addNode(0,0,1);
        initializeTree(root, particles, N);
        start = get_wall_time();
        #pragma omp parallel for num_threads(threads)
        for (int j = 0; j < N; j++){
            a[j][0] = 0, a[j][1] = 0;
            computeAcceleration(&particles[j], root, thetamax, G, a[j]);
            particles[j].velocity_x += dt*a[j][0];
            particles[j].velocity_y += dt*a[j][1];
            
        }
        for (int j = 0; j < N; j++){
            particles[j].pos_x += dt*particles[j].velocity_x;
            particles[j].pos_y += dt*particles[j].velocity_y;
        }
        end = get_wall_time();
        total += end-start;
        destroyTree(root);
    }

    #else 
    const double dt2 = dt*dt/2;
    double a_old[N][2];
    Node *root = addNode(0, 0, 1);
    initializeTree(root, particles, N);
    for (int j = 0; j < N; j++){ // initialize acceleration for velocity verlet
        a[j][0] = 0;
        a[j][1] = 0;
        computeAcceleration(&particles[j], root, thetamax, G, a[j]); 
    }
    for (int i = 0; i < timesteps; i++){
        
        for (int j = 0; j < N; j++){
            particles[j].pos_x += dt*particles[j].velocity_x+a[j][0]*dt2;
            particles[j].pos_y += dt*particles[j].velocity_y+a[j][1]*dt2;
            a_old[j][0] = a[j][0];
            a_old[j][1] = a[j][1];
            a[j][0] = 0; a[j][1] = 0;
        }
        destroyTree(root);
        Node *root = addNode(0, 0, 1);
        initializeTree(root, particles, N);
        
        #pragma omp parallel for num_threads(threads)
        for (int j = 0; j < N; j++){
            computeAcceleration(&particles[j], root, thetamax, G, a[j]);
            particles[j].velocity_x += dt*(a[j][0]+a_old[j][0])/2;
            particles[j].velocity_y += dt*(a[j][1]+a_old[j][1])/2;
        }
        
        total += end-start;
    }
    destroyTree(root);
    #endif


    printf("%f s\n",total);

    FILE *outputFile;
    outputFile = fopen("result.gal", "wb");
    if (outputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(particles, sizeof(Particle), N, outputFile);
    fclose(outputFile);
}