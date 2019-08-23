struct Vertex {
    double x, y, z;
};

struct Triangle {
    int vertex[3]; // vertex id
};

const int MAX_OBJ_CMD_SIZE = 256;
const double INF_COORD = 1e9,
             DFL_WIDTH = 100.0,
             DFL_HEIGHT = 100.0,
             DFL_DEPTH = 100.0;
