#ifndef YJSNPI_ENTITY
#define YJSNPI_ENTITY

#include <GL/glut.h>

typedef struct Entity {
    GLuint textureID;
    float x;
    float y;
    float width;
    float height;
} Entity;

Entity *createEntity(char *filename, float x, float y, float w, float h);
void releaseEntity(Entity *entity);
int Entity_update(Entity *entity);
void Entity_draw(Entity *entity);

#endif /* YJSNPI_ENTITY */
