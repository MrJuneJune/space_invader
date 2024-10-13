#include "block.h"

void Block::Draw() {
  if (health > 0) {
    Color color = (health == 3) ? PINK : (health == 2) ? ORANGE : YELLOW;
    DrawRectangle(entity.x, entity.y, entity.width, entity.height, color);
  }
}

bool Block::Hit(const Bullet &bullet) {
  bool collisionX = bullet.entity.x + bullet.entity.width >= entity.x &&
                    bullet.entity.x <= entity.x + entity.width;
  bool collisionY = bullet.entity.y + bullet.entity.height >= entity.y &&
                    bullet.entity.y <= entity.y + entity.height;

  if (collisionX && collisionY && bullet.isFired) {
    health--;
    return true;
  }

  return false;
}

bool Block::IsDestroyed() { return health <= 0; }
