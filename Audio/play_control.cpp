void StartMusicSystem(void) {
	if (StartAudioDaemon() == 0) {
		fprintf(stderr, "Starting audio daemon failed. Exiting\n");
		exit(255);
	}
	signal(SIGUSR1, SetTrack);
    SetTrack(SIGUSR1);
}

void StopMusicSystem(void) {
    kill(AUDIO_DAEMON_PID, SIGTERM);
}

void PauseMusicSystem(void) {
	kill(AUDIO_DAEMON_PID, SIGSTOP);
	MUSIC_PAUSED = 1;
}

void ContinueMusicSystem(void) {
	kill(AUDIO_DAEMON_PID, SIGCONT);
	MUSIC_PAUSED = 0;
}

bool MusicSystemPaused(void) {
	return MUSIC_PAUSED;
}

void MusicChangeTrack(void) {
	kill(AUDIO_DAEMON_PID, SIGUSR1);
}

void SetTrack(int signal) {
    int track = rand() % TRACK_NUM + 1;
    static char *command = new char[COMMAND_BUF_SIZE];
    sprintf(command, "echo \"play ./Audio/Tracks/%02d.mp3\" >> ./Audio/audio.fifo", track);
    system(command);
}
