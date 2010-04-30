/*****************************************
 ***Equipo***
 *
 *José Ugalde 1161507
 *Alejandro Morales 1161376
 *Jorge Dorantes 1011377
 *Enrique Peña 1162110
 *
 *Monito Final
*******************************************/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
//#include <stdio.h>
//#include <map>
#include <vector>
#include <string>

#include "obj_parser.h"
#include "objLoader.h"
#include "structs.h"

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
bool alphaswitch     = false;//true;
bool smoothswitch    = true;
bool capsuleswitch   = true;
bool jointswitch     = true;

bool skinvisswitch   = false;//true;
bool skinvertswitch  = false;//true;
bool shirtvisswitch  = true;
bool shirtvertswitch = false;//true;
//bool pantsvisswitch     = true;
//bool pantsvertswitch     = true;
bool gridswitch      = false;




bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 12.0;

objLoader *skindata;
objLoader *shirtdata;
//objLoader *pantsdata;

bodyvertex waistbv, chestbv, neckbv, headbv, headtopbv, 
       rshoulderbv, ruarmbv, rlarmbv, rhandbv, rhandtopbv, lshoulderbv, luarmbv, llarmbv, lhandbv, lhandtopbv, 
       rulegbv, rllegbv, rfootbv, rfoottopbv, lulegbv, lllegbv, lfootbv, lfoottopbv, 
       waistc1bv, waistc2bv, chestc1bv, chestc2bv;
//
Vec3 testvert;
//

capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc,
        chestc, waistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

treenode headn, neckn, rshouldern, lshouldern, ruarmn, luarmn, rlarmn, llarmn, rhandn, lhandn,
         chestn, waistn, rulegn, lulegn, rllegn, lllegn, rfootn, lfootn;

GLfloat bodypos[16];

capsule testcap;

bodyvertex   *bodyverts[NUMVERT];
capsule  *caps[NUMCAPS];
particle *particles;



//----------------------------------------------

float vDistance(Vec3 *v1, Vec3 *v2){
    return sqrt(pow((v1->f[0]-v2->f[0]),2) + pow((v1->f[1]-v2->f[1]),2) + pow((v1->f[2]-v2->f[2]),2));
}

float distance3d(float x1,float y1,float z1,float x2,float y2,float z2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2) + pow((z1-z2),2));
}

float distance2d(float x1,float y1,float x2,float y2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}

void drawJoint(Vec3 *v, int id){
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
         glTranslatef(v->f[0],v->f[1],v->f[2]);
         glutSolidSphere(jointsize,10,10);
     glPopMatrix();
     
}

