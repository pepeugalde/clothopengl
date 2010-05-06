#ifndef STRUCTS_H
#define STRUCTS_H

/*Punto, vector, vertice, como lo quieran ver
contiene x, y, z */
typedef struct Vec3{
    double f[3];
} Vec3;

/*vertice del cuerpo (hombro, cadera, codo, etc)
contiene un punto y bool para no rotarlo mas de una vez*/
typedef struct bodyvertex{
    Vec3 v;
    bool hasmoved;
} bodyvertex;

/*si*/
typedef struct capsule{
    bodyvertex *bv1;
    bodyvertex *bv2;
    
    float r;
    //capsule *sib;
    char name[16];
} capsule;

/*parte del cuerpo que contiene 2 vertices
igual y se puede simplificar hasta 1... no se*/
typedef struct treenode{
    capsule *cap;
    int id;
    bodyvertex *bv1;
    bodyvertex *bv2;
    struct treenode *sibling;
    struct treenode *child;
} treenode;

typedef struct binding{
    bodyvertex *bv;
    Vec3 *sv;
    float w;
} binding;

/////CLOTH

/* The particle class represents a particle of mass that can move around in 3D space*/
typedef struct particle{
	bool movable; // can the particle move or not ? used to pin parts of the cloth
	float mass; // the mass of the particle (is always 1 in this example)
	Vec3 *pos; // the current position of the particle in 3D space
	Vec3 old_pos; // the position of the particle in the previous time step, used as part of the verlet numerical integration scheme
	Vec3 acceleration; // a vector representing the current acceleration of the particle
	Vec3 accumulated_normal; // an accumulated normal (i.e. non normalized), used for OpenGL soft shading
} particle;

/*resorte entre 2 particulas*/
typedef struct spring{
	float rest_distance; // the length between particle p1 and p2 in rest configuration
	particle *p1, *p2; // the two particles that are connected through this constraint
} spring;

/*no se si usar esto*/
typedef struct cloth{
	int num_particles_width; // number of particles in "width" direction
	int num_particles_height; // number of particles in "height" direction
} cloth;

#endif
