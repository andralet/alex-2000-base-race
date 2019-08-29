#include "includes.hpp"

// consts & settings
    #include "Player/keyboard.hpp"

    time_t LAST_PLAY = 0,
           LAST_TIME = 0;
    bool WAS_PAUSED = 0;
    int REDRAWS_PER_SEC = 0;
    int OLD_FPS = 0;

    #include "Draw/draw.hpp"

    #include "Player/carDefines.hpp"

    bool PAUSED = 0,
         CRASHED = 0;
    bool MOVE_AVIABLE = 1;
    const double TARGET_FPS = 65.0,
                 USEC_IN_SEC = 1000000.0;
    bool FPS_TARGET_REACHED = 0;

    int score = 0;

// Player/Settings/optimization.cpp
    #include "Player/Settings/optimization.hpp"
    void LoadOptimization(const char *filename);
    void SetOption(FILE *input, int id);

// Draw/color.cpp
    #include "Draw/color.hpp"

    bool IsEqual(const Color &a, const Color &b);
    void SetColor(const Color &color);
    //void PushColor(const Color &color);
    //Color PopColor(void); // returns BLACK if stack is empty
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
    void DrawTrees(void);
    void DrawGround(void);
    void DrawHelp(Color textColor, double startY);
    void DrawHUD(void);
    void DrawCar(int x, int depth, Color carColor, Color lineColor = WHITE, bool isPlayer = 0);
    void DrawTree(int x, int depth);
    void DrawText(int x, int y, const char *text, Color textColor = WHITE);
    void Display(void);

// Draw/Model/
    #include "Draw/Model/defines.hpp"

// glut.cpp
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
#include "Player/Settings/optimization.cpp"
#include "Player/hero.cpp"
#include "play.cpp"
#include "Draw/draw.cpp"
#include "Draw/Model/cppfiles.hpp"
#include "glut.cpp"
#include "Player/keyboard.cpp"
