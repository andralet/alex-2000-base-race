void ScaleModel(ImageScale scale) {
    glScalef(scale.x / double(BASE_WINDOW_WIDTH) * WINDOW_WIDTH, scale.y / double(BASE_WINDOW_HEIGHT) * WINDOW_HEIGHT, scale.z / double(BASE_WINDOW_WIDTH) * WINDOW_WIDTH);
}

int GetNewInternalList(void) {
    static int firstFreeList = INTERNAL_LIST_START;
    firstFreeList++;
    return (firstFreeList - 1);
}

void CompileDefaultDrawCar(void) {
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

void CompileDrawObj(ModelFilepath modelFiles, ModelInfo &modelinfo, ImageScale &scale,
                    int drawList, void (*CompileDefaultDrawObj) (void)) {
    int partNumber = 0;
    if (LoadModelinfo(modelFiles.modelinfo, modelinfo, partNumber)) {
        int *loadParts = new int[partNumber];
        for (int i = 0; i < partNumber; i++)
            loadParts[i] = GetNewInternalList();

        if (!LoadObj(modelFiles.obj, partNumber, loadParts, scale) || !LoadScaleInfo(modelFiles.scale, scale))
            CompileDefaultDrawObj();
        else
            CompileModel(modelinfo, loadParts, drawList);

        delete[] loadParts;
    }
    else
        CompileDefaultDrawObj();
}

void CompileDrawCar(void) {
    CompileDrawObj(    CAR_MODEL_FILES,     CAR_MODELINFO,     CAR_SCALE,     DRAW_CAR_LIST, CompileDefaultDrawCar);
    CompileDrawObj(LOW_CAR_MODEL_FILES, LOW_CAR_MODELINFO, LOW_CAR_SCALE, DRAW_LOW_CAR_LIST, CompileDefaultDrawCar);
}

void CompileDefaultDrawTree(void) {
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

void CompileDrawTree(void) {
    CompileDrawObj(    TREE_MODEL_FILES,     TREE_MODELINFO,     TREE_SCALE,     DRAW_TREE_LIST, CompileDefaultDrawTree);
    CompileDrawObj(LOW_TREE_MODEL_FILES, LOW_TREE_MODELINFO, LOW_TREE_SCALE, DRAW_LOW_TREE_LIST, CompileDefaultDrawTree);
}
