#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quadtree.h"

Node *addNode(double x, double y, double width){
    Node *n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {return NULL;}
    
    n->x = x;
    n->y = y;
    n->width = width;
    n->p = NULL;
    n->mass = 0;
    for (int i = 0; i < 4; i++) {
        n->children[i] = NULL;
    }
    return n;
}

void insertParticle(Particle *p, Node *n){
    if (n->p == NULL){ 
        n->p = p;
    }

    else{ 
        if (p->pos_x < n->x+n->width/2 && p->pos_y > n->y+ n->width/2){ //NW
            if (n->children[0] == NULL){
                    n->children[0] = addNode(n->x, n->y+n->width/2, n->width/2);
                }
                insertParticle(p, n->children[0]);
        }
        if (p->pos_x > n->x+n->width/2 && p->pos_y > n->y+ n->width/2){ //NE
            if (n->children[1] == NULL){
                    n->children[1] = addNode(n->x+n->width/2, n->y+n->width/2, n->width/2);
                }
                insertParticle(p, n->children[1]);
        }
        if (p->pos_x < n->x+ n->width/2 && p->pos_y < n->y + n->width/2){ //SW
            if (n->children[2] == NULL){
                    n->children[2] = addNode(n->x, n->y, n->width/2);
                }
                insertParticle(p, n->children[2]);
        }
        if (p->pos_x > n->x + n->width/2 && p->pos_y < n->y + n->width/2){ //SE
            if (n->children[3] == NULL){
                    n->children[3] = addNode(n->x+n->width/2, n->y, n->width/2);
                }
                insertParticle(p, n->children[3]);
        }
    }
}

void initializeProperties(Node *n){
    // Calculates and stores the mass and center of mass for each node
    
    double totalMass = 0;
    double xTot = 0;
    double yTot = 0;

    for (int i = 0; i < 4; i++){
        if (n->children[i] != NULL){
            initializeProperties(n->children[i]);
            totalMass += n->children[i]->mass;
            xTot += n->children[i]->centerOfMassx*n->children[i]->mass;
            yTot += n->children[i]->centerOfMassy*n->children[i]->mass;
        }
    }
    
    if (n->p != NULL){
        totalMass += n->p->mass;
        xTot += n->p->pos_x*n->p->mass;
        yTot += n->p->pos_y*n->p->mass;
    }
 
    n->mass = totalMass;
    n->centerOfMassx = xTot/n->mass;
    n->centerOfMassy = yTot/n->mass;
}

void initializeTree(Node* root, Particle* particles, int N){
    for (int i = 0; i < N; i++){
        insertParticle(&particles[i], root);
    }
    initializeProperties(root);
}

void computeAcceleration(Particle *p, Node *n, const float thetaMax, double G, double *a){   
     
    double mj = n->mass;
    double rx = n->centerOfMassx-p->pos_x;
    double ry = n->centerOfMassy-p->pos_y;
    double r = sqrt(rx*rx+ry*ry)+epsilon;
    
    if (n->width/r > thetaMax){
        
        for (int i = 0; i < 4; i++){
            if (n->children[i] != NULL){
                computeAcceleration(p, n->children[i], thetaMax, G, a);
            }
        }
        
        mj = n->p->mass;
        rx = n->p->pos_x-p->pos_x;
        ry = n->p->pos_y-p->pos_y;
        r = sqrt(rx*rx+ry*ry)+epsilon;
    }

    a[0] += G*mj/(r*r*r)*rx;
    a[1] += G*mj/(r*r*r)*ry;
}

void destroyTree(Node* n){
    if (n == NULL) {return;}

    for (int i = 0; i < 4; i++){
        destroyTree(n->children[i]);
    }
    free(n);
}