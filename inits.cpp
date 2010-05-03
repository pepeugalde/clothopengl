#include <GL/glut.h>
#include <stdlib.h>
#include <string>

#include "inits.h"
#include "clothfunc.h"

char title[200];

double testx = 0;
double testy = 0;
double testz = 1.5;
float testballr = 0.5;

Vec3 testvert;

bodyvertex waistbv, chestbv, neckbv, headbv, headtopbv, 
       rshoulderbv, ruarmbv, rlarmbv, rhandbv, rhandtopbv, lshoulderbv, luarmbv, llarmbv, lhandbv, lhandtopbv, 
       rulegbv, rllegbv, rfootbv, rfoottopbv, lulegbv, lllegbv, lfootbv, lfoottopbv, 
       waistc1bv, waistc2bv, chestc1bv, chestc2bv;


capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc,
        chestc, waistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

treenode headn, neckn, rshouldern, lshouldern, ruarmn, luarmn, rlarmn, llarmn, rhandn, lhandn,
         chestn, waistn, rulegn, lulegn, rllegn, lllegn, rfootn, lfootn;

////STRUCTS
objLoader *skindata;
objLoader *shirtdata;
//objLoader *pantsdata;

//angulos del cuerpo
GLfloat bodypos[16];

bodyvertex   *bodyverts[NUMVERT];
capsule  *caps[NUMCAPS];

int totalshirtparticles;
int totalpantsparticles;
particle *shirtparticles;
particle *pantsparticles;

int totalshirtsprings;
int totalpantssprings;
spring *shirtsprings;
spring *pantssprings;

