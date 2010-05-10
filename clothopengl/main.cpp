/*****************************************
 ***Equipo***
 *
 * José Ugalde 1161507
 * Alejandro Morales 1161376
 * Jorge Dorantes 1011377
 * Enrique Peña 1162110
 *
 * Monito Final
 * v 4
*******************************************/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
//#include <stdio.h>
//#include <map>
#include <vector>
#include <string>

#include "funcdec.h"
#include "inits.h"
#include "objLoader.h"
#include "materials.h"  //arreglos de materiales
#include "clothfunc.h"  //funciones relativas a cloth
#include "structs.h"

/////SWITCHES
bool smoothswitch      = true;

bool capvisswitch      = false;//true;
bool capalphaswitch    = false;//true;

bool jointvisswitch    = false;//true;
bool jointalphaswitch  = false;//true;

bool skeletonswitch    = false;//true;

bool skinvisswitch     = true;
bool skinvertswitch    = false;//true;
bool skinalphaswitch   = false;//true;

bool shirtvisswitch    = true;
bool shirtvertswitch   = false;//true;
bool shirtalphaswitch  = false;//true;
bool shirtspringswitch = false;//true;

bool pantsvisswitch    = true;
bool pantsvertswitch   = false;//true;
bool pantsalphaswitch  = false;//true;
bool pantsspringswitch = false;//true;

bool hairvisswitch     = true;
bool hairvertswitch    = false;//true;
bool hairalphaswitch   = false;//true;
bool hairspringswitch  = false;//true;

bool gravityswitch     = true;

bool gridswitch        = false;
bool planeswitch       = false;

bool mouseDown = false;

float angdelta = 2; //cuanto se dobla
GLfloat anglex = 0; //en x
GLfloat angley = 0; //en y
GLfloat anglez = 0; //en z

int segselect = 1;
float jointsize = 0.2;
float vertsize = 0.05;
float particler = 0.05;
float shirtparticler = 0.15;
float pantsparticler = 0.1;
float hairparticler = 0.1;

GLUquadric* q = gluNewQuadric();

/////VARS DE CAMARA
float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 12.0;

float speed = 2;
float eTime = 0;
float timeDelta = 1;

float floory = -4.7;
float roomsize = 15;
float ceilingy = 20;

Vec3 floor0 = Vec3construct(-roomsize,floory,-roomsize);
Vec3 floor1 = Vec3construct(-roomsize,floory,roomsize);
Vec3 floor2 = Vec3construct(roomsize,floory,roomsize);
Vec3 floor3 = Vec3construct(roomsize,floory,-roomsize);
float floorn[3] = {0,1,0};

Vec3 lwall0 = Vec3construct(-roomsize,floory,-roomsize);
Vec3 lwall1 = Vec3construct(-roomsize,floory,roomsize);
Vec3 lwall2 = Vec3construct(-roomsize,ceilingy,roomsize);
Vec3 lwall3 = Vec3construct(-roomsize,ceilingy,-roomsize);
float lwalln[3] = {1,0,0};

Vec3 rwall0 = Vec3construct(roomsize,floory,-roomsize);
Vec3 rwall1 = Vec3construct(roomsize,floory,roomsize);
Vec3 rwall2 = Vec3construct(roomsize,ceilingy,roomsize);
Vec3 rwall3 = Vec3construct(roomsize,ceilingy,-roomsize);
float rwalln[3] = {-1,0,0};

Vec3 fwall0 = Vec3construct(-roomsize,floory,roomsize);
Vec3 fwall1 = Vec3construct(-roomsize,ceilingy,roomsize);
Vec3 fwall2 = Vec3construct(roomsize,ceilingy,roomsize);
Vec3 fwall3 = Vec3construct(roomsize,floory,roomsize);
float fwalln[3] = {0,0,-1};

Vec3 bwall0 = Vec3construct(-roomsize,floory,-roomsize);
Vec3 bwall1 = Vec3construct(-roomsize,ceilingy,-roomsize);
Vec3 bwall2 = Vec3construct(roomsize,ceilingy,-roomsize);
Vec3 bwall3 = Vec3construct(roomsize,floory,-roomsize);
float bwalln[3] = {0,0,1};

Vec3 ceiling0 = Vec3construct(-roomsize,ceilingy,-roomsize);
Vec3 ceiling1 = Vec3construct(-roomsize,ceilingy,roomsize);
Vec3 ceiling2 = Vec3construct(roomsize,ceilingy,roomsize);
Vec3 ceiling3 = Vec3construct(roomsize,ceilingy,-roomsize);
float ceilingn[3] = {0,-1,0};

///////////////DEBUG
//Vec3 planex0 = Vec3construct(0,-5,-5);
//Vec3 planex1 = Vec3construct(0,-5,5);
//Vec3 planex2 = Vec3construct(0,5,5);
//Vec3 planex3 = Vec3construct(0,5,-5);
//
//Vec3 planey0 = Vec3construct(-5,0,-5);
//Vec3 planey1 = Vec3construct(-5,0,5);
//Vec3 planey2 = Vec3construct(5,0,5);
//Vec3 planey3 = Vec3construct(5,0,-5);
//
//Vec3 planez0 = Vec3construct(-5,-5,0);
//Vec3 planez1 = Vec3construct(-5,5,0);
//Vec3 planez2 = Vec3construct(5,5,0);
//Vec3 planez3 = Vec3construct(5,-5,0);
//
//void drawplanex(){
//    glBegin(GL_QUADS);
//        glVertex3f(planex0.f[0], planex0.f[1], planex0.f[2]);
//        glVertex3f(planex1.f[0], planex1.f[1], planex1.f[2]);
//        glVertex3f(planex2.f[0], planex2.f[1], planex2.f[2]);
//        glVertex3f(planex3.f[0], planex3.f[1], planex3.f[2]);
//    glEnd();
//}
//void drawplaney(){
//    glBegin(GL_QUADS);
//        glVertex3f(planey0.f[0], planey0.f[1], planey0.f[2]);
//        glVertex3f(planey1.f[0], planey1.f[1], planey1.f[2]);
//        glVertex3f(planey2.f[0], planey2.f[1], planey2.f[2]);
//        glVertex3f(planey3.f[0], planey3.f[1], planey3.f[2]);
//    glEnd();
//}
//void drawplanez(){
//    glBegin(GL_QUADS);
//        glVertex3f(planez0.f[0], planez0.f[1], planez0.f[2]);
//        glVertex3f(planez1.f[0], planez1.f[1], planez1.f[2]);
//        glVertex3f(planez2.f[0], planez2.f[1], planez2.f[2]);
//        glVertex3f(planez3.f[0], planez3.f[1], planez3.f[2]);
//    glEnd();
//}
//
//void moveplanex(float x){
//    planex0.f[0] += x;
//    planex1.f[0] += x;
//    planex2.f[0] += x;
//    planex3.f[0] += x;
//}
//void moveplaney(float y){
//    planey0.f[1] += y;
//    planey1.f[1] += y;
//    planey2.f[1] += y;
//    planey3.f[1] += y;
//}
//void moveplanez(float z){
//    planez0.f[2] += z;
//    planez1.f[2] += z;
//    planez2.f[2] += z;
//    planez3.f[2] += z;
//}
///////

