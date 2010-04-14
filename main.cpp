/*****************************************
 *Equipo
 *
 *Monito Final
*******************************************/

#include "mesh.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


GLfloat angulos[10]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
int segmento=0;
float jointsize = 0.3;
GLUquadric* q = gluNewQuadric();
//bools
bool capsuleswitch = true;
bool skinswitch = true;
bool gridswitch = false;
bool shirtswitch = true;
bool vertswitch = false;
bool jointswitch = true;
float alphaswitch = 0.7;

bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 12.0;

mesh *skinobject;
mesh *shirtobject;

typedef struct capsule{
    float x1, y1, z1, x2, y2, z2;
    float radio;
} capsule;

capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc,
chestc, waistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

typedef struct treenode{
    float x1, y1, z1, x2, y2, z2;
    float radio;
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

void drawCapsule(float x1,float y1,float z1,float x2,float y2,float z2,float r){
     
     glColor3f(0.3,0.3,0.3);
     glLineWidth(5);
     glBegin(GL_LINES);
         glVertex3f(x1,y1,z1);
         glVertex3f(x2,y2,z2);
     glEnd();
     
     if(jointswitch){
         glColor4f(1,1,0,1);
         glutSolidSphere(jointsize,10,10);
     }

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
     
     glColor4f(0,0,1,alphaswitch);//rojo
     //glColor4f(1,0,0,alphaswitch);//rojo
     glPushMatrix();
         glTranslatef(x2,y2,z2);
         glutSolidSphere(r,10,10);
     glPopMatrix();
     glPushMatrix();     
         glTranslatef( x1,y1,z1 );
         glutSolidSphere(r,10,10);
         glRotatef(ax, rx, ry, 0.0);
         //glColor4f(0,0,1,alphaswitch);//azul
         gluCylinder(q, r, r, d, 20, 10);
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
            glColor3f(1,1,0);
            glVertex3f(-8,i,0.01);//x
            glVertex3f(8,i,0.01);
            glVertex3f(i,-8,0.01);//y
            glVertex3f(i,8,0.01);
            glColor3f(0,1,1);
            glVertex3f(0.01,i,-8);//zx
            glVertex3f(0.01,i,8);
            glVertex3f(0.01,-8,i);//zy
            glVertex3f(0.01,8,i);
        }
    }
    glEnd();
}

void initNodes(){
    //waist
    glLoadIdentity();
    glTranslatef(0.0,0.0,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, waistn.m);
    waistn.x1 = -0.5;
    waistn.y1 = 0;
    waistn.z1 = 0;
    waistn.x2 = 0.5;
    waistn.y2 = 0;
    waistn.z2 = 0;
    waistn.radio = 0.35;
    waistn.sibling = NULL;
    waistn.child = &chestn;
    
    //chest
    glLoadIdentity();
    glTranslatef(0,1.6,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, chestn.m);
    chestn.x1 = -0.5;
    chestn.y1 = -0.5;
    chestn.z1 = 0;
    chestn.x2 = 0.5;
    chestn.y2 = -0.5;
    chestn.z2 = 0;
    chestn.radio = 0.4;
    chestn.sibling = &rulegn;
    chestn.child = &neckn;
    
    //Neck
    glLoadIdentity();
    glTranslatef(0.0,0.8,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, neckn.m);
    neckn.x1 = 0;
    neckn.y1 = 0;
    neckn.z1 = 0;
    neckn.x2 = 0;
    neckn.y2 = 0.1;
    neckn.z2 = 0;
    neckn.radio = 0.25;
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
    headn.sibling = NULL;
    headn.child = NULL;

    //rshoulder
    glLoadIdentity();
    glTranslatef(-0.4,0.45,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rshouldern.m);
    rshouldern.x1 = 0;
    rshouldern.y1 = 0;
    rshouldern.z1 = 0;
    rshouldern.x2 = -0.7;
    rshouldern.y2 = -0.3;
    rshouldern.z2 = 0;
    rshouldern.radio = 0.3;
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
    ruarmn.sibling = NULL;
    ruarmn.child = &rlarmn;
    
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(-0.05,-1.6,-0.1);
    glGetFloatv(GL_MODELVIEW_MATRIX, rlarmn.m);
    rlarmn.x1 = 0;
    rlarmn.y1 = 0;
    rlarmn.z1 = 0;
    rlarmn.x2 = 0.05;
    rlarmn.y2 = -0.9;
    rlarmn.z2 = 0.1;
    rlarmn.radio = 0.15;                      
    rlarmn.sibling = NULL;        
    rlarmn.child = &rhandn;
    
    //rhand
    glLoadIdentity();
    glTranslatef(0.05,-1,0.1);
    glGetFloatv(GL_MODELVIEW_MATRIX, rhandn.m);
    rhandn.x1 = 0;
    rhandn.y1 = 0;
    rhandn.z1 = 0;
    rhandn.x2 = 0.05;
    rhandn.y2 = -0.5;
    rhandn.z2 = 0;
    rhandn.radio = 0.1;                     
    rhandn.sibling = NULL;        
    rhandn.child = NULL;
    
    //lshoulder
    glLoadIdentity();
    glTranslatef(0.4,0.45,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lshouldern.m);
    lshouldern.x1 = 0;
    lshouldern.y1 = 0;
    lshouldern.z1 = 0;
    lshouldern.x2 = 0.7;
    lshouldern.y2 = -0.3;
    lshouldern.z2 = 0;
    lshouldern.radio = 0.3;
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
    luarmn.sibling = NULL;        
    luarmn.child = &llarmn;                       
    
    

    
    //LEFT LOWER ARM
    glLoadIdentity();
    glTranslatef(0.05,-1.6,-0.1);
    glGetFloatv(GL_MODELVIEW_MATRIX, llarmn.m);
    llarmn.x1 = 0;
    llarmn.y1 = 0;
    llarmn.z1 = 0;
    llarmn.x2 = -0.05;
    llarmn.y2 = -0.9;
    llarmn.z2 = 0.1;
    llarmn.radio = 0.15;                
    llarmn.sibling = NULL;        
    llarmn.child = &lhandn;    
  
    //lhand
    glLoadIdentity();
    glTranslatef(-0.05,-1,0.1);
    glGetFloatv(GL_MODELVIEW_MATRIX, lhandn.m);
    lhandn.x1 = 0;
    lhandn.y1 = 0;
    lhandn.z1 = 0;
    lhandn.x2 = -0.05;
    lhandn.y2 = -0.5;
    lhandn.z2 = 0;
    lhandn.radio = 0.1;
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
    rulegn.y2 = -1.4;
    rulegn.z2 = 0.05;
    rulegn.radio = 0.3;
    rulegn.sibling = &lulegn;       
    rulegn.child = &rllegn; 
    
    //RIGHT LOWER LEG
    glLoadIdentity();
    glTranslatef(0.05,-1.6,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rllegn.m);
    rllegn.x1 = 0;
    rllegn.y1 = 0;
    rllegn.z1 = 0;
    rllegn.x2 = 0;
    rllegn.y2 = -1.5;
    rllegn.z2 = -0.05;
    rllegn.radio = 0.2;
    rllegn.sibling = NULL;
    rllegn.child = &rfootn;
    
    //rfoot
    glLoadIdentity();
    glTranslatef(-0.1,-1.75,0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rfootn.m);
    rfootn.x1 = 0;
    rfootn.y1 = 0;
    rfootn.z1 = 0;
    rfootn.x2 = 0;
    rfootn.y2 = 0;
    rfootn.z2 = 0.6;
    rfootn.radio = 0.1;
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
    lulegn.y2 = -1.4;
    lulegn.z2 = 0.05;
    lulegn.radio = 0.3;
    lulegn.sibling = NULL;       
    lulegn.child = &lllegn;                      
    
    //LEFT LOWER LEG
    glLoadIdentity();
    glTranslatef(-0.05,-1.6,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lllegn.m);
    lllegn.x1 = 0;
    lllegn.y1 = 0;
    lllegn.z1 = 0;
    lllegn.x2 = 0;
    lllegn.y2 = -1.5;
    lllegn.z2 = -0.05;
    lllegn.radio = 0.2;
    lllegn.sibling = NULL;        
    lllegn.child = &lfootn;
    
    //lfoot
    glLoadIdentity();
    glTranslatef(0.1,-1.75,0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lfootn.m);
    lfootn.x1 = 0;
    lfootn.y1 = 0;
    lfootn.z1 = 0;
    lfootn.x2 = 0;
    lfootn.y2 = 0;
    lfootn.z2 = 0.6;
    lfootn.radio = 0.1;
    lfootn.sibling = NULL;        
    lfootn.child = NULL;
}

