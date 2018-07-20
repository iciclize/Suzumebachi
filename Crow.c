/*
 * Crow.c
 */ 
#include "CommonHeader.h"
#include "Crow.h"
#include <stdlib.h>
#include <GL/glut.h>

#define GRAVITY 0.20
#define CROW_SPEED 16
#define CROW_POS_X 100

static void flap(Crow *crow);

Crow *createCrow(char *filename)
{
  Crow *crow = malloc(sizeof(Crow));
  crow->width = 64;
  crow->height = 32;
  crow->numFrames = 6;
  crow->frameIndex = 0;
  crow->frameDuration = 3;
  crow->accumulateFrame = 0;
  crow->x = -100;
  crow->y = 120;
  crow->vy = 0;
  crow->speed = 8;
  crow->flapping = 0;
  crow->textureID = loadTexture(filename, 0, 0, 255);

  return crow;
}

void releaseCrow(Crow *crow)
{
  free(crow);
}

int Crow_update(Crow *crow)
{
  if (crow->accumulateFrame >= crow->frameDuration)
  {
    if (crow->flapping == 1)
    {
      if (crow->frameIndex == 5)
      {
        crow->flapping = 0;
      }
      crow->frameIndex++;
    }
    else
    if (crow->frameIndex != 0)
    {
      crow->frameIndex++;
    }
    crow->accumulateFrame = 0;
  }
  else
  {
    crow->accumulateFrame += 1;
  }

  if (crow->frameIndex >= crow->numFrames)
  {
    crow->frameIndex = 0;
  }

  crow->vy += GRAVITY;
  if (crow->vy > 2.00) crow->vy = 2.00;
  crow->y -= crow->vy;

  if (crow->y + crow->height > WINDOW_HEIGHT)
  {
    crow->y = WINDOW_HEIGHT - crow->height;
  }

  if (crow->y < 145)
  {
    crow->vy += -1.5 * GRAVITY;
    crow->flapping = 1;
  }

  if (crow->speed < CROW_SPEED)
  {
    crow->speed += 0.3;
    if (crow->speed > CROW_SPEED)
    {
      crow->speed = CROW_SPEED;
    }
  }

  if (crow->x < CROW_POS_X)
  {
    crow->x += 1;
    if (crow->x > CROW_POS_X)
    {
      crow->x = CROW_POS_X;
    }
  }
  
  return 0;
}

void Crow_draw(Crow *crow)
{
  double frameRatio = 1.00 / crow->numFrames;
  double frameStart = 1.00 - frameRatio * (crow->numFrames - 1 - crow->frameIndex);

  float left = crow->x;
  float right = left + 64;
  float bottom = crow->y;
  float top = bottom + 32;

  /* テクスチャマッピング開始 */
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, crow->textureID);

  /* １枚の４角形を描く */
  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, frameStart); glVertex3f( left, bottom, 0.0); // 左下
  glTexCoord2f(1.0, frameStart); glVertex3f( right, bottom,  0.0); // 右下
  glTexCoord2f(1.0, frameStart - frameRatio); glVertex3f( right, top, 0.0); // 右上
  glTexCoord2f(0.0, frameStart - frameRatio); glVertex3f( left, top,  0.0); // 左上
  glEnd();

  /* テクスチャマッピング終了 */
  glDisable(GL_TEXTURE_2D);
}

void Crow_input(char key)
{
  if (key == ' ')
  {
    flap(crow);
  }
}


static void flap(Crow *crow)
{
  crow->vy = -3.8; 
  crow->frameIndex = 1;
  crow->flapping = 1;
}