//------------------FUNCIONES----------------------------
//Hasta ahorita detecta colision entre un punto y una capsula, 
//calcula la normal y regresa que tan adentro esta el punto h, 0 si esta fuera
float colDetect(capsule *cap, Vec3 *h, float hr){
    //dist entre punto uno de cap y *h
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
    
    float penetration = 0;
    
    //que tan adentro de la cap esta *h
    if(b < (cap->r + hr))
        penetration = b - (cap->r + hr);
    
    return penetration;
}

//Mueve la piel en x respecto a un bv
void moveskinx(bodyvertex *bv, float x){
    for(int j=0;j<numbindings;j++){
        if(&bindings[j].bv->v == &bv->v){
            bindings[j].sv->f[0] += (x * bindings[j].w);
        }
    }
}
//Mueve la piel en y respecto a un bv
void moveskiny(bodyvertex *bv, float y){
    for(int j=0;j<numbindings;j++){
        if(&bindings[j].bv->v == &bv->v){
            bindings[j].sv->f[1] += (y * bindings[j].w);
        }
    }
}
//Mueve la piel en x respecto a un bv
void moveskinz(bodyvertex *bv, float z){
    for(int j=0;j<numbindings;j++){
        if(&bindings[j].bv->v == &bv->v){
            bindings[j].sv->f[2] += (z * bindings[j].w);
        }
    }
}

//Rota la piel en x respecto a un bv
void rotskinx(bodyvertex *bv, Vec3 *pt, float nangx){
    for(int j=0;j<numbindings;j++){
        if(&bindings[j].bv->v == &bv->v){
            float angx = (nangx * bindings[j].w);
            Vec3 *sv = bindings[j].sv;
            float newy = pt->f[1] + (sv->f[1] - pt->f[1]) * cosf(angx * M_PI/180) - (sv->f[2] - pt->f[2]) * sinf(angx * M_PI/180);
            float newz = pt->f[2] + (sv->f[2] - pt->f[2]) * cosf(angx * M_PI/180) + (sv->f[1] - pt->f[1]) * sinf(angx * M_PI/180);
            sv->f[1] = newy;
            sv->f[2] = newz;
        }
    }
}
//Rota la piel en y respecto a un bv
void rotskiny(bodyvertex *bv, Vec3 *pt, float nangy){
    for(int j=0;j<numbindings;j++){
        if(&bindings[j].bv->v == &bv->v){
            float angy = (nangy * bindings[j].w);
            Vec3 *sv = bindings[j].sv;
            float newx = pt->f[0] + (sv->f[0] - pt->f[0]) * cosf(angy * M_PI/180) - (sv->f[2] - pt->f[2]) * sinf(angy * M_PI/180);
            float newz = pt->f[2] + (sv->f[2] - pt->f[2]) * cosf(angy * M_PI/180) + (sv->f[0] - pt->f[0]) * sinf(angy * M_PI/180);
            sv->f[0] = newx;
            sv->f[2] = newz;
        }
    }
}
//Rota la piel en z respecto a un bv
void rotskinz(bodyvertex *bv, Vec3 *pt, float nangz){
    for(int j=0;j<numbindings;j++){
        if(&bindings[j].bv->v == &bv->v){
            float angz = (nangz * bindings[j].w);
            Vec3 *sv = bindings[j].sv;
            float newx = pt->f[0] + (sv->f[0] - pt->f[0]) * cosf(angz * M_PI/180) - (sv->f[1] - pt->f[1]) * sinf(angz * M_PI/180);
            float newy = pt->f[1] + (sv->f[1] - pt->f[1]) * cosf(angz * M_PI/180) + (sv->f[0] - pt->f[0]) * sinf(angz * M_PI/180);
            sv->f[0] = newx;
            sv->f[1] = newy;
        }
    }
}

//Rota un vertice al rededor del eje X
void rotBVx(bodyvertex *bv, Vec3 *pt, float angx){
    float newy = pt->f[1] + (bv->v.f[1] - pt->f[1]) * cosf(angx * M_PI/180) - (bv->v.f[2] - pt->f[2]) * sinf(angx * M_PI/180);
    float newz = pt->f[2] + (bv->v.f[2] - pt->f[2]) * cosf(angx * M_PI/180) + (bv->v.f[1] - pt->f[1]) * sinf(angx * M_PI/180);
    bv->v.f[1] = newy;
    bv->v.f[2] = newz;
    rotskinx(bv, pt, angx);
}

//Rota un vertice al rededor del eje Y
void rotBVy(bodyvertex *bv, Vec3 *pt, float angy){
    float newx = pt->f[0] + (bv->v.f[0] - pt->f[0]) * cosf(angy * M_PI/180) - (bv->v.f[2] - pt->f[2]) * sinf(angy * M_PI/180);
    float newz = pt->f[2] + (bv->v.f[2] - pt->f[2]) * cosf(angy * M_PI/180) + (bv->v.f[0] - pt->f[0]) * sinf(angy * M_PI/180);
    bv->v.f[0] = newx;
    bv->v.f[2] = newz;
    rotskiny(bv, pt, angy);
}

//Rota un vertice al rededor del eje Z
void rotBVz(bodyvertex *bv, Vec3 *pt, float angz){
    float newx = pt->f[0] + (bv->v.f[0] - pt->f[0]) * cosf(angz * M_PI/180) - (bv->v.f[1] - pt->f[1]) * sinf(angz * M_PI/180);
    float newy = pt->f[1] + (bv->v.f[1] - pt->f[1]) * cosf(angz * M_PI/180) + (bv->v.f[0] - pt->f[0]) * sinf(angz * M_PI/180);
    bv->v.f[0] = newx;
    bv->v.f[1] = newy;
    rotskinz(bv, pt, angz);
}

