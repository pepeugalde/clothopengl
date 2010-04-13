#include <stdio.h>
#include <mesh.h>
#include <GL/glut.h>

//#include <stdlib.h> //si usan dev hay que descomentar esta linea
//#include <iostream.h> 

bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 5.0;

mesh *object;


GLfloat angulos[10]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
int segmento=0;
GLUquadric* q = gluNewQuadric();

typedef struct treenode
{
    GLfloat m[16];
    void (*f)();
    struct treenode *sibling;
    struct treenode *child;
    
} treenode;

treenode torso_node, head_node, leftUpperArm_node, leftLowerArm_node, rightUpperArm_node, rightLowerArm_node, leftUpperLeg_node, leftLowerLeg_node, rightUpperLeg_node, rightLowerLeg_node;


void torso(){
     glPushMatrix();
         glScalef(1.0,1.5,1.0);
         glutSolidCube(1);
     glPopMatrix();   
}

void head(){
     glPushMatrix();
         glTranslatef(0.0f, 0.5f, 0.0f);
         glScalef(0.5,0.5,0.5);
         glutSolidCube(1);
		 gluCylinder(q, 10, 10, 10, 10, 10);
     glPopMatrix();    
}


void upper(){
      glPushMatrix();
         glTranslatef(0.0f, -0.5f, 0.0f);
         glScalef(0.3,1.0,0.3);
         glutSolidCube(1);  
     glPopMatrix();       
}

void lower(){
      glPushMatrix();
         glTranslatef(0.0f, -0.35f, 0.0f);
         glScalef(0.3,0.7,0.3);
         glutSolidCube(1);  
     glPopMatrix();       
}

void initMesh(){
     object = new mesh("capsulas.obj");
     
     char mensaje[64];
     sprintf(mensaje, "Total de caras %d", object->fTotal);
     glutSetWindowTitle(mensaje);
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
     glColor3d(1,1,1);
     
     glBegin(GL_TRIANGLES);
     for(int i = 0; i<object->fTotal; i++){
             for(int j=0; j<3; j++){
//                     glVertex3fv(object->vList[i][object->faceList[i][j].v].ptr);
                       glVertex3fv(object->vList[object->faceList[i][j].v].ptr);
             }
     }
     glEnd();            
}

void init(){
     
	glColor3f(1.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
    printf("hola\n");

    //TORSO
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m); // guardar la matriz actual en m
    torso_node.f = torso;                           // torso() – función que dibuja
    torso_node.sibling = NULL;                      // no hay hermanos
    torso_node.child = &head_node;                  // primer hijo
    
    //HEAD
    glLoadIdentity();
    glTranslatef(0.0,0.7,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m); 
    head_node.f = head;                           
    head_node.sibling = &leftUpperArm_node;        
    head_node.child = NULL;                       

    //LEFT UPPER ARM
    glLoadIdentity();
    glTranslatef(-0.8,0.7,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, leftUpperArm_node.m); 
    leftUpperArm_node.f = upper;                           
    leftUpperArm_node.sibling = &rightUpperArm_node;        
    leftUpperArm_node.child = &leftLowerArm_node;                       
   
    //LEFT LOWER ARM
    glLoadIdentity();
    glTranslatef(0.0,-1.1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, leftLowerArm_node.m); 
    leftLowerArm_node.f = lower;                           
    leftLowerArm_node.sibling = NULL;        
    leftLowerArm_node.child = NULL;    
  
    //RIGHT UPPER ARM
    glLoadIdentity();
    glTranslatef(0.8,0.7,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rightUpperArm_node.m); 
    rightUpperArm_node.f = upper;                           
    rightUpperArm_node.sibling = &leftUpperLeg_node;        
    rightUpperArm_node.child = &rightLowerArm_node;                       
   
    //RIGHT LOWER ARM
    glLoadIdentity();
    glTranslatef(0.0,-1.1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rightLowerArm_node.m); 
    rightLowerArm_node.f = lower;                           
    rightLowerArm_node.sibling = NULL;        
    rightLowerArm_node.child = NULL;   
    
    //LEFT UPPER LEG
    glLoadIdentity();
    glTranslatef(-0.2,-0.9,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, leftUpperLeg_node.m); 
    leftUpperLeg_node.f = upper;                           
    leftUpperLeg_node.sibling = &rightUpperLeg_node;       
    leftUpperLeg_node.child = &leftLowerLeg_node;                      
   
    //LEFT LOWER LEG
    glLoadIdentity();
    glTranslatef(0.0,-1.1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, leftLowerLeg_node.m); 
    leftLowerLeg_node.f = lower;                           
    leftLowerLeg_node.sibling = NULL;        
    leftLowerLeg_node.child = NULL;    
  
    //RIGHT UPPER LEG
    glLoadIdentity();
    glTranslatef(0.2,-0.9,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rightUpperLeg_node.m); 
    rightUpperLeg_node.f = upper;                           
    rightUpperLeg_node.sibling = NULL;       
    rightUpperLeg_node.child = &rightLowerLeg_node;                      
   
    //RIGHT LOWER LEG
    glLoadIdentity();
    glTranslatef(0.0,-1.1,0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, rightLowerLeg_node.m); 
    rightLowerLeg_node.f = lower;                           
    rightLowerLeg_node.sibling = NULL;        
    rightLowerLeg_node.child = NULL;    
  

  
}

