#pragma once

#include <glm/glm.hpp>

class Primitive {
public:
  virtual ~Primitive();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal)=0;
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal);
};

class Cube : public Primitive {
public:
  virtual ~Cube();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal);

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
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal);
  virtual ~NonhierBox();

private:
  glm::vec3 m_pos;
  double m_size;
};
