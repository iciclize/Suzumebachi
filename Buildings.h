#ifndef YJSNPI_BUILDINGS
#define YJSNPI_BUILDINGS

#include <GL/glut.h>

typedef struct Buildings {
  GLuint textureID;
  float x;
  float y;
  float paraY;
} Buildings;

Buildings *createBuildings(char *filename, float y);
void releaseBuildings(Buildings *bldgs);
int Buildings_update(Buildings *bldgs, float speed);
void Buildings_draw(Buildings *bldgs);

#endif /* YJSNPI_BUILDINGS */