void init(){
	glColor3f(1.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void traverse (treenode *node){
    // guardar la matriz actual porque las transformaciones a realizarse 
    // sólo deben afectarle a él y a sus hijos
    glPushMatrix();
    
        // transformar relativo a su padre
        glMultMatrixf(node->m);
    
        // dibujar el nodo
        //node->f();
        if(capsuleswitch){
             glColor3f(1,1,1);
             drawCapsule(node -> x1, node -> y1, node -> z1, 
                    node -> x2, node -> y2, node -> z2, node -> radio);
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

void specialKey(int c, int x, int y){
	if(c == GLUT_KEY_RIGHT) {
		segmento=(segmento+1)%10;
		glutPostRedisplay();
	}
}


//void myReshape // clipping planes a 500


void drawVert(){
     glColor3d(1,0,0);
     glPointSize(10);
     int i;
     glBegin(GL_POINTS);
     for(i=0; i<skinobject->vTotal; i++)
             glVertex3fv(skinobject->vList[i].ptr);
     for(i=0; i<shirtobject->vTotal; i++)
             glVertex3fv(shirtobject->vList[i].ptr);
     glEnd();
}

void drawSkin(){
     glColor4f(1, 0.7, 0.8, alphaswitch);
     
     glBegin(GL_TRIANGLES);
     for(int i = 0; i<skinobject->fTotal; i++){
             for(int j=0; j<3; j++){
                       glVertex3fv(skinobject->vList[skinobject->faceList[i][j].v].ptr);
             }
     }
     glEnd();            
}

void drawShirt(){
     glColor4f(0.5, 0.5, 1, alphaswitch);
     
     glBegin(GL_TRIANGLES);
     for(int i = 0; i<shirtobject->fTotal; i++){
             for(int j=0; j<3; j++){
                       glVertex3fv(shirtobject->vList[shirtobject->faceList[i][j].v].ptr);
             }
     }
     glEnd();            
}

void display(){
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
	
    traverse(&waistn);
    
    if(skinswitch)
        drawSkin();
    if(shirtswitch)
        drawShirt();
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
     if(c=='q')
               exit(0);
     if(c=='+'){
                zoom -= 1;
                glutPostRedisplay();
     }
     if(c=='-'){
                zoom += 1;
                glutPostRedisplay();
     }
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
                if(alphaswitch == 1){
                    alphaswitch = 0.7; 
                }else{
                    alphaswitch = 1;
                }
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
  //glutSpecialFunc(special);
  init();
  initSkin();
  initShirt();
  initNodes();
  glutMainLoop();                               // Pasar el control a GLUT.
  return 0;                                     // Regresar 0 por cortesía.
}
