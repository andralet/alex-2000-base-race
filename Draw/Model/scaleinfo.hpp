struct ImageScale {
    double x, y, z;
};

ImageScale CAR_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH},
           LOW_CAR_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH},
           TREE_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH},
           LOW_TREE_SCALE = {BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT, BASE_WINDOW_WIDTH};
           
// Scaleinfo file format: 3 %lf numbers (x, y, z) for default window sizevoid UpdateMinMaxCoord(const Vertex &v, Vertex &minCoord, Vertex &maxCoord);
void UpdateMinMaxCoord(const Vertex &v, Vertex &minCoord, Vertex &maxCoord);
bool LoadScaleInfo(const char *filename, ImageScale &scale);
