#ifndef INITS_H
#define INITS_H

#include "structs.h"
#include "objLoader.h"

#define NUMVERTS 30 //28
#define NUMNODES 16
#define NUMCAPS  23 //22

extern char title[200];

extern GLfloat bodypos[16];

extern int shirtoption;
extern int pantsoption;
extern int hairoption;


extern bodyvertex waistbv, chestbv, abdomenbv, neckbv, headbv, headtopbv, 
                   rshoulderbv, relbowbv, rwristbv, rfingersbv, lshoulderbv, lelbowbv, lwristbv, lfingersbv, 
                   rulegbv, rkneebv, ranklebv, rtoesbv, lulegbv, lkneebv, lanklebv, ltoesbv, 
                   rabdomenbv, labdomenbv, rneckbv, lneckbv, rbuttbv, lbuttbv, nosebv, nosetipbv;

extern capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc, 
               chestc, rchestc, lchestc, waistc, rwaistc, lwaistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc, nosec;

extern treenode waistn, abdomenn, neckn, headn, 
        rshouldern, relbown, rwristn, lshouldern, lelbown, lwristn, 
        rulegn, rkneen, ranklen, lulegn, lkneen, lanklen;

////STRUCTS
extern objLoader *skindata;
extern objLoader *shirtdata;
extern objLoader *pantsdata;
extern objLoader *hairdata;

//arreglos de structs
extern treenode   *nodes[NUMNODES];
extern bodyvertex *bodyverts[NUMVERTS];
extern capsule    *caps[NUMCAPS];

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
