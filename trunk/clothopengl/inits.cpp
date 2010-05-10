#include "inits.h"
#include "clothfunc.h"

char title[200];

Vec3 gravity = Vec3construct(0,-0.2,0);

int shirtoption = 0;
int pantsoption = 0;
int hairoption  = 0;

float shirtmass = 30;
float pantsmass = 30;
float hairmass  = 20;
float afromass  = 100;

bodyvertex waistbv, chestbv, abdomenbv, neckbv, headbv, headtopbv, 
           rshoulderbv, relbowbv, rwristbv, rfingersbv, lshoulderbv, lelbowbv, lwristbv, lfingersbv, 
           rulegbv, rkneebv, ranklebv, rtoesbv, lulegbv, lkneebv, lanklebv, ltoesbv, 
           rabdomenbv, labdomenbv, rneckbv, lneckbv, rbuttbv, lbuttbv, nosebv, nosetipbv;

capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc, 
        chestc, rchestc, lchestc, waistc, rwaistc, lwaistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc, nosec;

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
     rshoulderv,relbowv, rwristv, rfingersv, lshoulderv, lelbowv, lwristv, lfingersv, 
     rulegv, rkneev, ranklev, rtoesv, lulegv, lkneev, lanklev, ltoesv, 
     rabdomenv, labdomenv, rneckv, lneckv, rbuttv, lbuttv, nosev, nosetipv;
    
    waistv.f[0] = 0;
    waistv.f[1] = -0.15;
    waistv.f[2] = 0;
    waistbv.v = waistv;
    
    chestv.f[0] = 0;
    chestv.f[1] = 1.7;
    chestv.f[2] = -0.05;
    chestbv.v = chestv;    
    
    abdomenv.f[0] = 0;
    abdomenv.f[1] = 0.5;
    abdomenv.f[2] = 0.05;
    abdomenbv.v = abdomenv;
    
    rabdomenv.f[0] = -(labdomenv.f[0] = -0.25);
    rabdomenv.f[1] = labdomenv.f[1] = 0.5;
    rabdomenv.f[2] = labdomenv.f[2] = 0.05;
    rabdomenbv.v = rabdomenv;
    labdomenbv.v = labdomenv;
    
    rneckv.f[0] = -(lneckv.f[0] = -0.3);
    rneckv.f[1] = lneckv.f[1] = 1.75;
    rneckv.f[2] = lneckv.f[2] = 0.05;
    rneckbv.v = rneckv;
    lneckbv.v = lneckv;

    neckv.f[0] = 0;
    neckv.f[1] = 2.1;
    neckv.f[2] = -0.1;
    neckbv.v = neckv;
    
    headv.f[0] = 0;
    headv.f[1] = 2.85;
    headv.f[2] = 0.15;
    headbv.v = headv;
    
    headtopv.f[0] = 0;
    headtopv.f[1] = 3.35;
    headtopv.f[2] = 0.05;
    headtopbv.v = headtopv;
    
    rshoulderv.f[0] = -(lshoulderv.f[0] = -0.7);
    rshoulderv.f[1] = lshoulderv.f[1]   = 2;
    rshoulderv.f[2] = lshoulderv.f[2]   = -0.2;
    rshoulderbv.v = rshoulderv;
    lshoulderbv.v = lshoulderv;
    
    relbowv.f[0] = -(lelbowv.f[0] = -1.9);
    relbowv.f[1] = lelbowv.f[1]   = 1.85;
    relbowv.f[2] = lelbowv.f[2]   = -0.35;
    relbowbv.v = relbowv;
    lelbowbv.v = lelbowv;
    rwristv.f[0] = -(lwristv.f[0] = -3);
    rwristv.f[1] = lwristv.f[1]   = 1.7;
    rwristv.f[2] = lwristv.f[2]   = 0;
    rwristbv.v = rwristv;
    lwristbv.v = lwristv;
    rfingersv.f[0] = -(lfingersv.f[0] = -3.6);
    rfingersv.f[1] = lfingersv.f[1]   = 1.65;
    rfingersv.f[2] = lfingersv.f[2]   = 0.25;
    rfingersbv.v = rfingersv;
    lfingersbv.v = lfingersv;
    
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
    ranklev.f[1] = lanklev.f[1]   = -4.3;
    ranklev.f[2] = lanklev.f[2]   = -0.2;
    ranklebv.v = ranklev;
    lanklebv.v = lanklev;
    rtoesv.f[0] = -(ltoesv.f[0] = -0.85);
    rtoesv.f[1] = ltoesv.f[1]   = -4.5;
    rtoesv.f[2] = ltoesv.f[2]   = 0.8;
    rtoesbv.v = rtoesv;
    ltoesbv.v = ltoesv;
    
    rbuttv.f[0] = -(lbuttv.f[0] = -0.3);
    rbuttv.f[1] = lbuttv.f[1]   = -0.1;
    rbuttv.f[2] = lbuttv.f[2]   = -0.2;
    rbuttbv.v = rbuttv;
    lbuttbv.v = lbuttv;
    
