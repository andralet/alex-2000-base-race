#include "defines.hpp"

int main(int argc, char *argv[]) {
	srand(time(NULL));

	fprintf(stderr, "Loading. Please, wait...\n");
	LoadOptimization(OPTIMIZATION_FILE);

	StartMusicSystem();
	PauseMusicSystem();
	InitGlut(argc, argv);
	LAST_PLAY = clock();
	LAST_TIME = time(NULL);
	fprintf(stderr, "Done.\n");
	glutMainLoop();
	return 0;
}
