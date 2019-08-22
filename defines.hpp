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

    const int CAR_DEPTH = 20, // 24, // firstly, was 12,
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
    struct Color {
        float r, g, b;
    };
    #include "Draw/colors.hpp"// list of some useful colors
    const Color NO_COLOR_CHANGE = {-1.0, -1.0, -1.0};
    const Color SKY_COLOR    = { 89.0 / 256.0, 181.0 / 256.0, 210.0 / 256.0},
                GROUND_COLOR = GREEN,
                TREE_COLOR   = {195.0 / 256.0, 115.0 / 256.0,  11.0 / 256.0},
                LEAVES_COLOR = DARK_GREEN;
    /*std::vector <Color> COLOR_STACK;
    int COLOR_STACK_SIZE = 0;*/

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
    const double SMALL_COORD = 1;
    void DrawRoad(void);
    void DrawGround(void);
    void DrawHelp(Color textColor, double startY);
    void DrawHUD(void);
    void DrawCar(int x, int depth, Color carColor, Color lineColor = WHITE, bool isPlayer = 0);
    void DrawTree(int x, int depth);
    void DrawText(int x, int y, const char *text, Color textColor = WHITE);
    void Display(void);

// Draw/obj.cpp
    struct Vertex {
        double x, y, z;
    };

    struct Triangle {
        int vertex[3]; // vertex id
    };

    struct ImageScale {
        double x, y, z;
    };

    const int MAX_OBJ_CMD_SIZE = 256;
    const double INF_COORD = 1e9,
                 DFL_WIDTH = 100.0,
                 DFL_HEIGHT = 100.0,
                 DFL_DEPTH = 100.0;

    void CreateList(int listId, const std::vector <Vertex> &v, const std::vector <Triangle> &f);
    void CopyList(int src, int dst);
    void UpdateMinMaxCoord(const Vertex &v, Vertex &minCoord, Vertex &maxCoord);
    // Just basic .obj format is supported for loading (you can look for examples in Draw/Models)
    // In Blender options are: Apply Modifiers, Objects as OBJ Objects,
    // Scale - 1.0 (generating later with 'make config', I think, is better), Path Mode - Auto, Forward - -Z Forward, Up - Y Up
    bool LoadObj(const char *filename, int partNumber, const int listId[], ImageScale &dfl);
    // Scaleinfo file format: 3 %lf numbers (x, y, z) for default window size
    bool LoadScaleInfo(const char *filename, ImageScale &scale);

    const char *CAR_OBJ_FILEPATH = "Draw/Models/car.obj",
               *CAR_SCALE_FILEPATH = "Draw/Models/car.scaleinfo",
               *LOW_CAR_OBJ_FILEPATH = "Draw/Models/car_low.obj",
               *LOW_CAR_SCALE_FILEPATH = "Draw/Models/car_low.scaleinfo",
               *TREE_OBJ_FILEPATH = "Draw/Models/tree.obj",
               *TREE_SCALE_FILEPATH = "Draw/Models/tree.scaleinfo",
               *LOW_TREE_OBJ_FILEPATH = "Draw/Models/tree_low.obj",
               *LOW_TREE_SCALE_FILEPATH = "Draw/Models/tree_low.scaleinfo";
    ImageScale CAR_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH},
               LOW_CAR_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH},
               TREE_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH},
               LOW_TREE_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH};

// Draw/compile.cpp
    const int DRAW_CAR_LIST = 1,
              DRAW_LOW_CAR_LIST = 2,
              DRAW_TREE_LIST = 3,
              DRAW_LOW_TREE_LIST = 4,
              INTERNAL_LIST_START = 1000001;
    void ScaleModel(ImageScale scale);
    int GetNewInternalList(void);
    void CompileDrawCar(void);
    void CompileDrawTree(void);

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
#include "Player/hero.cpp"
#include "play.cpp"
#include "Draw/draw.cpp"
#include "Draw/obj.cpp"
#include "Draw/compile.cpp"
#include "glut.cpp"
#include "Player/keyboard.cpp"
