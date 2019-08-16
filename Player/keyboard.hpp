typedef unsigned char Key;
typedef int KeyUsage;

std::map <Key, std::set <KeyUsage>> KEY_USAGES;
std::set <Key> USED_KEYS;

// KeyUsages must go as consecutive natural numbers
// Look after MAX_KEY_USAGE_ID or new keys won't work correctly)
const KeyUsage MIN_KEY_USAGE_ID = 1,
               KEY_LEFT = 1,
               KEY_RIGHT = 2,
               KEY_ESCAPE = 3,
               KEY_PAUSE = 4,
               KEY_MUSIC_PAUSE = 5,
               KEY_MUSIC_CONTINUE = 6,
               KEY_CHANGE_TRACK = 7,
               MAX_KEY_USAGE_ID = KEY_CHANGE_TRACK;

const int MAX_KEYS_PER_USAGE = 4;

const Key INIT_KEYS[MAX_KEY_USAGE_ID - MIN_KEY_USAGE_ID + 1][MAX_KEYS_PER_USAGE] =
    {{'a', 'A'},
     {'d', 'D'},
     {'\033'},
     {'p', 'P'},
     {'q', 'Q'},
     {'q', 'Q'},
     {'e', 'E'}};
