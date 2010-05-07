#ifndef FUNCDEC_H
#define FUNCDEC_H

#include "structs.h"
#include "objLoader.h"


//------------------FUNCIONES----------------------------
//distancia 3d entre 2 puntos
float vDistance(Vec3 *v1, Vec3 *v2);
//distancia 3d entre 2 puntos
float distance3d(float x1,float y1,float z1,float x2,float y2,float z2);
//distancea 2d entre 2 puntos
float distance2d(float x1,float y1,float x2,float y2);

//detecta colision entre un punto y una capsula, 
//calcula la normal y regresa que tan adentro esta el punto h, 0 si esta fuera
float colDetect(capsule *cap, Vec3 *h, float hr);
//Mueve la piel en x respecto a un bv
void moveskinx(bodyvertex *bv, float x);
void moveskiny(bodyvertex *bv, float y);
void moveskinz(bodyvertex *bv, float z);
//Rota la piel en x respecto a un bv
void rotskinx(bodyvertex *bv, Vec3 *pt, float nangx);
void rotskiny(bodyvertex *bv, Vec3 *pt, float nangy);
void rotskinz(bodyvertex *bv, Vec3 *pt, float nangz);
//Rota un vertice respecto a un punto
void rotBVx(bodyvertex *bv, Vec3 *pt, float angx);
void rotBVy(bodyvertex *bv, Vec3 *pt, float angy);
void rotBVz(bodyvertex *bv, Vec3 *pt, float angz);
//Rota capsulas respecto al punto *pt
void rotCapx(capsule *c, Vec3 *pt, float angx);
void rotCapy(capsule *c, Vec3 *pt, float angy);
void rotCapz(capsule *c, Vec3 *pt, float angz);
//Rota nodos hijos respecto al punto *pt... jajaja pete
void rotChildNodex(treenode *n, Vec3 *pt, float angx);
void rotChildNodey(treenode *n, Vec3 *pt, float angy);
void rotChildNodez(treenode *n, Vec3 *pt, float angz);
//Recibe un nodo, usa el metodo de arriba para 
//girar hijos respecto al primer vertice de un nodo
void rotNodex(treenode *n, float angx);
void rotNodey(treenode *n, float angy);
void rotNodez(treenode *n, float angz);

////////////DRAW
void setMaterials(GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess);
//dibuja los joints donde se dobla el mono
void drawJoint(Vec3 *v, int id);
//dibuja un unicornio
void drawCapsule(capsule *cap);
void drawCaps();
void drawBV();
//Dibuja todos los vertices de un mesh de obj (skindata)
void drawVert(objLoader *object, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess);
//Dibuja un mesh de obj (skindata, shirtdata o pantsdata)
void drawObject(objLoader *object, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess);
void drawParticles(particle *arr, int total, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess);
void drawSprings(spring *arr, int total, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat shininess);
void drawskeleton(treenode *n);
void traverse(treenode *node);
void display();

//invierte un Switch
void toggleSwitch(bool *ts);
//Invierte todos los switches de vertices
void toggleAllVert();
//Invierte todos los switches de alpha
void toggleAllAlpha();
//Resetea buffer de angulos (cuando picas flechas)
void resetAngles();
//Hace movibles los vertices del cuerpo
void resetVertFlags();
//saca un punto de una capsula
float disttocap(capsule *cap, Vec3 *h, float hr, Vec3 *N);
//saca un punto de una capsula
bool handleCollision(capsule *cap, particle *p, float hr);
void parrcollide(particle *parr, float pradius, int total);

///////IDLE
void idle();

void movebodyx(float x);
void movebodyy(float y);
void movebodyz(float z);
void reset();
void applyrotations();
///////MOUSE / KEYBOARD
void key(unsigned char c, int x, int y);
void special(int c, int x, int y);

////////////////////////////////////////////////INITS
void processMenu(int val);
int initMenus();
void init();

///////////////////////DEBUG
void drawplanex();
void drawplaney();
void drawplanez();

//si picas G se dibuja
void drawGrid();

#endif
