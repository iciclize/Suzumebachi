/*
 * Texture.c
 * ppmファイルを読み込んで透過処理をする
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Texture.h"
#include <GL/glut.h>

GLuint loadTexture(char *filename, unsigned char aR, unsigned char aG, unsigned char aB)
{
  FILE *fp = fopen(filename, "rb");
  if ( fp == NULL )
  {
    fprintf(stderr, "%d: %s\n", errno, strerror(errno));
    exit(1);
  }

  GLuint textureID;
  glGenTextures(1, &textureID);

  int width, height;
  char buffer[128];
  fgets(buffer, 128, fp); // ignore P6
  fgets(buffer, 128, fp); // comment or size
  if ( *buffer == '#' ) fgets(buffer, 128, fp); // ignore if comment
  sscanf(buffer, "%d %d\n", &width, &height);
  fgets(buffer, 128, fp); // ignore
  
  GLubyte *data = malloc(sizeof(GLubyte) * width * height * 4);
  for (int i = 0; i < sizeof(GLubyte) * width * height; i++)
  {
    GLubyte *p = data + 4 * i;
    fread(p, 3, 1, fp);
    *(p + 3) = ( *(p + 0) == aR
              && *(p + 1) == aG
              && *(p + 2) == aB ) ? 0 : 255;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  free(data);
  glBindTexture(GL_TEXTURE_2D, 0);

  return textureID;
}
