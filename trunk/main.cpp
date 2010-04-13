/*****************************************
 *Equipo
 *
 *Monito Final
*******************************************/

#include "mesh.h"
#include <GL/glut.h>
#include <stdlib.h>


GLfloat angulos[10]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
int segmento=0;

//bools
bool skinswitch = true;

bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 12.0;

mesh *object;

typedef struct capsule{
    float x1, y1, z1, x2, y2, z2;
    float radio;
} capsule;

capsule headc, neckc, rshoulderc, lshoulderc, ruarmc, luarmc, rlarmc, llarmc, rhandc, lhandc,
chestc, waistc, rulegc, lulegc, rllegc, lllegc, rfootc, lfootc;

typedef struct treenode{
    GLfloat m[16];
    void (*f)();
    struct treenode *sibling;
    struct treenode *child;
    
} treenode;

treenode headn, neckn, rshouldern, lshouldern, ruarmn, luarmn, rlarmn, llarmn, rhandn, lhandn,
chestn, waistn, rulegn, lulegn, rllegn, lllegn, rfootn, lfootn;

void headf(){
     glPushMatrix();
         glTranslatef(0.0f, 0.5f, 0.0f);
         glScalef(0.5,0.5,0.5);
         //glutSolidCube(1);
         glutSolidSphere(0.5,5,5);
		 //gluCylinder(q, 10, 10, 10, 10, 10);
     glPopMatrix();    
}

void neckf(){
     glPushMatrix();
         //glScalef(1.0,1.5,1.0);
         //glutSolidCube(1);
         glutSolidSphere(0.5,5,5);
     glPopMatrix();   
}

void torsof(){
     glPushMatrix();
         //glScalef(1.0,1.5,1.0);
         //glutSolidCube(1);
         glutSolidSphere(0.5,5,5);
     glPopMatrix();   
}

void upper(){
      glPushMatrix();
         //glTranslatef(0.0f, -0.5f, 0.0f);
         //glScalef(0.3,1.0,0.3);
         //glutSolidCube(1);
         glutSolidSphere(0.5,5,5); 
     glPopMatrix();       
}

void lower(){
      glPushMatrix();
         //glTranslatef(0.0f, -0.35f, 0.0f);
         //glScalef(0.3,0.7,0.3);
         //glutSolidCube(1);
         glutSolidSphere(0.5,5,5);
     glPopMatrix();       
}

