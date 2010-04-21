/*****************************************
 ***Equipo***
 *
 *José Ugalde 1161507
 *Alejandro Morales 1161376
 *Jorge Dorantes 1011377
 *Enrique Peña 1162110
 *
 *Monito Final Parte 1
*******************************************/

#include "mesh.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535
#define NUMVERT  27
#define NUMCAPS  18
#define NUMNODES 18

float testx = 0;
float testy = 0;
float testz = 1.5;

char title[60];

//materiales
GLfloat alphavalue = 0.5;

GLfloat lightPosition[] = { 10.0, 10.0, 10.0, 1.0 };

// a material that is all zeros
GLfloat zeroMaterial[]	= { 0.0, 0.0, 0.0, 1.0 };
// a red ambient material
GLfloat redAmbient[]	= { 0.83, 0.0, 0.0, 1.0 };

// a blue diffuse material
GLfloat blueDiffuse[]	= { 0.1, 0.5, 0.8, 1.0 };
// a blue diffuse material w alpha
GLfloat blueDiffuseAlpha[]	= { 0.1, 0.5, 0.8, alphavalue };
// a yellow diffuse material
GLfloat yellowDiffuse[]	= { 1.0, 1.0, 0.0, 1.0 };
// a yellow diffuse material w alpha
GLfloat yellowDiffuseAlpha[]= { 1.0, 1.0, 0.0, alphavalue };
// a red diffuse material
GLfloat redDiffuse[]	= { 1.0, 0.0, 0.0, 1.0 };
// a red diffuse material w alpha
GLfloat redDiffuseAlpha[]	= { 1.0, 0.0, 0.0, alphavalue };
//a white diffuse material
GLfloat whiteDiffuse[]	= { 1.0, 1.0, 1.0, 1.0 };
//a white diffuse material w alpha
GLfloat whiteDiffuseAlpha[]	= { 1.0, 1.0, 1.0, alphavalue };
//a pink diffuse material
GLfloat pinkDiffuse[]	= { 1.0, 0.7, 0.8, 1.0 };
//a pink diffuse material w alpha
GLfloat pinkDiffuseAlpha[]	= { 1.0, 0.7, 0.8, alphavalue };

// a white specular material
GLfloat whiteSpecular[]	= { 1.0, 1.0, 1.0, 1.0 };

// the degrees of shinnines (size of the specular highlight, bigger number means smaller highlight)
GLfloat noShininess	    =  0.0;
GLfloat highShininess	= 50.0;


float angdelta = 6;
GLfloat anglex = 0;
GLfloat angley = 0;

int segselect = 0;
float jointsize = 0.3;
GLUquadric* q = gluNewQuadric();

//SWITCHES
bool smoothswitch    = true;
bool capsuleswitch   = true;
bool skinswitch      = false;//true;
bool shirtswitch     = false;//true;
bool gridswitch      = false;
bool vertswitch      = false;
bool jointswitch     = true;
bool alphaswitch     = false;//true;

bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 12.0;

mesh *skinobject;
mesh *shirtobject;

typedef struct vertex{
    float x, y, z;
    bool hasmoved;
} vertex;

vertex waistv, chestv, neckv, headv, headtopv,
       rshoulderv, ruarmv, rlarmv, rhandv, rhandtopv, lshoulderv, luarmv, llarmv, lhandv, lhandtopv,
       rulegv, rllegv, rfootv, rfoottopv, lulegv, lllegv, lfootv, lfoottopv, 
       waistc1v, waistc2v, chestc1v, chestc2v;

vertex *vertices[NUMVERT];
//
vertex testvert;
//

typedef struct capsule{
    vertex *v1;
    vertex *v2;
    float r;
    char name[16];
} capsule;

capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc,
        chestc, waistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

capsule *caps[NUMCAPS];

typedef struct treenode{
    capsule *cap;
    int id;
    //GLfloat m[16];
    vertex *v1;
    vertex *v2;
    struct treenode *sibling;
    struct treenode *child;
    
} treenode;

treenode headn, neckn, rshouldern, lshouldern, ruarmn, luarmn, rlarmn, llarmn, rhandn, lhandn,
         chestn, waistn, rulegn, lulegn, rllegn, lllegn, rfootn, lfootn;

GLfloat bodypos[16];

capsule testcap;

void initSkin(){
     skinobject = new mesh("cuerpob.obj");
}

void initShirt(){
     shirtobject = new mesh("camisab.obj");
}

//void initPants(){
//     shirtobject = new mesh("pantsb.obj");
//}

float vertDistance(vertex *v1, vertex *v2){
    return sqrt(pow((v1->x-v2->x),2) + pow((v1->y-v2->y),2) + pow((v1->z-v2->z),2));
}