///
    nosev.f[0] = 0;
    nosev.f[1] = 3;
    nosev.f[2] = 0.6;
    nosebv.v = nosev;
    nosetipv.f[0] = 0;
    nosetipv.f[1] = 2.95;
    nosetipv.f[2] = 0.85;
    nosetipbv.v = nosetipv;
    
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
    bodyverts[21] = &rfingersbv;
    bodyverts[22] = &lfingersbv;
    bodyverts[23] = &rtoesbv;
    bodyverts[24] = &ltoesbv;
    bodyverts[25] = &rbuttbv;
    bodyverts[26] = &lbuttbv;
    bodyverts[27] = &chestbv;
///
    bodyverts[28] = &nosebv;
    bodyverts[29] = &nosetipbv;
}

void initCapsules(){
    waistc.bv1 = &waistbv;
    waistc.bv2 = &abdomenbv;
    rwaistc.bv1 = &rbuttbv;
    rwaistc.bv2 = &rabdomenbv;
    lwaistc.bv1 = &lbuttbv;
    lwaistc.bv2 = &labdomenbv;
    
    chestc.bv1 = &abdomenbv;
    chestc.bv2 = &chestbv;
    rchestc.bv1 = &rabdomenbv;
    rchestc.bv2 = &rneckbv;
    lchestc.bv1 = &labdomenbv;
    lchestc.bv2 = &lneckbv;
    
    waistc.r = 0.5;
    waistc.sib = &rwaistc;
    rwaistc.r = lwaistc.r = 0.4;
    rwaistc.sib = &lwaistc;
    lwaistc.sib = NULL;
    chestc.r = 0.55;
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
    neckc.sib = headc.sib = &nosec;// NULL;
    
    rshoulderc.bv1 = &neckbv;
    rshoulderc.bv2 = &rshoulderbv;
    ruarmc.bv1 = &rshoulderbv;
    ruarmc.bv2 = &relbowbv;
    rlarmc.bv1 = &relbowbv;
    rlarmc.bv2 = &rwristbv;
    rhandc.bv1 = &rwristbv;
    rhandc.bv2 = &rfingersbv;
    
    lshoulderc.bv1 = &neckbv;
    lshoulderc.bv2 = &lshoulderbv;
    luarmc.bv1 = &lshoulderbv;
    luarmc.bv2 = &lelbowbv;
    llarmc.bv1 = &lelbowbv;
    llarmc.bv2 = &lwristbv;
    lhandc.bv1 = &lwristbv;
    lhandc.bv2 = &lfingersbv;
    
    rshoulderc.r = lshoulderc.r = 0.35;
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
    rfootc.bv2 = &rtoesbv;
    
    lulegc.bv1 = &lulegbv;
    lulegc.bv2 = &lkneebv;
    lllegc.bv1 = &lkneebv;
    lllegc.bv2 = &lanklebv;
    lfootc.bv1 = &lanklebv;
    lfootc.bv2 = &ltoesbv;
    
    rulegc.r = lulegc.r = 0.4;
    rllegc.r = lllegc.r = 0.3;
    rfootc.r = lfootc.r = 0.25;
    rulegc.sib = rllegc.sib = rfootc.sib = NULL;
    lulegc.sib = lllegc.sib = lfootc.sib = NULL;
    
///
    nosec.bv1 = &nosebv;
    nosec.bv2 = &nosetipbv;
    nosec.r = 0.1;
    nosec.sib = NULL;
    
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
///
    caps[22] = &nosec;
}