//Rota capsulas respecto al punto *pt... jajaja pete
void rotCapx(capsule *c, Vec3 *pt, float angx){
    if(c->bv1->hasmoved == false){
        rotBVx(c->bv1, pt, angx);
        c->bv1->hasmoved = true;
    }

    if(c->bv2->hasmoved == false){
        rotBVx(c->bv2, pt, angx);
        c->bv2->hasmoved = true;
    }

    if(c->sib != NULL)
    	rotCapx(c->sib, pt, angx);
}
void rotCapy(capsule *c, Vec3 *pt, float angy){
    if(c->bv1->hasmoved == false){
        rotBVy(c->bv1, pt, angy);
        c->bv1->hasmoved = true;
    }

    if(c->bv2->hasmoved == false){
        rotBVy(c->bv2, pt, angy);
        c->bv2->hasmoved = true;
    }

    if(c->sib != NULL)
    	rotCapy(c->sib, pt, angy);
}
void rotCapz(capsule *c, Vec3 *pt, float angz){
    if(c->bv1->hasmoved == false){
        rotBVz(c->bv1, pt, angz);
        c->bv1->hasmoved = true;
    }

    if(c->bv2->hasmoved == false){
        rotBVz(c->bv2, pt, angz);
        c->bv2->hasmoved = true;
    }

    if(c->sib != NULL)
    	rotCapz(c->sib, pt, angz);
}

//Rota nodos hijos respecto al punto *pt... jajaja pete
void rotChildNodex(treenode *n, Vec3 *pt, float angx){
    if(n->bv->hasmoved == false){
        rotBVx(n->bv, pt, angx);
        n->bv->hasmoved = true;
    }
    if(n->child != NULL)
    	rotChildNodex(n->child, pt, angx);
        
    if(n->sib != NULL)
    	rotChildNodex(n->sib, pt, angx);
        
    rotCapx(n->cap, pt, angx);
}
void rotChildNodey(treenode *n, Vec3 *pt, float angy){
    if(n->bv->hasmoved == false){
        rotBVy(n->bv, pt, angy);
        n->bv->hasmoved = true;
    }
    if(n->child != NULL)
    	rotChildNodey(n->child, pt, angy);
        
    if(n->sib != NULL)
    	rotChildNodey(n->sib, pt, angy);
        
    rotCapy(n->cap, pt, angy);
}
void rotChildNodez(treenode *n, Vec3 *pt, float angz){
    if(n->bv->hasmoved == false){
        rotBVz(n->bv, pt, angz);
        n->bv->hasmoved = true;
    }
    if(n->child != NULL)
    	rotChildNodez(n->child, pt, angz);
        
    if(n->sib != NULL)
    	rotChildNodez(n->sib, pt, angz);
        
    rotCapz(n->cap, pt, angz);
}

//Recibe un nodo, usa el metodo de arriba para 
//girar hijos respecto al primer vertice de un nodo
void rotNodex(treenode *n, float angx){
    rotCapx(n->cap, &n->bv->v, angx);
    if(n->child != NULL)
    	rotChildNodex(n->child, &(n->bv->v), angx);
}
void rotNodey(treenode *n, float angy){
    rotCapy(n->cap, &n->bv->v, angy);
    if(n->child != NULL)
    	rotChildNodey(n->child, &(n->bv->v), angy);
}
void rotNodez(treenode *n, float angz){
    rotCapz(n->cap, &n->bv->v, angz);
    if(n->child != NULL)
    	rotChildNodez(n->child, &(n->bv->v), angz);
}

////////////DRAW
void setMaterials(GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess){
    glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
	glMaterialf(GL_FRONT,  GL_SHININESS, shininess);
}

void drawroom(){
    glBegin(GL_QUADS);
        glNormal3fv(floorn);
        glVertex3f(floor0.f[0], floor0.f[1], floor0.f[2]);
        glVertex3f(floor1.f[0], floor1.f[1], floor1.f[2]);
        glVertex3f(floor2.f[0], floor2.f[1], floor2.f[2]);
        glVertex3f(floor3.f[0], floor3.f[1], floor3.f[2]);
        
//        glNormal3fv(lwalln);
//        glVertex3f(lwall0.f[0], lwall0.f[1], lwall0.f[2]);
//        glVertex3f(lwall1.f[0], lwall1.f[1], lwall1.f[2]);
//        glVertex3f(lwall2.f[0], lwall2.f[1], lwall2.f[2]);
//        glVertex3f(lwall3.f[0], lwall3.f[1], lwall3.f[2]);
//        
//        glNormal3fv(rwalln);
//        glVertex3f(rwall0.f[0], rwall0.f[1], rwall0.f[2]);
//        glVertex3f(rwall1.f[0], rwall1.f[1], rwall1.f[2]);
//        glVertex3f(rwall2.f[0], rwall2.f[1], rwall2.f[2]);
//        glVertex3f(rwall3.f[0], rwall3.f[1], rwall3.f[2]);
//        
//        glNormal3fv(fwalln);
//        glVertex3f(fwall0.f[0], fwall0.f[1], fwall0.f[2]);
//        glVertex3f(fwall1.f[0], fwall1.f[1], fwall1.f[2]);
//        glVertex3f(fwall2.f[0], fwall2.f[1], fwall2.f[2]);
//        glVertex3f(fwall3.f[0], fwall3.f[1], fwall3.f[2]);
//        
//        glNormal3fv(bwalln);
//        glVertex3f(bwall0.f[0], bwall0.f[1], bwall0.f[2]);
//        glVertex3f(bwall1.f[0], bwall1.f[1], bwall1.f[2]);
//        glVertex3f(bwall2.f[0], bwall2.f[1], bwall2.f[2]);
//        glVertex3f(bwall3.f[0], bwall3.f[1], bwall3.f[2]);
//        
//        glNormal3fv(ceilingn);
//        glVertex3f(ceiling0.f[0], ceiling0.f[1], ceiling0.f[2]);
//        glVertex3f(ceiling1.f[0], ceiling1.f[1], ceiling1.f[2]);
//        glVertex3f(ceiling2.f[0], ceiling2.f[1], ceiling2.f[2]);
//        glVertex3f(ceiling3.f[0], ceiling3.f[1], ceiling3.f[2]);
    glEnd();
}

