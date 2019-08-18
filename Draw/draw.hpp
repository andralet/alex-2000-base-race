const int BASE_WINDOW_WIDTH = 800,
          BASE_WINDOW_HEIGHT = 600;

const double ROAD_WIDTH_K = 60.0/80.0,
             MOVE_SPEED_K = 1.0/80.0,
             CAR_WIDTH_K = 5.0/80.0,
             LINE_WIDTH_K = 6.0/80.0,
             CAR_HEIGHT_K = 6.0/60.0,

             TREE_HEIGHT_K = 10.0/60.0,
             TREE_RADIUS_K = 2.0/80.0,
             LEAVES_RADIUS_K = 10.0/80.0,
             LEAVES_TREE_CONNECT_SIZE_K = 1.0/80.0,
             TREE_DISTANCE_K = 50.0/80.0,
             TREE_X_K = 80.0 / 80.0,

             PERSPECTIVE_DEPTH_K = 10000.0 / 80.0,
             DRAW_ROAD_DEPTH_K = 1000.0 / 80.0,
             FOG_DENSITY_K = 0.00016 * 800.0,
             LINE_DEPTH_K = 5.0/80.0,
             LINE_SPACE_K = 20.0/80.0,
             EYE_DEPTH_K = -10.0/80.0;

#define                ROAD_WIDTH (              ROAD_WIDTH_K *  WINDOW_WIDTH)
#define                MOVE_SPEED (              MOVE_SPEED_K *  WINDOW_WIDTH)
#define                CAR_WIDTH  (               CAR_WIDTH_K *  WINDOW_WIDTH)
#define                LINE_WIDTH (              LINE_WIDTH_K *  WINDOW_WIDTH)
#define                CAR_HEIGHT (              CAR_HEIGHT_K * WINDOW_HEIGHT)

#define               TREE_HEIGHT (             TREE_HEIGHT_K * WINDOW_HEIGHT)
#define               TREE_RADIUS (             TREE_RADIUS_K *  WINDOW_WIDTH)
#define             LEAVES_RADIUS (           LEAVES_RADIUS_K *  WINDOW_WIDTH)
#define  LEAVES_TREE_CONNECT_SIZE (LEAVES_TREE_CONNECT_SIZE_K *  WINDOW_WIDTH)
#define             TREE_DISTANCE (           TREE_DISTANCE_K *  WINDOW_WIDTH)
#define                    TREE_X (                  TREE_X_K *  WINDOW_WIDTH)

#define         PERSPECTIVE_DEPTH (       PERSPECTIVE_DEPTH_K *  WINDOW_WIDTH)
#define           DRAW_ROAD_DEPTH (         DRAW_ROAD_DEPTH_K *  WINDOW_WIDTH)
#define               FOG_DENSITY (             FOG_DENSITY_K /  WINDOW_WIDTH)
#define                LINE_DEPTH (              LINE_DEPTH_K *  WINDOW_WIDTH)
#define                LINE_SPACE (              LINE_SPACE_K *  WINDOW_WIDTH)
#define                 EYE_DEPTH (               EYE_DEPTH_K *  WINDOW_WIDTH)

const int TREE_SLICES = 10,
          TREE_STACKS = 1,
          LEAVES_SLICES = 20,
          LEAVES_STACKS = 10;
double ENV_START_DEPTH_K = -TREE_DISTANCE_K;
#define ENV_START_DEPTH (ENV_START_DEPTH_K * WINDOW_WIDTH)
#define ENV_MOVE_SPEED (CAR_SPEED / 500.0)


const double SPEED_DRAW_MUL = 10.0;
const int MAX_DRAW_TEXT = 128,
          FONT_SIZE = 24;

const char *WINDOW_NAME = "Race (by alex2000)";
const int HELP_LINES_NUM = 4;
const char *HELP_MESSAGE[HELP_LINES_NUM] = {
    "Use 'A' and 'D' to move,",
    "'ESC' to exit and 'P' to pause game.",
    "You can pause music with 'Q' and switch tracks with 'E'.",
    "Good luck!:)"
};

const double HELP_MESSAGE_SPACE[HELP_LINES_NUM] = {
    24.0 / 4.0 - 0.75,
    36.0 / 4.0 - 1.75,
    56.0 / 4.0 - 1.4,
    12.0 / 4.0 - 0.7
};
