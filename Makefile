main: CommonHeader.h main.o Initialization.o Texture.o Callback.o Entity.o Buildings.o Crow.o Suzumebachi.o EnemyEmitter.o ScoreCounter.o
	gcc -g -o main main.o Initialization.o Texture.o Callback.o Entity.o Buildings.o Crow.o Suzumebachi.o EnemyEmitter.o ScoreCounter.o -lGL -lGLU -lglut

.c.o:
	gcc -g -c $< -Wno-deprecated

clean:
	rm -rf *.o