//dibuja los joints donde se dobla el mono
void drawJoint(Vec3 *v, int id){
     if(id == segselect){
         glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
    	 if(jointalphaswitch)
             glMaterialfv(GL_FRONT, GL_DIFFUSE,   yellowDiffuseAlpha);
         else
             glMaterialfv(GL_FRONT, GL_DIFFUSE,   yellowDiffuse);
    	 glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
    	 glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
     }else{
         glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
         if(jointalphaswitch)
    	     glMaterialfv(GL_FRONT, GL_DIFFUSE,   redDiffuseAlpha);
   	     else
   	         glMaterialfv(GL_FRONT, GL_DIFFUSE,   redDiffuse);
    	 glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
    	 glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
     }
     glPushMatrix();
         glTranslatef(v->f[0],v->f[1],v->f[2]);
         glutSolidSphere(jointsize,10,10);
     glPopMatrix();
}

//dibuja un unicornio
void drawCapsule(capsule *cap){
//     glLineWidth(5);
//     glBegin(GL_LINES);
//         glVertex3f(cap->bv1->v.f[0],cap->bv1->v.f[1],cap->bv1->v.f[2]);
//         glVertex3f(cap->bv2->v.f[0],cap->bv2->v.f[1],cap->bv2->v.f[2]);
//     glEnd();

     float d = distance3d(cap->bv1->v.f[0], cap->bv1->v.f[1], cap->bv1->v.f[2], 
                          cap->bv2->v.f[0], cap->bv2->v.f[1], cap->bv2->v.f[2]);
     
     float vx = cap->bv2->v.f[0] - cap->bv1->v.f[0];
     float vy = cap->bv2->v.f[1] - cap->bv1->v.f[1];
     float vz = cap->bv2->v.f[2] - cap->bv1->v.f[2];
     
     //handle the degenerate case of z1 == z2 with an approximation
     if(vz == 0)
          vz = 0.0001;
    
     float v = sqrt( vx*vx + vy*vy + vz*vz );
     float ax = 57.2957795*acos( vz/v );
     if ( vz < 0.0 )
         ax = -ax;
     float rx = -vy*vz;
     float ry = vx*vz;
     
     glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
     if(capalphaswitch)
   	     glMaterialfv(GL_FRONT, GL_DIFFUSE,   whiteDiffuseAlpha);
     else
   	     glMaterialfv(GL_FRONT, GL_DIFFUSE,   whiteDiffuse);
  	 glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
  	 glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
  	 
     glPushMatrix();
         glTranslatef(cap->bv2->v.f[0], cap->bv2->v.f[1], cap->bv2->v.f[2]);
         glutSolidSphere(cap->r,10,10);
     glPopMatrix();
     glPushMatrix();
         glTranslatef(cap->bv1->v.f[0], cap->bv1->v.f[1], cap->bv1->v.f[2]);
         glutSolidSphere(cap->r,10,10);
         glRotatef(ax, rx, ry, 0.0);
         gluCylinder(q, cap->r, cap->r, d, 20, 1);
     glPopMatrix();

}

void drawCaps(){
    for(int i=0;i<NUMCAPS;i++){
        drawCapsule(caps[i]);
    }     
}

void drawBV(){
    setMaterials(zeroMaterial, greenDiffuseAlpha, zeroMaterial, noShininess);
    for(int i=0;i<NUMVERTS;i++){
         glPushMatrix();
             glTranslatef(bodyverts[i]->v.f[0],bodyverts[i]->v.f[1],bodyverts[i]->v.f[2]);
             glutSolidCube(jointsize+0.1);
         glPopMatrix();
    }
}

//si picas G se dibuja
void drawGrid(){
    float i,j;
    glBegin(GL_LINES);
//    for(i=-80;i<80;i++){
//        for(j=-80;j<80;j++){
//            glVertex3f(-8,i/10,0);//x
//            glVertex3f(8,i/10,0);
//            glVertex3f(i/10,-8,0);//y
//            glVertex3f(i/10,8,0);
//            glVertex3f(0,i/10,-8);//zx
//            glVertex3f(0,i/10,8);
//            glVertex3f(0,-8,i/10);//zy
//            glVertex3f(0,8,i/10);
//        }
//    }

    for(i=-8;i<8;i++){
        for(j=-8;j<8;j++){
        	
            glVertex3f(-8,i,0.01);//x
            glVertex3f(8,i,0.01);
            glVertex3f(i,-8,0.01);//y
            glVertex3f(i,8,0.01);
            
            glVertex3f(0.01,i,-8);//zx
            glVertex3f(0.01,i,8);
            glVertex3f(0.01,-8,i);//zy
            glVertex3f(0.01,8,i);
        }
    }
    glEnd();
}

//Dibuja todos los vertices de un mesh de obj (skindata)
void drawVert(objLoader *object, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess){
     int i;
     double *v;
     
     setMaterials(ambient, diffuse, specular, shininess);
     
     for(i=0; i<object->vertexCount; i++){
          v = object->vertexList[i]->f;
          glPushMatrix();
              glTranslatef(v[0], v[1], v[2]);
              glutSolidSphere(vertsize, 5,5);
          glPopMatrix();
     }
}

//Dibuja un mesh de obj (skindata, shirtdata o pantsdata)
void drawObject(objLoader *object, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess){
     setMaterials(ambient, diffuse, specular, shininess);
   	 
   	 obj_face *o_f;
     glBegin(GL_TRIANGLES);
         ///calculate normals
         GLdouble normals[3];
         float ax, ay, az, bx, by, bz, nx, ny, nz, n;
         for(int i = 0; i < object->faceCount; i++){
             ///calc nor
             o_f = object->faceList[i];
             
             ax = object->vertexList[o_f->vertex_index[1]]->f[0] - object->vertexList[o_f->vertex_index[0]]->f[0];
             ay = object->vertexList[o_f->vertex_index[1]]->f[1] - object->vertexList[o_f->vertex_index[0]]->f[1];
             az = object->vertexList[o_f->vertex_index[1]]->f[2] - object->vertexList[o_f->vertex_index[0]]->f[2];
             bx = object->vertexList[o_f->vertex_index[2]]->f[0] - object->vertexList[o_f->vertex_index[0]]->f[0];
             by = object->vertexList[o_f->vertex_index[2]]->f[1] - object->vertexList[o_f->vertex_index[0]]->f[1];
             bz = object->vertexList[o_f->vertex_index[2]]->f[2] - object->vertexList[o_f->vertex_index[0]]->f[2];
             nx = ay*bz - az*by;
             ny = az*bx - ax*bz;
             nz = ax*by - ay*bx;
             n = sqrt(nx*nx+ny*ny+nz*nz);
             if (n != 0.0) {
                n = 1.0/n;
            	nx *= n; ny *= n; nz *= n;
             }
             normals[0] = nx;
             normals[1] = ny;
             normals[2] = nz;

             for(int j=0; j<3; j++){
                  glNormal3dv(normals);
                  glVertex3dv(object->vertexList[o_f->vertex_index[j]]->f);
             }
         }
     glEnd();            
}