float distance3d(float x1,float y1,float z1,float x2,float y2,float z2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2) + pow((z1-z2),2));
}

float distance2d(float x1,float y1,float x2,float y2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}

void drawJoint(vertex *v, int id){
     if(id == segselect){
         glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
    	 if(alphaswitch)
             glMaterialfv(GL_FRONT, GL_DIFFUSE,   yellowDiffuseAlpha);
         else
             glMaterialfv(GL_FRONT, GL_DIFFUSE,   yellowDiffuse);
    	 glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
    	 glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
     }else{
         glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
         if(alphaswitch)
    	     glMaterialfv(GL_FRONT, GL_DIFFUSE,   redDiffuseAlpha);
   	     else
   	         glMaterialfv(GL_FRONT, GL_DIFFUSE,   redDiffuse);
    	 glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
    	 glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
     }
     glPushMatrix();
         glTranslatef(v->x,v->y,v->z);
         glutSolidSphere(jointsize,10,10);
     glPopMatrix();
     
}

void drawCapsule(capsule *cap){
//     glLineWidth(5);
//     glBegin(GL_LINES);
//         glVertex3f(cap->v1->x,cap->v1->y,cap->v1->z);
//         glVertex3f(cap->v2->x,cap->v2->y,cap->v2->z);
//     glEnd();
     
     float d = distance3d(cap->v1->x, cap->v1->y, cap->v1->z, 
                          cap->v2->x, cap->v2->y, cap->v2->z);
     
     float vx = cap->v2->x - cap->v1->x;
     float vy = cap->v2->y - cap->v1->y;
     float vz = cap->v2->z - cap->v1->z;
     
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
     if(alphaswitch)
   	     glMaterialfv(GL_FRONT, GL_DIFFUSE,   whiteDiffuseAlpha);
     else
   	     glMaterialfv(GL_FRONT, GL_DIFFUSE,   whiteDiffuse);
  	 glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
  	 glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
  	 
     glPushMatrix();
         glTranslatef(cap->v2->x, cap->v2->y, cap->v2->z);
         glutSolidSphere(cap->r,10,10);
     glPopMatrix();
     glPushMatrix();
         glTranslatef(cap->v1->x, cap->v1->y, cap->v1->z);
         glutSolidSphere(cap->r,10,10);
         glRotatef(ax, rx, ry, 0.0);
         gluCylinder(q, cap->r, cap->r, d, 20, 1);
     glPopMatrix();
     
}

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
            glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
      	    if(alphaswitch)
                glMaterialfv(GL_FRONT, GL_DIFFUSE,   pinkDiffuseAlpha);
            else
                glMaterialfv(GL_FRONT, GL_DIFFUSE,   pinkDiffuse);
        	glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
        	glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
        	
            glVertex3f(-8,i,0.01);//x
            glVertex3f(8,i,0.01);
            glVertex3f(i,-8,0.01);//y
            glVertex3f(i,8,0.01);
            
            glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
    	    if(alphaswitch)
                glMaterialfv(GL_FRONT, GL_DIFFUSE,   pinkDiffuseAlpha);
            else
                glMaterialfv(GL_FRONT, GL_DIFFUSE,   pinkDiffuse);
    	    glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
    	    glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
            
            glVertex3f(0.01,i,-8);//zx
            glVertex3f(0.01,i,8);
            glVertex3f(0.01,-8,i);//zy
            glVertex3f(0.01,8,i);
        }
    }
    glEnd();
}

