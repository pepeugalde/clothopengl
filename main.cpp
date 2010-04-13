/*****************************************
 *Equipo
 *
 *Monito Final
*******************************************/

#include <mesh.h>
#include <GL/glut.h>
#include <stdlib.h>


GLfloat angulos[10]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
int segmento=0;

bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom = 5.0;

mesh *object;

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
		 //gluCylinder(q, 10, 10, 10, 10, 10);
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

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
    gluLookAt(
    0.0f, 5.0f, zoom,
    0.0f, 5.0f, 0.0f,
    0.0f, 1.0f, 0.0f);
    
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	
    dibujarCaras();
    traverse(&torso_node);
//    dibujarVertices();

   	glutSwapBuffers();
}



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
}

void key(unsigned char c, int x, int y){
     if(c=='q')
               exit(0);
     if(c=='+'){
                zoom=zoom+1;
                glutPostRedisplay();
     }
     if(c=='-'){
                zoom=zoom-1;
                glutPostRedisplay();
     }
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

int main(int argc, char **argv)
{
  int mode = GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH;   // Modo de despliegue: Colores RGB, Doble buffer para despliegue
  glutInitDisplayMode(mode);                    // Inicializar modo de despliegue.
  glutInitWindowSize(500,500);                  // Inicializar tamaño de la ventana
  glutInit(&argc, argv);                        // Inicializar GLUT
  glutCreateWindow("Skin");                   // Crear una ventana con el título indicado.
  glutDisplayFunc(display);                     // Indicar la función para desplegar.
  glutReshapeFunc(reshape);                     // Indicar la función en caso de cambio de tamaño de la ventana
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(key);
  //glutSpecialFunc(special);
  //glutKeyboardFunc(key);
  init();
  initMesh();                                       // Inicialización general
  glutMainLoop();                               // Pasar el control a GLUT.
  return 0;                                     // Regresar 0 por cortesía.
}
