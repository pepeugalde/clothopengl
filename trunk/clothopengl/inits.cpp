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

bodyvertex waistbv, chestbv, abdomenbv, neckbv, headbv, headtopbv, 
           rshoulderbv, relbowbv, rwristbv, rhandtopbv, lshoulderbv, lelbowbv, lwristbv, lhandtopbv, 
           rulegbv, rkneebv, ranklebv, rfoottopbv, lulegbv, lkneebv, lanklebv, lfoottopbv, 
           rabdomenbv, labdomenbv, rneckbv, lneckbv;

capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc, 
        chestc, rchestc, lchestc, waistc, rwaistc, lwaistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

treenode waistn, abdomenn, neckn, headn, 
            rshouldern, relbown, rwristn, lshouldern, lelbown, lwristn, 
            rulegn, rkneen, ranklen, lulegn, lkneen, lanklen;

////STRUCTS
objLoader *skindata;
objLoader *shirtdata;
objLoader *pantsdata;
objLoader *hairdata;

//angulos del cuerpo
GLfloat bodypos[16];

treenode   *nodes[NUMNODES];
bodyvertex *bodyverts[NUMVERTS];
capsule    *caps[NUMCAPS];

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
    
    Vec3 waistv, chestv, abdomenv, neckv, headv, headtopv, 
     rshoulderv,relbowv, rwristv, rhandtopv, lshoulderv, lelbowv, lwristv, lhandtopv, 
     rulegv, rkneev, ranklev, rfoottopv, lulegv, lkneev, lanklev, lfoottopv, 
     rabdomenv, labdomenv, rneckv, lneckv;
    
    waistv.f[0] = 0;
    waistv.f[1] = -0.1;
    waistv.f[2] = 0;
    waistbv.v = waistv;
    
    chestv.f[0] = 0;
    chestv.f[1] = 1.8;
    chestv.f[2] = 0;
    chestbv.v = chestv;    
    
    abdomenv.f[0] = 0;
    abdomenv.f[1] = 0.8;
    abdomenv.f[2] = 0.05;
    abdomenbv.v = abdomenv;
    
    rabdomenv.f[0] = -(labdomenv.f[0] = -0.25);
    rabdomenv.f[1] = labdomenv.f[1] = 0.6;
    rabdomenv.f[2] = labdomenv.f[2] = 0.05;
    rabdomenbv.v = rabdomenv;
    labdomenbv.v = labdomenv;
    
    rneckv.f[0] = -(lneckv.f[0] = -0.3);
    rneckv.f[1] = lneckv.f[1] = 1.8;
    rneckv.f[2] = lneckv.f[2] = 0;
    rneckbv.v = rneckv;
    lneckbv.v = lneckv;

    neckv.f[0] = 0;
    neckv.f[1] = 2.1;
    neckv.f[2] = -0.1;
    neckbv.v = neckv;
    
    headv.f[0] = 0;
    headv.f[1] = 2.8;
    headv.f[2] = 0.15;
    headbv.v = headv;
    
    headtopv.f[0] = 0;
    headtopv.f[1] = 3.35;
    headtopv.f[2] = 0.1;
    headtopbv.v = headtopv;
    
    rshoulderv.f[0] = -(lshoulderv.f[0] = -0.7);
    rshoulderv.f[1] = lshoulderv.f[1]   = 1.9;
    rshoulderv.f[2] = lshoulderv.f[2]   = -0.2;
    rshoulderbv.v = rshoulderv;
    lshoulderbv.v = lshoulderv;
    
    relbowv.f[0] = -(lelbowv.f[0] = -1.9);
    relbowv.f[1] = lelbowv.f[1]   = 1.8;
    relbowv.f[2] = lelbowv.f[2]   = -0.35;
    relbowbv.v = relbowv;
    lelbowbv.v = lelbowv;
    rwristv.f[0] = -(lwristv.f[0] = -3);
    rwristv.f[1] = lwristv.f[1]   = 1.7;
    rwristv.f[2] = lwristv.f[2]   = 0;
    rwristbv.v = rwristv;
    lwristbv.v = lwristv;
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
    rkneev.f[0] = -(lkneev.f[0] = -0.6);
    rkneev.f[1] = lkneev.f[1]   = -2.2;
    rkneev.f[2] = lkneev.f[2]   = 0;
    rkneebv.v = rkneev;
    lkneebv.v = lkneev;
    ranklev.f[0] = -(lanklev.f[0] = -0.7);
    ranklev.f[1] = lanklev.f[1]   = -4.5;
    ranklev.f[2] = lanklev.f[2]   = -0.2;
    ranklebv.v = ranklev;
    lanklebv.v = lanklev;
    rfoottopv.f[0] = -(lfoottopv.f[0] = -0.85);
    rfoottopv.f[1] = lfoottopv.f[1]   = -4.5;
    rfoottopv.f[2] = lfoottopv.f[2]   = 0.8;
    rfoottopbv.v = rfoottopv;
    lfoottopbv.v = lfoottopv;
    
    //seleccionables
    bodyverts[1] = &waistbv;
    bodyverts[2] = &abdomenbv;
    bodyverts[3] = &neckbv;
    bodyverts[4] = &headbv;
    
    bodyverts[5] = &rshoulderbv;
    bodyverts[6] = &relbowbv;
    bodyverts[7] = &rwristbv;
    
    bodyverts[8] = &lshoulderbv;
    bodyverts[9] = &lelbowbv;
    bodyverts[0] = &lwristbv;
    
    bodyverts[10] = &rulegbv;
    bodyverts[11] = &rkneebv;
    bodyverts[12] = &ranklebv;
    
    bodyverts[13] = &lulegbv;
    bodyverts[14] = &lkneebv;
    bodyverts[15] = &lanklebv;
    
    //no seleccionables
    bodyverts[16] = &rabdomenbv;
    bodyverts[17] = &labdomenbv;
    bodyverts[18] = &rneckbv;
    bodyverts[19] = &lneckbv;
    
    bodyverts[20] = &headtopbv;
    bodyverts[21] = &rhandtopbv;
    bodyverts[22] = &lhandtopbv;
    bodyverts[23] = &rfoottopbv;
    bodyverts[24] = &lfoottopbv;
}