void initVertices(){
    //
    testvert.x = testx;
    testvert.y = testy;
    testvert.z = testz;
    //
     
    waistv.x = 0;
    waistv.y = -0.4;
    waistv.z = 0;
    chestv.x = 0;
    chestv.y = 0.6;
    chestv.z = 0;
    
    waistc1v.x = -(waistc2v.x = -0.5);
    waistc1v.y = waistc2v.y   = 0.3;
    waistc1v.z = waistc2v.z   = 0;
    chestc1v.x = -(chestc2v.x = -0.5);
    chestc1v.y = chestc2v.y   = 1.2;
    chestc1v.z = chestc2v.z   = 0;
    
    neckv.x = 0;
    neckv.y = 2.4;
    neckv.z = 0;
    headv.x = 0;
    headv.y = 2.9;
    headv.z = 0;
    headtopv.x = 0;
    headtopv.y = 3.3;
    headtopv.z = 0;
    
    rshoulderv.x = -(lshoulderv.x = -0.4);
    rshoulderv.y = lshoulderv.y   = 2.05;
    rshoulderv.z = lshoulderv.z   = 0;
    ruarmv.x = -(luarmv.x = -1.15);
    ruarmv.y = luarmv.y   = 1.7;
    ruarmv.z = luarmv.z   = 0;
    rlarmv.x = -(llarmv.x = -1.3);
    rlarmv.y = llarmv.y   = 0.3;
    rlarmv.z = llarmv.z   = -0.05;
    rhandv.x = -(lhandv.x = -1.25);
    rhandv.y = lhandv.y   = -0.8;
    rhandv.z = lhandv.z   = 0;
    rhandtopv.x = -(lhandtopv.x = -1.2);
    rhandtopv.y = lhandtopv.y   = -1.5;
    rhandtopv.z = lhandtopv.z   = 0;
    
    rulegv.x = -(lulegv.x = -0.5);
    rulegv.y = lulegv.y   = -0.4;
    rulegv.z = lulegv.z   = 0;
    rllegv.x = -(lllegv.x = -0.45);
    rllegv.y = lllegv.y   = -2.4;
    rllegv.z = lllegv.z   = 0.05;
    rfootv.x = -(lfootv.x = -0.45);
    rfootv.y = lfootv.y   = -4.35;
    rfootv.z = lfootv.z   = 0;
    rfoottopv.x = -(lfoottopv.x = -0.45);
    rfoottopv.y = lfoottopv.y   = -4.35;
    rfoottopv.z = lfoottopv.z   = 0.7;
    
    vertices[0] = &waistv;
    vertices[1] = &chestv;
    vertices[2] = &neckv;
    vertices[3] = &headv;
    vertices[4] = &headtopv;
    vertices[5] = &rshoulderv;
    vertices[6] = &ruarmv;
    vertices[7] = &rlarmv;
    vertices[8] = &rhandv;
    vertices[9] = &rhandtopv;
    vertices[10] = &lshoulderv;
    vertices[11] = &luarmv;
    vertices[12] = &llarmv;
    vertices[13] = &lhandv;
    vertices[14] = &lhandtopv;
    vertices[15] = &rulegv;
    vertices[16] = &rllegv;
    vertices[17] = &rfootv;
    vertices[18] = &rfoottopv;
    vertices[19] = &lulegv;
    vertices[20] = &lllegv;
    vertices[21] = &lfootv;
    vertices[22] = &lfoottopv;
    vertices[23] = &waistc1v;
    vertices[24] = &waistc2v;
    vertices[25] = &chestc1v;
    vertices[26] = &chestc2v;
}

