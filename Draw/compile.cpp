void ScaleModel(ImageScale scale) {
    glScalef(scale.x / double(BASE_WINDOW_WIDTH) * WINDOW_WIDTH, scale.y / double(BASE_WINDOW_HEIGHT) * WINDOW_HEIGHT, scale.z / double(BASE_WINDOW_WIDTH) * WINDOW_WIDTH);
}

int GetNewInternalList(void) {
    static int firstFreeList = INTERNAL_LIST_START;
    firstFreeList++;
    return (firstFreeList - 1);
}

void CompileDrawCar(void) {
    const int LOAD_PART_NUMBER = 3;
    int LOAD_PARTS[LOAD_PART_NUMBER] = {};
    int LOAD_PARTS_LOW[LOAD_PART_NUMBER] = {};
    const Color LOAD_PART_COLORS[LOAD_PART_NUMBER] = {NO_COLOR_CHANGE, DARK_GRAY, BLACK};
    for (int i = 0; i < LOAD_PART_NUMBER; i++) {
        LOAD_PARTS[i] = GetNewInternalList();
        LOAD_PARTS_LOW[i] = GetNewInternalList();
    }

    if (!LoadObj(CAR_OBJ_FILEPATH, LOAD_PART_NUMBER, LOAD_PARTS, CAR_SCALE) || !LoadScaleInfo(CAR_SCALE_FILEPATH, CAR_SCALE) ||
        !LoadObj(LOW_CAR_OBJ_FILEPATH, LOAD_PART_NUMBER, LOAD_PARTS_LOW, LOW_CAR_SCALE) || !LoadScaleInfo(LOW_CAR_SCALE_FILEPATH, LOW_CAR_SCALE)) {
        double xLeft  = -CAR_WIDTH_K / 2,
               xRight = CAR_WIDTH_K / 2;
        double drawCloseDepth = double(-CAR_DEPTH) / 2.0 / ROAD_DEPTH * DRAW_ROAD_DEPTH_K;
        double drawFarDepth = double(CAR_DEPTH) / 2.0 / ROAD_DEPTH * DRAW_ROAD_DEPTH_K;
        glNewList(DRAW_CAR_LIST, GL_COMPILE); {
            glBegin(GL_QUAD_STRIP);
            glVertex3f(xLeft, 0, drawCloseDepth);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xRight, 0, drawCloseDepth);
            glVertex3f(xRight, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xRight, 0, drawFarDepth);
            glVertex3f(xRight, CAR_HEIGHT_K, drawFarDepth);
            glVertex3f(xLeft, 0, drawFarDepth);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawFarDepth);
            glVertex3f(xLeft, 0, drawCloseDepth);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawCloseDepth);
            glEnd();
            glBegin(GL_QUADS);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xRight, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xRight, CAR_HEIGHT_K, drawFarDepth);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawFarDepth);
            glEnd();
        } glEndList();
        /*glNewList(DRAW_CAR_LINES_LIST, GL_COMPILE); {
            glBegin(GL_LINE_STRIP);
            glVertex3f(xLeft, 0, drawCloseDepth);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xRight, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xRight, 0, drawCloseDepth);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xLeft, CAR_HEIGHT_K, drawFarDepth);
            glVertex3f(xRight, CAR_HEIGHT_K, drawCloseDepth);
            glVertex3f(xRight, CAR_HEIGHT_K, drawFarDepth);
            glEnd();
        } glEndList();*/
        CAR_SCALE.x = BASE_WINDOW_WIDTH;
        CAR_SCALE.y = BASE_WINDOW_HEIGHT;
        CAR_SCALE.z = BASE_WINDOW_WIDTH;
    }
    else {
        glNewList(DRAW_CAR_LIST, GL_COMPILE); {
            for (int i = 0; i < LOAD_PART_NUMBER; i++) {
                SetColor(LOAD_PART_COLORS[i]);
                glCallList(LOAD_PARTS[i]);
            }
        } glEndList();
        glNewList(DRAW_LOW_CAR_LIST, GL_COMPILE); {
            for (int i = 0; i < LOAD_PART_NUMBER; i++) {
                SetColor(LOAD_PART_COLORS[i]);
                glCallList(LOAD_PARTS_LOW[i]);
            }
        } glEndList();
    }
}

void CompileDrawTree(void) {
    const int LOAD_PART_NUMBER = 2;
    int LOAD_PARTS[LOAD_PART_NUMBER] = {};
    int LOAD_PARTS_LOW[LOAD_PART_NUMBER] = {};
    const Color LOAD_PART_COLORS[LOAD_PART_NUMBER] = {TREE_COLOR, LEAVES_COLOR};
    for (int i = 0; i < LOAD_PART_NUMBER; i++) {
        LOAD_PARTS[i] = GetNewInternalList();
        LOAD_PARTS_LOW[i] = GetNewInternalList();
    }

    if (!LoadObj(TREE_OBJ_FILEPATH, LOAD_PART_NUMBER, LOAD_PARTS, TREE_SCALE) || !LoadScaleInfo(TREE_SCALE_FILEPATH, TREE_SCALE) ||
        !LoadObj(LOW_TREE_OBJ_FILEPATH, LOAD_PART_NUMBER, LOAD_PARTS_LOW, LOW_TREE_SCALE) || !LoadScaleInfo(LOW_TREE_SCALE_FILEPATH, LOW_TREE_SCALE)) {
        GLUquadricObj *tree = gluNewQuadric();
        glNewList(DRAW_TREE_LIST, GL_COMPILE); {
            SetColor(TREE_COLOR);
            glTranslatef(0.0, TREE_HEIGHT_K, 0.0);
            glRotatef(90.0, 1.0, 0.0, 0.0);
            gluCylinder(tree, TREE_RADIUS_K, TREE_RADIUS_K, TREE_HEIGHT_K, TREE_SLICES, TREE_STACKS);

            SetColor(LEAVES_COLOR);
            glTranslatef(0.0, 0.0, - (LEAVES_RADIUS_K - LEAVES_TREE_CONNECT_SIZE_K)); // in rotated matrix coordinates
            gluSphere(tree, LEAVES_RADIUS_K, LEAVES_SLICES, LEAVES_STACKS);
        } glEndList();
        glNewList(DRAW_LOW_TREE_LIST, GL_COMPILE); {
            glCallList(DRAW_TREE_LIST);
        } glEndList();
        LOW_TREE_SCALE.x = TREE_SCALE.x = BASE_WINDOW_WIDTH;
        LOW_TREE_SCALE.y = TREE_SCALE.y = BASE_WINDOW_HEIGHT;
        LOW_TREE_SCALE.z = TREE_SCALE.z = BASE_WINDOW_WIDTH;
    }
    else {
        glNewList(DRAW_TREE_LIST, GL_COMPILE); {
            for (int i = 0; i < LOAD_PART_NUMBER; i++) {
                SetColor(LOAD_PART_COLORS[i]);
                glCallList(LOAD_PARTS[i]);
            }
        } glEndList();
        glNewList(DRAW_LOW_TREE_LIST, GL_COMPILE); {
            for (int i = 0; i < LOAD_PART_NUMBER; i++) {
                SetColor(LOAD_PART_COLORS[i]);
                glCallList(LOAD_PARTS_LOW[i]);
            }
        } glEndList();
    }
}