void initCapsules(){
    waistc.bv1 = &waistbv;
    waistc.bv2 = &abdomenbv;
    rwaistc.bv1 = &rulegbv;
    rwaistc.bv2 = &rabdomenbv;
    lwaistc.bv1 = &lulegbv;
    lwaistc.bv2 = &labdomenbv;
    
    chestc.bv1 = &abdomenbv;
    chestc.bv2 = &chestbv;
    rchestc.bv1 = &rabdomenbv;
    rchestc.bv2 = &rneckbv;
    lchestc.bv1 = &labdomenbv;
    lchestc.bv2 = &lneckbv;
    
    waistc.r = 0.45;
    waistc.sib = &rwaistc;
    rwaistc.r = lwaistc.r = 0.3;
    rwaistc.sib = &lwaistc;
    lwaistc.sib = NULL;
    chestc.r = 0.5;
    chestc.sib = &rchestc;
    rchestc.r = lchestc.r = 0.4;
    rchestc.sib = &lchestc;
    lchestc.sib = NULL;
    
    neckc.bv1 = &neckbv;
    neckc.bv2 = &headbv;
    headc.bv1 = &headbv;
    headc.bv2 = &headtopbv;
    neckc.r = 0.3;
    headc.r = 0.45;
    neckc.sib = headc.sib = NULL;
    
    rshoulderc.bv1 = &neckbv;
    rshoulderc.bv2 = &rshoulderbv;
    ruarmc.bv1 = &rshoulderbv;
    ruarmc.bv2 = &relbowbv;
    rlarmc.bv1 = &relbowbv;
    rlarmc.bv2 = &rwristbv;
    rhandc.bv1 = &rwristbv;
    rhandc.bv2 = &rhandtopbv;
    
    lshoulderc.bv1 = &neckbv;
    lshoulderc.bv2 = &lshoulderbv;
    luarmc.bv1 = &lshoulderbv;
    luarmc.bv2 = &lelbowbv;
    llarmc.bv1 = &lelbowbv;
    llarmc.bv2 = &lwristbv;
    lhandc.bv1 = &lwristbv;
    lhandc.bv2 = &lhandtopbv;
    
    rshoulderc.r = lshoulderc.r = 0.4;
    ruarmc.r = luarmc.r = 0.35;
    rlarmc.r = llarmc.r = 0.25;
    rhandc.r = lhandc.r = 0.25;
    rshoulderc.sib = ruarmc.sib = rlarmc.sib = rhandc.sib = NULL;
    lshoulderc.sib = luarmc.sib = llarmc.sib = lhandc.sib = NULL;
    
    rulegc.bv1 = &rulegbv;
    rulegc.bv2 = &rkneebv;
    rllegc.bv1 = &rkneebv;
    rllegc.bv2 = &ranklebv;
    rfootc.bv1 = &ranklebv;
    rfootc.bv2 = &rfoottopbv;
    
    lulegc.bv1 = &lulegbv;
    lulegc.bv2 = &lkneebv;
    lllegc.bv1 = &lkneebv;
    lllegc.bv2 = &lanklebv;
    lfootc.bv1 = &lanklebv;
    lfootc.bv2 = &lfoottopbv;
    
    rulegc.r = lulegc.r = 0.4;
    rllegc.r = lllegc.r = 0.3;
    rfootc.r = lfootc.r = 0.25;
    rulegc.sib = rllegc.sib = rfootc.sib = NULL;
    lulegc.sib = lllegc.sib = lfootc.sib = NULL;
    
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
    
    caps[18] = &rwaistc;
    caps[19] = &lwaistc;
    caps[20] = &rchestc;
    caps[21] = &lchestc;
}

