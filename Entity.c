/*
 * Entity.c
 * 任意のテクスチャを任意のサイズで任意の場所に貼り付けるための関数群
 */ 
#include "CommonHeader.h"
#include "Entity.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>


Entity *createEntity(char *filename, float x, float y, float w, float h)
{
  Entity *entity = malloc(sizeof(Entity));
  entity->textureID = loadTexture(filename, 0, 0, 0);
  entity->x = x;
  entity->y = y;
  entity->width = w;
  entity->height = h;
  return entity;
}

void releaseEntity(Entity *entity)
{
  free(entity);
}

int Entity_update(Entity *entity)
{
  return 0;
}

void Entity_draw(Entity *entity)
{

  float left = entity->x;
  float bottom = entity->y;
  float right = left + entity->width;
  float top = bottom + entity->height;

  /* テクスチャマッピング開始 */
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, entity->textureID);

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
