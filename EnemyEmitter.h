#ifndef YJSNPI_ENEMY_EMITTER
#define YJSNPI_ENEMY_EMITTER

#include <GL/glut.h>

typedef struct EnemyEmitter {
  GLuint textureID;
} EnemyEmitter;

EnemyEmitter *createEnemyEmitter(char *filename);
void releaseEnemyEmitter(EnemyEmitter *emitter);
int EnemyEmitter_update(EnemyEmitter *emitter);

#endif /* YJSNPI_ENEMY_EMITTER */
