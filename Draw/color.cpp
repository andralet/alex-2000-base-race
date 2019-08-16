struct Color {
    float r, g, b;
};

const Color DARK_GREEN  = {   0, 0.25,    0},
            GREEN       = {   0, 0.75,    0},
            LIGHT_GREEN = {   0,    1,    0},
            DARK_RED    = {0.25,    0,    0},
            RED         = {0.75,    0,    0},
            LIGHT_RED   = {   1,    0,    0},
            DARK_BLUE   = {   0,    0, 0.25},
            BLUE        = {   0,    0, 0.75},
            LIGHT_BLUE  = {   0,    0,    1},
            BLACK       = {   0,    0,    0},
            WHITE       = {   1,    1,    1},
            DARK_GRAY   = {0.25, 0.25, 0.25},
            GRAY        = { 0.5,  0.5,  0.5},
            LIGHT_GRAY  = {0.75, 0.75, 0.75};

const Color SKY_COLOR    = { 89.0 / 256.0, 181.0 / 256.0, 210.0 / 256.0},
            TREE_COLOR   = {195.0 / 256.0, 115.0 / 256.0,  11.0 / 256.0},
            LEAVES_COLOR = DARK_GREEN;

inline void SetColor(const Color &color) {
    glColor3f(color.r, color.g, color.b);
}
