#include <GL/glut.h>
#include <stdlib.h>
#include <string>

#include "inits.h"
#include "clothfunc.h"

char title[200];

Vec3 gravity = Vec3construct(0,-0.1,0);

int shirtoption = 0;
int pantsoption = 0;
int hairoption  = 0;


float shirtmass = 30;
float pantsmass = 30;
float hairmass  = 20;
float afromass  = 100;

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
objLoader *pantsdata;
objLoader *hairdata;

//angulos del cuerpo
GLfloat bodypos[16];

bodyvertex   *bodyverts[NUMVERT];
capsule  *caps[NUMCAPS];

int numbindings;
binding *bindings;

int totalshirtparticles;
int totalpantsparticles;
int totalhairparticles;
particle *shirtparticles;
particle *pantsparticles;
particle *hairparticles;

int totalshirtsprings;
int totalpantssprings;
int totalhairsprings;
spring *shirtsprings;
spring *pantssprings;
spring *hairsprings;

/////////////////FUNCIONES
void initVertices(){
    //
//    testvert.f[0] = testx;
//    testvert.f[1] = testy;
//    testvert.f[2] = testz;
    //
    
    Vec3 waistv, chestv, neckv, headv, headtopv, 
     rshoulderv, ruarmv, rlarmv, rhandv, rhandtopv, lshoulderv, luarmv, llarmv, lhandv, lhandtopv, 
     rulegv, rllegv, rfootv, rfoottopv, lulegv, lllegv, lfootv, lfoottopv, 
     waistc1v, waistc2v, chestc1v, chestc2v;
    
    waistv.f[0] = 0;
    waistv.f[1] = -0.1;
    waistv.f[2] = 0;
    waistbv.v = waistv;
    
    chestv.f[0] = 0;
    chestv.f[1] = 0.8;
    chestv.f[2] = 0;
    chestbv.v = chestv;
    
    waistc1v.f[0] = -(waistc2v.f[0] = -0.25);
    waistc1v.f[1] = waistc2v.f[1]   = 0.4;
    waistc1v.f[2] = waistc2v.f[2]   = -0.05;
    waistc1bv.v = waistc1v;
    waistc2bv.v = waistc2v;
    chestc1v.f[0] = -(chestc2v.f[0] = -0.2);
    chestc1v.f[1] = chestc2v.f[1]   = 1.6;
    chestc1v.f[2] = chestc2v.f[2]   = -0.05;
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
    neckv.f[1] = 2.1;
    neckv.f[2] = 0;
    neckbv.v = neckv;
    
    headv.f[0] = 0;
    headv.f[1] = 2.8;
    headv.f[2] = 0.15;
    headbv.v = headv;
    
    headtopv.f[0] = 0;
    headtopv.f[1] = 3.35;
    headtopv.f[2] = 0.1;
    headtopbv.v = headtopv;
    
    rshoulderv.f[0] = -(lshoulderv.f[0] = -0.3);
    rshoulderv.f[1] = lshoulderv.f[1]   = 2;
    rshoulderv.f[2] = lshoulderv.f[2]   = -0.2;
    rshoulderbv.v = rshoulderv;
    lshoulderbv.v = lshoulderv;
    
    ruarmv.f[0] = -(luarmv.f[0] = -0.7);
    ruarmv.f[1] = luarmv.f[1]   = 1.9;
    ruarmv.f[2] = luarmv.f[2]   = -0.2;
    ruarmbv.v = ruarmv;
    luarmbv.v = luarmv;
    rlarmv.f[0] = -(llarmv.f[0] = -1.9);
    rlarmv.f[1] = llarmv.f[1]   = 1.8;
    rlarmv.f[2] = llarmv.f[2]   = -0.35;
    rlarmbv.v = rlarmv;
    llarmbv.v = llarmv;
    rhandv.f[0] = -(lhandv.f[0] = -3);
    rhandv.f[1] = lhandv.f[1]   = 1.7;
    rhandv.f[2] = lhandv.f[2]   = 0;
    rhandbv.v = rhandv;
    lhandbv.v = lhandv;
    rhandtopv.f[0] = -(lhandtopv.f[0] = -3.6);
    rhandtopv.f[1] = lhandtopv.f[1]   = 1.65;
    rhandtopv.f[2] = lhandtopv.f[2]   = 0.25;
    rhandtopbv.v = rhandtopv;
    lhandtopbv.v = lhandtopv;
    
    rulegv.f[0] = -(lulegv.f[0] = -0.4);
    rulegv.f[1] = lulegv.f[1]   = -0.1;
    rulegv.f[2] = lulegv.f[2]   = -0.05;
    rulegbv.v = rulegv;
    lulegbv.v = lulegv;
    rllegv.f[0] = -(lllegv.f[0] = -0.6);
    rllegv.f[1] = lllegv.f[1]   = -2.2;
    rllegv.f[2] = lllegv.f[2]   = 0;
    rllegbv.v = rllegv;
    lllegbv.v = lllegv;
    rfootv.f[0] = -(lfootv.f[0] = -0.7);
    rfootv.f[1] = lfootv.f[1]   = -4.5;
    rfootv.f[2] = lfootv.f[2]   = -0.2;
    rfootbv.v = rfootv;
    lfootbv.v = lfootv;
    rfoottopv.f[0] = -(lfoottopv.f[0] = -0.85);
    rfoottopv.f[1] = lfoottopv.f[1]   = -4.5;
    rfoottopv.f[2] = lfoottopv.f[2]   = 0.8;
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
    
    chestc.bv1 = &chestc1bv;
    chestc.bv2 = &chestc2bv;
    
    neckc.bv1 = &neckbv;
    neckc.bv2 = &headbv;
    
    headc.bv1 = &headbv;
    headc.bv2 = &headtopbv;
    
    waistc.r = 0.55;
    chestc.r = 0.55;
    neckc.r = 0.3;
    headc.r = 0.45;
    
    rshoulderc.bv1 = &rshoulderbv;
    rshoulderc.bv2 = &ruarmbv;
    ruarmc.bv1 = &ruarmbv;
    ruarmc.bv2 = &rlarmbv;
    rlarmc.bv1 = &rlarmbv;
    rlarmc.bv2 = &rhandbv;
    rhandc.bv1 = &rhandbv;
    rhandc.bv2 = &rhandtopbv;
    
    lshoulderc.bv1 = &lshoulderbv;
    lshoulderc.bv2 = &luarmbv;
    luarmc.bv1 = &luarmbv;
    luarmc.bv2 = &llarmbv;
    llarmc.bv1 = &llarmbv;
    llarmc.bv2 = &lhandbv;
    lhandc.bv1 = &lhandbv;
    lhandc.bv2 = &lhandtopbv;
    
    rshoulderc.r = lshoulderc.r = 0.4;
    ruarmc.r = luarmc.r = 0.3;
    rlarmc.r = llarmc.r = 0.25;
    rhandc.r = lhandc.r = 0.25;
    
    rulegc.bv1 = &rulegbv;
    rulegc.bv2 = &rllegbv;
    rllegc.bv1 = &rllegbv;
    rllegc.bv2 = &rfootbv;
    rfootc.bv1 = &rfootbv;
    rfootc.bv2 = &rfoottopbv;
    
    lulegc.bv1 = &lulegbv;
    lulegc.bv2 = &lllegbv;
    lllegc.bv1 = &lllegbv;
    lllegc.bv2 = &lfootbv;
    lfootc.bv1 = &lfootbv;
    lfootc.bv2 = &lfoottopbv;
    
    rulegc.r = lulegc.r = 0.4;
    rllegc.r = lllegc.r = 0.3;
    rfootc.r = lfootc.r = 0.25;
    
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
    skindata->load("human.obj");
    shirtdata = new objLoader();
    pantsdata = new objLoader();
    hairdata = new objLoader();
    shirtdata->load("shirt.obj");
    pantsdata->load("pants.obj");
    hairdata->load("hair.obj");
    if(shirtoption == 0)
        shirtdata->load("shirt.obj");
    else
        shirtdata->load("vest.obj");
        
    if(pantsoption == 0)
        pantsdata->load("pants.obj");
    else
        pantsdata->load("tidusp.obj");
        
    if(hairoption == 0)
        hairdata->load("hair.obj");
    else
        hairdata->load("afro.obj");
}