void drawParticles(particle *arr, int total, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess){
    setMaterials(ambient, diffuse, specular, shininess);
    Vec3 v;
    particle *ptemp;
    int i=0;
    for(i=0; i<total; i++){
          ptemp = &arr[i];
          if(ptemp->movable)
              setMaterials(ambient, diffuse, specular, shininess);
          else
              setMaterials(ambient, redDiffuse, specular, shininess);
          glPushMatrix();
              glTranslatef(ptemp->pos->f[0], ptemp->pos->f[1], ptemp->pos->f[2]);
              glutSolidSphere(particler, 5,5);
          glPopMatrix();
     }
}

void drawSprings(spring *arr, int total, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess){
    setMaterials(ambient, diffuse, specular, shininess);
    
    int i=0;
    
    for(i=0; i<total; i++){
          double *p1temp = arr[i].p1->pos->f;
          double *p2temp = arr[i].p2->pos->f;
          glLineWidth(2);
          glBegin(GL_LINES);
              glVertex3f(p1temp[0], p1temp[1], p1temp[2]);
              glVertex3f(p2temp[0], p2temp[1], p2temp[2]);
          glEnd();
     }
}

void drawskeleton(treenode *n){
    treenode *son;
    son = n->child;
    if(son != NULL){
        glBegin(GL_LINES);
            glColor3f(0.8,0,0);
           	glVertex3f(n->bv->v.f[0], n->bv->v.f[1], n->bv->v.f[2]);
            glColor3f(1,0.8,0.8);
            glVertex3f(son->bv->v.f[0], son->bv->v.f[1], son->bv->v.f[2]);
        glEnd();
        drawskeleton(n->child);
        while(son->sib != NULL){
            son = son->sib;
            drawskeleton(son);
            glBegin(GL_LINES);
                glColor3f(0,0,0.8);
               	glVertex3f(n->bv->v.f[0], n->bv->v.f[1], n->bv->v.f[2]);
                glColor3f(0.8,0.8,1);
                glVertex3f(son->bv->v.f[0], son->bv->v.f[1], son->bv->v.f[2]);
            glEnd();
        }
    }
    if(n->sib != NULL){
        glBegin(GL_LINES);
            glColor3f(0,0.8,0);
           	glVertex3f(n->bv->v.f[0], n->bv->v.f[1], n->bv->v.f[2]);
            glColor3f(0.8,1,0.8);
            glVertex3f(n->sib->bv->v.f[0], n->sib->bv->v.f[1], n->sib->bv->v.f[2]);
        glEnd();
        drawskeleton(n->sib);
    }
    
}

void traverse(treenode *node){
    if(jointvisswitch)
        drawJoint(&(node->bv->v), node->id);
    
    // primer recorrer los hijos (si hay)
    if(node->child != NULL)
    	traverse(node->child);
        
    // después recorrer los hermanos (si hay)
    if(node->sib != NULL)
    	traverse(node->sib);
}

void display(){     
    if (smoothswitch)
		glShadeModel(GL_SMOOTH); 
	else
		glShadeModel(GL_FLAT); 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
    gluLookAt(
    0.0f, 0.0f, zoom,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f);
    
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    
    //
    if(gridswitch){
        glDisable(GL_LIGHTING);
   	    drawGrid();
   	    glEnable(GL_LIGHTING);
    }
	
    //sprintf(title, "x: %f    y: %f    z: %f    g: %f", planex0.f[0], planey0.f[1], planez0.f[2], gravity.f[1]);
    sprintf(title, "Selected segment: %d     Gravity: %f", segselect, gravity.f[1]);
    glutSetWindowTitle(title);
    ///////

    //MONO
    traverse(&waistn);
    
    if(skeletonswitch){
        glDisable(GL_LIGHTING);
            drawskeleton(&waistn);
   	    glEnable(GL_LIGHTING);
    }
    
    //drawBV();
    
    if(capvisswitch)
        drawCaps();
    
    //SKIN
    if(skinvisswitch)
        if(skinalphaswitch)
            drawObject(skindata, zeroMaterial, pinkDiffuseAlpha, zeroMaterial, noShininess);
        else
            drawObject(skindata, zeroMaterial, pinkDiffuse, zeroMaterial, noShininess);
    
    //CLOTH
    if(shirtvisswitch)
        if(shirtalphaswitch)
            drawObject(shirtdata, zeroMaterial, blueDiffuseAlpha, zeroMaterial, noShininess);
        else
            drawObject(shirtdata, zeroMaterial, blueDiffuse, zeroMaterial, noShininess);

    if(pantsvisswitch)
        if(pantsalphaswitch)
            drawObject(pantsdata, zeroMaterial, khakhiDiffuseAlpha, zeroMaterial, noShininess);
        else
            drawObject(pantsdata, zeroMaterial, khakhiDiffuse, zeroMaterial, noShininess);
    
    if(hairvisswitch)
        if(hairalphaswitch)
            drawObject(hairdata, zeroMaterial, brownDiffuseAlpha, zeroMaterial, noShininess);
        else
            drawObject(hairdata, zeroMaterial, brownDiffuse, zeroMaterial, noShininess);
    
    //VERTICES
    if(skinvertswitch)
        drawVert(skindata, zeroMaterial, purpleDiffuse, zeroMaterial, noShininess);

    
    //PARTICLES
    if(shirtvertswitch)
        drawParticles(shirtparticles, totalshirtparticles, zeroMaterial, dblueDiffuse, zeroMaterial, noShininess);
    if(pantsvertswitch)
        drawParticles(pantsparticles, totalpantsparticles, zeroMaterial, greenDiffuse, zeroMaterial, noShininess);
    if(hairvertswitch)
        drawParticles(hairparticles, totalhairparticles, zeroMaterial, dgreenDiffuse, zeroMaterial, noShininess);

        
    //SPRINGS
    glDisable(GL_LIGHTING);
        if(shirtspringswitch)
            drawSprings(shirtsprings, totalshirtsprings, zeroMaterial, grayDiffuse, zeroMaterial, noShininess);
        if(pantsspringswitch)
            drawSprings(pantssprings, totalpantssprings, zeroMaterial, khakhiDiffuse, zeroMaterial, noShininess);
        if(hairspringswitch)
            drawSprings(hairsprings, totalhairsprings, zeroMaterial, khakhiDiffuse, zeroMaterial, noShininess);
    glEnable(GL_LIGHTING);
    
    
    //ROOM
    setMaterials(zeroMaterial, greenDiffuseAlpha, zeroMaterial, highShininess);
    drawroom();
    
    /////
//    if(planeswitch){
//        glDisable(GL_LIGHTING);
//        glColor4f(1,0,0,0.3);
//        drawplanex();
//        glColor4f(0,1,0,0.3);
//        drawplaney();
//        glColor4f(0,0,1,0.3);
//        drawplanez();
//        glEnable(GL_LIGHTING);
//    }
    
   	glutSwapBuffers();
   	
    /////
//    idle();

}

