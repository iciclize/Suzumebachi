/*
 * main.c
 * クソデカファイル
 * シーンごとの処理・ランキング読込／保存など(適当)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <GL/glut.h>

#include "CommonHeader.h"
#include "Initialization.h"
#include "Callback.h"
#include "Texture.h"
#include "Entity.h"
#include "Buildings.h"
#include "ScoreCounter.h"

#define RANK_FILENAME "top10.yjsnpi"

/* 要 */
void display(void);
void tick(void);
void draw(void);

/* シーンごとの処理です */
void Top_update(void);
void Top_draw(void);
void Playing_update(void);
void Playing_draw(void);
void GameOver_update(void);
void GameOver_draw(void);
void Result_update(void);
void Result_draw(void);


/*
 * もうダメこれ以上ファイル増やせないわ
 * リスト構造も却下
 */
typedef struct Rank {
  int score;
  char name[MAX_PLAYER_NAME_LENGTH + 1];
} Rank;

static int loadRank(char *filename, Rank *top10);
static int saveRank(char *filename, Rank *top10);
static void sortRank(Rank *top10);
static void swapRank(Rank *A, Rank *B);
static void insertRank(Rank insert, int number, Rank *top10);

Rank rankArray[10];

int currentScene = SCENE_TOP;

int WINDOW_WIDTH = 640;    /* ウィンドウの横幅 */
int WINDOW_HEIGHT = 480;   /* ウィンドウの縦幅 */
double MS_PER_UPDATE = 1000 / FPS;

/* ================================
 * こ↑こ↓大域変数
 * ================================ */
int playerRank = -1;
char playerName[MAX_PLAYER_NAME_LENGTH + 1] = "\0";
Suzumebachi *enemies[MAX_ENEMIES];
Entity *background;
Entity *titleImage;
Buildings *bldgs0;
Buildings *bldgs1;
Buildings *bldgs2;
Crow *crow;
ScoreCounter *counter;
EnemyEmitter *enemyEmitter;


void display(void)
{
  static int previousTime;
  int currentTime = glutGet(GLUT_ELAPSED_TIME);
  int ms_delta = currentTime - previousTime;
  if ( ms_delta >= MS_PER_UPDATE )
  {
    tick();
    draw();
    previousTime += ms_delta + (ms_delta - MS_PER_UPDATE);
  }
}


/* ゲームループを回すためだけの関数 */
void loop(int i)
{
  glutTimerFunc(1, loop, 0);
  glutPostRedisplay();
}


/* 1フレーム分の処理 */
void tick(void)
{
  switch (currentScene)
  {
    case SCENE_TOP:
      Top_update();
      break;
    case SCENE_PLAYING:
      Playing_update();
      break;
    case SCENE_GAMEOVER:
      GameOver_update();
      break;
    case SCENE_RESULT:
      Result_update();
      break;
  }
}


/* フレーム描画 */
void draw(void)
{
  switch (currentScene)
  {
    case SCENE_TOP:
      Top_draw();
      break;
    case SCENE_PLAYING:
      Playing_draw();
      break;
    case SCENE_GAMEOVER:
      GameOver_draw();
      break;
    case SCENE_RESULT:
      Result_draw();
      break;
  }
}

/* こんなところにmain関数 */
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("main");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  loop(0); // ゲームループ開始
  glutMainLoop();
  return 0;
}

/* =====================================
 * シーンごとの処理が書かれている.
 * (時間的に分割の余裕が)ないです。
 * ===================================== */

/* タイトル画面 */
void Top_update(void)
{
  Entity_update(background);
  Entity_update(titleImage);
  Buildings_update(bldgs2, 8);
  Buildings_update(bldgs1, 8);
  Buildings_update(bldgs0, 8);
}

void Top_draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  Entity_draw(background);
  Entity_draw(titleImage);
  Buildings_draw(bldgs2);
  Buildings_draw(bldgs1);
  Buildings_draw(bldgs0);

  glPushMatrix();

  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(200, 200);
  char *message = "PRESS SPACE TO START";
  for (int i = 0; i < strlen(message); i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
  }

  glPopMatrix();

  glFlush();
}


/* プレイ画面 */
void Playing_update(void)
{
  Entity_update(background);
  Buildings_update(bldgs2, crow->speed);
  Buildings_update(bldgs1, crow->speed);
  Buildings_update(bldgs0, crow->speed);
  Crow_update(crow);
  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    Suzumebachi_update(enemies[i]);
  }
  EnemyEmitter_update(enemyEmitter);
  ScoreCounter_update(counter);
}

void Playing_draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  Entity_draw(background);
  Buildings_draw(bldgs2);
  Buildings_draw(bldgs1);
  Buildings_draw(bldgs0);
  Crow_draw(crow);
  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    Suzumebachi_draw(enemies[i]);
  }
  ScoreCounter_draw(counter);

  glFlush();
}


/* ゲーム終了・名前入力画面
 * ここから時間なくてきたない */
void GameOver_update(void)
{
  Entity_update(background);
  Buildings_update(bldgs2, 4);
  Buildings_update(bldgs1, 4);
  Buildings_update(bldgs0, 4);
}

void GameOver_draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  Entity_draw(background);
  Buildings_draw(bldgs2);
  Buildings_draw(bldgs1);
  Buildings_draw(bldgs0);
  ScoreCounter_draw(counter);

  drawCharacter("YOU ARE RANKED IN THE TOP 10!", 200, 400);
  char buf[36];
  sprintf(buf, "DISTANCE: %dm, RANK: %d", (int)counter->score, playerRank + 1);
  drawCharacter(buf, 200, 380);
  drawCharacter("INPUT YOUR NAME:", 200, 360);
  drawCharacter("__________", 350, 360);
  drawCharacter(playerName, 350, 362);

  glFlush();
}


