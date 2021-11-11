#pragma once

#include <glm/glm.hpp>

class Primitive {
public:
  virtual ~Primitive();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans)=0;
  float tol = 0.01f;
};

class Sphere : public Primitive {
public:
  Sphere() {}
  virtual ~Sphere();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans);

};

class Cube : public Primitive {
public:
  Cube(){}
  virtual ~Cube();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans);

};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius) {}
  virtual ~NonhierSphere();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans);

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size){}
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans);
  virtual ~NonhierBox();

private:
  glm::vec3 m_pos;
  double m_size;
};
