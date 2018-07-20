#ifndef YJSNPI_COMMON_HEADER
#define YJSNPI_COMMON_HEADER

#include "Texture.h"
#include "Entity.h"
#include "Buildings.h"
#include "Crow.h"
#include "Suzumebachi.h"
#include "EnemyEmitter.h"
#include "ScoreCounter.h"
#include <GL/glut.h>

void gameStart(int restart);
void gameOver(void);
void switchResult(void);
void drawCharacter(char *string, float x, float y);

void oshiri(void);

#define FPS 60

#define SCENE_TOP 1
#define SCENE_PLAYING 2
#define SCENE_GAMEOVER 3
#define SCENE_RESULT 4

#define MAX_PLAYER_NAME_LENGTH 10
extern int playerRank;
extern char playerName[MAX_PLAYER_NAME_LENGTH + 1];

extern int currentScene;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern double MS_PER_UPDATE;

#define MAX_ENEMIES 8
extern Suzumebachi *enemies[MAX_ENEMIES];

extern Entity *background;
extern Entity *titleImage;
extern Buildings *bldgs0;
extern Buildings *bldgs1;
extern Buildings *bldgs2;
extern Crow *crow;
extern ScoreCounter *counter;

extern EnemyEmitter *enemyEmitter;

#endif /* YJSNPI_COMMON_HEADER */