//invierte un Switch
void toggleSwitch(bool *ts){
    *ts = !*ts;
}

//Invierte todos los switches de vertices
void toggleAllVert(){
    toggleSwitch(&skinvertswitch);
    toggleSwitch(&shirtvertswitch);
    toggleSwitch(&pantsvertswitch);
    toggleSwitch(&hairvertswitch);
    glutPostRedisplay();
}

//Invierte todos los switches de alpha
void toggleAllAlpha(){
    toggleSwitch(&capalphaswitch);
    toggleSwitch(&jointalphaswitch);
    toggleSwitch(&skinalphaswitch);
    toggleSwitch(&shirtalphaswitch);
    toggleSwitch(&pantsalphaswitch);
    toggleSwitch(&hairalphaswitch);
    glutPostRedisplay();
}

//Resetea buffer de angulos (cuando picas flechas)
void resetAngles(){
     anglex = 0;
     angley = 0;
     anglez = 0;
}

//Hace movibles los vertices del cuerpo
void resetVertFlags(){
    for(int i=0;i<NUMVERTS;i++){
        bodyverts[i]->hasmoved = false;
    }
    for(int i=0;i<NUMVERTS;i++){
      if(bodyverts[i]->hasmoved){
      sprintf(title, "FAAAAAIIILLLL");
      glutSetWindowTitle(title);
      }
    }
    
}

//saca un punto de una capsula
bool handleCollision(capsule *cap, particle *p, float hr){
    Vec3 N = Vec3construct(0,0,0);
    float depth = disttocap(cap, p->pos, hr, &N);
    
    if(depth < 0){ //si nueva pos esta adentro
        //Vec3 oN;
//        float olddepth = disttocap(cap, &p->old_pos, hr, &oN);
//        if(olddepth < 0){ //si la vieja pos esta adentro
            p->pos->f[0] -= N.f[0] * depth;
            p->pos->f[1] -= N.f[1] * depth;
            p->pos->f[2] -= N.f[2] * depth;
        //}else{
//            p->pos->f[0] = p->old_pos.f[0] + (p->pos->f[0] - p->old_pos.f[0])/3;
//            p->pos->f[1] = p->old_pos.f[1] + (p->pos->f[1] - p->old_pos.f[1])/3;
//            p->pos->f[2] = p->old_pos.f[2] + (p->pos->f[2] - p->old_pos.f[2])/3;
//        }
        return true;
    }
    
    if(p->pos->f[1] <= floory){
        p->pos->f[1] = floory;
        return true;
    }
    
    return false;
}

void parrcollide(particle *parr, float pradius, int total){
    int i, j;
    for(i=0;i<total;i++){
        for(j=0;j<NUMCAPS;j++){
            if(handleCollision(caps[j], &parr[i], pradius)){
                //break;
            }
        }
    }
}

///////IDLE
void idle(void){
  eTime += timeDelta;
  if(eTime > speed){
      eTime = 0;
      
      int i = 0;
      int j = 0;
      
      if(gravityswitch){
          //aplica fuerzas a shirt
          for(i=0;i<totalshirtparticles;i++){
              partaddForce(&shirtparticles[i], gravity);
              parttimeStep(&shirtparticles[i]);
          }
          //aplica fuerzas a pants
          for(i=0;i<totalpantsparticles;i++){
              partaddForce(&pantsparticles[i], gravity);
              parttimeStep(&pantsparticles[i]);
          }
          //aplica fuerzas a hair
          for(i=0;i<totalhairparticles;i++){
              partaddForce(&hairparticles[i], gravity);
              parttimeStep(&hairparticles[i]);
          }
      }
      
      for(j=0;j<CONSTRAINT_ITERATIONS;j++){
          //resortes de shirt
          for(i=0;i<totalshirtsprings;i++){
              satisfyConstraint(&shirtsprings[i]);
          }    
          //resortes de pants
          for(i=0;i<totalpantssprings;i++){
              satisfyConstraint(&pantssprings[i]);
          }
          //resortes de hair
          for(i=0;i<totalhairsprings;i++){
              satisfyConstraint(&hairsprings[i]);
          }
      }
      //checa colisiones de shirt
      parrcollide(shirtparticles, shirtparticler, totalshirtparticles);
      //checa colisiones de pants
      parrcollide(pantsparticles, pantsparticler, totalpantsparticles);
      //checa colisiones de hair
      parrcollide(hairparticles, hairparticler, totalhairparticles);
  }
  glutPostRedisplay();
}

void movebodyx(float x){
    int i;
    int j;
    for(i=0;i<NUMVERTS;i++){
        bodyverts[i]->v.f[0] += x;
        moveskinx(bodyverts[i], x);
    }
}
void movebodyy(float y){
    int i;
    int j;
    for(i=0;i<NUMVERTS;i++){
        bodyverts[i]->v.f[1] += y;
        for(j=0;j<numbindings;j++){
            if(&bindings[j].bv->v == &bodyverts[i]->v){
                glutSetWindowTitle(title);
                bindings[j].sv->f[1] += (y * bindings[j].w);
            }
        }
    }
}
void movebodyz(float z){
    int i;
    int j;
    for(i=0;i<NUMVERTS;i++){
        bodyverts[i]->v.f[2] += z;
        for(j=0;j<numbindings;j++){
            if(&bindings[j].bv->v == &bodyverts[i]->v){
                glutSetWindowTitle(title);
                bindings[j].sv->f[2] += (z * bindings[j].w);
            }
        }
    }
}

void reset(){
    initObj();
    initVertices();
    initCapsules();
    initSkin();
    initNodes();
    initParticles();
    initSprings();
}

