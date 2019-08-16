// audio.cpp
    const int BITS = 8;
    void InitAudio(int *driver, mpg123_handle **mh, size_t *buffer_size, unsigned char **buffer);
    void ShutdownAudio(mpg123_handle *(&mh), unsigned char *(&buffer));
    bool StopPlayingFile(void);
    void PlayFile(const char *filename, int &driver, mpg123_handle *(&mh), size_t &buffer_size, unsigned char *(&buffer));

// daemon.cpp
    const char *FIFO_NAME = "Audio/audio.fifo",
               *LOG_NAME = "Audio/audio.log";
    const int FIFO_MODE = 0640;

    const int COMMAND_BUF_SIZE = 1024;
    const char *EXIT_COMMAND = "exit",
               *PLAY_COMMAND = "play";

    enum Duplication {NOT_DUPLICATE, DUPLICATE};

    bool FINISH_DAEMON = 0,
         SWITCH_DAEMON_TRACK = 0;

    void Log(FILE *(&log), const char *message, Duplication duplicateOnScreen = NOT_DUPLICATE);
    void LogTimeStamp(FILE *(&log), Duplication duplicateOnScreen = NOT_DUPLICATE);
    bool StartAudioDaemon(bool ignoreSIGINT = 0);
    void FinishAudioDaemon(int signal);
    void SwitchDaemonTrack(int signal);
    bool RunAudioDaemon(bool ignoreSIGINT = 0);

// play_control
    pid_t AUDIO_DAEMON_PID = -1;
    bool MUSIC_PAUSED = 0;
    int TRACK_NUM = 2;
    void StartMusicSystem(void);
    void StopMusicSystem(void);

    void PauseMusicSystem(void);
    void ContinueMusicSystem(void);
    bool MusicSystemPaused(void);
    void MusicChangeTrack(void);
    void SetTrack(int signal);

// other code files
    #include "audio.cpp"
    #include "audio_daemon.cpp"
    #include "play_control.cpp"