// recorrido a profundidad: primero los hijos, luego los hermanos
void traverse (treenode *node)
{
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

void display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f) ;             // fondo blanco
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);  // borrar el buffer de color y de profundidad.
	
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;

	gluLookAt(
    0.0f, 5.0f, zoom,
    0.0f, 5.0f, 0.0f,
    0.0f, 1.0f, 0.0f);
    
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0) ;            // para ver de lado el cubo y desde un poco más arriba
	 
	traverse(&torso_node);
	dibujarCaras();
	
	glutSwapBuffers();                                // intercambiar el buffer de dibujado por el buffer de despliegue.
}

void reshape(int w, int h)
{
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
/*
void mouse(int btn, int state, int x, int y){
   if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
        angulos[segmento]=5.0;
   }   
   if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        angulos[segmento]=-5.0;                    
   }    
   
   glPushMatrix();
   glLoadIdentity();
   
       switch(segmento){      
          case 0:
              glMultMatrixf(torso_node.m);
              glRotatef(angulos[segmento],0.0,1.0,0.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
              break;
          case 1:
              glMultMatrixf(leftUpperArm_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, leftUpperArm_node.m);
              break;
          case 2:
              glMultMatrixf(leftLowerArm_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, leftLowerArm_node.m);
              break;
          case 3:
              glMultMatrixf(rightUpperArm_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rightUpperArm_node.m);
              break;
          case 4:
              glMultMatrixf(rightLowerArm_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rightLowerArm_node.m);
              break;
          case 5:
              glMultMatrixf(leftUpperLeg_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, leftUpperLeg_node.m);
              break;
          case 6:
              glMultMatrixf(leftLowerLeg_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, leftLowerLeg_node.m);
              break;
          case 7:
              glMultMatrixf(rightUpperLeg_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rightUpperLeg_node.m);
              break;
          case 8:
              glMultMatrixf(rightLowerLeg_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, rightLowerLeg_node.m);
              break;
          case 9:
              glMultMatrixf(head_node.m);
              glRotatef(angulos[segmento],0.0,0.0,1.0);
              glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
              break;
              
       }
       
   glPopMatrix();
   glutPostRedisplay(); 
}*/



void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = x - xdiff;
        xrot = y + ydiff;
        
        glutPostRedisplay();
    }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Monito Final");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutSpecialFunc(specialKey);
    init();
    initMesh();
    glutMainLoop();
    return 0;
}