/////////////////FUNCIONES
void initVertices(){
    //
    testvert.f[0] = testx;
    testvert.f[1] = testy;
    testvert.f[2] = testz;
    //
    Vec3 waistv, chestv, neckv, headv, headtopv, 
     rshoulderv, ruarmv, rlarmv, rhandv, rhandtopv, lshoulderv, luarmv, llarmv, lhandv, lhandtopv, 
     rulegv, rllegv, rfootv, rfoottopv, lulegv, lllegv, lfootv, lfoottopv, 
     waistc1v, waistc2v, chestc1v, chestc2v;
    
    waistv.f[0] = 0;
    waistv.f[1] = -0.4;
    waistv.f[2] = 0;
    waistbv.v = waistv;
    
    chestv.f[0] = 0;
    chestv.f[1] = 0.6;
    chestv.f[2] = 0;
    chestbv.v = chestv;
    
    waistc1v.f[0] = -(waistc2v.f[0] = -0.5);
    waistc1v.f[1] = waistc2v.f[1]   = 0.3;
    waistc1v.f[2] = waistc2v.f[2]   = 0;
    waistc1bv.v = waistc1v;
    waistc2bv.v = waistc2v;
    chestc1v.f[0] = -(chestc2v.f[0] = -0.5);
    chestc1v.f[1] = chestc2v.f[1]   = 1.2;
    chestc1v.f[2] = chestc2v.f[2]   = 0;
    chestc1bv.v = chestc1v;
    chestc2bv.v = chestc2v;
    
    //waistl1v.f[0] = -(waistr1v.f[0] = -0.5);
//    waistl1v.f[1] = waistr1v.f[1]   = 0.3;
//    waistl1v.f[2] = waistr1v.f[2]   = 0;
//    bv.v = v;
//    waistl2v.f[0] = -(waistr2v.f[0] = -0.5);
//    waistl2v.f[1] = waistr2v.f[1]   = 0.3;
//    waistl2v.f[2] = waistr2v.f[2]   = 0;
//    bv.v = v;
//    chestlv.f[0] = -(chestc2v.f[0] = -0.5);
//    chestlv.f[1] = chestc2v.f[1]   = 1.2;
//    chestlv.f[2] = chestc2v.f[2]   = 0;
//    bv.v = v;

    neckv.f[0] = 0;
    neckv.f[1] = 2.2;
    neckv.f[2] = 0;
    neckbv.v = neckv;
    
    headv.f[0] = 0;
    headv.f[1] = 2.9;
    headv.f[2] = 0;
    headbv.v = headv;
    
    headtopv.f[0] = 0;
    headtopv.f[1] = 3.3;
    headtopv.f[2] = 0;
    headtopbv.v = headtopv;
    
    rshoulderv.f[0] = -(lshoulderv.f[0] = -0.4);
    rshoulderv.f[1] = lshoulderv.f[1]   = 2.05;
    rshoulderv.f[2] = lshoulderv.f[2]   = 0;
    rshoulderbv.v = rshoulderv;
    lshoulderbv.v = lshoulderv;
    ruarmv.f[0] = -(luarmv.f[0] = -1.15);
    ruarmv.f[1] = luarmv.f[1]   = 1.7;
    ruarmv.f[2] = luarmv.f[2]   = 0;
    ruarmbv.v = ruarmv;
    luarmbv.v = luarmv;
    rlarmv.f[0] = -(llarmv.f[0] = -1.3);
    rlarmv.f[1] = llarmv.f[1]   = 0.3;
    rlarmv.f[2] = llarmv.f[2]   = -0.05;
    rlarmbv.v = rlarmv;
    llarmbv.v = llarmv;
    rhandv.f[0] = -(lhandv.f[0] = -1.25);
    rhandv.f[1] = lhandv.f[1]   = -0.8;
    rhandv.f[2] = lhandv.f[2]   = 0;
    rhandbv.v = rhandv;
    lhandbv.v = lhandv;
    rhandtopv.f[0] = -(lhandtopv.f[0] = -1.2);
    rhandtopv.f[1] = lhandtopv.f[1]   = -1.5;
    rhandtopv.f[2] = lhandtopv.f[2]   = 0;
    rhandtopbv.v = rhandtopv;
    lhandtopbv.v = lhandtopv;
    
    rulegv.f[0] = -(lulegv.f[0] = -0.5);
    rulegv.f[1] = lulegv.f[1]   = -0.4;
    rulegv.f[2] = lulegv.f[2]   = 0;
    rulegbv.v = rulegv;
    lulegbv.v = lulegv;
    rllegv.f[0] = -(lllegv.f[0] = -0.45);
    rllegv.f[1] = lllegv.f[1]   = -2.4;
    rllegv.f[2] = lllegv.f[2]   = 0.05;
    rllegbv.v = rllegv;
    lllegbv.v = lllegv;
    rfootv.f[0] = -(lfootv.f[0] = -0.45);
    rfootv.f[1] = lfootv.f[1]   = -4.35;
    rfootv.f[2] = lfootv.f[2]   = 0;
    rfootbv.v = rfootv;
    lfootbv.v = lfootv;
    rfoottopv.f[0] = -(lfoottopv.f[0] = -0.45);
    rfoottopv.f[1] = lfoottopv.f[1]   = -4.35;
    rfoottopv.f[2] = lfoottopv.f[2]   = 0.7;
    rfoottopbv.v = rfoottopv;
    lfoottopbv.v = lfoottopv;
    
    bodyverts[0] = &waistbv;
    bodyverts[1] = &chestbv;
    bodyverts[2] = &neckbv;
    bodyverts[3] = &headbv;
    bodyverts[4] = &headtopbv;
    bodyverts[5] = &rshoulderbv;
    bodyverts[6] = &ruarmbv;
    bodyverts[7] = &rlarmbv;
    bodyverts[8] = &rhandbv;
    bodyverts[9] = &rhandtopbv;
    bodyverts[10] = &lshoulderbv;
    bodyverts[11] = &luarmbv;
    bodyverts[12] = &llarmbv;
    bodyverts[13] = &lhandbv;
    bodyverts[14] = &lhandtopbv;
    bodyverts[15] = &rulegbv;
    bodyverts[16] = &rllegbv;
    bodyverts[17] = &rfootbv;
    bodyverts[18] = &rfoottopbv;
    bodyverts[19] = &lulegbv;
    bodyverts[20] = &lllegbv;
    bodyverts[21] = &lfootbv;
    bodyverts[22] = &lfoottopbv;
    bodyverts[23] = &waistc1bv;
    bodyverts[24] = &waistc2bv;
    bodyverts[25] = &chestc1bv;
    bodyverts[26] = &chestc2bv;
}