void initNodes(){
    
    //waist
    waistn.cap = &waistc;
    waistn.bv1 = &waistbv;
    waistn.id = 1;
    waistn.sibling = &rulegn;
    waistn.child = &abdomenn;
    
    //abdomen
    abdomenn.cap = &chestc;
    abdomenn.bv1 = &abdomenbv;
    abdomenn.id = 2;
    abdomenn.sibling = NULL;
    abdomenn.child = &neckn;
    
    //Neck
    neckn.cap = &neckc;
    neckn.bv1 = &neckbv;
    neckn.id = 3;
    neckn.sibling = &rshouldern;
    neckn.child = &headn;
    
    //Head
    headn.cap = &headc;
    headn.bv1 = &headbv;
    headn.id = 4;
    headn.sibling = NULL;
    headn.child = NULL;
    
    //shoulder
    rshouldern.cap = &rshoulderc;
    rshouldern.bv1 = &rshoulderbv;
    rshouldern.id = 5;
    rshouldern.sibling = &lshouldern;
    rshouldern.child = &relbown;
    
    //relbow
    relbown.cap = &ruarmc;
    relbown.bv1 = &relbowbv;
    relbown.id = 6;
    relbown.sibling = NULL;
    relbown.child = &rwristn;
    
    //rwrist
    rwristn.cap = &rlarmc;
    rwristn.bv1 = &rwristbv;
    rwristn.id = 7;
    rwristn.sibling = NULL;        
    rwristn.child = NULL;
    
    //lshoulder
    lshouldern.cap = &lshoulderc;
    lshouldern.bv1 = &lshoulderbv;
    lshouldern.id = 8;
    lshouldern.sibling = NULL;
    lshouldern.child = &lelbown;
    
    //lelbow
    lelbown.cap = &luarmc;
    lelbown.bv1 = &lelbowbv;
    lelbown.id = 9;
    lelbown.sibling = NULL;        
    lelbown.child = &lwristn;
    
    //lwrist
    lwristn.cap = &llarmc;
    lwristn.bv1 = &lwristbv;
    lwristn.id = 0;
    lwristn.sibling = NULL;        
    lwristn.child = NULL;
    
    //ruleg
    rulegn.cap = &rulegc;
    rulegn.bv1 = &rulegbv;
    rulegn.id = 10;
    rulegn.sibling = &lulegn;       
    rulegn.child = &rkneen; 
    
    //rlleg
    rkneen.cap = &rllegc;
    rkneen.bv1 = &rkneebv;
    rkneen.id = 11;
    rkneen.sibling = NULL;
    rkneen.child = &ranklen;
    
    //rankle
    ranklen.cap = &rfootc;
    ranklen.bv1 = &ranklebv;
    ranklen.id = 12;
    ranklen.sibling = NULL;
    ranklen.child = NULL;
    
    //luleg
    lulegn.cap = &lulegc;
    lulegn.bv1 = &lulegbv;
    lulegn.id = 13;
    lulegn.sibling = NULL;       
    lulegn.child = &lkneen;                      
    
    //llleg
    lkneen.cap = &lllegc;
    lkneen.bv1 = &lkneebv;
    lkneen.id = 14;
    lkneen.sibling = NULL;        
    lkneen.child = &lanklen;
    
    //lankle
    lanklen.cap = &lfootc;
    lanklen.bv1 = &lanklebv;
    lanklen.id = 15;
    lanklen.sibling = NULL;        
    lanklen.child = NULL;
    
    //seleccionables
    nodes[1] = &waistn;
    nodes[2] = &abdomenn;
    nodes[3] = &neckn;
    nodes[4] = &headn;
    
    nodes[5] = &rshouldern;
    nodes[6] = &relbown;
    nodes[7] = &rwristn;
    
    nodes[8] = &lshouldern;
    nodes[9] = &lelbown;
    nodes[0] = &lwristn;
    
    nodes[10] = &rulegn;
    nodes[11] = &rkneen;
    nodes[12] = &ranklen;
    
    nodes[13] = &lulegn;
    nodes[14] = &lkneen;
    nodes[15] = &lanklen;
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
sprintf(title, "bind: %f   %f   %f      %d / %d", nbv->v.f[0], nbv->v.f[1], nbv->v.f[2], numbindings, (skindata->vertexCount + shirtdata->vertexCount + pantsdata->vertexCount + hairdata->vertexCount) * 2);
glutSetWindowTitle(title);
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
    bindings = (binding*)calloc((skindata->vertexCount + shirtdata->vertexCount + pantsdata->vertexCount + hairdata->vertexCount) * 2, sizeof(binding));
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
            bind(&lwristbv, iter, 1);
        }else
        ////manoder
        if(betweenx(iter, 3.05, 4)){
            bind(&rwristbv, iter, 1);
        }else
        //munecaizq
        if(betweenx(iter, -2.75, -3.05)){
            bind(&lelbowbv, iter, 0.5);
            bind(&lwristbv, iter, 0.5);
        }else
        //munecader
        if(betweenx(iter, 2.75, 3.05)){
            bind(&relbowbv, iter, 0.5);
            bind(&rwristbv, iter, 0.5);
        }else
        ////anteizq
        if(betweenx(iter, -2.1, -2.75)){
            bind(&lelbowbv, iter, 1);
        }else
        //anteder
        if(betweenx(iter, 2.1, 2.75)){
            bind(&relbowbv, iter, 1);
        }else
        //codoizq
        if(betweenx(iter, -1.75, -2.1)){
            bind(&lelbowbv, iter, 0.5);
            bind(&lshoulderbv, iter, 0.5);
        }else
        //cododer
        if(betweenx(iter, 1.75, 2.1)){
            bind(&relbowbv, iter, 0.5);
            bind(&rshoulderbv, iter, 0.5);
        }else
        //brazoizq
        if(betweenx(iter, -1.2, -1.75) && betweeny(iter, 1.4, 2.35)){
            bind(&lshoulderbv, iter, 1);
        }else
        //brazoder
        if(betweenx(iter, 1.2, 1.75) && betweeny(iter, 1.4, 2.35)){
            bind(&rshoulderbv, iter, 1);
        }else
        //hombroizq
        if(betweenx(iter, -0.5, -1.2) && betweeny(iter, 1.55, 2.3)){
            bind(&lshoulderbv, iter, 1);
        }else
        //hombroder
        if(betweenx(iter, 0.5, 1.2) && betweeny(iter, 1.55, 2.3)){
            bind(&rshoulderbv, iter, 1);
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
            bind(&abdomenbv, iter, 0.5);
        }else
        
        //torso pierna izq
        if(betweenx(iter, -0.1, -1.2) && betweeny(iter, -0.6, 0.4)){
            bind(&lulegbv, iter, 0.3);
            bind(&abdomenbv, iter, 0.3);
            bind(&waistbv, iter, 0.4);
        }else
        //torso pierna der
        if(betweenx(iter, 0.1, 1.2) && betweeny(iter, -0.6, 0.4)){
            bind(&rulegbv, iter, 0.3);
            bind(&abdomenbv, iter, 0.3);
            bind(&waistbv, iter, 0.4);
        }else
        //torso
        if(betweeny(iter, -0.6, 2.3)){ //recorte
            bind(&abdomenbv, iter, 1);
        }else
