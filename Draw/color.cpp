bool IsEqual(const Color &a, const Color &b) {
    return (a.r == b.r && a.g == b.g && a.b == b.b);
}

void SetColor(const Color &color) {
    if (!IsEqual(color, NO_COLOR_CHANGE))
        glColor3f(color.r, color.g, color.b);
}

// Not using for now, but it may be useful in the future
/*void PushColor(const Color &color) {
    if (COLOR_STACK.size() > COLOR_STACK_SIZE)
        COLOR_STACK[COLOR_STACK_SIZE] = color;
    else
        COLOR_STACK.push_back(color);
    COLOR_STACK_SIZE++;
    fprintf(stderr, "%d\n", COLOR_STACK_SIZE);
}

Color PopColor(void) {
    if (COLOR_STACK_SIZE > 0) {
        COLOR_STACK_SIZE--;
        return COLOR_STACK[COLOR_STACK_SIZE];
    }
    // else (stack is empty)
    return BLACK;
}*/
