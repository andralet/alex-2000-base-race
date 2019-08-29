// Model file format:
// First string: <Number of parts>
// Other strings: <Number of displayed part from zero> <Color (r, g, b from 0.0 to 1.0)>
// Can be generated with 'make config-models' or 'make-autoconfig'

struct PartInfo {
    int id;
    Color color;
};

typedef std::vector <PartInfo> ModelInfo;

ModelInfo CAR_MODELINFO = {{0, NO_COLOR_CHANGE}, {1, DARK_GRAY}, {2, BLACK}},
          LOW_CAR_MODELINFO = {{0, NO_COLOR_CHANGE}, {1, DARK_GRAY}, {2, BLACK}},
          TREE_MODELINFO = {{0, TREE_COLOR}, {1, LEAVES_COLOR}},
          LOW_TREE_MODELINFO = {{0, TREE_COLOR}, {1, LEAVES_COLOR}};
