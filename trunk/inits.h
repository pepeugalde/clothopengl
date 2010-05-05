#ifndef INITS_H
#define INITS_H

#include "structs.h"
#include "objLoader.h"

#define NUMVERT  27
#define NUMCAPS  18
#define NUMNODES 18

extern char title[200];

extern GLfloat bodypos[16];

extern double testx;
extern double testy;
extern double testz;
extern float testballr;

extern bodyvertex waistbv, chestbv, neckbv, headbv, headtopbv, 
       rshoulderbv, ruarmbv, rlarmbv, rhandbv, rhandtopbv, lshoulderbv, luarmbv, llarmbv, lhandbv, lhandtopbv, 
       rulegbv, rllegbv, rfootbv, rfoottopbv, lulegbv, lllegbv, lfootbv, lfoottopbv, 
       waistc1bv, waistc2bv, chestc1bv, chestc2bv;


extern capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc,
        chestc, waistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

extern treenode headn, neckn, rshouldern, lshouldern, ruarmn, luarmn, rlarmn, llarmn, rhandn, lhandn,
         chestn, waistn, rulegn, lulegn, rllegn, lllegn, rfootn, lfootn;

////STRUCTS
extern objLoader *skindata;
extern objLoader *shirtdata;
extern objLoader *pantsdata;
extern objLoader *hairdata;

//arreglos de structs
extern bodyvertex   *bodyverts[NUMVERT];
extern capsule  *caps[NUMCAPS];

extern int numbindings;
extern binding *bindings;

extern int totalshirtparticles;
extern int totalpantsparticles;
extern int totalhairparticles;
extern particle *shirtparticles;
extern particle *pantsparticles;
extern particle *hairparticles;

extern int totalshirtsprings;
extern int totalpantssprings;
extern int totalhairsprings;
extern spring *shirtsprings;
extern spring *pantssprings;
extern spring *hairsprings;

extern Vec3 testvert;

extern Vec3 gravity;
extern float shirtmass;
extern float pantsmass;
extern float hairmass;

/////////////FUNCIONES
void initVertices();
void initCapsules();
void initNodes();

void initObj();
void bind(Vec3 *nbv, Vec3 *nsv, int pos);
void initSkin();
void initParticles();
bool isDuplicateSpring(spring *array, int total, particle *pa1, particle *pa2);
void initSprings();

#endif
