#include "bullet.h"

void Bullet::Draw() {
  DrawRectangle(entity.x, entity.y, entity.width, entity.height, RED);
}

void Bullet::Update(float deltaTime) { entity.y -= entity.speed * deltaTime; }
