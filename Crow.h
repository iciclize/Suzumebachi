#ifndef YJSNPI_CROW
#define YJSNPI_CROW

#include <GL/glut.h>

typedef struct Crow {
  GLuint textureID;
  float width;
  float height;
  float vy;
  float x;
  float y;
  float speed;
  int flapping;
  int numFrames;
  int frameIndex;
  float frameDuration;
  float accumulateFrame;
} Crow;

Crow *createCrow(char *filename);
void releaseCrow(Crow *crow);
int Crow_update(Crow *crow);
void Crow_draw(Crow *crow);
void Crow_input(char key);

#endif /* YJSNPI_CROW */
