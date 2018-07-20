#ifndef YJSNPI_SUZUMEBACHI
#define YJSNPI_SUZUMEBACHI

#include <GL/glut.h>

typedef struct Suzumebachi {
    GLuint textureID;
    float width;
    float height;
    float x;
    float y;
    float baseY;
    float vx;
    float boundW;
    float boundH;
    int isAppearing;
} Suzumebachi;

Suzumebachi *createSuzumebachi(GLuint textureID, float speed);
void releaseSuzumebachi(Suzumebachi *suzumebachi);
int Suzumebachi_update(Suzumebachi *suzumebachi);
void Suzumebachi_draw(Suzumebachi *suzumebachi);

void Suzumebachi_setSpeed(Suzumebachi *suzumebachi, float speed);
void Suzumebachi_setY(Suzumebachi *suzumebachi, float y);
void Suzumebachi_go(Suzumebachi *suzumebachi);
void Suzumebachi_away(Suzumebachi *suzumebachi);

int Suzumebachi_isHit(Suzumebachi *suzumebachi);

#endif /* YJSNPI_SUZUMEBACHI */
