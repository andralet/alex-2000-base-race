#include "includes.hpp"

// consts & settings
    #include "Player/keyboard.hpp"

    time_t LAST_PLAY = 0,
           LAST_TIME = 0;
    bool WAS_PAUSED = 0;
    int REDRAWS_PER_SEC = 0;
    int OLD_FPS = 0;

    #include "Draw/draw.hpp"
    GLint WINDOW_WIDTH = BASE_WINDOW_WIDTH,
          WINDOW_HEIGHT = BASE_WINDOW_HEIGHT;

    const int CAR_DEPTH = 12,
              ROAD_DEPTH = 2000 + CAR_DEPTH;
    double CAR_SPEED = 3.0,
           SPEED_ADD = CAR_SPEED / 2500.0;

    bool PAUSED = 0,
         CRASHED = 0;
    bool MOVE_AVIABLE = 1;
    const double TARGET_FPS = 65.0,
                 USEC_IN_SEC = 1000000.0;

    const int RAND_PARTS = RAND_MAX,
              MAX_ENEMY = 200,
              ENEMY_CREATE_CYCLE_LIMIT = 100;
    double CAR_CHANCE = 0.005,
           CHANCE_ADD = CAR_CHANCE / 2500.0;

    int score = 0;
// Draw/color.cpp
    struct Color;
    // list of some useful colors in "color.cpp"
    inline void SetColor(const Color &color);
    #include "Draw/color.cpp"

// Player/hero.cpp
    class Hero;
    // Hero hero;
    const Color HERO_COLOR = LIGHT_BLUE,
                HERO_LINE_COLOR = BLUE;
    inline bool CanMoveHero(void);

// play.hpp
    class Car;
    const Color ENEMY_COLOR = LIGHT_RED,
                ENEMY_LINE_COLOR = RED;
    // Car enemy[MAX_ENEMY];
    int enemyEnd = 0;
    void FreeCarSpace(void);
    void AddCar(void);
    inline bool CanPlay(void);
    void Play(void);

// Draw/draw.cpp
    void DrawRoad(void);
    void DrawSky(void);
    void DrawHelp(Color textColor, double startY);
    void DrawHUD(void);
    void DrawCar(int x, int depth, Color carColor, Color lineColor = WHITE);
    void DrawTree(int x, int depth);
    void DrawText(int x, int y, const char *text, Color textColor = WHITE);
    void Display(void);

// glut.cpp
    const int DRAW_CAR_BODY_LIST = 1,
              DRAW_CAR_LINES_LIST = 2,
              DRAW_TREE_LIST = 3;
    void CompileDrawCar(void);
    void Reshape(int width, int height);
    void InitGlut(int argc, char *argv[]);

// Player/keyboard.cpp
    bool IsKeySet(Key key);
    void InitKeyboard(void);
    inline bool HasUsage(Key key, KeyUsage usage);
    void Keyboard(Key key, int x, int y);
    void KeyboardNormalHandler(unsigned char key, int x, int y);
    void KeyboardSpecialHandler(int key, int x, int y);

// audio daemon
    #include "Audio/audio.hpp"

// headers
#include "Player/hero.cpp"
#include "play.cpp"
#include "Draw/draw.cpp"
#include "glut.cpp"
#include "Player/keyboard.cpp"