void applyrotations(){
    if(segselect >= 0 && segselect < NUMNODES){
        if(anglex != 0) rotNodex(nodes[segselect], anglex);
        resetVertFlags();
        if(angley != 0) rotNodey(nodes[segselect], angley);
        resetVertFlags();
        if(anglez != 0) rotNodez(nodes[segselect], anglez);
        resetVertFlags();
    }
    if(segselect == 16){
        if(anglex != 0) rotChildNodex(&waistn, &waistn.bv->v, anglex);
        resetVertFlags();
        if(angley != 0) rotChildNodey(&waistn, &waistn.bv->v, angley);
        resetVertFlags();
        if(anglez != 0) rotChildNodez(&waistn, &waistn.bv->v, anglez);
        resetVertFlags();

    }

}
///////MOUSE / KEYBOARD
void key(unsigned char c, int x, int y){
    switch(c){
        case 27://esc
            exit(0);
            break;
        //ZOOM
        case '+':
            zoom -= 1;
            glutPostRedisplay();
            break;
        case '-':
            zoom += 1;
            glutPostRedisplay();
            break;
        case 'n':
            gravity.f[1] -= 0.05;
            glutPostRedisplay();
            break;
        case 'm':
            gravity.f[1] += 0.05;
            glutPostRedisplay();
            break;
        //SWITCHES
        case 's':
            toggleSwitch(&smoothswitch);
            glutPostRedisplay();
            break;
        case 'd':
            toggleSwitch(&skinvisswitch);
            glutPostRedisplay();
            break;
        case 'f':
            toggleSwitch(&shirtvisswitch);
            glutPostRedisplay();
            break;
        case 'g':
            toggleSwitch(&pantsvisswitch);
            glutPostRedisplay();
            break;
        case 'h':
            toggleSwitch(&hairvisswitch);
            glutPostRedisplay();
            break;
        case 'c':
            toggleSwitch(&capvisswitch);
            glutPostRedisplay();
            break;
        case 'v':
            toggleAllVert();
            break;
        case 'a':
            toggleAllAlpha();
            break;
        case 'j':
            toggleSwitch(&jointvisswitch);
            glutPostRedisplay();
            break;
        case 'k':
            toggleSwitch(&gridswitch);
            glutPostRedisplay();
            break;
        case 'l':
            toggleSwitch(&planeswitch);
            glutPostRedisplay();
            break;
        case 'z':
            toggleSwitch(&gravityswitch);
            glutPostRedisplay();
            break;
        //SELECTS
        case '0':
            segselect=0;
            break;
        case '1':
            segselect=1;
            break;
        case '2':
            segselect=2;
            break;
        case '3':
            segselect=3;
            break;
        case '4':
            segselect=4;
            break;
        case '5':
            segselect=5;
            break;
        case '6':
            segselect=6;
            break;
        case '7':
            segselect=7;
            break;
        case '8':
            segselect=8;
            break;
        case '9':
            segselect=9;
            break;
        case 'q':
        case 'Q':
            segselect=10;
            break;
        case 'w':
        case 'W':
            segselect=11;
            break;
        case 'e':
        case 'E':
            segselect=12;
            break;
        case 'r':
        case 'R':
            segselect=13;
            break;
        case 't':
        case 'T':
            segselect=14;
            break;
        case 'y':
        case 'Y':
            segselect=15;
            break;
        case 'u':
        case 'U':
            segselect=16;
            break;
        case '!':
            segselect=-1;
            break;
        case 'i':
        case 'I':
            reset();
            glutPostRedisplay();
            break;
    }
}

void special(int c, int x, int y){
     if(c==GLUT_KEY_UP){
         anglex = -angdelta;
//         moveplanez(-0.05);
         if(segselect == -1)
             movebodyz(-0.1);
     }
     if(c==GLUT_KEY_DOWN){
         anglex = angdelta;
//         moveplanez(0.05);
         if(segselect == -1)
             movebodyz(0.1);
     }
     if(c==GLUT_KEY_RIGHT){
         angley = -angdelta;
//         moveplanex(0.05);
         if(segselect == -1)
             movebodyx(0.1);
     }
     if(c==GLUT_KEY_LEFT){
         angley = angdelta;
//         moveplanex(-0.05);
         if(segselect == -1)
             movebodyx(-0.1);
     }
     if(c==GLUT_KEY_PAGE_UP){
         anglez = angdelta;
//         moveplaney(0.05);
         if(segselect == -1)
             movebodyy(0.1);           
     }
     if(c==GLUT_KEY_PAGE_DOWN){
         anglez = -angdelta;
//         moveplaney(-0.05);
         if(segselect == -1)
             movebodyy(-0.1);
     }
     
     glPushMatrix();
         glLoadIdentity();
         applyrotations();
     glPopMatrix();
     resetAngles();
     glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y){
    if (mouseDown){
        yrot = x - xdiff;
        xrot = y + ydiff;
        glutPostRedisplay();
    }
}

void reshape(int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLdouble)w/(GLdouble)h, 1.0, 100.0) ;
}

////////////////////////////////////////////////INITS
void processMenu(int val){
	switch(val){
        case 1:
             toggleSwitch(&smoothswitch);
             break;
        case 2:
             toggleAllVert();
             break;
        case 3:
             toggleAllAlpha();
             break;
        case 4:
             toggleSwitch(&gravityswitch);
             break;
        case 5:
             toggleSwitch(&skeletonswitch);
             break;
        case 11:
             toggleSwitch(&capvisswitch);
             break;
        case 12:
             toggleSwitch(&capalphaswitch);
             break;
        case 21:
             toggleSwitch(&jointvisswitch);
             break;
        case 22:
             toggleSwitch(&jointalphaswitch);
             break;
        case 31:
             toggleSwitch(&skinvisswitch);
             break;
        case 32:
             toggleSwitch(&skinalphaswitch);
             break;
        case 33:
             toggleSwitch(&skinvertswitch);
             break;
        case 41:
             toggleSwitch(&shirtvisswitch);
             break;
        case 42:
             toggleSwitch(&shirtalphaswitch);
             break;
        case 43:
             toggleSwitch(&shirtvertswitch);
             break;
        case 44:
             toggleSwitch(&shirtspringswitch);
             break;
        case 51:
             toggleSwitch(&pantsvisswitch);
             break;
        case 52:
             toggleSwitch(&pantsalphaswitch);
             break;
        case 53:
             toggleSwitch(&pantsvertswitch);
             break;
        case 54:
             toggleSwitch(&pantsspringswitch);
             break;
        case 61:
             toggleSwitch(&hairvisswitch);
             break;
        case 62:
             toggleSwitch(&hairalphaswitch);
             break;
        case 63:
             toggleSwitch(&hairvertswitch);
             break;
        case 64:
             toggleSwitch(&hairspringswitch);
             break;
        case 71:
             shirtoption = 0;
             reset();
             break;
        case 72:
             shirtoption = 1;
             reset();
             break;
        case 81:
             pantsoption = 0;
             reset();
             break;
        case 82:
             pantsoption = 1;
             reset();
             break;
        case 91:
             hairoption = 0;
             reset();
             break;
        case 92:
             hairoption = 1;
             reset();
             break;
        case 0:
             exit(0);
    }
    glutPostRedisplay();
}

