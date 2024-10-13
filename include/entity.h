#ifndef ENTITY_H
#define ENTITY_H

struct Entity {
  float x = 0;
  float y = 0;
  float width = 20;
  float height = 20;
  float speed = 200;

  bool destructable = true;
};

#endif // ENTITY_H