void bind(bodyvertex *nbv, Vec3 *nsv, float nw){
    binding newbind;
    newbind.bv = nbv;
    newbind.sv = nsv;
    newbind.w = nw;
    bindings[numbindings] = newbind;
    numbindings++;
}

bool betweenx(Vec3 *v, float xlow, float xhigh){
     float a, b;
     if(xlow < xhigh){
         a = xlow;
         b = xhigh;
     }else{
         b = xlow;
         a = xhigh;
     }
     if(v->f[0] >= a && v->f[0] < b)
         return true;
     return false;
}

bool betweeny(Vec3 *v, float ylow, float yhigh){
     float a, b;
     if(ylow < yhigh){
         a = ylow;
         b = yhigh;
     }else{
         b = ylow;
         a = yhigh;
     }
     if(v->f[1] >= a && v->f[1] < b)
         return true;
     return false;
}

bool betweenz(Vec3 *v, float zlow, float zhigh){
     float a, b;
     if(zlow < zhigh){
         a = zlow;
         b = zhigh;
     }else{
         b = zlow;
         a = zhigh;
     }
     if(v->f[2] >= a && v->f[2] < b)
         return true;
     return false;
}

void initSkin(){
    bindings = (binding*)calloc(skindata->vertexCount * 2, sizeof(binding));
    if(bindings == NULL){
        //println("COULD NOT ALLOCATE MEMORY FOR BINDINGS");
        sprintf(title, "COULD NOT ALLOCATE MEMORY FOR BINDINGS");
        glutSetWindowTitle(title);
        exit(-1);
    }
    int i=0;
    numbindings = 0;
    Vec3 *iter;
    for(i=0;i<skindata->vertexCount;i++){
        iter = skindata->vertexList[i];
        //////manoizq
        if(betweenx(iter, -3.05, -4)){
            bind(&lhandbv, iter, 1);
        }else
        ////manoder
        if(betweenx(iter, 3.05, 4)){
            bind(&rhandbv, iter, 1);
        }else
        //munecaizq
        if(betweenx(iter, -2.75, -3.05)){
            bind(&llarmbv, iter, 0.5);
            bind(&lhandbv, iter, 0.5);
        }else
        //munecader
        if(betweenx(iter, 2.75, 3.05)){
            bind(&rlarmbv, iter, 0.5);
            bind(&rhandbv, iter, 0.5);
        }else
        ////anteizq
        if(betweenx(iter, -2.1, -2.75)){
            bind(&llarmbv, iter, 1);
        }else
        //anteder
        if(betweenx(iter, 2.1, 2.75)){
            bind(&rlarmbv, iter, 1);
        }else
        //codoizq
        if(betweenx(iter, -1.75, -2.1)){
            bind(&llarmbv, iter, 0.5);
            bind(&luarmbv, iter, 0.5);
        }else
        //cododer
        if(betweenx(iter, 1.75, 2.1)){
            bind(&rlarmbv, iter, 0.5);
            bind(&ruarmbv, iter, 0.5);
        }else
        //brazoizq
        if(betweenx(iter, -1.2, -1.75) && betweeny(iter, 1.4, 2.35)){
            bind(&luarmbv, iter, 1);
        }else
        //brazoder
        if(betweenx(iter, 1.2, 1.75) && betweeny(iter, 1.4, 2.35)){
            bind(&ruarmbv, iter, 1);
        }else
        //hombroizq
        if(betweenx(iter, -0.5, -1.2) && betweeny(iter, 1.55, 2.3)){
            bind(&luarmbv, iter, 1);
        }else
        //hombroder
        if(betweenx(iter, 0.5, 1.2) && betweeny(iter, 1.55, 2.3)){
            bind(&ruarmbv, iter, 1);
        }else
        
        //cabeza cuello
        if(betweenx(iter, -0.5, 0.5) && betweeny(iter, 2.45, 2.6) && betweenz(iter, -0.5, 0.35)){
            bind(&headbv, iter, 0.5);
            bind(&neckbv, iter, 0.5);
        }else
        //cabeza
        if(betweeny(iter, 2.45, 3.8)){ //recorte
            bind(&headbv, iter, 1);
        }else
        //cuello
        if(betweeny(iter, 2.4, 2.45)){
            bind(&neckbv, iter, 1);
        }else
        //cuello torso
        if(betweeny(iter, 2.3, 2.4)){
            bind(&neckbv, iter, 0.5);
            bind(&chestbv, iter, 0.5);
        }else
        
        //torso pierna izq
        if(betweenx(iter, -0.1, -1.2) && betweeny(iter, -0.6, 0.4)){
            bind(&lulegbv, iter, 0.3);
            bind(&chestbv, iter, 0.3);
            bind(&waistbv, iter, 0.4);
        }else
        //torso pierna der
        if(betweenx(iter, 0.1, 1.2) && betweeny(iter, -0.6, 0.4)){
            bind(&rulegbv, iter, 0.3);
            bind(&chestbv, iter, 0.3);
            bind(&waistbv, iter, 0.4);
        }else
        //torso
        if(betweeny(iter, -0.6, 2.3)){ //recorte
            bind(&chestbv, iter, 1);
        }else
//        //cadera torso
//        if(betweeny(iter, 0.3, 0.7)){
//            bind(&chestbv, iter, 0.5);
//            bind(&waistbv, iter, 0.5);
//        }else
//        //cadera
//        if(betweenx(iter, -0.1, 0.1) && betweeny(iter, -0.6, 0.3)){
//            bind(&waistbv, iter, 1);
//        }else
//        //cadera pierna izq
//        if(betweenx(iter, -0.1, -1.2) && betweeny(iter, -0.6, 0.3)){
//            bind(&lulegbv, iter, 0.5);
//            bind(&waistbv, iter, 0.5);
//        }else
//        //cadera pierna der
//        if(betweenx(iter, 0.1, 1.2) && betweeny(iter, -0.6, 0.3)){
//            bind(&rulegbv, iter, 0.5);
//            bind(&waistbv, iter, 0.5);
//        }else
        
        //pierna izq
        if(betweenx(iter, 0, -1.2) && betweeny(iter, -0.6, -2)){
            bind(&lulegbv, iter, 1);
        }else
        //pierna der
        if(betweenx(iter, 0, 1.2) && betweeny(iter, -0.6, -2)){
            bind(&rulegbv, iter, 1);
        }else
        //rodilla izq
        if(betweenx(iter, 0, -1.2) && betweeny(iter, -2, -2.6)){
            bind(&lulegbv, iter, 0.5);
            bind(&lllegbv, iter, 0.5);
        }else
        //rodilla der
        if(betweenx(iter, 0, 1.2) && betweeny(iter, -2, -2.6)){
            bind(&rulegbv, iter, 0.5);
            bind(&rllegbv, iter, 0.5);
        }else

        //chamorro izq
        if(betweenx(iter, 0, -1.2) && betweeny(iter, -2.6, -3.8)){
            bind(&lllegbv, iter, 1);
        }else
        //chamorro der
        if(betweenx(iter, 0, 1.2) && betweeny(iter, -2.6, -3.8)){
            bind(&rllegbv, iter, 1);
        }else

        //tobillo izq
        if(betweenx(iter, 0, -1.5) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, -4.2)){
            bind(&lllegbv, iter, 0.5);
            bind(&lfootbv, iter, 0.5);
        }else
        //tobillo der
        if(betweenx(iter, 0, 1.5) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, -4.2)){
            bind(&rllegbv, iter, 0.5);
            bind(&rfootbv, iter, 0.5);
        }else
        //pie izq
        if(betweenx(iter, 0, -1.2) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, 1.2)){
            bind(&lfootbv, iter, 1);
        }else
        //pie der
        if(betweenx(iter, 0, 1.2) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, 1.2)){
            bind(&rfootbv, iter, 1);
        }
    }
}

