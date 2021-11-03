#pragma once

#include <glm/glm.hpp>

class Primitive {
public:
  virtual ~Primitive();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir)=0;
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir);
};

class Cube : public Primitive {
public:
  virtual ~Cube();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir);

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size)
  {
  }
  virtual float intersect(glm::vec3 origin, glm::vec3 dir);
  virtual ~NonhierBox();

private:
  glm::vec3 m_pos;
  double m_size;
};
