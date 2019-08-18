bool IsKeySet(Key key) {
    return (key.first != NO_KEY);
}

void InitKeyboard(void) {
    USED_KEYS.clear();
    KEY_USAGES.clear();
    for (KeyUsage i = MIN_KEY_USAGE_ID; i <= MAX_KEY_USAGE_ID; i++)
        for (int j = 0; j < KEYS_PER_USAGE; j++)
            if (IsKeySet(INIT_KEYS[i - MIN_KEY_USAGE_ID][j])) {
                USED_KEYS.insert(INIT_KEYS[i - MIN_KEY_USAGE_ID][j]);
                KEY_USAGES[INIT_KEYS[i - MIN_KEY_USAGE_ID][j]].insert(i);
            }
}

inline bool HasUsage(Key key, KeyUsage usage) {
    return (KEY_USAGES[key].find(usage) != KEY_USAGES[key].end());
}

void Keyboard(Key key, int x, int y) {
    static bool musicSystemAutoPaused = 0;
    if (USED_KEYS.find(key) != USED_KEYS.end()) {
        if (CanMoveHero() && (HasUsage(key, KEY_LEFT) || HasUsage(key, KEY_RIGHT))) {
            hero.Move(key);
            MOVE_AVIABLE = 0;
        }
        else if (HasUsage(key, KEY_PAUSE)) {
            PAUSED = !PAUSED;
            if (PAUSED) {
                WAS_PAUSED = 1;
                if (!MusicSystemPaused()) {
                    PauseMusicSystem();
                    musicSystemAutoPaused = 1;
                }
            }
            else if (!PAUSED) {
                if (musicSystemAutoPaused && MusicSystemPaused())
                    ContinueMusicSystem();
                musicSystemAutoPaused = 0;
            }
        }
        else if (HasUsage(key, KEY_MUSIC_PAUSE) && !MusicSystemPaused())
            PauseMusicSystem();
        else if (HasUsage(key, KEY_MUSIC_CONTINUE) && MusicSystemPaused())
            ContinueMusicSystem();
        else if (HasUsage(key, KEY_CHANGE_TRACK))
            MusicChangeTrack();
        else if (HasUsage(key, KEY_ESCAPE)) {
            StopMusicSystem();
            exit(0);
        }
    }
}

void KeyboardNormalHandler(unsigned char key, int x, int y) {
    // For now it should be okay
    Keyboard({key, 0}, x, y);
}

void KeyboardSpecialHandler(int key, int x, int y) {
    // For now it should be okay
    Keyboard({key, 1}, x, y);
}