void initParticles(){
    totalshirtparticles = shirtdata->vertexCount;
    totalpantsparticles = pantsdata->vertexCount;
    totalhairparticles = hairdata->vertexCount;
    shirtparticles = (particle*)calloc(totalshirtparticles, sizeof(particle));
    pantsparticles = (particle*)calloc(totalpantsparticles, sizeof(particle));
    hairparticles = (particle*)calloc(totalhairparticles, sizeof(particle));
    
    if(shirtparticles == NULL || pantsparticles == NULL || hairparticles == NULL){
        //println("COULD NOT ALLOCATE MEMORY FOR PARTICLES");
        sprintf(title, "COULD NOT ALLOCATE MEMORY FOR PARTICLES");
        glutSetWindowTitle(title);
        exit(-1);
    }
    
    int i=0;
    ////construye particulas con masa y un punto
    for(i=0; i < totalshirtparticles; i++){
        particle ptemp = particleconstruct(shirtdata->vertexList[i]);
        //si esta a la altura de los hombros, no se cae
        //if(betweeny(ptemp.pos, 2.35, 2.6) ptemp.movable = false;
        ptemp.mass = shirtmass;
        shirtparticles[i] = ptemp;
    }
    
    //igual para pants
    for(i=0; i < totalpantsparticles; i++){
        particle ptemp = particleconstruct(pantsdata->vertexList[i]);
        //si esta a la altura de la cintura, no se cae
        if(betweeny(ptemp.pos, 0.05, 0.4)){
            ptemp.movable = false;
        }
        if(betweeny(ptemp.pos, -0.5, 0.4)){
            bind(&chestbv, ptemp.pos, 1);
        }
        ptemp.mass = pantsmass;
        pantsparticles[i] = ptemp;
    }
    
    //igual para hair
    for(i=0; i < totalhairparticles; i++){
        particle ptemp = particleconstruct(hairdata->vertexList[i]);
        //si esta por el centro, no se cae y se pega a la cabeza
        if(hairoption == 0){ //l. s. kennedy
            if(betweenx(ptemp.pos, -0.25, 0.25) && betweeny(ptemp.pos, 3.6, 4)){
                ptemp.movable = false;
                bind(&headbv, ptemp.pos, 1);
            }
            ptemp.mass = hairmass;
        }
        if(hairoption == 1){ //bob ross
            if(betweenx(ptemp.pos, -0.55, 0.55) && betweeny(ptemp.pos, 2.55, 3.45) && betweenz(ptemp.pos, -0.35, 0.7)){
                ptemp.movable = false;
                bind(&headbv, ptemp.pos, 1);
            }
            ptemp.mass = afromass;
        }
        hairparticles[i] = ptemp;
    }
}

