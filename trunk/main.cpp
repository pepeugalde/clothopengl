/*****************************************
 ***Equipo***
 *
 *Enrique Peña 1162110
 *Jorge Dorantes 1011377
 *José Ugalde 1161507
 *Alejandro Morales 1161376
 *
 *Monito Final Parte 1
*******************************************/

#include "mesh.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

//materiales
int smoothOn =1;
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


int angdelta = 5;
GLfloat anglesx[15]={0.0,0.0,0.0,0.0,0.0,
                     0.0,0.0,0.0,0.0,0.0,
                     0.0,0.0,0.0,0.0,0.0};
GLfloat anglesy[15]={0.0,0.0,0.0,0.0,0.0,
                     0.0,0.0,0.0,0.0,0.0,
                     0.0,0.0,0.0,0.0,0.0};
int segselect = 0;
float jointsize = 0.3;
GLUquadric* q = gluNewQuadric();

//SWITCHES
bool capsuleswitch   = true;
bool skinswitch      = true;
bool shirtswitch     = false;//true;
bool gridswitch      = false;
bool vertswitch      = false;
bool jointswitch     = true;
bool alphaswitch     = true;

bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 12.0;

mesh *skinobject;
mesh *shirtobject;

//typedef struct capsule{
//    float x1, y1, z1, x2, y2, z2;
//    float radio;
//} capsule;

//capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc,
//chestc, waistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

typedef struct treenode{
    float x1, y1, z1, x2, y2, z2;
    float radio;
    int id;
    GLfloat m[16];
    struct treenode *sibling;
    struct treenode *child;
    
} treenode;

treenode headn, neckn, rshouldern, lshouldern, ruarmn, luarmn, rlarmn, llarmn, rhandn, lhandn,
chestn, waistn, rulegn, lulegn, rllegn, lllegn, rfootn, lfootn;

void initSkin(){
     skinobject = new mesh("cuerpob.obj");
}

void initShirt(){
     shirtobject = new mesh("camisab.obj");
}

float distance3d(float x1,float y1,float z1,float x2,float y2,float z2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2) + pow((z1-z2),2));
}

float distance2d(float x1,float y1,float x2,float y2){
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}

void drawJoint(int id){
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
    	     glMaterialfv(GL_FRONT, GL_DIFFUSE,   whiteDiffuseAlpha);
   	     else
   	         glMaterialfv(GL_FRONT, GL_DIFFUSE,   whiteDiffuse);
    	 glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
    	 glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
     }
     glutSolidSphere(jointsize,10,10);
}
void drawCapsule(float x1,float y1,float z1,float x2,float y2,float z2,float r, int id){
     
     glLineWidth(5);
     glBegin(GL_LINES);
         glVertex3f(x1,y1,z1);
         glVertex3f(x2,y2,z2);
     glEnd();

     float d = distance3d(x1,y1,z1,x2,y2,z2);
     
     float vx = x2-x1;
     float vy = y2-y1;
     float vz = z2-z1;
     //handle the degenerate case of z1 == z2 with an approximation
     if(vz == 0)
          vz = .0001;
    
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
         glTranslatef(x2,y2,z2);
         glutSolidSphere(r,10,10);
     glPopMatrix();
     glPushMatrix();     
         glTranslatef( x1,y1,z1 );
         glutSolidSphere(r,10,10);
         glRotatef(ax, rx, ry, 0.0);
         //glColor4f(0,0,1,alphaswitch);//azul
         gluCylinder(q, r, r, d, 20, 1);
     glPopMatrix();
     
}

