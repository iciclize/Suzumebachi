/*
 * Buildings.c
 */
#include "CommonHeader.h"
#include "Buildings.h"
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

Buildings *createBuildings(char *filename, float y)
{
  Buildings *bldgs = malloc(sizeof(Buildings));
  bldgs->y = y;
  bldgs->x = 0;
  bldgs->paraY = 0;
  bldgs->textureID = loadTexture(filename, 0, 0, 0);

  return bldgs;
}

void releaseBuildings(Buildings *bldgs)
{
  free(bldgs);
}

int Buildings_update(Buildings *bldgs, float speed)
{
  Buildings *b = bldgs;
  b->paraY = 15 - 30 * (crow->y - 125) / WINDOW_HEIGHT / (b->y + 36) * 60;
  b->x -= (speed / 1.5) / (b->y + 50) / (b->y + 50) * 120;
  if (b->x <= -WINDOW_WIDTH)
  {
    b->x = b->x + WINDOW_WIDTH;
  }
  else
  if (b->x >= 0)
  {
    b->x = b->x - WINDOW_WIDTH;
  }
  return 0;
}

void Buildings_draw(Buildings *bldgs)
{
  float left = bldgs->x;
  float bottom = bldgs->y + bldgs->paraY;
  float right = left + WINDOW_WIDTH * 2;
  float top = bottom + 200;

  /* テクスチャマッピング開始 */
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, bldgs->textureID);

  /* １枚の４角形を描く */
  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 1.0); glVertex3f( left, bottom, 0.0); // 左下
  glTexCoord2f(2.0, 1.0); glVertex3f( right, bottom,  0.0); // 右下
  glTexCoord2f(2.0, 0.0); glVertex3f( right, top, 0.0); // 右上
  glTexCoord2f(0.0, 0.0); glVertex3f( left, top,  0.0); // 左上
  glEnd();

  /* テクスチャマッピング終了 */
  glDisable(GL_TEXTURE_2D);
}
