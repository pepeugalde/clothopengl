#ifndef MATERIALS_H
#define MATERIALS_H

////////MATERIALES
extern GLfloat alphavalue;

extern GLfloat lightPosition[];

// a material that is all zeros
extern GLfloat zeroMaterial[];
// a red ambient material
extern GLfloat redAmbient[];

extern GLfloat blueDiffuse[];
extern GLfloat blueDiffuseAlpha[];
extern GLfloat dblueDiffuse[];
extern GLfloat dblueDiffuseAlpha[];
extern GLfloat greenDiffuse[];
extern GLfloat greenDiffuseAlpha[];
extern GLfloat dgreenDiffuse[];
extern GLfloat dgreenDiffuseAlpha[];
extern GLfloat grayDiffuse[];
extern GLfloat grayDiffuseAlpha[];
extern GLfloat blackDiffuse[];
extern GLfloat blackDiffuseAlpha[];
extern GLfloat brownDiffuse[];
extern GLfloat brownDiffuseAlpha[];
extern GLfloat khakhiDiffuse[];
extern GLfloat khakhiDiffuseAlpha[];
extern GLfloat yellowDiffuse[];
extern GLfloat yellowDiffuseAlpha[];
extern GLfloat redDiffuse[];
extern GLfloat redDiffuseAlpha[];
extern GLfloat purpleDiffuse[];
extern GLfloat purpleDiffuseAlpha[];
extern GLfloat whiteDiffuse[];
extern GLfloat whiteDiffuseAlpha[];
extern GLfloat pinkDiffuse[];
extern GLfloat pinkDiffuseAlpha[];

// a white specular material
extern GLfloat whiteSpecular[];

// the degrees of shininess (size of the specular highlight, bigger number means smaller highlight)
extern GLfloat noShininess;
extern GLfloat midshininess;
extern GLfloat highShininess;

#endif
