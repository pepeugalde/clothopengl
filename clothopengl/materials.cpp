#include <GL/glut.h>
//#include "materials.h"

////////MATERIALES
GLfloat alphavalue = 0.5;

GLfloat lightPosition[] = { 10.0, 10.0, 10.0, 1.0 };

// a material that is all zeros
GLfloat zeroMaterial[]	= { 0.0, 0.0, 0.0, 1.0 };
// a red ambient material
GLfloat redAmbient[]	= { 0.83, 0.0, 0.0, 1.0 };

GLfloat blueDiffuse[]	    = { 0.1, 0.5, 0.8, 1.0 };
GLfloat blueDiffuseAlpha[]	= { 0.1, 0.5, 0.8, alphavalue };
GLfloat dblueDiffuse[]	    = { 0.1, 0.3, 0.5, 1.0 };
GLfloat dblueDiffuseAlpha[]	= { 0.1, 0.3, 0.5, alphavalue };
GLfloat greenDiffuse[]	    = { 0.1, 0.8, 0.3, 1.0 };
GLfloat greenDiffuseAlpha[]	= { 0.1, 0.8, 0.3, alphavalue };
GLfloat dgreenDiffuse[]	    = { 0.1, 0.5, 0.2, 1.0 };
GLfloat dgreenDiffuseAlpha[]= { 0.1, 0.5, 0.2, alphavalue };
GLfloat grayDiffuse[]	    = { 0.6, 0.6, 0.6, 1.0 };
GLfloat grayDiffuseAlpha[]	= { 0.6, 0.6, 0.6, alphavalue };
GLfloat blackDiffuse[]	    = { 0.1, 0.1, 0.1, 1.0 };
GLfloat blackDiffuseAlpha[]	= { 0.1, 0.1, 0.1, alphavalue };
GLfloat brownDiffuse[]	    = { 0.4, 0.3, 0.3, 1.0 };
GLfloat brownDiffuseAlpha[]	= { 0.4, 0.3, 0.3, alphavalue };
GLfloat khakhiDiffuse[]	    = { 0.9, 0.7, 0.4, 1.0 };
GLfloat khakhiDiffuseAlpha[]= { 0.9, 0.7, 0.4, alphavalue };
GLfloat yellowDiffuse[]	    = { 1.0, 1.0, 0.0, 1.0 };
GLfloat yellowDiffuseAlpha[]= { 1.0, 1.0, 0.0, alphavalue };
GLfloat redDiffuse[]	    = { 1.0, 0.0, 0.0, 1.0 };
GLfloat redDiffuseAlpha[]	= { 1.0, 0.0, 0.0, alphavalue };
GLfloat purpleDiffuse[]	    = { 0.5, 0.0, 1.0, 1.0 };
GLfloat purpleDiffuseAlpha[]= { 0.5, 0.0, 1.0, alphavalue };
GLfloat whiteDiffuse[]	    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat whiteDiffuseAlpha[]	= { 1.0, 1.0, 1.0, alphavalue };
GLfloat pinkDiffuse[]	    = { 0.9, 0.7, 0.7, 1.0 };
GLfloat pinkDiffuseAlpha[]	= { 0.9, 0.7, 0.7, alphavalue };

// a white specular material
GLfloat whiteSpecular[]	= { 1.0, 1.0, 1.0, 1.0 };

// the degrees of shinnines (size of the specular highlight, bigger number means smaller highlight)
GLfloat noShininess	    =  0.0;
GLfloat highShininess	= 50.0;
