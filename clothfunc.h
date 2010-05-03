#ifndef CLOTH_FUNC_H
#define CLOTH_FUNC_H

///////////////////////////////////////////////METODOS DE CLOTH
Vec3 Vec3construct(double x, double y, double z);
float Vec3length(Vec3 *v);
Vec3 Vec3normalize(Vec3 *v);
void Vec3sumeq (Vec3 *vs, Vec3 *v);
Vec3 Vec3div (Vec3 *vec, const double &a);
Vec3 Vec3minus (Vec3 *vec, const Vec3 *v);
Vec3 Vec3sum (Vec3 *vec, const Vec3 *v);
Vec3 Vec3mult (Vec3 *vec, const double &a);
Vec3 Vec3neg(Vec3 *vec);
Vec3 Vec3cross(Vec3 *vec, const Vec3 *v);
double Vec3dot(Vec3 *vec, const Vec3 *v);
///////////////PARTICLE
particle particleconstruct(Vec3 *npos);
void partaddForce(particle *p, Vec3 f);
void parttimeStep(particle *p);
Vec3& partgetPos(particle *p);
void partresetAcceleration(particle *p);
void partoffsetPos(particle *p, Vec3 v);
void partmakeUnmovable(particle *p);
void partaddToNormal(particle *p, Vec3 normal);
Vec3& partgetNormal(particle *p);
void partresetNormal(particle *p);
/////////////////////////CONSTRAINT
spring springconstruct(particle *p1, particle *p2);
void satisfyConstraint(spring *c);
///////////////////////////CLOTH
Vec3 calcTriangleNormal(particle *p1, particle *p2, particle *p3);
void addWindForcesForTriangle(particle *p1,particle *p2,particle *p3, const Vec3 direction);
void drawTriangle(particle *p1, particle *p2, particle *p3, const Vec3 color);
///////////////////////////////////////

#endif
