const char *OPTIMIZATION_FILE = "Player/Settings/settings.txt";

enum OPTION_TYPE {BOOLEAN, DOUBLE, INTEGER};

struct OptionDescription {
    const char *name;
    OPTION_TYPE type;
    void *data;
};

const int OPTION_NUMBER = 6,
          MAX_OPTION_NAME = 256;

bool ENABLE_DOUBLE_BUFFER = 1,
     ENABLE_FOG = 1,
     ENABLE_FPS_LIMIT = 1, // if you fps isn't too high, you can set this option false.
     SHOW_FPS = 1; // can give a minor speed up if disabled

double LOW_TREE_DEPTH_K = 1000.0/80.0,
       LOW_CAR_DEPTH_K  = 1000.0/80.0;

#define            LOW_TREE_DEPTH (          LOW_TREE_DEPTH_K *  WINDOW_WIDTH)
#define             LOW_CAR_DEPTH (          LOW_CAR_DEPTH_K *  WINDOW_WIDTH)

// Options' names must be without spaces
const OptionDescription OPTION_LIST[OPTION_NUMBER] = {
    { "DoubleBuffer", BOOLEAN, &ENABLE_DOUBLE_BUFFER},
    {          "Fog", BOOLEAN, &ENABLE_FOG},
    {  "SetFpsLimit", BOOLEAN, &ENABLE_FPS_LIMIT},
    {      "ShowFps", BOOLEAN, &SHOW_FPS},
    {"LowTreeDepthK",  DOUBLE, &LOW_TREE_DEPTH_K},
    { "LowCarDepthK",  DOUBLE, &LOW_CAR_DEPTH_K}
};
