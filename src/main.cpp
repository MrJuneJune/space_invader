#include "raylib.h"
#include <algorithm>
#include <array>
#include <vector>

struct Entity {
  float x = 0;
  float y = 0;
  float width = 20;
  float height = 20;
  float speed = 200;

  bool destructable = true;
};

struct Bullet {
  Entity entity;

  bool isFired = false;

  void Draw() {
    DrawRectangle(entity.x, entity.y, entity.width, entity.height, RED);
  }

  void Update(float deltaTime) { entity.y -= entity.speed * deltaTime; }
};

struct Block {
  Entity entity;
  int health = 3;

  void Draw() {
    if (health > 0) {
      Color color = (health == 3) ? PINK : (health == 2) ? ORANGE : YELLOW;
      DrawRectangle(entity.x, entity.y, entity.width, entity.height, color);
    }
  }

  bool Hit(const Bullet &bullet) {
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

  bool IsDestroyed() { return health <= 0; }
};

struct Player {
  Entity entity;
  int health = 10;

  void Draw() {
    DrawRectangle(entity.x, entity.y, entity.width, entity.height, BLUE);
  }

  void Update(float deltaTime) {
    if (IsKeyDown(KEY_LEFT))
      entity.x -= entity.speed * deltaTime;
    if (IsKeyDown(KEY_RIGHT))
      entity.x += entity.speed * deltaTime;

    if (entity.x < 0)
      entity.x = 0;
    if (entity.x + entity.width > GetScreenWidth())
      entity.x = GetScreenWidth() - entity.width;
  }
};

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(screenWidth, screenHeight, "Space Invader Game");

  SetTargetFPS(60);

  Player player = {0};
  player.entity.x = screenWidth / 2 - player.entity.width / 2;
  player.entity.y = screenHeight - 50;

  std::array<std::vector<int>, 10> skips;
  skips[0] = {0, 1, 4, 5, 8, 9};
  skips[1] = {0, 9};
  skips[2] = {};
  skips[3] = {};
  skips[4] = {};
  skips[5] = {0, 9};
  skips[6] = {0, 1, 8, 9};
  skips[7] = {0, 1, 2, 7, 8, 9};
  skips[8] = {0, 1, 2, 3, 6, 7, 8, 9};

  const int NUM_BLOCKS = 10;
  const int NUM_ROWS = 9;

  Block *blocks[(NUM_BLOCKS * NUM_ROWS)];
  int blockIndex = 0;

  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_BLOCKS; j++) {
      if (std::find(skips[i].begin(), skips[i].end(), j) != skips[i].end())
        continue;

      Block *block = new Block();
      block->entity.x = screenWidth / 4 + j * (block->entity.width + 10);
      block->entity.y = 100 + i * (block->entity.height + 10);
      blocks[blockIndex++] = block;
    }
  }

  // Bullet
  Bullet bullet = {0};
  bullet.entity.width = 5;
  bullet.entity.height = 10;
  bullet.entity.speed = 500;

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    // Update player
    player.Update(deltaTime);

    // Shoot a bullet
    if (IsKeyPressed(KEY_SPACE) && !bullet.isFired) {
      bullet.entity.x =
          player.entity.x + player.entity.width / 2 - bullet.entity.width / 2;
      bullet.entity.y = player.entity.y;
      bullet.isFired = true;
    }

    // Update bullet position
    if (bullet.isFired) {
      bullet.Update(deltaTime);
      if (bullet.entity.y < 0) {
        bullet.isFired = false; // Reset bullet when it goes off screen
      }
    }

    // Check for block collisions with the bullet
    for (int i = 0; i < blockIndex; i++) {
      Block *block = blocks[i];
      if (block == nullptr)
        continue;

      if (block->Hit(bullet)) {
        bullet.isFired = false; // Bullet disappears after hit
      }

      if (block->IsDestroyed()) {
        delete block;
        blocks[i] = nullptr;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    player.Draw();

    // Draw blocks
    for (int i = 0; i < blockIndex; i++) {
      Block *block = blocks[i];
      if (block != nullptr) {
        block->Draw();
      }
    }

    if (bullet.isFired) {
      bullet.Draw();
    }

    EndDrawing();
  }

  for (int i = 0; i < blockIndex; i++) {
    if (blocks[i] != nullptr) {
      delete blocks[i];
    }
  }

  CloseWindow();
  return 0;
}
