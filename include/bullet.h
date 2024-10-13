#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include "raylib.h"

struct Bullet {
  Entity entity;
  bool isFired = false;

  void Draw();
  void Update(float deltaTime);
};

#endif // BULLET_H