int initMenus(){
	int mainMenu, capMenu, jointMenu, 
    skinMenu, shirtMenu, pantsMenu, hairMenu, 
    wshirtMenu, wpantsMenu, whairMenu;
	mainMenu  = glutCreateMenu(processMenu);
	capMenu   = glutCreateMenu(processMenu);
	jointMenu = glutCreateMenu(processMenu);
	skinMenu  = glutCreateMenu(processMenu);
	shirtMenu = glutCreateMenu(processMenu);
	pantsMenu = glutCreateMenu(processMenu);
	hairMenu = glutCreateMenu(processMenu);
	wshirtMenu = glutCreateMenu(processMenu);
	wpantsMenu = glutCreateMenu(processMenu);
	whairMenu  = glutCreateMenu(processMenu);
	
	glutSetMenu(mainMenu);
    	glutAddSubMenu("Capsules",           capMenu);
        glutAddSubMenu("Joints",           jointMenu);
    	glutAddSubMenu("SKIN",              skinMenu);
    	glutAddSubMenu("   SHIRT",         shirtMenu);
    	glutAddSubMenu("   PANTS",         pantsMenu);
    	glutAddSubMenu("   HAIR",           hairMenu);
    	glutAddMenuEntry("Toggle Skeleton",        5);
        glutAddMenuEntry("Toggle Smooth (S)",      1);
    	glutAddMenuEntry("Toggle All Vertices (V)",2);
    	glutAddMenuEntry("Toggle All Alphas (A)",  3);
    	glutAddMenuEntry("Toggle Gravity (Z)",     4);
    	glutAddMenuEntry("Quit (Esc)",             0);
	
	glutSetMenu(capMenu);
    	glutAddMenuEntry("Toggle Visibility (C)", 11);
    	glutAddMenuEntry("Toggle Alpha",          12);
	
	glutSetMenu(jointMenu);
    	glutAddMenuEntry("Toggle Visibility (J)", 21);
    	glutAddMenuEntry("Toggle Alpha",          22);

	glutSetMenu(skinMenu);
    	glutAddMenuEntry("Toggle Visibility (D)",    31);
    	glutAddMenuEntry("Toggle Alpha",             32);
    	glutAddMenuEntry("Toggle Vertex Visibility", 33);
	
    glutSetMenu(shirtMenu);
        glutAddSubMenu("Shape",                wshirtMenu);
    	glutAddMenuEntry("Toggle Visibility (F)",      41);
    	glutAddMenuEntry("Toggle Alpha",               42);
    	glutAddMenuEntry("Toggle Particle Visibility", 43);
    	glutAddMenuEntry("Toggle Spring Visibility",   44);
	
	glutSetMenu(pantsMenu);
    	glutAddSubMenu("Shape",                wpantsMenu);
    	glutAddMenuEntry("Toggle Visibility (G)",      51);
    	glutAddMenuEntry("Toggle Alpha",               52);
    	glutAddMenuEntry("Toggle Particle Visibility", 53);
    	glutAddMenuEntry("Toggle Spring Visibility",   54);
	
	glutSetMenu(hairMenu);
    	glutAddSubMenu("Shape",                 whairMenu);
    	glutAddMenuEntry("Toggle Visibility (H)",      61);
    	glutAddMenuEntry("Toggle Alpha",               62);
    	glutAddMenuEntry("Toggle Particle Visibility", 63);
    	glutAddMenuEntry("Toggle Spring Visibility",   64);
	
	glutSetMenu(wshirtMenu);
    	glutAddMenuEntry("Shirt",                  71);
    	glutAddMenuEntry("Vest",                   72);
	glutSetMenu(wpantsMenu);
    	glutAddMenuEntry("Pants",                  81);
    	glutAddMenuEntry("Tidus",                  82);
	glutSetMenu(whairMenu);
    	glutAddMenuEntry("Leon Kennedy",           91);
    	glutAddMenuEntry("Bob Ross",               92);

	glutSetMenu(mainMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(){
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
    
      glClearColor (1, 1, 1, 0.0);
    
    // define the light color and intensity
    GLfloat ambientLight[]	= { 0.5, 0.5, 0.5, 1.0 };
    GLfloat diffuseLight[]	= { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specularLight[]	= { 1.0, 1.0, 1.0, 1.0 };

	//  the global ambient light level
    GLfloat globalAmbientLight[] = { 1, 1, 1, 1.0 };

	// set the global ambient light level
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

	// define the color and intensity for light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT,   ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR,  diffuseLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,   specularLight);

	// enable lighting 
    glEnable(GL_LIGHTING);
	// enable light 0
    glEnable(GL_LIGHT0);

	// turn on depth testing so that polygons are drawn in the correct order
	glEnable(GL_DEPTH_TEST);

	// make sure the normals are unit vectors
	glEnable(GL_NORMALIZE);
}

int main(int argc, char **argv)
{
  int mode = GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH;   // Modo de despliegue: Colores RGB, Doble buffer para despliegue
  glutInitDisplayMode(mode);                    // Inicializar modo de despliegue.
  glutInitWindowSize(500,500);                  // Inicializar tamaño de la ventana
  glutInit(&argc, argv);                        // Inicializar GLUT
  glutCreateWindow("Proyecto Final!");          // Crear una ventana con el título indicado.
  glutDisplayFunc(display);                     // Indicar la función para desplegar.
  glutReshapeFunc(reshape);                     // Indicar la función en caso de cambio de tamaño de la ventana
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(key);
  glutSpecialFunc(special);
  glutIdleFunc(idle);
  	
  init();
  initMenus();
  initObj();
  initVertices();
  initCapsules();
  initNodes();
  initSkin();
  initParticles();
  initSprings();
  
  glutMainLoop();                               // Pasar el control a GLUT.
  return 0;                                     // Regresar 0 por cortesía.
}
