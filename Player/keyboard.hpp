typedef std::pair <int, bool> Key; // int code; bool isSpecial;
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

const int KEYS_PER_USAGE = 3,
          NO_KEY = '\0';

const Key INIT_KEYS[MAX_KEY_USAGE_ID - MIN_KEY_USAGE_ID + 1][KEYS_PER_USAGE] = {
    {   {'a', 0},    {'A', 0},  {GLUT_KEY_LEFT, 1}},
    {   {'d', 0},    {'D', 0}, {GLUT_KEY_RIGHT, 1}},
    {{'\033', 0}, {NO_KEY, 0},         {NO_KEY, 0}},
    {   {'p', 0},    {'P', 0},    {GLUT_KEY_F1, 1}},
    {   {'q', 0},    {'Q', 0},         {NO_KEY, 0}},
    {   {'q', 0},    {'Q', 0},         {NO_KEY, 0}},
    {   {'e', 0},    {'E', 0},         {NO_KEY, 0}}
};
