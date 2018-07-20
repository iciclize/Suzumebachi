/*
 * EnemyEmitter.c
 * スズメバチを定数匹分確保して管理する
 */ 
#include "CommonHeader.h"
#include "EnemyEmitter.h"
#include "Suzumebachi.h"
#include <stdlib.h>
#include <GL/glut.h>

static float count = 120;
static GLuint textureID;
Suzumebachi *enemies[MAX_ENEMIES];

static int emitEnemy(void);

EnemyEmitter *createEnemyEmitter(char *filename)
{
  EnemyEmitter *emitter = malloc(sizeof(EnemyEmitter));
  textureID = loadTexture(filename, 255, 255, 255);
  emitter->textureID = textureID;
  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    enemies[i] = createSuzumebachi(textureID, 2);
  }

  return emitter;
}

void releaseEnemyEmitter(EnemyEmitter *emitter)
{
  free(emitter);
}

int EnemyEmitter_update(EnemyEmitter *emitter)
{
  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    Suzumebachi_update(enemies[i]);
  }

  count -= 1;
  if (count <= 0)
  {
    count = rand() % (int)(FPS * 1.0) + (FPS / 8);
    emitEnemy();
  }
  return 0;
}

static int emitEnemy(void)
{
  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    Suzumebachi *enemy = enemies[i];
    if (enemy->isAppearing == 1) continue;
    /* 視差効果の分 */
    Suzumebachi_setY(enemy, (140 + rand() % (WINDOW_HEIGHT - 140) - enemy->height) );
    // Suzumebachi_setSpeed(enemy, 16);
    Suzumebachi_go(enemy);
    break;
  }

  return 0;
}