void initCapsules(){
    waistc.bv1 = &waistc1bv;
    waistc.bv2 = &waistc2bv;
    waistc.r = 0.35;
    chestc.bv1 = &chestc1bv;
    chestc.bv2 = &chestc2bv;
    chestc.r = 0.4;
    
    neckc.bv1 = &neckbv;
    neckc.bv2 = &headbv;
    neckc.r = 0.25;
    headc.bv1 = &headbv;
    headc.bv2 = &headtopbv;
    headc.r = 0.4;
    
    rshoulderc.bv1 = &rshoulderbv;
    rshoulderc.bv2 = &ruarmbv;
    rshoulderc.r = 0.3;
    ruarmc.bv1 = &ruarmbv;
    ruarmc.bv2 = &rlarmbv;
    ruarmc.r = 0.2;
    rlarmc.bv1 = &rlarmbv;
    rlarmc.bv2 = &rhandbv;
    rlarmc.r = 0.15;
    rhandc.bv1 = &rhandbv;
    rhandc.bv2 = &rhandtopbv;
    rhandc.r = 0.1;
    
    lshoulderc.bv1 = &lshoulderbv;
    lshoulderc.bv2 = &luarmbv;
    lshoulderc.r = 0.3;
    luarmc.bv1 = &luarmbv;
    luarmc.bv2 = &llarmbv;
    luarmc.r = 0.2;
    llarmc.bv1 = &llarmbv;
    llarmc.bv2 = &lhandbv;
    llarmc.r = 0.15;
    lhandc.bv1 = &lhandbv;
    lhandc.bv2 = &lhandtopbv;
    lhandc.r = 0.1;
    
    rulegc.bv1 = &rulegbv;
    rulegc.bv2 = &rllegbv;
    rulegc.r = 0.3;
    rllegc.bv1 = &rllegbv;
    rllegc.bv2 = &rfootbv;
    rllegc.r = 0.2;
    rfootc.bv1 = &rfootbv;
    rfootc.bv2 = &rfoottopbv;
    rfootc.r = 0.1;
    
    lulegc.bv1 = &lulegbv;
    lulegc.bv2 = &lllegbv;
    lulegc.r = 0.3;
    lllegc.bv1 = &lllegbv;
    lllegc.bv2 = &lfootbv;
    lllegc.r = 0.2;
    lfootc.bv1 = &lfootbv;
    lfootc.bv2 = &lfoottopbv;
    lfootc.r = 0.1;
    
    caps[0] = &waistc;
    caps[1] = &chestc;
    caps[2] = &neckc;
    caps[3] = &headc;
    caps[4] = &rshoulderc;
    caps[5] = &ruarmc;
    caps[6] = &rlarmc;
    caps[7] = &rhandc;
    caps[8] = &lshoulderc;
    caps[9] = &luarmc;
    caps[10] = &llarmc;
    caps[11] = &lhandc;
    caps[12] = &rulegc;
    caps[13] = &rllegc;
    caps[14] = &rfootc;
    caps[15] = &lulegc;
    caps[16] = &lllegc;
    caps[17] = &lfootc;
}