//checa si el resorte ya esta en la lista
//checa si a->b  y  b->a son repetidos
bool isDuplicateSpring(spring *array, int total, particle *pa1, particle *pa2){
    bool flag = false;
    int i=0;
    for(i=0;i<total;i++){
        if((array[i].p1->pos == pa1->pos && array[i].p2->pos == pa2->pos) || (array[i].p1->pos == pa2->pos && array[i].p2->pos == pa1->pos)){
            flag = true;
        }
    }
    return flag;
}

void initSprings(){
    shirtsprings = (spring*)calloc(shirtdata->faceCount * 3, sizeof(spring));
    pantssprings = (spring*)calloc(pantsdata->faceCount * 3, sizeof(spring));
    hairsprings = (spring*)calloc(hairdata->faceCount * 3, sizeof(spring));
    
    if(shirtsprings == NULL || pantssprings == NULL || hairsprings == NULL){
        //println("COULD NOT ALLOCATE MEMORY FOR SPRINGS");
        sprintf(title, "COULD NOT ALLOCATE MEMORY FOR SPRINGS");
        glutSetWindowTitle(title);
        exit(-1);
    }
    
    int i=0;//iterador
    int currentindex = 0;//no toma en cuenta resortes repetidos
    totalshirtsprings = 0;
    totalpantssprings = 0;
    totalhairsprings = 0;
    
    ////agrega 3 resortes (aristas) por cada cara, pero checa que no se repitan
    for(i=0 ;i < shirtdata->faceCount; i++){ //5;i++){//
        ///arista 1
        particle *pt1a = &(shirtparticles[shirtdata->faceList[i]->vertex_index[0]]);
        particle *pt2a = &(shirtparticles[shirtdata->faceList[i]->vertex_index[1]]);
        if(!(isDuplicateSpring(shirtsprings, totalshirtsprings, pt1a, pt2a))){
            spring stemp = springconstruct(pt1a, pt2a);
            shirtsprings[totalshirtsprings] = stemp;
            totalshirtsprings++;
        }
        ///arista 2
        particle *pt1b = &(shirtparticles[shirtdata->faceList[i]->vertex_index[1]]);
        particle *pt2b = &(shirtparticles[shirtdata->faceList[i]->vertex_index[2]]);
        if(!(isDuplicateSpring(shirtsprings, totalshirtsprings, pt1b, pt2b))){
            spring stemp = springconstruct(pt1b, pt2b);
            shirtsprings[totalshirtsprings] = stemp;
            totalshirtsprings++;
        }
        ///arista 3
        particle *pt1c = &(shirtparticles[shirtdata->faceList[i]->vertex_index[2]]);
        particle *pt2c = &(shirtparticles[shirtdata->faceList[i]->vertex_index[0]]);
        if(!(isDuplicateSpring(shirtsprings, totalshirtsprings, pt1c, pt2c))){
            spring stemp = springconstruct(pt1c, pt2c);
            shirtsprings[totalshirtsprings] = stemp;
            totalshirtsprings++;
        }
    }
    
    ////agrega 3 resortes (aristas) por cada cara, pero checa que no se repitan
    for(i=0 ;i < pantsdata->faceCount; i++){ //5;i++){//
        ///arista 1
        particle *pt1a = &(pantsparticles[pantsdata->faceList[i]->vertex_index[0]]);
        particle *pt2a = &(pantsparticles[pantsdata->faceList[i]->vertex_index[1]]);
        if(!(isDuplicateSpring(pantssprings, totalpantssprings, pt1a, pt2a))){
            spring stemp = springconstruct(pt1a, pt2a);
            pantssprings[totalpantssprings] = stemp;
            totalpantssprings++;
        }
        ///arista 2
        particle *pt1b = &(pantsparticles[pantsdata->faceList[i]->vertex_index[1]]);
        particle *pt2b = &(pantsparticles[pantsdata->faceList[i]->vertex_index[2]]);
        if(!(isDuplicateSpring(pantssprings, totalpantssprings, pt1b, pt2b))){
            spring stemp = springconstruct(pt1b, pt2b);
            pantssprings[totalpantssprings] = stemp;
            totalpantssprings++;
        }
        ///arista 3
        particle *pt1c = &(pantsparticles[pantsdata->faceList[i]->vertex_index[2]]);
        particle *pt2c = &(pantsparticles[pantsdata->faceList[i]->vertex_index[0]]);
        if(!(isDuplicateSpring(pantssprings, totalpantssprings, pt1c, pt2c))){
            spring stemp = springconstruct(pt1c, pt2c);
            pantssprings[totalpantssprings] = stemp;
            totalpantssprings++;
        }
    }
    
    ////agrega 3 resortes (aristas) por cada cara, pero checa que no se repitan
    for(i=0 ;i < hairdata->faceCount; i++){ //5;i++){//
        ///arista 1
        particle *pt1a = &(hairparticles[hairdata->faceList[i]->vertex_index[0]]);
        particle *pt2a = &(hairparticles[hairdata->faceList[i]->vertex_index[1]]);
        if(!(isDuplicateSpring(hairsprings, totalhairsprings, pt1a, pt2a))){
            spring stemp = springconstruct(pt1a, pt2a);
            hairsprings[totalhairsprings] = stemp;
            totalhairsprings++;
        }
        ///arista 2
        particle *pt1b = &(hairparticles[hairdata->faceList[i]->vertex_index[1]]);
        particle *pt2b = &(hairparticles[hairdata->faceList[i]->vertex_index[2]]);
        if(!(isDuplicateSpring(hairsprings, totalhairsprings, pt1b, pt2b))){
            spring stemp = springconstruct(pt1b, pt2b);
            hairsprings[totalhairsprings] = stemp;
            totalhairsprings++;
        }
        ///arista 3
        particle *pt1c = &(hairparticles[hairdata->faceList[i]->vertex_index[2]]);
        particle *pt2c = &(hairparticles[hairdata->faceList[i]->vertex_index[0]]);
        if(!(isDuplicateSpring(hairsprings, totalhairsprings, pt1c, pt2c))){
            spring stemp = springconstruct(pt1c, pt2c);
            hairsprings[totalhairsprings] = stemp;
            totalhairsprings++;
        }
    }
}