void initNodes(){
    
    //waist
    waistn.cap = &waistc;
    waistn.bv = &waistbv;
    waistn.id = 1;
    nodes[1] = &waistn;
    waistn.sib = &rulegn;
    waistn.child = &abdomenn;
    
    //abdomen
    abdomenn.cap = &chestc;
    abdomenn.bv = &abdomenbv;
    abdomenn.id = 2;
    nodes[2] = &abdomenn;
    abdomenn.sib = NULL;
    abdomenn.child = &neckn;
    
    //Neck
    neckn.cap = &neckc;
    neckn.bv = &neckbv;
    neckn.id = 3;
    nodes[3] = &neckn;
    neckn.sib = &rshouldern;
    neckn.child = &headn;
    
    //Head
    headn.cap = &headc;
    headn.bv = &headbv;
    headn.id = 4;
    nodes[4] = &headn;
    headn.sib = NULL;
    headn.child = NULL;
    
    //shoulder
    rshouldern.cap = &ruarmc;
    rshouldern.bv = &rshoulderbv;
    rshouldern.id = 5;
    nodes[5] = &rshouldern;
    rshouldern.sib = &lshouldern;
    rshouldern.child = &relbown;
    
    //relbow
    relbown.cap = &rlarmc;
    relbown.bv = &relbowbv;
    relbown.id = 6;
    nodes[6] = &relbown;
    relbown.sib = NULL;
    relbown.child = &rwristn;
    
    //rwrist
    rwristn.cap = &rhandc;
    rwristn.bv = &rwristbv;
    rwristn.id = 7;
    nodes[7] = &rwristn;
    rwristn.sib = NULL;        
    rwristn.child = NULL;
    
    //lshoulder
    lshouldern.cap = &luarmc;
    lshouldern.bv = &lshoulderbv;
    lshouldern.id = 8;
    nodes[8] = &lshouldern;
    lshouldern.sib = NULL;
    lshouldern.child = &lelbown;
    
    //lelbow
    lelbown.cap = &llarmc;
    lelbown.bv = &lelbowbv;
    lelbown.id = 9;
    nodes[9] = &lelbown;
    lelbown.sib = NULL;        
    lelbown.child = &lwristn;
    
    //lwrist
    lwristn.cap = &lhandc;
    lwristn.bv = &lwristbv;
    lwristn.id = 0;
    nodes[0] = &lwristn;
    lwristn.sib = NULL;        
    lwristn.child = NULL;
    
    //ruleg
    rulegn.cap = &rulegc;
    rulegn.bv = &rulegbv;
    rulegn.id = 10;
    nodes[10] = &rulegn;
    rulegn.sib = &lulegn;       
    rulegn.child = &rkneen; 
    
    //rlleg
    rkneen.cap = &rllegc;
    rkneen.bv = &rkneebv;
    rkneen.id = 11;
    nodes[11] = &rkneen;
    rkneen.sib = NULL;
    rkneen.child = &ranklen;
    
    //rankle
    ranklen.cap = &rfootc;
    ranklen.bv = &ranklebv;
    ranklen.id = 12;
    nodes[12] = &ranklen;
    ranklen.sib = NULL;
    ranklen.child = NULL;
    
    //luleg
    lulegn.cap = &lulegc;
    lulegn.bv = &lulegbv;
    lulegn.id = 13;
    nodes[13] = &lulegn;
    lulegn.sib = NULL;       
    lulegn.child = &lkneen;                      
    
    //llleg
    lkneen.cap = &lllegc;
    lkneen.bv = &lkneebv;
    lkneen.id = 14;
    nodes[14] = &lkneen;
    lkneen.sib = NULL;        
    lkneen.child = &lanklen;
    
    //lankle
    lanklen.cap = &lfootc;
    lanklen.bv = &lanklebv;
    lanklen.id = 15;
    nodes[15] = &lanklen;
    lanklen.sib = NULL;        
    lanklen.child = NULL;
}

//Carga objs a skindata, shirtdata y pantsdata
void initObj(){
    skindata = new objLoader();
    skindata->load("surprise.obj");//("human.obj");
    shirtdata = new objLoader();
    pantsdata = new objLoader();
    hairdata = new objLoader();
    
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

//distancia 3d entre 2 puntos
float vDistance(Vec3 *v1, Vec3 *v2){
    return sqrt(pow((v1->f[0]-v2->f[0]),2) + pow((v1->f[1]-v2->f[1]),2) + pow((v1->f[2]-v2->f[2]),2));
}
//distancia 3d entre 2 puntos
float distance3d(float x1,float y1,float z1,float x2,float y2,float z2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2) + pow((z1-z2),2));
}
//distancea 2d entre 2 puntos
float distance2d(float x1,float y1,float x2,float y2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}