//        //cadera torso
//        if(betweeny(iter, 0.3, 0.7)){
//            bind(&abdomenbv, iter, 0.5);
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
            bind(&lkneebv, iter, 0.5);
        }else
        //rodilla der
        if(betweenx(iter, 0, 1.2) && betweeny(iter, -2, -2.6)){
            bind(&rulegbv, iter, 0.5);
            bind(&rkneebv, iter, 0.5);
        }else

        //chamorro izq
        if(betweenx(iter, 0, -1.2) && betweeny(iter, -2.6, -3.8)){
            bind(&lkneebv, iter, 1);
        }else
        //chamorro der
        if(betweenx(iter, 0, 1.2) && betweeny(iter, -2.6, -3.8)){
            bind(&rkneebv, iter, 1);
        }else

        //tobillo izq
        if(betweenx(iter, 0, -1.5) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, -4.2)){
            bind(&lkneebv, iter, 0.5);
            bind(&lanklebv, iter, 0.5);
        }else
        //tobillo der
        if(betweenx(iter, 0, 1.5) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, -4.2)){
            bind(&rkneebv, iter, 0.5);
            bind(&ranklebv, iter, 0.5);
        }else
        //pie izq
        if(betweenx(iter, 0, -1.2) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, 1.2)){
            bind(&lanklebv, iter, 1);
        }else
        //pie der
        if(betweenx(iter, 0, 1.2) && betweeny(iter, -3.8, -4.9) && betweenz(iter, 0.2, 1.2)){
            bind(&ranklebv, iter, 1);
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
            //bind(&abdomenbv, ptemp.pos, 1);
        }
        ptemp.mass = pantsmass;
        pantsparticles[i] = ptemp;
    }
    

    //igual para hair
    for(i=0; i < totalhairparticles; i++){
        particle ptemp = particleconstruct(hairdata->vertexList[i]);
        //si esta por el centro, no se cae y se pega a la cabeza
//        if(hairoption == 0){ //l. s. kennedy
//            if(betweenx(ptemp.pos, -0.25, 0.25) && betweeny(ptemp.pos, 3.6, 4)){
//                ptemp.movable = false;
//                bind(&headbv, ptemp.pos, 1);
//            }
//            ptemp.mass = hairmass;
//        }
//        if(hairoption == 1){ //bob ross
//            if(betweenx(ptemp.pos, -0.55, 0.55) && betweeny(ptemp.pos, 2.55, 3.45) && betweenz(ptemp.pos, -0.35, 0.7)){
//                ptemp.movable = false;
//                bind(&headbv, ptemp.pos, 1);
//            }
//            ptemp.mass = afromass;
//        }
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
