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
    void DrawGround(void);
    void DrawHelp(Color textColor, double startY);
    void DrawHUD(void);
    void DrawCar(int x, int depth, Color carColor, Color lineColor = WHITE, bool isPlayer = 0);
    void DrawTree(int x, int depth);
    void DrawText(int x, int y, const char *text, Color textColor = WHITE);
    void Display(void);

// Draw/scaleinfo.cpp
    #include "Draw/obj.hpp"
    #include "Draw/scaleinfo.hpp"

// Draw/modelinfo.cpp
    #include "Draw/modelinfo.hpp"
    bool LoadModelinfo(const char *filename, std::vector <PartInfo> &targetModelinfo, int &partNumber);
    void CompileModel(std::vector <PartInfo> &modelinfo, int partLists[], const int targetList);

// Draw/obj.cpp
    void CreateList(int listId, const std::vector <Vertex> &v, const std::vector <Triangle> &f);
    void CopyList(int src, int dst);
    // Just basic .obj format is supported for loading (you can look for examples in Draw/Models)
    // In Blender options are: Apply Modifiers, Objects as OBJ Objects,
    // Scale - 1.0 (generating later with 'make config', I think, is better), Path Mode - Auto, Forward - -Z Forward, Up - Y Up
    bool LoadObj(const char *filename, int partNumber, const int listId[], ImageScale &dfl);
    #include "Draw/modelfiles.hpp"

// Draw/model.hpp
    struct Model;

// Draw/compile.cpp
    const int DRAW_CAR_LIST = 1,
              DRAW_LOW_CAR_LIST = 2,
              DRAW_TREE_LIST = 3,
              DRAW_LOW_TREE_LIST = 4,
              INTERNAL_LIST_START = 1000001;
    void ScaleModel(ImageScale scale);
    int GetNewInternalList(void);
    void CompileDefaultDrawCar(void);
    void CompileDrawObj(ModelFilepath modelFiles, ModelInfo &modelinfo, ImageScale &scale,
                        int drawList, void (*CompileDefaultDrawObj) (void));
    void CompileDrawCar(void);
    void CompileDefaultDrawTree(void);
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
#include "Player/Settings/optimization.cpp"
#include "Player/hero.cpp"
#include "play.cpp"
#include "Draw/draw.cpp"
#include "Draw/scaleinfo.cpp"
#include "Draw/modelinfo.cpp"
#include "Draw/obj.cpp"
#include "Draw/compile.cpp"
#include "glut.cpp"
#include "Player/keyboard.cpp"
