struct Color {
    float r, g, b;
};
#include "colors.hpp"// list of some useful colors
const Color NO_COLOR_CHANGE = {-1.0, -1.0, -1.0};
const Color SKY_COLOR    = { 89.0 / 256.0, 181.0 / 256.0, 210.0 / 256.0},
            GROUND_COLOR = GREEN,
            TREE_COLOR   = {195.0 / 256.0, 115.0 / 256.0,  11.0 / 256.0},
            LEAVES_COLOR = DARK_GREEN;
/*std::vector <Color> COLOR_STACK;
int COLOR_STACK_SIZE = 0;*/
