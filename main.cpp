#include "defines.hpp"

int main(int argc, char *argv[]) {
	srand(time(NULL));

	StartMusicSystem();
	PauseMusicSystem();
	InitGlut(argc, argv);
	LAST_PLAY = clock();
	LAST_TIME = time(NULL);
	glutMainLoop();
	return 0;
}