void initMesh(){
     object = new mesh("cuerpob.obj");
     
     char mensaje[64];
     sprintf(mensaje, "Total de caras %d", object->fTotal);
     glutSetWindowTitle(mensaje);
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

void initCapsules(){
     ///headc
     headc.x1 = 0;
     headc.y1 = 3.3;
     headc.z1 = 0;
     headc.x2 = 0;
     headc.y2 = 2.8;
     headc.z2 = 0;
     headc.radio = 0.3;
     ///neckc
     neckc.x1 = 0;
     neckc.y1 = 2.6;
     neckc.z1 = 0;
     neckc.x2 = 0;
     neckc.y2 = 2.4;
     neckc.z2 = 0;
     neckc.radio = 0.2;
     ///rshoulderc
     rshoulderc.x1 = -0.2;
     rshoulderc.y1 = 2.2;
     rshoulderc.z1 = 0;
     rshoulderc.x2 = -1.2;
     rshoulderc.y2 = 1.8;
     rshoulderc.z2 = 0;
     rshoulderc.radio = 0.4;
     ///lshoulderc
     lshoulderc.x1 = 0.2;
     lshoulderc.y1 = 2.2;
     lshoulderc.z1 = 0;
     lshoulderc.x2 = 1.2;
     lshoulderc.y2 = 1.8;
     lshoulderc.z2 = 0;
     lshoulderc.radio = 0.4;
     ///ruarmc
     ruarmc.x1 = -1.25;
     ruarmc.y1 = 1.5;
     ruarmc.z1 = 0;
     ruarmc.x2 = -1.3;
     ruarmc.y2 = 0.5;
     ruarmc.z2 = 0;
     ruarmc.radio = 0.4;
     ///luarmc
     luarmc.x1 = 1.25;
     luarmc.y1 = 1.5;
     luarmc.z1 = 0;
     luarmc.x2 = 1.3;
     luarmc.y2 = 0.5;
     luarmc.z2 = 0;
     luarmc.radio = 0.4;
     ///rlarmc
     rlarmc.x1 = -1.3;
     rlarmc.y1 = 0.1;
     rlarmc.z1 = 0;
     rlarmc.x2 = -1.3;
     rlarmc.y2 = -0.9;
     rlarmc.z2 = 0;
     rlarmc.radio = 0.3;
     ///llarmc
     llarmc.x1 = 1.3;
     llarmc.y1 = 0.1;
     llarmc.z1 = 0;
     llarmc.x2 = -1.3;
     llarmc.y2 = -0.9;
     llarmc.z2 = 0;
     llarmc.radio = 0.3;
     ///rhandc
     rhandc.x1 = -1.25;
     rhandc.y1 = -1.1;
     rhandc.z1 = 0;
     rhandc.x2 = -1.25;
     rhandc.y2 = -1.5;
     rhandc.z2 = 0;
     rhandc.radio = 0.2;
     ///lhandc
     lhandc.x1 = 1.25;
     lhandc.y1 = -1.1;
     lhandc.z1 = 0;
     lhandc.x2 = 1.25;
     lhandc.y2 = -1.5;
     lhandc.z2 = 0;
     lhandc.radio = 0.2;
     ///chestc
     chestc.x1 = -0.6;
     chestc.y1 = 1.1;
     chestc.z1 = 0;
     chestc.x2 = 0.6;
     chestc.y2 = 1.1;
     chestc.z2 = 0;
     chestc.radio = 0.7;
     ///waistc
     waistc.x1 = -0.5;
     waistc.y1 = -0.1;
     waistc.z1 = 0;
     waistc.x2 = 0.5;
     waistc.y2 = -0.1;
     waistc.z2 = 0;
     waistc.radio = 0.6;
     ///rulegc
     rulegc.x1 = -0.5;
     rulegc.y1 = -0.8;
     rulegc.z1 = 0;
     rulegc.x2 = -0.5;
     rulegc.y2 = -2.2;
     rulegc.z2 = 0.1;
     rulegc.radio = 0.4;
     ///lulegc
     lulegc.x1 = 0.5;
     lulegc.y1 = -0.8;
     lulegc.z1 = 0;
     lulegc.x2 = -0.5;
     lulegc.y2 = -2.2;
     lulegc.z2 = 0.1;
     lulegc.radio = 0.4;
     ///rllegc
     rllegc.x1 = -0.4;
     rllegc.y1 = -2.5;
     rllegc.z1 = 0.1;
     rllegc.x2 = -0.4;
     rllegc.y2 = -4;
     rllegc.z2 = 0;
     rllegc.radio = 0.3;
     ///lllegc
     lllegc.x1 = 0.4;
     lllegc.y1 = -2.5;
     lllegc.z1 = 0.1;
     lllegc.x2 = 0.4;
     lllegc.y2 = -4;
     lllegc.z2 = 0;
     lllegc.radio = 0.3;
     ///rfootc
     rfootc.x1 = -0.4;
     rfootc.y1 = -4.4;
     rfootc.z1 = 0;
     rfootc.x2 = -0.4;
     rfootc.y2 = -4.4;
     rfootc.z2 = 0.6;
     rfootc.radio = 0.15;
     ///lfootc
     lfootc.x1 = 0.4;
     lfootc.y1 = -4.4;
     lfootc.z1 = 0;
     lfootc.x2 = 0.4;
     lfootc.y2 = -4.4;
     lfootc.z2 = 0.6;
     lfootc.radio = 0.15;

}

void initNodes(){
    //waist
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(0.0,0.0,0.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, waistn.m);
    glPopMatrix();
    waistn.f = torsof;
    waistn.sibling = NULL;
    waistn.child = &chestn;
    
    //chest
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(0,1.6,0.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, chestn.m);
    glPopMatrix();
    chestn.f = torsof;
    chestn.sibling = &rulegn;
    chestn.child = &neckn;
    
    //Neck
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(0.0,2.5,0.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, neckn.m);
    glPopMatrix();
    neckn.f = neckf;
    neckn.sibling = &rshouldern;
    neckn.child = &headn;
    
    //HEAD
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(0.0,3,0.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, headn.m);
    glPopMatrix();
    headn.f = headf;
    headn.sibling = NULL;
    headn.child = NULL;

    //rshoulder
    glLoadIdentity();
    glTranslatef(-0.8,2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rshouldern.m);
    rshouldern.f = upper;
    rshouldern.sibling = &lshouldern;
    rshouldern.child = &ruarmn;
    
    //RIGHT UPPER ARM
    glLoadIdentity();
    glTranslatef(-1.2,1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, ruarmn.m); 
    ruarmn.f = upper;
    ruarmn.sibling = NULL;
    ruarmn.child = &rlarmn;
    
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(-1.1,-0.3,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rlarmn.m); 
    rlarmn.f = lower;                           
    rlarmn.sibling = NULL;        
    rlarmn.child = &rhandn;
    
    //rhand
    glLoadIdentity();
    glTranslatef(-1.2,-1.2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rhandn.m); 
    rhandn.f = lower;                           
    rhandn.sibling = NULL;        
    rhandn.child = NULL;
    
    //lshoulder
    glLoadIdentity();
    glTranslatef(0.8,2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lshouldern.m);
    lshouldern.f = upper;
    lshouldern.sibling = NULL;
    lshouldern.child = &luarmn;
    
    //LEFT UPPER ARM
    glLoadIdentity();
    glTranslatef(1.2,1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, luarmn.m); 
    luarmn.f = upper;                           
    luarmn.sibling = NULL;        
    luarmn.child = &llarmn;                       
    
    //LEFT LOWER ARM
    glLoadIdentity();
    glTranslatef(1.1,-0.3,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, llarmn.m); 
    llarmn.f = lower;                           
    llarmn.sibling = NULL;        
    llarmn.child = &lhandn;    
  
    //lhand
    glLoadIdentity();
    glTranslatef(1.2,-1.2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lhandn.m); 
    lhandn.f = lower;                           
    lhandn.sibling = NULL;        
    lhandn.child = NULL; 
    
    //RIGHT UPPER LEG
    glLoadIdentity();
    glTranslatef(-0.4,-1.3,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rulegn.m); 
    rulegn.f = upper;                           
    rulegn.sibling = &lulegn;       
    rulegn.child = &rllegn; 
    
    //RIGHT LOWER LEG
    glLoadIdentity();
    glTranslatef(-0.3,-3.2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rllegn.m); 
    rllegn.f = lower;                           
    rllegn.sibling = NULL;
    rllegn.child = &rfootn;
    
    //rfoot
    glLoadIdentity();
    glTranslatef(-0.3,-4.3,0.3);
    glGetFloatv(GL_MODELVIEW_MATRIX, rfootn.m); 
    rfootn.f = lower;                           
    rfootn.sibling = NULL;
    rfootn.child = NULL;
    
    //LEFT UPPER LEG
    glLoadIdentity();
    glTranslatef(0.4,-1.3,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lulegn.m); 
    lulegn.f = upper;                           
    lulegn.sibling = NULL;       
    lulegn.child = &lllegn;                      
    
    //LEFT LOWER LEG
    glLoadIdentity();
    glTranslatef(0.3,-3.2,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, lllegn.m); 
    lllegn.f = lower;                           
    lllegn.sibling = NULL;        
    lllegn.child = &lfootn;
    
    //lfoot
    glLoadIdentity();
    glTranslatef(0.3,-4.3,0.3);
    glGetFloatv(GL_MODELVIEW_MATRIX, lfootn.m); 
    lfootn.f = lower;                           
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
        node->f();
        
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


void dibujarVertices(){
     glColor3d(1,0,0);
     glPointSize(10);
     
     glBegin(GL_POINTS);
     for(int i=0; i<object->vTotal; i++)
             glVertex3fv(object->vList[i].ptr);
     glEnd();
}

void dibujarCaras(){
     glColor4f(1, 0.7, 0.8, 0.5);
     
     glBegin(GL_TRIANGLES);
     for(int i = 0; i<object->fTotal; i++){
             for(int j=0; j<3; j++){
//                     glVertex3fv(object->vList[i][object->faceList[i][j].v].ptr);
                       glVertex3fv(object->vList[object->faceList[i][j].v].ptr);
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
    
	drawGrid();
	
    traverse(&waistn);
    
    if(skinswitch)
        dibujarCaras();
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0.3,-4.3,0.3);
    glEnd();
//    dibujarVertices();

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
  //glutKeyboardFunc(key);
  init();
  initMesh();                                       // Inicialización general
  initNodes();
  initCapsules();
  glutMainLoop();                               // Pasar el control a GLUT.
  return 0;                                     // Regresar 0 por cortesía.
}
