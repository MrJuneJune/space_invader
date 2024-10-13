#include "player.h"

void Player::Draw() {
  DrawRectangle(entity.x, entity.y, entity.width, entity.height, BLUE);
}

void Player::Update(float deltaTime) {
  if (IsKeyDown(KEY_LEFT)) {
    entity.x -= entity.speed * deltaTime;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    entity.x += entity.speed * deltaTime;
  }

  if (entity.x < 0) {
    entity.x = 0;
  }
  if (entity.x + entity.width > GetScreenWidth()) {
    entity.x = GetScreenWidth() - entity.width;
  }
}