void drawCapsule(capsule *cap){
//     glLineWidth(5);
//     glBegin(GL_LINES);
//         glVertex3f(cap->v1->f[0],cap->v1->f[1],cap->v1->f[2]);
//         glVertex3f(cap->v2->f[0],cap->v2->f[1],cap->v2->f[2]);
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
     if(alphaswitch)
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

float colDetect(capsule *cap, Vec3 *h){
       
    float D[3];
    D[0] = h->f[0] - cap->bv1->v.f[0];
    D[1] = h->f[1] - cap->bv1->v.f[1];
    D[2] = h->f[2] - cap->bv1->v.f[2];

    float C[3];
    C[0] = (cap->bv1->v.f[0] + cap->bv2->v.f[0])/2;
    C[1] = (cap->bv1->v.f[1] + cap->bv2->v.f[1])/2;
    C[2] = (cap->bv1->v.f[2] + cap->bv2->v.f[2])/2;
    
    float A[3];
    A[0] = (cap->bv2->v.f[0] - cap->bv1->v.f[0]) / (sqrt((cap->bv2->v.f[0] - cap->bv1->v.f[0])*(cap->bv2->v.f[0] - cap->bv1->v.f[0]) + (cap->bv2->v.f[1] - cap->bv1->v.f[1]) * (cap->bv2->v.f[1]-cap->bv1->v.f[1]) + (cap->bv2->v.f[2]-cap->bv1->v.f[2]) * (cap->bv2->v.f[2]-cap->bv1->v.f[2])));
    A[1] = (cap->bv2->v.f[1] - cap->bv1->v.f[1]) / (sqrt((cap->bv2->v.f[0] - cap->bv1->v.f[0])*(cap->bv2->v.f[0] - cap->bv1->v.f[0]) + (cap->bv2->v.f[1] - cap->bv1->v.f[1]) * (cap->bv2->v.f[1]-cap->bv1->v.f[1]) + (cap->bv2->v.f[2]-cap->bv1->v.f[2]) * (cap->bv2->v.f[2]-cap->bv1->v.f[2])));
    A[2] = (cap->bv2->v.f[2] - cap->bv1->v.f[2]) / (sqrt((cap->bv2->v.f[0] - cap->bv1->v.f[0])*(cap->bv2->v.f[0] - cap->bv1->v.f[0]) + (cap->bv2->v.f[1] - cap->bv1->v.f[1]) * (cap->bv2->v.f[1]-cap->bv1->v.f[1]) + (cap->bv2->v.f[2]-cap->bv1->v.f[2]) * (cap->bv2->v.f[2]-cap->bv1->v.f[2])));

    float d = D[0] * A[0] + D[1] * A[1] + D[2] * A[2];
    if(d<0)
        d = 0;
    float caplen = vDistance(&(cap->bv1->v), &(cap->bv2->v));
    if(d>caplen)
        d = caplen;
    
    float R[3];
    R[0] = cap->bv1->v.f[0] + (A[0] * d);
    R[1] = cap->bv1->v.f[1] + (A[1] * d);
    R[2] = cap->bv1->v.f[2] + (A[2] * d);
    float b = distance3d(h->f[0],h->f[1],h->f[2], R[0],R[1],R[2]);
    
    float penetration = 0;
    
    if(b < cap->r)
        penetration = b - cap->r;
    
    float N[3];
    N[0] = h->f[0] - R[0] / b;
    N[1] = h->f[1] - R[1] / b;
    N[2] = h->f[2] - R[2] / b;
    
    return penetration;
}

void rotVertX(Vec3 *v, Vec3 *pt, float angx){
    float newy = pt->f[1] + (v->f[1] - pt->f[1]) * cosf(angx * M_PI/180) - (v->f[2] - pt->f[2]) * sinf(angx * M_PI/180);
    float newz = pt->f[2] + (v->f[2] - pt->f[2]) * cosf(angx * M_PI/180) + (v->f[1] - pt->f[1]) * sinf(angx * M_PI/180);
    v->f[1] = newy;
    v->f[2] = newz;
}

void rotVertY(Vec3 *v, Vec3 *pt, float angy){
    float newx = pt->f[0] + (v->f[0] - pt->f[0]) * cosf(angy * M_PI/180) - (v->f[2] - pt->f[2]) * sinf(angy * M_PI/180);
    float newz = pt->f[2] + (v->f[2] - pt->f[2]) * cosf(angy * M_PI/180) + (v->f[0] - pt->f[0]) * sinf(angy * M_PI/180);
    v->f[0] = newx;
    v->f[2] = newz;
}

void rotVertZ(Vec3 *v, Vec3 *pt, float angz){
    float newx = pt->f[0] + (v->f[0] - pt->f[0]) * cosf(angz * M_PI/180) - (v->f[1] - pt->f[1]) * sinf(angz * M_PI/180);
    float newy = pt->f[1] + (v->f[1] - pt->f[1]) * cosf(angz * M_PI/180) + (v->f[0] - pt->f[0]) * sinf(angz * M_PI/180);
    v->f[0] = newx;
    v->f[1] = newy;
}

void rotChildNode(treenode *n, Vec3 *pt, float angx, float angy, float angz){
    if(n->bv1->hasmoved == false){
        if(angx != 0)
            rotVertX(&(n->bv1->v), pt, angx);
        if(angy != 0)
            rotVertY(&(n->bv1->v), pt, angy);
        if(angz != 0)
            rotVertZ(&(n->bv1->v), pt, angz);
        n->bv1->hasmoved = true;
    }
    if(n->bv2->hasmoved == false){
        if(angx != 0)
            rotVertX(&(n->bv2->v), pt, angx);
        if(angy != 0)
            rotVertY(&(n->bv2->v), pt, angy);
        if(angz != 0)
            rotVertZ(&(n->bv2->v), pt, angz);
        n->bv2->hasmoved = true;
    }
    if(n->cap->bv1->hasmoved == false){
        if(angx != 0)
            rotVertX(&(n->cap->bv1->v), pt, angx);
        if(angy != 0)
            rotVertY(&(n->cap->bv1->v), pt, angy);
        if(angz != 0)
            rotVertZ(&(n->cap->bv1->v), pt, angz);
        n->cap->bv1->hasmoved = true;
    }
    if(n->cap->bv2->hasmoved == false){
        if(angx != 0)
            rotVertX(&(n->cap->bv2->v), pt, angx);
        if(angy != 0)
            rotVertY(&(n->cap->bv2->v), pt, angy);
        if(angz != 0)
            rotVertZ(&(n->cap->bv2->v), pt, angz);
        n->cap->bv2->hasmoved = true;
    }
    if(n->child != NULL)
    	rotChildNode(n->child, pt, angx, angy, angz);
        
    if(n->sibling != NULL)
    	rotChildNode(n->sibling, pt, angx, angy, angz);
}

void rotNode(treenode *n, float angx, float angy, float angz){
    if(n->bv2->hasmoved == false){
        if(angx != 0)
            rotVertX(&(n->bv2->v), &(n->bv1->v), angx);
        if(angy != 0)
            rotVertY(&(n->bv2->v), &(n->bv1->v), angy);
        if(angz != 0)
            rotVertZ(&(n->bv2->v), &(n->bv1->v), angz);
        n->bv2->hasmoved = true;
    }
    if(n->cap->bv1->hasmoved == false){
        if(angx != 0)
            rotVertX(&(n->cap->bv1->v), &(n->bv1->v), angx);
        if(angy != 0)
            rotVertY(&(n->cap->bv1->v), &(n->bv1->v), angy);
        if(angz != 0)
            rotVertZ(&(n->cap->bv1->v), &(n->bv1->v), angz);
        n->cap->bv1->hasmoved = true;
    }
    if(n->cap->bv2->hasmoved == false){
        if(angx != 0)
            rotVertX(&(n->cap->bv2->v), &(n->bv1->v), angx);
        if(angy != 0)
            rotVertY(&(n->cap->bv2->v), &(n->bv1->v), angy);
        if(angz != 0)
            rotVertZ(&(n->cap->bv2->v), &(n->bv1->v), angz);
        n->cap->bv2->hasmoved = true;
    }
    if(n->child != NULL)
    	rotChildNode(n->child, &(n->bv1->v), angx, angy, angz);
}

void traverse (treenode *node){
    if(jointswitch){
        drawJoint(&(node->bv1->v), node->id);
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

void drawVert(objLoader *object){
     glPointSize(10);
     int i;
     obj_face *o_f;
     glBegin(GL_POINTS);
         for(i=0; i<object->faceCount; i++){
              o_f = object->faceList[i];
              glNormal3dv(object->normalList[o_f->normal_index[0]]->e);
              glVertex3dv(object->vertexList[o_f->vertex_index[0]]->e);
         }
     glEnd();
}

void drawObject(objLoader *object, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess){
     glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
     glMaterialf(GL_FRONT,  GL_SHININESS, shininess);
   	 
   	 obj_face *o_f;
     glBegin(GL_TRIANGLES);
         ///calculate normals
         GLfloat normals[3];
         float ax, ay, az, bx, by, bz, nx, ny, nz, n;
         for(int i = 0; i < object->faceCount; i++){
             //ax = object->vertexList[object->faceList[i][1]].e[0] - object->vertexList[object->faceList[i][0]].e[0];
//             ay = object->vertexList[object->faceList[i][1]].e[1] - object->vertexList[object->faceList[i][0]].e[1];
//             az = object->vertexList[object->faceList[i][1]].e[2] - object->vertexList[object->faceList[i][0]].e[2];
//             bx = object->vertexList[object->faceList[i][2]].e[0] - object->vertexList[object->faceList[i][0]].e[0];
//             by = object->vertexList[object->faceList[i][2]].e[1] - object->vertexList[object->faceList[i][0]].e[1];
//             bz = object->vertexList[object->faceList[i][2]].e[2] - object->vertexList[object->faceList[i][0]].e[2];
//             nx = ay*bz - az*by;
//             ny = az*bx - ax*bz;
//             nz = ax*by - ay*bx;
//             n = sqrt(nx*nx+ny*ny+nz*nz);
//             if (n != 0.0) {
//                n = 1.0/n;
//            	nx *= n; ny *= n; nz *= n;
//             }
//             normals[0] = nx;
//             normals[1] = ny;
//             normals[2] = nz;
             ///calc nor
             o_f = object->faceList[i];
             for(int j=0; j<3; j++){
                  glNormal3dv(object->normalList[o_f->normal_index[j]]->e);
                  glVertex3dv(object->vertexList[o_f->vertex_index[j]]->e);
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
        glTranslatef(testvert.f[0], testvert.f[1], testvert.f[2]);
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
    
        if(skinvisswitch)
            if(alphaswitch)
                drawObject(skindata, zeroMaterial, pinkDiffuseAlpha, zeroMaterial, noShininess);
            else
                drawObject(skindata, zeroMaterial, pinkDiffuse, zeroMaterial, noShininess);
                
        if(shirtvisswitch)
            if(alphaswitch)
                drawObject(shirtdata, zeroMaterial, blueDiffuseAlpha, zeroMaterial, noShininess);
            else
                drawObject(shirtdata, zeroMaterial, blueDiffuse, zeroMaterial, noShininess);
        
//        if(pantsvisswitch)
//            if(alphaswitch)
//                drawObject(pantsdata, zeroMaterial, pinkDiffuseAlpha, zeroMaterial, noShininess);
//            else
//                drawObject(pantsdata, zeroMaterial, pinkDiffuse, zeroMaterial, noShininess);
        
        glDisable(GL_LIGHTING);
            glColor3f(0.7, 0.7, 0.7);
            if(skinvertswitch)
                drawVert(skindata);
            if(shirtvertswitch)
                drawVert(shirtdata);
            //if(vertswitch)
                //drawVert(pantsdata);
        glEnable(GL_LIGHTING);
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
                skinvisswitch = !skinvisswitch;
                glutPostRedisplay();
     }
     if(c=='f'){
                shirtvisswitch = !shirtvisswitch;
                glutPostRedisplay();
     }
     if(c=='c'){
                capsuleswitch = !capsuleswitch;
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
        bodyverts[i]->hasmoved = false;
    }
}

void special(int c, int x, int y){
     if(c==GLUT_KEY_UP){
         angley = -angdelta;
         if(segselect==0)testvert.f[2] -= 0.1;
     }
     if(c==GLUT_KEY_DOWN){
         angley = angdelta;
         if(segselect==0)testvert.f[2] += 0.1;
     }
     if(c==GLUT_KEY_RIGHT){
         anglex = -angdelta;
         if(segselect==0)testvert.f[0] += 0.1;
     }
     if(c==GLUT_KEY_LEFT){
         anglex = +angdelta;
         if(segselect==0)testvert.f[0] -= 0.1;
     }
     if(c==GLUT_KEY_PAGE_UP){
         //testcap.r+=0.1;
         if(segselect==0)testvert.f[1] += 0.1;
     }
     if(c==GLUT_KEY_PAGE_DOWN){
         //testcap.r-=0.1;
         if(segselect==0)testvert.f[1] -= 0.1;
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

void processMenu(int val){
	switch(val){
        case 1:
             alphaswitch = !alphaswitch;
             break;
        case 2:
             smoothswitch = !smoothswitch;
             break;
        case 3:
             capsuleswitch = !capsuleswitch;
             break;
        case 4:
             jointswitch = !jointswitch;
             break;
        case 11:
             skinvisswitch = !skinvisswitch;
             break;
        case 12:
             skinvertswitch = !skinvertswitch;
             break;
        case 21:
             shirtvisswitch = !shirtvisswitch;
             break;
        case 22:
             shirtvertswitch = !shirtvertswitch;
             break;
        //case 31:
//             pantsvisswitch = !pantsvisswitch;
//             break;
//        case 32:
//             pantsvertswitch = !pantsvertswitch;
//             break;
        case 0:
             exit(0);
    }
    glutPostRedisplay();
}

void initObj(){
    skindata = new objLoader();
    skindata->load("cuerpob.obj");
    
    shirtdata = new objLoader();
    shirtdata->load("camisab.obj");
    
    //pantsdata = new objLoader();
    //pantsdata->load("pantsb.obj");
}

void initCloth(){
    int numSprings = 0;
    for(int i=0;i < shirtdata->faceCount; i++){
        
    }
}

int initMenus(){
	int mainMenu, skinMenu, shirtMenu;//,pantsMenu;
	mainMenu = glutCreateMenu(processMenu);
	skinMenu = glutCreateMenu(processMenu);
	shirtMenu = glutCreateMenu(processMenu);
	//pantsMenu = glutCreateMenu(processMenu);
	glutSetMenu(mainMenu);
	glutAddSubMenu("Skin", skinMenu);
	glutAddSubMenu("Shirt", shirtMenu);
	//glutAddSubMenu("Pants", pantsMenu);
	glutAddMenuEntry("Toggle Alpha",              1);
	glutAddMenuEntry("Toggle Smooth",             2);
	glutAddMenuEntry("Toggle Capsule Visibility", 3);
	glutAddMenuEntry("Toggle Joint Visibility",   4);
	glutAddMenuEntry("Quit", 0);
	glutSetMenu(skinMenu);
	glutAddMenuEntry("Toggle Visibility",        11);
	glutAddMenuEntry("Toggle Vertex Visibility", 12);
	glutSetMenu(shirtMenu);
	glutAddMenuEntry("Toggle Visibility",        21);
	glutAddMenuEntry("Toggle Vertex Visibility", 22);
	//glutSetMenu(pantsMenu);
//	glutAddMenuEntry("Toggle Visibility",        31);
//	glutAddMenuEntry("Toggle Vertex Visibility", 32);
	glutSetMenu(mainMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
  initMenus();
  initObj();
  initCloth();
  initVertices();
  initCapsules();
  initNodes();
  
  glutMainLoop();                               // Pasar el control a GLUT.
  return 0;                                     // Regresar 0 por cortesía.
}
