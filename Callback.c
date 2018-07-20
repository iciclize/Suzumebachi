/*
 * Callback.c
 * ここのコードクッソ汚い
 */
#include "CommonHeader.h"
#include "Callback.h"
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

/* キーボード入力のためのコールバック関数 */
void keyboard(unsigned char key, int x, int y)
{
  switch (currentScene)
  {
    case SCENE_TOP:
      if ( key ==  ' ' )
      {
        gameStart(0);
      }
      else
      if ( key == 'q' )
      {
        oshiri();
      }
      break;
    case SCENE_PLAYING:
      if ( key == ' ' )
      {
        Crow_input(' ');
      }
      else
      if ( key == 'r' )
      {
        gameStart(1);
      }
      else
      if ( key == 'q')
      {
        oshiri();
      }
      break;
    case SCENE_GAMEOVER:
      /* ENTER */
      if ( key == (char)13 )
      {
        if ( strlen(playerName) == 0 )
        {
          strcpy(playerName, "NONAME");
        }
        switchResult();
        break;
      }

      /* 入力が小文字のときは大文字に */
      if ( 'a' <= key && key <= 'z' )
      {
        key = key - 32;
      }

      /* アルファベット・数字以外は受け付けない */
      if ( key < 'A' || 'Z' < key )
      {
        if ( key < '0' || '9' < key )
        {
          break;
        }
      }

      playerName[strlen(playerName)] = key;
      if ( strlen(playerName) == MAX_PLAYER_NAME_LENGTH )
      {
        switchResult();
        break;
      }

      break;
    case SCENE_RESULT:
      if ( key == 'q' )
      {
        oshiri();
      }
      else
      if ( key == 'r' )
      {
        gameStart(1);
      }
      break;
  }
}
