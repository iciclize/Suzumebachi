/*
 * ScoreCounter.c
 * 得点(飛行距離)の管理と表示
 */
#include "CommonHeader.h"
#include "ScoreCounter.h"
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

ScoreCounter *createScoreCounter(float x, float y)
{
  ScoreCounter *counter = malloc(sizeof(ScoreCounter));
  counter->x = x;
  counter->y = y;
  counter->score = 0;
  return counter;
}

void releaseScoreCounter(ScoreCounter *counter)
{
  free(counter);
}

int ScoreCounter_update(ScoreCounter *counter)
{
  counter->score += 0.07;
  return 0;
}

void ScoreCounter_draw(ScoreCounter *counter)
{
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(counter->x, counter->y);
  char str[12];
  sprintf(str, "%dm", (int)counter->score);
  for (int i = 0; i < strlen(str); i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
  }
}

void ScoreCounter_reset(ScoreCounter *counter)
{
  counter->score = 0; 
}
