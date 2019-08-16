void Log(FILE *(&log), const char *message, Duplication duplicateOnScreen) {
    fprintf(log, "%s", message);
    if (duplicateOnScreen == DUPLICATE)
        fprintf(stderr, "%s", message);
}

void LogTimeStamp(FILE *(&log), Duplication duplicateOnScreen) {
    time_t curTime = time(NULL);
    Log(log, ctime(&curTime), duplicateOnScreen);
}

bool StartAudioDaemon(bool ignoreSIGINT) {
    pid_t forkPID = fork();
    if (forkPID == 0) {
        if (RunAudioDaemon(ignoreSIGINT) == 0)
            return 0;
        // else
        exit(0);
    }
    else if (forkPID > 0) {
        // parent process just continuing, but remembering child pid
        AUDIO_DAEMON_PID = forkPID;
        return 1;
    }
    else // an error occured
        return 0;
}

void FinishAudioDaemon(int signal) {
    FINISH_DAEMON = 1;
}

void SwitchDaemonTrack(int signal) {
    SWITCH_DAEMON_TRACK = 1;
}

bool RunAudioDaemon(bool ignoreSIGINT) {
    if (ignoreSIGINT)
        signal(SIGINT, SIG_IGN);
    //else
    //    signal(SIGINT, SIG_DFL);
    signal(SIGTERM, FinishAudioDaemon);
    signal(SIGUSR1, SwitchDaemonTrack);

    FILE *log = fopen(LOG_NAME, "a");
    if (log == NULL) {
        fprintf(stderr, "Error: cannot open log file\nStarting daemon FAILED.\n");
        return 0;
    }

    Log(log, "Starting daemon...\n");
    LogTimeStamp(log);

    FILE *fifo = fopen(FIFO_NAME, "r");
    if (fifo == NULL) {
        if (mkfifo(FIFO_NAME, FIFO_MODE) < 0) {
            Log(log, "Error: cannot create fifo\nStarting daemon FAILED.\n", DUPLICATE);
            fclose(log);
            return 0;
        }

        fifo = fopen(FIFO_NAME, "r");
        if (fifo == NULL) {
            Log(log, "Error: cannot open fifo\nStarting daemon FAILED.\n", DUPLICATE);
            fclose(log);
            fclose(fifo);
            unlink(FIFO_NAME);
            return 0;
        }
    }

    char *command = (char *) malloc(COMMAND_BUF_SIZE);
    if (command == NULL) {
        Log(log, "malloc() error\nStarting daemon FAILED.\n", DUPLICATE);
        fclose(log);
        fclose(fifo);
        unlink(FIFO_NAME);
        return 0;
    }

    int driver = 0;
    mpg123_handle *mh = NULL;
    size_t buffer_size = 0;
    unsigned char *buffer = NULL;
    InitAudio(driver, mh, buffer_size, buffer);

    Log(log, "Daemon successfuly started.\n");
    while (!FINISH_DAEMON) {
        fscanf(fifo, "%s", command);
        if (strcmp(command, EXIT_COMMAND) == 0)
            break; // shutting down
        else if (strcmp(command, PLAY_COMMAND) == 0) {
            fscanf(fifo, "%s", command);
            Log(log, "Playing file ");
            Log(log, command);
            Log(log, "\n");
            PlayFile(command, driver, mh, buffer_size, buffer);
            SWITCH_DAEMON_TRACK = 0;
            pid_t parent = getppid();
            kill(parent, SIGUSR1);
        }
    }

    Log(log, "Shutting down.\n");
    LogTimeStamp(log);
    ShutdownAudio(mh, buffer);
    free(command);
    fclose(log);
    fclose(fifo);
    unlink(FIFO_NAME);
    exit(0);
}