void initNodes(){
    //body
    glPushMatrix();
        glMultMatrixf(bodypos);
        glLoadIdentity();
        glGetFloatv(GL_MODELVIEW_MATRIX, bodypos);
    glPopMatrix();
    
    //waist
    glLoadIdentity();
    glTranslatef(0.0,-0.4,0.0);
    waistn.cap = &waistc;
    waistn.bv1 = &waistbv;
    waistn.bv2 = &chestbv;
    waistn.id = 1;
    waistn.sibling = &rulegn;
    waistn.child = &chestn;
    
    //chest
    glLoadIdentity();
    glTranslatef(0,1.0,0.0);
    chestn.cap = &chestc;
    chestn.bv1 = &chestbv;
    chestn.bv2 = &neckbv;
    chestn.id = 16;
    chestn.sibling = NULL;
    chestn.child = &neckn;
    
    //Neck
    glLoadIdentity();
    glTranslatef(0.0,1.8,0.0);
    neckn.cap = &neckc;
    neckn.bv1 = &neckbv;
    neckn.bv2 = &headbv;
    neckn.id = 2;
    neckn.sibling = &rshouldern;
    neckn.child = &headn;
    
    //HEAD
    glLoadIdentity();
    glTranslatef(0.0,0.5,0.0);
    headn.cap = &headc;
    headn.bv1 = &headbv;
    headn.bv2 = &headtopbv;
    headn.id = 3;
    headn.sibling = NULL;
    headn.child = NULL;

    //rshoulder
    glLoadIdentity();
    glTranslatef(-0.4,1.45,0.0);
    rshouldern.cap = &rshoulderc;
    rshouldern.bv1 = &rshoulderbv;
    rshouldern.bv2 = &ruarmbv;
    rshouldern.id = 17;
    rshouldern.sibling = &lshouldern;
    rshouldern.child = &ruarmn;
    
    //RIGHT UPPER ARM
    glLoadIdentity();
    glTranslatef(-0.85,-0.35,0.0);
    ruarmn.cap = &ruarmc;
    ruarmn.bv1 = &ruarmbv;
    ruarmn.bv2 = &rlarmbv;
    ruarmn.id = 4;
    ruarmn.sibling = NULL;
    ruarmn.child = &rlarmn;
    
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(-0.05,-1.3,-0.05);
    rlarmn.cap = &rlarmc;
    rlarmn.bv1 = &rlarmbv;
    rlarmn.bv2 = &rhandbv;
    rlarmn.id = 5;
    rlarmn.sibling = NULL;        
    rlarmn.child = &rhandn;
    
    //rhand
    glLoadIdentity();
    glTranslatef(0.05,-1.3,0.05);
    rhandn.cap = &rhandc;
    rhandn.bv1 = &rhandbv;
    rhandn.bv2 = &rhandtopbv;
    rhandn.id = 6;
    rhandn.sibling = NULL;        
    rhandn.child = NULL;
    
    //lshoulder
    glLoadIdentity();
    glTranslatef(0.4,1.45,0.0);
    lshouldern.cap = &lshoulderc;
    lshouldern.bv1 = &lshoulderbv;
    lshouldern.bv2 = &luarmbv;
    lshouldern.id = 17;
    lshouldern.sibling = NULL;
    lshouldern.child = &luarmn;
    
    //RIGHT UPPER ARM
    glLoadIdentity();
    glTranslatef(0.85,-0.35,0.0);
    luarmn.cap = &luarmc;
    luarmn.bv1 = &luarmbv;
    luarmn.bv2 = &llarmbv;
    luarmn.id = 7;
    luarmn.sibling = NULL;
    luarmn.child = &llarmn;
    
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(0.05,-1.3,-0.05);

    llarmn.cap = &llarmc;
    llarmn.bv1 = &llarmbv;
    llarmn.bv2 = &lhandbv;
    llarmn.id = 8;
    llarmn.sibling = NULL;        
    llarmn.child = &lhandn;
    
    //rhand
    glLoadIdentity();
    glTranslatef(-0.05,-1.3,0.05);
    lhandn.cap = &lhandc;
    lhandn.bv1 = &lhandbv;
    lhandn.bv2 = &lhandtopbv;
    lhandn.id = 9;
    lhandn.sibling = NULL;        
    lhandn.child = NULL;
    
    //RIGHT UPPER LEG
    glLoadIdentity();
    glTranslatef(-0.5,-0.4,0.0);
    rulegn.cap = &rulegc;
    rulegn.bv1 = &rulegbv;
    rulegn.bv2 = &rllegbv;
    rulegn.id = 10;
    rulegn.sibling = &lulegn;       
    rulegn.child = &rllegn; 
    
    //RIGHT LOWER LEG
    glLoadIdentity();
    glTranslatef(0.05,-2,0.0);
    rllegn.cap = &rllegc;
    rllegn.bv1 = &rllegbv;
    rllegn.bv2 = &rfootbv;
    rllegn.id = 11;
    rllegn.sibling = NULL;
    rllegn.child = &rfootn;
    
    //rfoot
    glLoadIdentity();
    glTranslatef(0,-2,0);
    rfootn.cap = &rfootc;
    rfootn.bv1 = &rfootbv;
    rfootn.bv2 = &rfoottopbv;
    rfootn.id = 12;
    rfootn.sibling = NULL;
    rfootn.child = NULL;
    
    //LEFT UPPER LEG
    glLoadIdentity();
    glTranslatef(0.5,-0.4,0.0);
    lulegn.cap = &lulegc;
    lulegn.bv1 = &lulegbv;
    lulegn.bv2 = &lllegbv;
    lulegn.id = 13;
    lulegn.sibling = NULL;       
    lulegn.child = &lllegn;                      
    
    //LEFT LOWER LEG
    glLoadIdentity();
    glTranslatef(-0.05,-2,0.0);
    lllegn.cap = &lllegc;
    lllegn.bv1 = &lllegbv;
    lllegn.bv2 = &lfootbv;
    lllegn.id = 14;
    lllegn.sibling = NULL;        
    lllegn.child = &lfootn;
    
    //lfoot
    glLoadIdentity();
    glTranslatef(0,-2,0);
    lfootn.cap = &lfootc;
    lfootn.bv1 = &lfootbv;
    lfootn.bv2 = &lfoottopbv;
    lfootn.id = 15;
    lfootn.sibling = NULL;        
    lfootn.child = NULL;
}

//Carga objs a skindata, shirtdata y pantsdata
void initObj(){
    skindata = new objLoader();
    skindata->load("cuerpob.obj");
    
    shirtdata = new objLoader();
    shirtdata->load("camisab.obj");
    
    //pantsdata = new objLoader();
    //pantsdata->load("pantsb.obj");
}