void initCapsules(){
    waistc.v1 = &waistc1v;
    waistc.v2 = &waistc2v;
    waistc.r = 0.35;
    chestc.v1 = &chestc1v;
    chestc.v2 = &chestc2v;
    chestc.r = 0.4;
    
    
    neckc.v1 = &neckv;
    neckc.v2 = &headv;
    neckc.r = 0.25;
    headc.v1 = &headv;
    headc.v2 = &headtopv;
    headc.r = 0.4;
    
    rshoulderc.v1 = &rshoulderv;
    rshoulderc.v2 = &ruarmv;
    rshoulderc.r = 0.3;
    ruarmc.v1 = &ruarmv;
    ruarmc.v2 = &rlarmv;
    ruarmc.r = 0.2;
    rlarmc.v1 = &rlarmv;
    rlarmc.v2 = &rhandv;
    rlarmc.r = 0.15;
    rhandc.v1 = &rhandv;
    rhandc.v2 = &rhandtopv;
    rhandc.r = 0.1;
    
    lshoulderc.v1 = &lshoulderv;
    lshoulderc.v2 = &luarmv;
    lshoulderc.r = 0.3;
    luarmc.v1 = &luarmv;
    luarmc.v2 = &llarmv;
    luarmc.r = 0.2;
    llarmc.v1 = &llarmv;
    llarmc.v2 = &lhandv;
    llarmc.r = 0.15;
    lhandc.v1 = &lhandv;
    lhandc.v2 = &lhandtopv;
    lhandc.r = 0.1;
    
    rulegc.v1 = &rulegv;
    rulegc.v2 = &rllegv;
    rulegc.r = 0.3;
    rllegc.v1 = &rllegv;
    rllegc.v2 = &rfootv;
    rllegc.r = 0.2;
    rfootc.v1 = &rfootv;
    rfootc.v2 = &rfoottopv;
    rfootc.r = 0.1;
    
    lulegc.v1 = &lulegv;
    lulegc.v2 = &lllegv;
    lulegc.r = 0.3;
    lllegc.v1 = &lllegv;
    lllegc.v2 = &lfootv;
    lllegc.r = 0.2;
    lfootc.v1 = &lfootv;
    lfootc.v2 = &lfoottopv;
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
    waistn.v1 = &waistv;
    waistn.v2 = &chestv;
    waistn.id = 1;
    waistn.sibling = &rulegn;
    waistn.child = &chestn;
    
    //chest
    glLoadIdentity();
    glTranslatef(0,1.0,0.0);
    chestn.cap = &chestc;
    chestn.v1 = &chestv;
    chestn.v2 = &neckv;
    chestn.id = 16;
    chestn.sibling = NULL;
    chestn.child = &neckn;
    
    //Neck
    glLoadIdentity();
    glTranslatef(0.0,1.8,0.0);
    neckn.cap = &neckc;
    neckn.v1 = &neckv;
    neckn.v2 = &headv;
    neckn.id = 2;
    neckn.sibling = &rshouldern;
    neckn.child = &headn;
    
    //HEAD
    glLoadIdentity();
    glTranslatef(0.0,0.5,0.0);
    headn.cap = &headc;
    headn.v1 = &headv;
    headn.v2 = &headtopv;
    headn.id = 3;
    headn.sibling = NULL;
    headn.child = NULL;

    //rshoulder
    glLoadIdentity();
    glTranslatef(-0.4,1.45,0.0);
    rshouldern.cap = &rshoulderc;
    rshouldern.v1 = &rshoulderv;
    rshouldern.v2 = &ruarmv;
    rshouldern.id = 17;
    rshouldern.sibling = &lshouldern;
    rshouldern.child = &ruarmn;
    
    //RIGHT UPPER ARM
    glLoadIdentity();
    glTranslatef(-0.85,-0.35,0.0);
    ruarmn.cap = &ruarmc;
    ruarmn.v1 = &ruarmv;
    ruarmn.v2 = &rlarmv;
    ruarmn.id = 4;
    ruarmn.sibling = NULL;
    ruarmn.child = &rlarmn;
    
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(-0.05,-1.3,-0.05);
    rlarmn.cap = &rlarmc;
    rlarmn.v1 = &rlarmv;
    rlarmn.v2 = &rhandv;
    rlarmn.id = 5;
    rlarmn.sibling = NULL;        
    rlarmn.child = &rhandn;
    
    //rhand
    glLoadIdentity();
    glTranslatef(0.05,-1.3,0.05);
    rhandn.cap = &rhandc;
    rhandn.v1 = &rhandv;
    rhandn.v2 = &rhandtopv;
    rhandn.id = 6;
    rhandn.sibling = NULL;        
    rhandn.child = NULL;
    
    //lshoulder
    glLoadIdentity();
    glTranslatef(0.4,1.45,0.0);
    lshouldern.cap = &lshoulderc;
    lshouldern.v1 = &lshoulderv;
    lshouldern.v2 = &luarmv;
    lshouldern.id = 17;
    lshouldern.sibling = NULL;
    lshouldern.child = &luarmn;
    
    //RIGHT UPPER ARM
    glLoadIdentity();
    glTranslatef(0.85,-0.35,0.0);
    luarmn.cap = &luarmc;
    luarmn.v1 = &luarmv;
    luarmn.v2 = &llarmv;
    luarmn.id = 7;
    luarmn.sibling = NULL;
    luarmn.child = &llarmn;
    
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(0.05,-1.3,-0.05);

    llarmn.cap = &llarmc;
    llarmn.v1 = &llarmv;
    llarmn.v2 = &lhandv;
    llarmn.id = 8;
    llarmn.sibling = NULL;        
    llarmn.child = &lhandn;
    
    //rhand
    glLoadIdentity();
    glTranslatef(-0.05,-1.3,0.05);
    lhandn.cap = &lhandc;
    lhandn.v1 = &lhandv;
    lhandn.v2 = &lhandtopv;
    lhandn.id = 9;
    lhandn.sibling = NULL;        
    lhandn.child = NULL;
    
    //RIGHT UPPER LEG
    glLoadIdentity();
    glTranslatef(-0.5,-0.4,0.0);
    rulegn.cap = &rulegc;
    rulegn.v1 = &rulegv;
    rulegn.v2 = &rllegv;
    rulegn.id = 10;
    rulegn.sibling = &lulegn;       
    rulegn.child = &rllegn; 
    
    //RIGHT LOWER LEG
    glLoadIdentity();
    glTranslatef(0.05,-2,0.0);
    rllegn.cap = &rllegc;
    rllegn.v1 = &rllegv;
    rllegn.v2 = &rfootv;
    rllegn.id = 11;
    rllegn.sibling = NULL;
    rllegn.child = &rfootn;
    
    //rfoot
    glLoadIdentity();
    glTranslatef(0,-2,0);
    rfootn.cap = &rfootc;
    rfootn.v1 = &rfootv;
    rfootn.v2 = &rfoottopv;
    rfootn.id = 12;
    rfootn.sibling = NULL;
    rfootn.child = NULL;
    
    //LEFT UPPER LEG
    glLoadIdentity();
    glTranslatef(0.5,-0.4,0.0);
    lulegn.cap = &lulegc;
    lulegn.v1 = &lulegv;
    lulegn.v2 = &lllegv;
    lulegn.id = 13;
    lulegn.sibling = NULL;       
    lulegn.child = &lllegn;                      
    
    //LEFT LOWER LEG
    glLoadIdentity();
    glTranslatef(-0.05,-2,0.0);
    lllegn.cap = &lllegc;
    lllegn.v1 = &lllegv;
    lllegn.v2 = &lfootv;
    lllegn.id = 14;
    lllegn.sibling = NULL;        
    lllegn.child = &lfootn;
    
    //lfoot
    glLoadIdentity();
    glTranslatef(0,-2,0);
    lfootn.cap = &lfootc;
    lfootn.v1 = &lfootv;
    lfootn.v2 = &lfoottopv;
    lfootn.id = 15;
    lfootn.sibling = NULL;        
    lfootn.child = NULL;
}

