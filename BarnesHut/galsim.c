#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quadtree.h"
#include <sys/time.h>
#include "graphics.h"

//Solution to the n-body problem using the Barnes-Hut algorithm

#define SYMPLECTIC_EULER 1 // 1 compiles symplectic euler time integration, 0 compiles velocity verlet
const float circleColor=0;


double get_wall_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * 1.0e-6;
}

int main(int argc, char* argv[]){
    const int N = 1000;
    const double G = 100.0/N;
    const float thetamax = 0.25;
    const double T = 2e-2;
    const int timesteps = 2e3;
    const double dt = T/timesteps;
    printf("%e\n",dt);
    InitializeGraphics(argv[0], 800, 800);
    SetCAxes(0, 1);

    int threads = N/20+1;
    if (threads>20){
    threads = 20;
    }
    
    double start, end, total = 0; // timings

    char file_path[50];
    snprintf(file_path, sizeof(file_path), "input_data/ellipse_N_%0*d.gal", 5, N);

    // char *file_path = "input_data/sun_and_planets_N_3.gal";

    // char *file_path = "input_data/circles_N_2.gal";

    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return 1;
    }

    Particle particles[N];
    
    int dummy = fread(particles, sizeof(Particle), N, file); dummy += 0;
    fclose(file);
    Node* root;
    double a[N][2];
    #if SYMPLECTIC_EULER
    for (int i = 0; i < timesteps; i++){
        ClearScreen();
        root = addNode(0, 0, 1);
        initializeTree(root, particles, N);
        start = get_wall_time();
        #pragma omp parallel for schedule(guided) num_threads(threads)
        for (int j = 0; j < N; j++){
            a[j][0] = 0, a[j][1] = 0;
            computeAcceleration(&particles[j], root, thetamax, G, a[j]);
            
            particles[j].velocity_x += dt*a[j][0];
            particles[j].velocity_y += dt*a[j][1];
        }

        for (int j = 0; j < N; j++){
            particles[j].pos_x += dt*particles[j].velocity_x;
            particles[j].pos_y += dt*particles[j].velocity_y;
            if (particles[j].pos_x>1||particles[j].pos_y>1 || particles[j].pos_x<0||particles[j].pos_y<0) {
            printf("Particles outside box\n"); return 0;}
            DrawCircle(particles[j].pos_x, particles[j].pos_y, 1, 1, particles[j].mass/100, circleColor);
        }
        Refresh();
        usleep(100000/N);
        end = get_wall_time();
        total += end-start;
        
        destroyTree(root);
    }
    FlushDisplay();
    CloseDisplay();
    

    #else
    const double dt2 = dt*dt/2;
    double a_old[N][2];
    root = addNode(0, 0, 1);
    initializeTree(root, particles, N);
    #pragma omp parallel for schedule(guided) num_threads(threads)
    for (int j = 0; j < N; j++){ // initialize acceleration for velocity verlet
        a[j][0] = 0;
        a[j][1] = 0;
        computeAcceleration(&particles[j], root, thetamax, G, a[j]); 
    }
    for (int i = 0; i < timesteps; i++){
        #pragma omp parallel for schedule(guided) num_threads(threads)
        for (int j = 0; j < N; j++){
            particles[j].pos_x += dt*particles[j].velocity_x+a[j][0]*dt2;
            particles[j].pos_y += dt*particles[j].velocity_y+a[j][1]*dt2;
            a_old[j][0] = a[j][0];
            a_old[j][1] = a[j][1];
            a[j][0] = 0; a[j][1] = 0;
        }
        start = get_wall_time();
        destroyTree(root);
        root = addNode(0, 0, 1);
        initializeTree(root, particles, N);
        end = get_wall_time();

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
