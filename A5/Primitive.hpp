#pragma once

#include <glm/glm.hpp>
#include "Hit.hpp"
using namespace glm;

class Primitive {
public:
  virtual ~Primitive();
  virtual float intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans)=0;
  float tol = 0.01f;
};

class Sphere : public Primitive {
public:
  Sphere() {}
  virtual ~Sphere();
  virtual float intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans);

};

class Cube : public Primitive {
public:
  Cube(){}
  virtual ~Cube();
  virtual float intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans);

};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const vec3& pos, double radius)
    : m_pos(pos), m_radius(radius) {}
  virtual ~NonhierSphere();
  virtual float intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans);

private:
  vec3 m_pos;
  double m_radius;
};

class Cone : public Primitive {
public:
  Cone(const vec3& pos, double height, double radius)
    : m_pos(pos), m_height(height), m_radius(radius) {}
  virtual ~Cone();
  virtual float intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans);

private:
  vec3 m_pos;
  double m_radius;
  double m_height;

};

class Cylinder : public Primitive {
public:
  Cylinder(const vec3& pos, double height, double radius)
    : m_pos(pos), m_height(height), m_radius(radius) {}
  virtual ~Cylinder();
  virtual float intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans);

private:
  vec3 m_pos;
  double m_radius;
  double m_height;

};

class NonhierBox : public Primitive {
public:
  NonhierBox(const vec3& pos, double size)
    : m_pos(pos), m_size(size){}
  virtual float intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans);
  virtual ~NonhierBox();

private:
  vec3 m_pos;
  double m_size;
};
