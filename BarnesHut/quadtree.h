#define epsilon 1e-3

typedef struct Particle {
    double pos_x; 
    double pos_y; 
    double mass;
    double velocity_x; 
    double velocity_y;
    double brightness;
} Particle;

typedef struct Node {
    double x, y; //lower left corner point
    double width; 
    Particle *p;
    double mass;
    double centerOfMassx;
    double centerOfMassy;
    struct Node *children[4]; //in order NW, NE, SW, SE
} Node;

Node *addNode(double x, double y, double width);
void insertParticle(Particle *p, Node *n);
void initializeProperties(Node* n);
void initializeTree(Node* root, Particle* particles, int N);
void destroyTree(Node* n);
void computeAcceleration(Particle *p, Node *n, float thetaMax, double G, double *a);