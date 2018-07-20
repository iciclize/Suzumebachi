/*
 * Suzumebachi.c
 * ウ　ン　チ　ー　コ　ン　グ
 */
#include "CommonHeader.h"
#include "Suzumebachi.h"
#include <stdlib.h>
#include <GL/glut.h>

Suzumebachi *createSuzumebachi(GLuint textureID, float speed)
{
  Suzumebachi *suzumebachi = malloc(sizeof(Suzumebachi));
  suzumebachi->width = 54;
  suzumebachi->height = 52;
  suzumebachi->boundW = 28;
  suzumebachi->boundH = 28;
  suzumebachi->x = WINDOW_WIDTH + suzumebachi->width;
  suzumebachi->y = 300;
  suzumebachi->baseY = 300;
  suzumebachi->vx = -speed;
  suzumebachi->isAppearing = 0;
  suzumebachi->textureID = textureID;

  return suzumebachi;
}

void releaseSuzumebachi(Suzumebachi *suzumebachi)
{
  free(suzumebachi);
}

int Suzumebachi_update(Suzumebachi *suzumebachi)
{
  Suzumebachi *s = suzumebachi;

  if (s->isAppearing == 0) return 0;

  if ( Suzumebachi_isHit(s) == 1 )
  {
    gameOver();
  }
  
  s->x += s->vx;
  s->y = s->baseY - 0.5 * crow->y * (WINDOW_HEIGHT - 140) / WINDOW_HEIGHT;

  if (s->x < 0 - s->width)
  {
    Suzumebachi_away(s);
  }

  return 0;
}

void Suzumebachi_draw(Suzumebachi *suzumebachi)
{
  if (suzumebachi->isAppearing == 0) return;

  Suzumebachi *s = suzumebachi;

  float left = s->x;
  float right = left + s->width;
  float bottom = s->y;
  float top = bottom + s->height;

  /* テクスチャマッピング開始 */
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, s->textureID);

  /* １枚の４角形を描く */
  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 1.0); glVertex3f( left, bottom, 0.0); // 左下
  glTexCoord2f(1.0, 1.0); glVertex3f( right, bottom,  0.0); // 右下
  glTexCoord2f(1.0, 0.0); glVertex3f( right, top, 0.0); // 右上
  glTexCoord2f(0.0, 0.0); glVertex3f( left, top,  0.0); // 左上
  glEnd();

  /* テクスチャマッピング終了 */
  glDisable(GL_TEXTURE_2D);
}

void Suzumebachi_setSpeed(Suzumebachi *suzumebachi, float speed)
{
  suzumebachi->vx = -speed;
}

void Suzumebachi_setY(Suzumebachi *suzumebachi, float y)
{
  suzumebachi->baseY = y * 1.4;
}

void Suzumebachi_go(Suzumebachi *suzumebachi)
{
  suzumebachi->x = WINDOW_WIDTH + suzumebachi->width;
  suzumebachi->isAppearing = 1;
}

void Suzumebachi_away(Suzumebachi *suzumebachi)
{
  suzumebachi->isAppearing = 0;
}

int Suzumebachi_isHit(Suzumebachi *suzumebachi)
{
  Suzumebachi *s = suzumebachi;
  float sBoundLeft = s->x + (s->width - s->boundW) / 2;
  float sBoundRight = sBoundLeft + s->boundW;
  float sBoundBottom = s->y + (s->height - s->boundH) / 2;
  float sBoundTop = sBoundBottom + s->boundH;

  if ( crow->y + crow->height < sBoundBottom ) return 0;
  if ( crow->y > sBoundTop ) return 0;
  if ( crow->x + crow->width < sBoundLeft ) return 0;
  if ( crow->x > sBoundRight ) return 0;
  return 1;
}
