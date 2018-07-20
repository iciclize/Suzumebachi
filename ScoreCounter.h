#ifndef YJSNPI_SCORE_COUNTER
#define YJSNPI_SCORE_COUNTER

typedef struct ScoreCounter {
  float x;
  float y;
  float score;
} ScoreCounter;

ScoreCounter *createScoreCounter(float x, float y);
void releaseScoreCounter(ScoreCounter *counter);
int ScoreCounter_update(ScoreCounter *counter);
void ScoreCounter_draw(ScoreCounter *counter);
void ScoreCounter_reset(ScoreCounter *counter);

#endif /* YJSNPI_SCORE_COUNTER */