//saca un punto de una capsula
float disttocap(capsule *cap, Vec3 *h, float hr, Vec3 *N){

    ////dist entre punto uno de cap y *h
    float D[3];
    D[0] = h->f[0] - cap->bv1->v.f[0];
    D[1] = h->f[1] - cap->bv1->v.f[1];
    D[2] = h->f[2] - cap->bv1->v.f[2];
    
    //vector unitario
    float A[3];
    A[0] = (cap->bv2->v.f[0] - cap->bv1->v.f[0]) / (sqrt((cap->bv2->v.f[0] - cap->bv1->v.f[0])*(cap->bv2->v.f[0] - cap->bv1->v.f[0]) + (cap->bv2->v.f[1] - cap->bv1->v.f[1]) * (cap->bv2->v.f[1]-cap->bv1->v.f[1]) + (cap->bv2->v.f[2]-cap->bv1->v.f[2]) * (cap->bv2->v.f[2]-cap->bv1->v.f[2])));
    A[1] = (cap->bv2->v.f[1] - cap->bv1->v.f[1]) / (sqrt((cap->bv2->v.f[0] - cap->bv1->v.f[0])*(cap->bv2->v.f[0] - cap->bv1->v.f[0]) + (cap->bv2->v.f[1] - cap->bv1->v.f[1]) * (cap->bv2->v.f[1]-cap->bv1->v.f[1]) + (cap->bv2->v.f[2]-cap->bv1->v.f[2]) * (cap->bv2->v.f[2]-cap->bv1->v.f[2])));
    A[2] = (cap->bv2->v.f[2] - cap->bv1->v.f[2]) / (sqrt((cap->bv2->v.f[0] - cap->bv1->v.f[0])*(cap->bv2->v.f[0] - cap->bv1->v.f[0]) + (cap->bv2->v.f[1] - cap->bv1->v.f[1]) * (cap->bv2->v.f[1]-cap->bv1->v.f[1]) + (cap->bv2->v.f[2]-cap->bv1->v.f[2]) * (cap->bv2->v.f[2]-cap->bv1->v.f[2])));
    
    //distancia entre el punto 1 de la cap y la proyeccion de *h
    float d = D[0] * A[0] + D[1] * A[1] + D[2] * A[2];
    if(d<0)
        d = 0;
    float caplen = vDistance(&(cap->bv1->v), &(cap->bv2->v));
    if(d>caplen)
        d = caplen;
    
    //punto donde se proyecta *h sobre la linea de la cap
    float R[3];
    R[0] = cap->bv1->v.f[0] + (A[0] * d);
    R[1] = cap->bv1->v.f[1] + (A[1] * d);
    R[2] = cap->bv1->v.f[2] + (A[2] * d);
    float b = distance3d(h->f[0],h->f[1],h->f[2], R[0],R[1],R[2]);
    
    //que tan adentro de la cap esta *h
    float depth = 0;
    
    //if(b < (cap->r + hr)){
        depth = b - (cap->r + hr);
    //}
    
    if(depth < 0){
        N->f[0] = (h->f[0] - R[0]) / b;
        N->f[1] = (h->f[1] - R[1]) / b;
        N->f[2] = (h->f[2] - R[2]) / b;
        
//        h->f[0] -= N->f[0] * depth;
//        h->f[1] -= N->f[1] * depth;
//        h->f[2] -= N->f[2] * depth;
    }
      
    return depth;
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
    int j=0; //
    Vec3 N = Vec3construct(0,0,0);
    numbindings = 0;
    Vec3 *iter;
    for(i=0;i<skindata->vertexCount;i++){
        
        iter = skindata->vertexList[i];
        
//        /////////////////
//        capsule *mincap1 = NULL;
//        capsule *mincap2 = NULL;
//        float dc1, dc2;
//        float dc1v1, dc1v2, dc2v1, dc2v2;
//        for(j=0;j<NUMCAPS;j++){
//            if(mincap1 == NULL){
//                mincap1 = caps[j];
//                dc1 = disttocap(caps[j], iter, 0, &N);
//                dc1v1 = vDistance(&caps[j]->bv1->v, iter);
//                dc1v2 = vDistance(&caps[j]->bv2->v, iter);
//            }else if(mincap2 == NULL){
//                mincap2 = caps[j];
//                dc2 = disttocap(caps[j], iter, 0, &N);
//                dc2v1 = vDistance(&caps[j]->bv1->v, iter);
//                dc2v2 = vDistance(&caps[j]->bv2->v, iter);
//            }else{
//                if(disttocap(caps[j], iter, 0, &N) < dc1){
//                    mincap1 = caps[j];
//                    dc1 = disttocap(caps[j], iter, 0, &N);
//                    dc1v1 = vDistance(&caps[j]->bv1->v, iter);
//                    dc1v2 = vDistance(&caps[j]->bv2->v, iter);
//                }else if(disttocap(caps[j], iter, 0, &N) < dc2){
//                    mincap2 = caps[j];
//                    dc2 = disttocap(caps[j], iter, 0, &N);
//                    dc2v1 = vDistance(&caps[j]->bv1->v, iter);
//                    dc2v2 = vDistance(&caps[j]->bv2->v, iter);
//                }
//            }
//        }
//        if(mincap1 != NULL){
////            if(mincap2 != NULL){//se dividen el peso
////                
////            }else{//todo pertenece a mincap1
////                bind(&chestbv, iter, 0.8);
////            }
//            if(dc1v1 < dc1v2){
//                bind(mincap1->bv1, iter, 1);
//            }else{
//                bind(mincap1->bv2, iter, 1);
//            }
//        }
//        
//        /////////////////
        
        if(betweeny(iter, 0.7, 4)){//mitad de arriba
            if(betweenx(iter, -0.95, 0.95)){//pecho
                if(betweeny(iter, 0.7, 2.3)){//pecho
                    if(betweenx(iter, 0.55, 0.95) && betweeny(iter, 1.35, 2.3)){//hombro izq
                        bind(&rshoulderbv, iter, 0.2);
                        bind(&chestbv, iter, 0.8);
                    }else if(betweenx(iter, -0.55, -0.95) && betweeny(iter, 1.35, 2.3)){//hombro der
                        bind(&lshoulderbv, iter, 0.2);
                        bind(&chestbv, iter, 0.8);
                    }else{//pecho
                        bind(&chestbv, iter, 1);
                    }
                }else{//cabeza
                    if(betweeny(iter, 1.35, 2.3)){//cuello pecho
                        bind(&chestbv, iter, 0.5);
                        bind(&neckbv, iter, 0.5);
                    }else if(betweeny(iter, 2.3, 2.55) && betweenz(iter, -0.5, 0.3)){//cuello
                        bind(&neckbv, iter, 1);
                    }else{//cabeza
                        bind(&headbv, iter, 1);
                    }
                }

            }else{//brazos
                if(iter->f[0]>0){//der
                    if(betweenx(iter, 0.95, 2.15)){//hombro codo
                        if(betweenx(iter, 0.95, 1.7)){
                            bind(&rshoulderbv, iter, 1);
                        }else if(betweenx(iter, 1.7, 1.35)){
                            bind(&rshoulderbv, iter, 0.7);
                            bind(&relbowbv, iter, 0.3);
                        }else if(betweenx(iter, 1.35, 2)){
                            bind(&rshoulderbv, iter, 0.5);
                            bind(&relbowbv, iter, 0.5);
                        }else{ //2 _ 2.15
                            bind(&rshoulderbv, iter, 0.3);
                            bind(&relbowbv, iter, 0.7);
                        }
                    }else{//ante mano
                        if(betweenx(iter, 2.15, 2.8)){//ante
                            bind(&relbowbv, iter, 1);
                        }else if(betweenx(iter, 2.8, 2.95)){//wrist
                            bind(&relbowbv, iter, 0.5);
                            bind(&rwristbv, iter, 0.5);
                        }else{//mano
                            bind(&rwristbv, iter, 1);
                        }

                    }
                }else{//izq
                    if(betweenx(iter, -0.95, -2.15)){//hombro codo
                        if(betweenx(iter, -0.95, -1.7)){
                            bind(&lshoulderbv, iter, 1);
                        }else if(betweenx(iter, -1.7, -1.35)){
                            bind(&lshoulderbv, iter, 0.7);
                            bind(&lelbowbv, iter, 0.3);
                        }else if(betweenx(iter, -1.35, -2)){
                            bind(&lshoulderbv, iter, 0.5);
                            bind(&lelbowbv, iter, 0.5);
                        }else{ //2 _ 2.15
                            bind(&lshoulderbv, iter, 0.3);
                            bind(&lelbowbv, iter, 0.7);
                        }
                    }else{//ante mano
                        if(betweenx(iter, -2.15, -2.8)){//ante
                            bind(&lelbowbv, iter, 1);
                        }else if(betweenx(iter, -2.8, -2.95)){//wrist
                            bind(&lelbowbv, iter, 0.5);
                            bind(&lwristbv, iter, 0.5);
                        }else{//mano
                            bind(&lwristbv, iter, 1);
                        }
                    }

                }
            }
        }else{//mitad de abajo
            if(betweeny(iter, -0.6, 0.7)){//waist
                if(betweeny(iter, 0.3, 0.7)){//lonja
                    bind(&abdomenbv, iter, 0.5);
                    bind(&waistbv, iter, 0.5);
                }else if(betweeny(iter, 0.3, 0.05)){
                    bind(&abdomenbv, iter, 0.3);
                    bind(&waistbv, iter, 0.7);
                }else{//chon
                    if(betweenx(iter, 0.05, 0.9)){//pder
                        bind(&rulegbv, iter, 0.5);
                        bind(&waistbv, iter, 0.5);
                    }else if(betweenx(iter, -0.05, -0.9)){//pizq
                        bind(&lulegbv, iter, 0.5);
                        bind(&waistbv, iter, 0.5);
                    }else{//waist
                        bind(&waistbv, iter, 1);
                    }
                }
            }else{//piernas
                if(iter->f[0]>0){//der
                    if(betweeny(iter, -0.6, -2.65)){//uleg knee
                        if(betweeny(iter, -0.6, -2)){//uleg
                            bind(&rulegbv, iter, 1);
                        }else if(betweeny(iter, -2, -2.2)){
                            bind(&rulegbv, iter, 0.7);
                            bind(&rkneebv, iter, 0.3);
                        }else if(betweeny(iter, -2.2, -2.45)){
                            bind(&rulegbv, iter, 0.5);
                            bind(&rkneebv, iter, 0.5);
                        }else{
                            bind(&rulegbv, iter, 0.3);
                            bind(&rkneebv, iter, 0.7);
                        }
                    }else{//below knee
                        if(betweeny(iter, -2.65, -3.85)){//chamorro
                            bind(&rkneebv, iter, 1);
                        }else if(betweeny(iter, -3.85, -4.05)){//chamorro pie
                            bind(&rkneebv, iter, 0.5);
                            bind(&ranklebv, iter, 0.5);
                        }else{//foot
                            bind(&ranklebv, iter, 1);
                        }
                    }
                }else{//izq
                    if(betweeny(iter, -0.6, -2.65)){//uleg knee
                        if(betweeny(iter, -0.6, -2)){//uleg
                            bind(&lulegbv, iter, 1);
                        }else if(betweeny(iter, -2, -2.2)){
                            bind(&lulegbv, iter, 0.7);
                            bind(&lkneebv, iter, 0.3);
                        }else if(betweeny(iter, -2.2, -2.45)){
                            bind(&lulegbv, iter, 0.5);
                            bind(&lkneebv, iter, 0.5);
                        }else{
                            bind(&lulegbv, iter, 0.3);
                            bind(&lkneebv, iter, 0.7);
                        }
                    }else{//below knee
                        if(betweeny(iter, -2.65, -3.85)){//chamorro
                            bind(&lkneebv, iter, 1);
                        }else if(betweeny(iter, -3.85, -4.05)){//chamorro pie
                            bind(&lkneebv, iter, 0.5);
                            bind(&lanklebv, iter, 0.5);
                        }else{//foot
                            bind(&lanklebv, iter, 1);
                        }
                    }
                }
            }
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
            bind(&waistbv, ptemp.pos, 1);
        }else if(betweeny(ptemp.pos, -2, -2.7)){
            if(ptemp.pos->f[0]>0){
                bind(&rkneebv, ptemp.pos, 0.5);
            }else{
                bind(&lkneebv, ptemp.pos, 0.5);
            }
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
