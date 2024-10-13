#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "raylib.h"

struct Player {
  Entity entity;
  int health = 10;

  void Draw();
  void Update(float deltaTime);
};

#endif // PLAYER_H