void initParticles(){
    totalshirtparticles = shirtdata->vertexCount;
    //totalpantsparticles = pantsdata->vertexCount;
    shirtparticles = (particle*)calloc(totalshirtparticles, sizeof(particle));
    //pantsparticles = (particle*)calloc(totalpantsparticles, sizeof(particle));
    
    if(shirtparticles == NULL){// || pantsparticles == NULL){
        //println("COULD NOT ALLOCATE MEMORY FOR PARTICLES");
        sprintf(title, "COULD NOT ALLOCATE MEMORY FOR PARTICLES");
        glutSetWindowTitle(title);
        exit(-1);
    }
    
    
    int i=0;
    ////construye particulas con masa y un punto
    for(i=0; i < totalshirtparticles; i++){
        particle ptemp = particleconstruct(shirtdata->vertexList[i]);
        shirtparticles[i] = ptemp;
    }
    
    //sprintf(title, "shirtvert 0: %f %f %f ", shirtdata->vertexList[i]->f[0], shirtdata->vertexList[i]->f[1], shirtdata->vertexList[i]->f[2]);
    //sprintf(title, "shirtvert 0: %f %f %f ", shirtparticles[i].pos->f[0], shirtparticles[i].pos->f[1], shirtparticles[i].pos->f[2]);
    //sprintf(title, "tshirtpart: %d", totalshirtparticles);
    //glutSetWindowTitle(title);

    
    //igual para pants
    //for(i=0; i < totalpantsparticles; i++){
//        particle ptemp = particleconstruct(pantsdata->vertexList[i]);
//        pantsparticles[i] = ptemp;
//    }
}

//checa si el resorte ya esta en la lista
//checa si a->b  y  b->a son repetidos
bool isDuplicateSpring(spring *array, int total, particle *pa1, particle *pa2){
    bool flag = false;
    int i=0;
    for(i=0;i<total;i++){
        //if((array[i].p1->pos == pa1->pos && array[i].p2->pos == pa2->pos) || (array[i].p1->pos == pa2->pos && array[i].p2->pos == pa1->pos));
        //if(array[i].p1->pos == pa1->pos)
//        if(array[i].p2->pos == pa2->pos)
//        if(array[i].p1->pos == pa2->pos)
//        if(array[i].p2->pos == pa1->pos)
            flag = true;
    }
    return flag;
}

void initSprings(){
    shirtsprings = (spring*)calloc(shirtdata->faceCount * 3, sizeof(spring));
    //pantssprings = (spring*)calloc(pantsdata->faceCount * 3, sizeof(spring));
    
    if(shirtsprings == NULL){ // || pantssprings == NULL){
        //println("COULD NOT ALLOCATE MEMORY FOR SPRINGS");
        sprintf(title, "COULD NOT ALLOCATE MEMORY FOR SPRINGS");
        glutSetWindowTitle(title);
        exit(-1);
    }
    
    int i=0;//iterador
    int currentindex = 0;//no toma en cuenta resortes repetidos
    totalshirtsprings = 0;
    totalpantssprings = 0;
    
    ////agrega 3 resortes (aristas) por cada cara, pero checa que no se repitan
    for(i=0 ;i < shirtdata->faceCount; i++){ //5;i++){//
        ///arista 1
        particle *pt1a = &(shirtparticles[shirtdata->faceList[i]->vertex_index[0]]);
        particle *pt2a = &(shirtparticles[shirtdata->faceList[i]->vertex_index[1]]);
        if(!(isDuplicateSpring(shirtsprings, totalshirtsprings, (pt1a), (pt2a)))){
            spring stemp = springconstruct(pt1a, pt2a);
            shirtsprings[totalshirtsprings] = stemp;
            totalshirtsprings++;
        }
        ///arista 2
        particle *pt1b = &(shirtparticles[shirtdata->faceList[i]->vertex_index[1]]);
        particle *pt2b = &(shirtparticles[shirtdata->faceList[i]->vertex_index[2]]);
        if(!(isDuplicateSpring(shirtsprings, totalshirtsprings, (pt1b), (pt2b)))){
            spring stemp = springconstruct(pt1b, pt2b);
            shirtsprings[totalshirtsprings] = stemp;
            totalshirtsprings++;
        }
        ///arista 3
        particle *pt1c = &(shirtparticles[shirtdata->faceList[i]->vertex_index[2]]);
        particle *pt2c = &(shirtparticles[shirtdata->faceList[i]->vertex_index[0]]);
        if(!(isDuplicateSpring(shirtsprings, totalshirtsprings, (pt1c), (pt2c)))){
            spring stemp = springconstruct(pt1c, pt2c);
            shirtsprings[totalshirtsprings] = stemp;
            totalshirtsprings++;
        }
    }    
}
