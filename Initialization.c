/*
 * Initialization.c
 * 主に大域変数の初期化です
 */
#include "CommonHeader.h"
#include "Entity.h"
#include "Buildings.h"
#include "ScoreCounter.h"
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>

/* 初期化処理 */
void init(void)
{
  srand(time(NULL));

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glLineWidth(3.f);                   /* 線の太さを指定 */
  glEnable(GL_LINE_SMOOTH);           /* 線をなめらかに表示するための設定 */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

  /* 左下を原点にする */
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  background = createEntity("sky.ppm", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  titleImage = createEntity("title.ppm", 250, 260, 300, 180);
  bldgs0 = createBuildings("layer0.ppm", 0 - 15);
  bldgs1 = createBuildings("layer1.ppm", 30 - 15);
  bldgs2 = createBuildings("layer2.ppm", 70 - 15);
  crow = createCrow("crow.ppm");
  counter = createScoreCounter(20, WINDOW_HEIGHT - 30);
  enemyEmitter = createEnemyEmitter("suzumebachi.ppm");
}
