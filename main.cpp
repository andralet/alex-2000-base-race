#include "defines.hpp"

int main(int argc, char *argv[]) {
	srand(time(NULL));

	StartMusicSystem();
	InitGlut(argc, argv);
	LAST_PLAY = clock();
	LAST_TIME = time(NULL);
	glutMainLoop();
	return 0;
}