/* ランキングの画面 */
void Result_update(void)
{
  Entity_update(background);
  Buildings_update(bldgs2, 8);
  Buildings_update(bldgs1, 8);
  Buildings_update(bldgs0, 8);
}

void Result_draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  Entity_draw(background);
  Buildings_draw(bldgs2);
  Buildings_draw(bldgs1);
  Buildings_draw(bldgs0);
  ScoreCounter_draw(counter);

  drawCharacter("TOP 10:", 200, 400);
  for (int i = 0; i < 10; i++)
  {
    int posY = 400 - 20 * (i + 1);
    char buf[16] = { '\0' };
    sprintf(buf, "%d", i + 1);
    drawCharacter(buf, 200, posY);
    drawCharacter(rankArray[i].name, 250, posY);
    sprintf(buf, "%d", rankArray[i].score);
    buf[strlen(buf)] = 'm';
    buf[strlen(buf)] = '\0';
    drawCharacter(buf, 440, posY);
  }

  drawCharacter("q: QUIT, r: REPLAY", 200, 175);

  glFlush();
}

/* =====================================
 * シーンごとの関数おわり
 * ===================================== */



/* =====================================
 * シーン遷移のための関数たち
 * ===================================== */
void gameStart(int restart)
{
  /* プレイヤーネームをnull文字で埋める */
  for (int i = 0; i < MAX_PLAYER_NAME_LENGTH + 1; i++)
  {
    playerName[i] = '\0';
  }
  playerRank = -1;

  if (restart == 1)
  {
    crow->y = 140;
  }

  currentScene = SCENE_PLAYING;
  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    Suzumebachi_away(enemies[i]);
    ScoreCounter_reset(counter);
  }
}

void gameOver(void)
{
  currentScene = SCENE_GAMEOVER;
  
  /* まだ記録ファイルがなかったら作る */
  if ( loadRank(RANK_FILENAME, rankArray) == 1 )
  {
    for (int i = 0; i < 10; i++)
    {
      Rank tmp = { 0, "NONAME" };
      rankArray[i] = tmp;
    }
    saveRank(RANK_FILENAME, rankArray);
  }

  /* 何位か出す */
  for (int i = 0; i < 10; i++)
  {
    if ( counter->score > rankArray[i].score )
    {
      playerRank = i;
      break;
    }
  }

  /* ランクインしていなかったらリザルト画面行き */
  if ( playerRank == -1 )
  {
    currentScene = SCENE_RESULT;
  }
}

void switchResult(void)
{
  currentScene = SCENE_RESULT;
  Rank tmp;
  tmp.score = counter->score;
  strcpy(tmp.name, playerName);
  sortRank(rankArray);
  insertRank(tmp, playerRank, rankArray);
  saveRank(RANK_FILENAME, rankArray);
}

/* =====================================
 * シーン遷移のための関数おわり
 * ===================================== */


/* =====================================
 * ランキングを計算・操作するための関数群
 * 本当はこんなところに書きたくはない
 * ===================================== */

static int loadRank(char *filename, Rank *top10)
{
  FILE *fp = fopen(filename, "r");
  if ( fp == NULL)
  {
    return 1;
  }

  for (int i = 0; i < 10; i++)
  {
    int score;
    char name[17];
    fscanf(fp, "%d %s\n", &score, name); 
    top10[i].score = score;
    strcpy(top10[i].name, name);
  }
  fclose(fp);
  return 0;
}

static int saveRank(char *filename, Rank *top10)
{
  FILE *fp = fopen(filename, "w");
  if ( fp == NULL)
  {
    return 1;
  }
  
  for (int i = 0; i < 10; i++)
  {
     fprintf(fp, "%d %s\n", top10[i].score, top10[i].name);
  }
  fclose(fp);
  return 0;
}

/* ノームソート */
static void sortRank(Rank *top10)
{
  int i = 1;
  while ( i < 10 )
  {
    if ( top10[i - 1].score >= top10[i].score )
    {
      i++;
    }
    else
    {
      swapRank(&top10[i - 1], &top10[i]);
      i--;
      if ( i == 0 )
      {
        i++;
      }      
    }
  }
}

static void swapRank(Rank *A, Rank *B)
{
  Rank tmp = *A;
  A->score = B->score;
  strcpy(A->name, B->name);
  B->score = tmp.score;
  strcpy(B->name, tmp.name);
}

/* ゴリゴリ入れ替えて挿入する筋肉アルゴリズム */
static void insertRank(Rank insert, int number, Rank *top10)
{
  if ( number == 9 )
  {
    top10[9] = insert;
    return;
  }

  for (int i = 9; i > number; i--)
  {
    swapRank(&top10[i], &top10[i - 1]);
  }
  top10[number] = insert;
}

/* =====================================
 * ランキングを計算・操作するための関数群おわり
 * ===================================== */


/* =====================================
 * 画面に文字を書くための処理をコピペだよ！
 * ===================================== */

void drawCharacter(char *string, float x, float y)
{
  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(x, y);
  for (int i = 0; i < strlen(string); i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
  }
  glPopMatrix();
}


/* ====================================
 * おわり
 * ==================================== */
void oshiri(void)
{
  releaseEntity(background);
  releaseEntity(titleImage);
  releaseBuildings(bldgs0);
  releaseBuildings(bldgs1);
  releaseBuildings(bldgs2);
  releaseCrow(crow);
  releaseScoreCounter(counter);
  for (int i = 0; i < MAX_ENEMIES; i++)
    releaseSuzumebachi(enemies[i]);
  releaseEnemyEmitter(enemyEmitter);
  exit(0);
}