void init(){
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // define the light color and intensity
    GLfloat ambientLight[]	= { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuseLight[]	= { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specularLight[]	= { 1.0, 1.0, 1.0, 1.0 };

	//  the global ambient light level
    GLfloat globalAmbientLight[] = { 0.4, 0.4, 0.4, 1.0 };

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

float colDetect(capsule *cap, vertex *h){
       
    float D[3];
    D[0] = h->x - cap->v1->x;
    D[1] = h->y - cap->v1->y;
    D[2] = h->z - cap->v1->z;

    float C[3];
    C[0] = (cap->v1->x + cap->v2->x)/2;
    C[1] = (cap->v1->y + cap->v2->y)/2;
    C[2] = (cap->v1->z + cap->v2->z)/2;
    
    float A[3];
    A[0] = (cap->v2->x - cap->v1->x) / (sqrt((cap->v2->x - cap->v1->x)*(cap->v2->x - cap->v1->x) + (cap->v2->y - cap->v1->y) * (cap->v2->y-cap->v1->y) + (cap->v2->z-cap->v1->z) * (cap->v2->z-cap->v1->z)));
    A[1] = (cap->v2->y - cap->v1->y) / (sqrt((cap->v2->x - cap->v1->x)*(cap->v2->x - cap->v1->x) + (cap->v2->y - cap->v1->y) * (cap->v2->y-cap->v1->y) + (cap->v2->z-cap->v1->z) * (cap->v2->z-cap->v1->z)));
    A[2] = (cap->v2->z - cap->v1->z) / (sqrt((cap->v2->x - cap->v1->x)*(cap->v2->x - cap->v1->x) + (cap->v2->y - cap->v1->y) * (cap->v2->y-cap->v1->y) + (cap->v2->z-cap->v1->z) * (cap->v2->z-cap->v1->z)));

    float d = D[0] * A[0] + D[1] * A[1] + D[2] * A[2];
    if(d<0)
        d = 0;
    float caplen = vertDistance(cap->v1, cap->v2);
    if(d>caplen)
        d = caplen;
    
    float R[3];
    R[0] = cap->v1->x + (A[0] * d);
    R[1] = cap->v1->y + (A[1] * d);
    R[2] = cap->v1->z + (A[2] * d);
    float b = distance3d(h->x,h->y,h->z, R[0],R[1],R[2]);
    
    float penetration = 0;
    
    if(b < cap->r)
        penetration = b - cap->r;
    
    float N[3];
    N[0] = h->x - R[0] / b;
    N[1] = h->y - R[1] / b;
    N[2] = h->z - R[2] / b;
    
    return penetration;
}

void rotVertX(vertex *v, vertex *pt, float angx){
    float newy = pt->y + (v->y - pt->y) * cosf(angx * M_PI/180) - (v->z - pt->z) * sinf(angx * M_PI/180);
    float newz = pt->z + (v->z - pt->z) * cosf(angx * M_PI/180) + (v->y - pt->y) * sinf(angx * M_PI/180);
    v->y = newy;
    v->z = newz;
}

void rotVertY(vertex *v, vertex *pt, float angy){
    float newx = pt->x + (v->x - pt->x) * cosf(angy * M_PI/180) - (v->z - pt->z) * sinf(angy * M_PI/180);
    float newz = pt->z + (v->z - pt->z) * cosf(angy * M_PI/180) + (v->x - pt->x) * sinf(angy * M_PI/180);
    v->x = newx;
    v->z = newz;
}

void rotVertZ(vertex *v, vertex *pt, float angz){
    float newx = pt->x + (v->x - pt->x) * cosf(angz * M_PI/180) - (v->y - pt->y) * sinf(angz * M_PI/180);
    float newy = pt->y + (v->y - pt->y) * cosf(angz * M_PI/180) + (v->x - pt->x) * sinf(angz * M_PI/180);
    v->x = newx;
    v->y = newy;
}

void rotChildNode(treenode *n, vertex *pt, float angx, float angy, float angz){
    if(n->v1->hasmoved == false){
        if(angx != 0)
            rotVertX(n->v1, pt, angx);
        if(angy != 0)
            rotVertY(n->v1, pt, angy);
        if(angz != 0)
            rotVertZ(n->v1, pt, angz);
        n->v1->hasmoved = true;
    }
    if(n->v2->hasmoved == false){
        if(angx != 0)
            rotVertX(n->v2, pt, angx);
        if(angy != 0)
            rotVertY(n->v2, pt, angy);
        if(angz != 0)
            rotVertZ(n->v2, pt, angz);
        n->v2->hasmoved = true;
    }
    if(n->cap->v1->hasmoved == false){
        if(angx != 0)
            rotVertX(n->cap->v1, pt, angx);
        if(angy != 0)
            rotVertY(n->cap->v1, pt, angy);
        if(angz != 0)
            rotVertZ(n->cap->v1, pt, angz);
        n->cap->v1->hasmoved = true;
    }
    if(n->cap->v2->hasmoved == false){
        if(angx != 0)
            rotVertX(n->cap->v2, pt, angx);
        if(angy != 0)
            rotVertY(n->cap->v2, pt, angy);
        if(angz != 0)
            rotVertZ(n->cap->v2, pt, angz);
        n->cap->v2->hasmoved = true;
    }
    if(n->child != NULL)
    	rotChildNode(n->child, pt, angx, angy, angz);
        
    if(n->sibling != NULL)
    	rotChildNode(n->sibling, pt, angx, angy, angz);
}

void rotNode(treenode *n, float angx, float angy, float angz){
    if(n->v2->hasmoved == false){
        if(angx != 0)
            rotVertX(n->v2, n->v1, angx);
        if(angy != 0)
            rotVertY(n->v2, n->v1, angy);
        if(angz != 0)
            rotVertZ(n->v2, n->v1, angz);
        n->v2->hasmoved = true;
    }
    if(n->cap->v1->hasmoved == false){
        if(angx != 0)
            rotVertX(n->cap->v1, n->v1, angx);
        if(angy != 0)
            rotVertY(n->cap->v1, n->v1, angy);
        if(angz != 0)
            rotVertZ(n->cap->v1, n->v1, angz);
        n->cap->v1->hasmoved = true;
    }
    if(n->cap->v2->hasmoved == false){
        if(angx != 0)
            rotVertX(n->cap->v2, n->v1, angx);
        if(angy != 0)
            rotVertY(n->cap->v2, n->v1, angy);
        if(angz != 0)
            rotVertZ(n->cap->v2, n->v1, angz);
        n->cap->v2->hasmoved = true;
    }
    if(n->child != NULL)
    	rotChildNode(n->child, n->v1, angx, angy, angz);
}

void traverse (treenode *node){
    if(jointswitch){
        drawJoint(node->v1, node->id);
    }
    
    if(capsuleswitch){
         drawCapsule(node->cap);
    }
    
    // primer recorrer los hijos (si hay)
    if(node->child != NULL)
    	traverse(node->child);
        
    // después recorrer los hermanos (si hay)
    if(node->sibling != NULL)
    	traverse(node->sibling);
}

void reshape(int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLdouble)w/(GLdouble)h, 1.0, 100.0) ;
}

void drawVert(){
     glPointSize(10);
     int i;
     glBegin(GL_POINTS);
     for(i=0; i<skinobject->vTotal; i++)
             glVertex3fv(skinobject->vList[i].ptr);
     for(i=0; i<shirtobject->vTotal; i++)
             glVertex3fv(shirtobject->vList[i].ptr);
     glEnd();
}

void drawMesh(mesh *object, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess){
     glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
     glMaterialf(GL_FRONT,  GL_SHININESS, shininess);
    	 
     glBegin(GL_TRIANGLES);
         GLfloat normals[3];
         float ax, ay, az, bx, by, bz, nx, ny, nz, n;
         for(int i = 0; i < object->fTotal; i++){
             ax = object->vList[object->faceList[i][1].v].ptr[0] - object->vList[object->faceList[i][0].v].ptr[0];
             ay = object->vList[object->faceList[i][1].v].ptr[1] - object->vList[object->faceList[i][0].v].ptr[1];
             az = object->vList[object->faceList[i][1].v].ptr[2] - object->vList[object->faceList[i][0].v].ptr[2];
             bx = object->vList[object->faceList[i][2].v].ptr[0] - object->vList[object->faceList[i][0].v].ptr[0];
             by = object->vList[object->faceList[i][2].v].ptr[1] - object->vList[object->faceList[i][0].v].ptr[1];
             bz = object->vList[object->faceList[i][2].v].ptr[2] - object->vList[object->faceList[i][0].v].ptr[2];
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
                  glNormal3fv(normals);
                  glVertex3fv(object->vList[object->faceList[i][j].v].ptr);
             }
         }
     glEnd();            
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
    
    if(gridswitch)
   	    drawGrid();
	
	///////
	//drawCapsule(testcap);
	
    glPushMatrix();
        glTranslatef(testvert.x, testvert.y, testvert.z);
        glutSolidSphere(0.1,10,10);
    glPopMatrix();
    
    float mincoll = 0;
    int numcap = -1;
    
    for(int i=0;i<NUMCAPS;i++){
        if(colDetect(caps[i], &testvert) < 0){
            glPushMatrix();
                glTranslatef(-2,3,0);
                glutSolidCube(1);
            glPopMatrix();
            
            if(mincoll > colDetect(caps[i], &testvert))
                mincoll = colDetect(caps[i], &testvert);
                numcap = i;
        }
    }
    sprintf(title, "Collision at: %g, capsule num: %d", mincoll, numcap);
    glutSetWindowTitle(title);
    ///////


	glPushMatrix();
        glMultMatrixf(bodypos);
        traverse(&waistn);
    glPopMatrix();  
    
        if(skinswitch)
            if(alphaswitch)
                drawMesh(skinobject, zeroMaterial, pinkDiffuseAlpha, zeroMaterial, noShininess);
            else
                drawMesh(skinobject, zeroMaterial, pinkDiffuse, zeroMaterial, noShininess);
                
        if(shirtswitch)
            if(alphaswitch)
                drawMesh(shirtobject, zeroMaterial, blueDiffuseAlpha, zeroMaterial, noShininess);
            else
                drawMesh(shirtobject, zeroMaterial, blueDiffuse, zeroMaterial, noShininess);
                
        if(vertswitch)
            drawVert();

   	glutSwapBuffers();
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

void key(unsigned char c, int x, int y){
     if(c==27)//esc
                exit(0);
     //ZOOM
     if(c=='+'){
                zoom -= 1;
                glutPostRedisplay();
     }
     if(c=='-'){
                zoom += 1;
                glutPostRedisplay();
     }
     //SWITCHES
     if(c=='s'){
                smoothswitch = !smoothswitch;
                glutPostRedisplay();
     }
     if(c=='d'){
                skinswitch = !skinswitch;
                glutPostRedisplay();
     }
     if(c=='f'){
                shirtswitch = !shirtswitch;
                glutPostRedisplay();
     }
     if(c=='c'){
                capsuleswitch = !capsuleswitch;
                glutPostRedisplay();
     }
     if(c=='v'){
                vertswitch = !vertswitch;
                glutPostRedisplay();
     }
     if(c=='a'){
                alphaswitch = !alphaswitch;
                glutPostRedisplay();
     }
     if(c=='j'){
                jointswitch = !jointswitch;
                glutPostRedisplay();
     }
     if(c=='g'){
                gridswitch = !gridswitch;
                glutPostRedisplay();
     }
     //SELECTS
     if(c == '0'){
          segselect=0;
     }
     if(c == '1'){
          segselect=1;
     }
     if(c == '2'){
          segselect=2;
     }
     if(c == '3'){
          segselect=3;
     }
     if(c == '4'){
          segselect=4;
     }
     if(c == '5'){
          segselect=5;
     }
     if(c == '6'){
          segselect=6;
     }
     if(c == '7'){
          segselect=7;
     }
     if(c == '8'){
          segselect=8;
     }
     if(c == '9'){
          segselect=9;
     }
     if(c == 'q'){
          segselect=10;
     }
     if(c == 'w'){
          segselect=11;
     }
     if(c == 'e'){
          segselect=12;
     }
     if(c == 'r'){
          segselect=13;
     }
     if(c == 't'){
          segselect=14;
     }
     if(c == 'y'){
          segselect=15;
     }
     if(c == 'i'){
          initVertices();
          initCapsules();
          initNodes();
     }
     glutPostRedisplay();

}

void resetAngles(){
     anglex = 0;
     angley = 0;
}

void resetVertFlags(){
    for(int i=0;i<NUMVERT;i++){
        vertices[i]->hasmoved = false;
    }
}

void special(int c, int x, int y){
     if(c==GLUT_KEY_UP){
         angley = -angdelta;
         if(segselect==0)testvert.z-=0.1;
     }
     if(c==GLUT_KEY_DOWN){
         angley = angdelta;
         if(segselect==0)testvert.z+=0.1;
     }
     if(c==GLUT_KEY_RIGHT){
         anglex = -angdelta;
         if(segselect==0)testvert.x+=0.1;
     }
     if(c==GLUT_KEY_LEFT){
         anglex = +angdelta;
         if(segselect==0)testvert.x-=0.1;
     }
     if(c==GLUT_KEY_PAGE_UP){
         //testcap.r+=0.1;
         if(segselect==0)testvert.y+=0.1;
     }
     if(c==GLUT_KEY_PAGE_DOWN){
         //testcap.r-=0.1;
         if(segselect==0)testvert.y-=0.1;
     }
     
     glPushMatrix();
     glLoadIdentity();
     
     switch(segselect){
         case 0:
              //glMultMatrixf(bodypos);
//              glRotatef(anglex,1.0,0.0,0.0);
//              glRotatef(angley,0.0,1.0,0.0);
//              glGetFloatv(GL_MODELVIEW_MATRIX, bodypos);
              break;
         case 1:
              rotNode(&waistn, 0,anglex,0);
              resetVertFlags();
              rotNode(&waistn, angley,0,0);
              resetVertFlags();
              break;

         case 2:
              rotNode(&neckn, 0,0,anglex);
              resetVertFlags();
              rotNode(&neckn, angley,0,0);
              resetVertFlags();
              break;
         case 3:
              rotNode(&headn, 0,anglex,0);
              resetVertFlags();
              rotNode(&headn, angley,0,0);
              resetVertFlags();
              break;
         case 4:
              rotNode(&ruarmn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&ruarmn, angley,0,0);
              resetVertFlags();
              break;
         case 5:
              rotNode(&rlarmn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&rlarmn, angley,0,0);
              resetVertFlags();
              break;
         case 6:
              rotNode(&rhandn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&rhandn, angley,0,0);
              resetVertFlags();
              break;
         case 7:
              rotNode(&luarmn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&luarmn, angley,0,0);
              resetVertFlags();
              break;
         case 8:
              rotNode(&llarmn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&llarmn, angley,0,0);
              resetVertFlags();
              break;
         case 9:
              rotNode(&lhandn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&lhandn, angley,0,0);
              resetVertFlags();
              break;
         case 10:
              rotNode(&rulegn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&rulegn, angley,0,0);
              resetVertFlags();
              break;
         case 11:
              rotNode(&rllegn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&rllegn, angley,0,0);
              resetVertFlags();
              break;
         case 12:
              rotNode(&rfootn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&rfootn, angley,0,0);
              resetVertFlags();
              break;
         case 13:
              rotNode(&lulegn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&lulegn, angley,0,0);
              resetVertFlags();
              break;
         case 14:
              rotNode(&lllegn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&lllegn, angley,0,0);
              resetVertFlags();
              break;
         case 15:
              rotNode(&lfootn, 0,0,-anglex);
              resetVertFlags();
              rotNode(&lfootn, angley,0,0);
              resetVertFlags();
              break;
     }
     glPopMatrix();
     resetAngles();
     glutPostRedisplay();
}

void mouseMotion(int x, int y){
    if (mouseDown){
        yrot = x - xdiff;
        xrot = y + ydiff;
        
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
  int mode = GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH;   // Modo de despliegue: Colores RGB, Doble buffer para despliegue
  glutInitDisplayMode(mode);                    // Inicializar modo de despliegue.
  glutInitWindowSize(500,500);                  // Inicializar tamaño de la ventana
  glutInit(&argc, argv);                        // Inicializar GLUT
  glutCreateWindow("Proyecto");                 // Crear una ventana con el título indicado.
  glutDisplayFunc(display);                     // Indicar la función para desplegar.
  glutReshapeFunc(reshape);                     // Indicar la función en caso de cambio de tamaño de la ventana
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(key);
  glutSpecialFunc(special);
  
  init();
  initSkin();
  initShirt();
  //initPants();
  initVertices();
  initCapsules();
  initNodes();
  
  glutMainLoop();                               // Pasar el control a GLUT.
  return 0;                                     // Regresar 0 por cortesía.
}