void drawGrid(){
    float i,j;
    glBegin(GL_LINES);
//    for(i=-80;i<80;i++){
//        for(j=-80;j<80;j++){
//            glColor3f(1,0,0);
//            glVertex3f(-8,i/10,0);//x
//            glVertex3f(8,i/10,0);
//            glVertex3f(i/10,-8,0);//y
//            glVertex3f(i/10,8,0);
//            glColor3f(0,0,1);
//            glVertex3f(0,i/10,-8);//zx
//            glVertex3f(0,i/10,8);
//            glVertex3f(0,-8,i/10);//zy
//            glVertex3f(0,8,i/10);
//        }
//    }

    for(i=-8;i<8;i++){
        for(j=-8;j<8;j++){
            //glColor3f(1,1,0);
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
            
            //glColor3f(0,1,1);
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

void initNodes(){
    //chest
    glLoadIdentity();
    glTranslatef(0,0.6,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, chestn.m);
    chestn.x1 = -0.5;
    chestn.y1 = 0.6;
    chestn.z1 = 0;
    chestn.x2 = 0.5;
    chestn.y2 = 0.6;
    chestn.z2 = 0;
    chestn.radio = 0.4;
    chestn.id = 0;
    chestn.sibling = NULL;
    chestn.child = &waistn;
    
    //waist
    glLoadIdentity();
    glTranslatef(0.0,-0.8,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, waistn.m);
    waistn.x1 = -0.5;
    waistn.y1 = 0.5;
    waistn.z1 = 0;
    waistn.x2 = 0.5;
    waistn.y2 = 0.5;
    waistn.z2 = 0;
    waistn.radio = 0.35;
    waistn.id = 1;
    waistn.sibling = &rulegn;
    waistn.child = &neckn;
    
    //Neck
    glLoadIdentity();
    glTranslatef(0.0,2.6,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, neckn.m);
    neckn.x1 = 0;
    neckn.y1 = 0;
    neckn.z1 = 0;
    neckn.x2 = 0;
    neckn.y2 = 0.1;
    neckn.z2 = 0;
    neckn.radio = 0.25;
    neckn.id = 2;
    neckn.sibling = &rshouldern;
    neckn.child = &headn;
    
    //HEAD
    glLoadIdentity();
    glTranslatef(0.0,0.5,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, headn.m);
    headn.x1 = 0;
    headn.y1 = 0;
    headn.z1 = 0;
    headn.x2 = 0;
    headn.y2 = 0.4;
    headn.z2 = 0;
    headn.radio = 0.4;
    headn.id = 3;
    headn.sibling = NULL;
    headn.child = NULL;

    //rshoulder
    glLoadIdentity();
    glTranslatef(-0.4,2.2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rshouldern.m);
    rshouldern.x1 = 0;
    rshouldern.y1 = 0;
    rshouldern.z1 = 0;
    rshouldern.x2 = -0.7;
    rshouldern.y2 = -0.3;
    rshouldern.z2 = 0;
    rshouldern.radio = 0.3;
    rshouldern.id = 16;
    rshouldern.sibling = &lshouldern;
    rshouldern.child = &ruarmn;
    
    //RIGHT UPPER ARM
    glLoadIdentity();
    glTranslatef(-0.85,-0.4,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, ruarmn.m);
    ruarmn.x1 = 0;
    ruarmn.y1 = 0;
    ruarmn.z1 = 0;
    ruarmn.x2 = -0.05;
    ruarmn.y2 = -1.4;
    ruarmn.z2 = -0.05;
    ruarmn.radio = 0.2;
    ruarmn.id = 4;
    ruarmn.sibling = NULL;
    ruarmn.child = &rlarmn;
    
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(-0.05,-1.6,-0.05);
    glGetFloatv(GL_MODELVIEW_MATRIX, rlarmn.m);
    rlarmn.x1 = 0;
    rlarmn.y1 = 0;
    rlarmn.z1 = 0;
    rlarmn.x2 = 0.05;
    rlarmn.y2 = -0.9;
    rlarmn.z2 = 0.05;
    rlarmn.radio = 0.15;
    rlarmn.id = 5;
    rlarmn.sibling = NULL;        
    rlarmn.child = &rhandn;
    
    //rhand
    glLoadIdentity();
    glTranslatef(0.05,-1,0.05);
    glGetFloatv(GL_MODELVIEW_MATRIX, rhandn.m);
    rhandn.x1 = 0;
    rhandn.y1 = 0;
    rhandn.z1 = 0;
    rhandn.x2 = 0;
    rhandn.y2 = -0.5;
    rhandn.z2 = 0;
    rhandn.radio = 0.1;
    rhandn.id = 6;
    rhandn.sibling = NULL;        
    rhandn.child = NULL;
    
    //lshoulder
    glLoadIdentity();
    glTranslatef(0.4,2.2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lshouldern.m);
    lshouldern.x1 = 0;
    lshouldern.y1 = 0;
    lshouldern.z1 = 0;
    lshouldern.x2 = 0.7;
    lshouldern.y2 = -0.3;
    lshouldern.z2 = 0;
    lshouldern.radio = 0.3;
    lshouldern.id = 17;
    lshouldern.sibling = NULL;
    lshouldern.child = &luarmn;
    
    //LEFT UPPER ARM
    glLoadIdentity();
    glTranslatef(0.85,-0.4,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, luarmn.m);
    luarmn.x1 = 0;
    luarmn.y1 = 0;
    luarmn.z1 = 0;
    luarmn.x2 = 0.05;
    luarmn.y2 = -1.4;
    luarmn.z2 = -0.05;
    luarmn.radio = 0.2;
    luarmn.id = 7;
    luarmn.sibling = NULL;        
    luarmn.child = &llarmn;                       
    
    //LEFT LOWER ARM
    glLoadIdentity();
    glTranslatef(0.05,-1.6,-0.05);
    glGetFloatv(GL_MODELVIEW_MATRIX, llarmn.m);
    llarmn.x1 = 0;
    llarmn.y1 = 0;
    llarmn.z1 = 0;
    llarmn.x2 = -0.05;
    llarmn.y2 = -0.9;
    llarmn.z2 = 0.05;
    llarmn.radio = 0.15;
    llarmn.id = 8;
    llarmn.sibling = NULL;        
    llarmn.child = &lhandn;    
  
    //lhand
    glLoadIdentity();
    glTranslatef(-0.05,-1,0.05);
    glGetFloatv(GL_MODELVIEW_MATRIX, lhandn.m);
    lhandn.x1 = 0;
    lhandn.y1 = 0;
    lhandn.z1 = 0;
    lhandn.x2 = 0;
    lhandn.y2 = -0.5;
    lhandn.z2 = 0;
    lhandn.radio = 0.1;
    lhandn.id = 9;
    lhandn.sibling = NULL;        
    lhandn.child = NULL; 
    
    //RIGHT UPPER LEG
    glLoadIdentity();
    glTranslatef(-0.5,-1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rulegn.m);
    rulegn.x1 = 0;
    rulegn.y1 = 0;
    rulegn.z1 = 0;
    rulegn.x2 = 0.05;
    rulegn.y2 = -2;
    rulegn.z2 = 0.05;
    rulegn.radio = 0.3;
    rulegn.id = 10;
    rulegn.sibling = &lulegn;       
    rulegn.child = &rllegn; 
    
    //RIGHT LOWER LEG
    glLoadIdentity();
    glTranslatef(0.05,-2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rllegn.m);
    rllegn.x1 = 0;
    rllegn.y1 = 0;
    rllegn.z1 = 0;
    rllegn.x2 = 0;
    rllegn.y2 = -1.7;
    rllegn.z2 = -0.05;
    rllegn.radio = 0.2;
    rllegn.id = 11;
    rllegn.sibling = NULL;
    rllegn.child = &rfootn;
    
    //rfoot
    glLoadIdentity();
    glTranslatef(0,-2,0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rfootn.m);
    rfootn.x1 = 0;
    rfootn.y1 = 0;
    rfootn.z1 = 0;
    rfootn.x2 = 0;
    rfootn.y2 = 0;
    rfootn.z2 = 0.7;
    rfootn.radio = 0.1;
    rfootn.id = 12;
    rfootn.sibling = NULL;
    rfootn.child = NULL;
    
    //LEFT UPPER LEG
    glLoadIdentity();
    glTranslatef(0.5,-1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lulegn.m);
    lulegn.x1 = 0;
    lulegn.y1 = 0;
    lulegn.z1 = 0;
    lulegn.x2 = -0.05;
    lulegn.y2 = -2;
    lulegn.z2 = 0.05;
    lulegn.radio = 0.3;
    lulegn.id = 13;
    lulegn.sibling = NULL;       
    lulegn.child = &lllegn;                      
    
    //LEFT LOWER LEG
    glLoadIdentity();
    glTranslatef(-0.05,-2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lllegn.m);
    lllegn.x1 = 0;
    lllegn.y1 = 0;
    lllegn.z1 = 0;
    lllegn.x2 = 0;
    lllegn.y2 = -1.7;
    lllegn.z2 = -0.05;
    lllegn.radio = 0.2;
    lllegn.id = 14;
    lllegn.sibling = NULL;        
    lllegn.child = &lfootn;
    
    //lfoot
    glLoadIdentity();
    glTranslatef(0,-2,0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lfootn.m);
    lfootn.x1 = 0;
    lfootn.y1 = 0;
    lfootn.z1 = 0;
    lfootn.x2 = 0;
    lfootn.y2 = 0;
    lfootn.z2 = 0.7;
    lfootn.radio = 0.1;
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

void traverse (treenode *node){
    // guardar la matriz actual porque las transformaciones a realizarse 
    // sólo deben afectarle a él y a sus hijos
    glPushMatrix();
    
        // transformar relativo a su padre
        glMultMatrixf(node->m);
    
        // dibujar el nodo
        //node->f();
        
        if(jointswitch){
            drawJoint(node -> id);
        }
        
        if(capsuleswitch){
             drawCapsule(node -> x1, node -> y1, node -> z1, 
                         node -> x2, node -> y2, node -> z2, 
                         node -> radio, node -> id);
        }
        
        // primer recorrer los hijos (si hay)
        if (node->child != NULL)
        	traverse(node->child);
        
    glPopMatrix();
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
     //glColor3d(1,0,0);
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
    if (smoothOn)
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
	
    traverse(&chestn);
    
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
                skinswitch = !skinswitch;
                glutPostRedisplay();
     }
     if(c=='d'){
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
     
     glutPostRedisplay();

}

void resetAngles(){
     for(int i=0;i<15;i++){
         anglesx[i] = 0.0;
         anglesy[i] = 0.0;
     }
}

void special(int c, int x, int y){
     if(c==GLUT_KEY_UP){
         anglesx[segselect] = -angdelta;
     }
     if(c==GLUT_KEY_DOWN){
         anglesx[segselect] = angdelta;
     }
     if(c==GLUT_KEY_RIGHT){
         anglesy[segselect] = angdelta;
     }
     if(c==GLUT_KEY_LEFT){
         anglesy[segselect] = -angdelta;
     }
     
     glPushMatrix();
     glLoadIdentity();
     
     switch(segselect){
         case 0:
              glMultMatrixf(chestn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,1.0,0.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, chestn.m);
              break;
         case 1:
              glMultMatrixf(waistn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,1.0,0.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, waistn.m);
              break;
         case 2:
              glMultMatrixf(neckn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,-1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, neckn.m);
              break;
         case 3:
              glMultMatrixf(headn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,1.0,0.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, headn.m);
              break;
         case 4:
              glMultMatrixf(ruarmn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, ruarmn.m);
              break;
         case 5:
              glMultMatrixf(rlarmn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rlarmn.m);
              break;
         case 6:
              glMultMatrixf(rhandn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rhandn.m);
              break;
         case 7:
              glMultMatrixf(luarmn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, luarmn.m);
              break;
         case 8:
              glMultMatrixf(llarmn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, llarmn.m);
              break;
         case 9:
              glMultMatrixf(lhandn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, lhandn.m);
              break;
         case 10:
              glMultMatrixf(rulegn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rulegn.m);
              break;
         case 11:
              glMultMatrixf(rllegn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rllegn.m);
              break;
         case 12:
              glMultMatrixf(rfootn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,1.0,0.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rfootn.m);
              break;
         case 13:
              glMultMatrixf(lulegn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, lulegn.m);
              break;
         case 14:
              glMultMatrixf(lllegn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, lllegn.m);
              break;
         case 15:
              glMultMatrixf(lfootn.m);
              glRotatef(anglesx[segselect],1.0,0.0,0.0);
              glRotatef(anglesy[segselect],0.0,1.0,0.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, lfootn.m);
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
  initNodes();
  
  glutMainLoop();                               // Pasar el control a GLUT.
  return 0;                                     // Regresar 0 por cortesía.
}
