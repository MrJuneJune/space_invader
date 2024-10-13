#ifndef BLOCK_H
#define BLOCK_H

#include "bullet.h"
#include "entity.h"
#include "raylib.h"

struct Block {
  Entity entity;
  int health = 3;

  void Draw();
  bool Hit(const Bullet &bullet);
  bool IsDestroyed();
};

#endif // BLOCK_H
