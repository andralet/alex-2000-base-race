void Reshape(int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    glViewport(0, 0, width, height);
    glFogf(GL_FOG_DENSITY, FOG_DENSITY);
    // EXPERIMENTAL. Don't work yet:(
    // glDepthRange(0, PERSPECTIVE_DEPTH);
}

void CompileDrawCar(void) {
    double xLeft  = 0,
           xRight = CAR_WIDTH_K;
    double drawCloseDepth = 0;
    double drawFarDepth = double(CAR_DEPTH) / ROAD_DEPTH * DRAW_ROAD_DEPTH_K;
    glNewList(DRAW_CAR_BODY_LIST, GL_COMPILE); {
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
    glNewList(DRAW_CAR_LINES_LIST, GL_COMPILE); {
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
    } glEndList();
}

void CompileDrawTree(void) {
    GLUquadricObj *tree = gluNewQuadric();
    glNewList(DRAW_TREE_LIST, GL_COMPILE); {
        SetColor(TREE_COLOR);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(tree, TREE_RADIUS_K, TREE_RADIUS_K, TREE_HEIGHT_K, TREE_SLICES, TREE_STACKS);

        SetColor(LEAVES_COLOR);
        glTranslatef(0.0, 0.0, - (LEAVES_RADIUS_K - LEAVES_TREE_CONNECT_SIZE_K)); // in rotated matrix coordinates
        gluSphere(tree, LEAVES_RADIUS_K, LEAVES_SLICES, LEAVES_STACKS);
    } glEndList();
}

void InitGlut(int argc, char *argv[]) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // But Z-buffer don't work. I don't know why :(
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_NAME);

    glutDisplayFunc(Display);
    glutIdleFunc(Play);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyboardNormalHandler);
    glutSpecialFunc(KeyboardSpecialHandler);
    // no glutMouseFunc

    glutSetCursor(GLUT_CURSOR_NONE);

    GLfloat FogColor[4]={0.5, 0.5, 0.5, 1};
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, FOG_DENSITY);
    glFogfv(GL_FOG_COLOR, FogColor);
    CompileDrawCar();
    CompileDrawTree();

	InitKeyboard();
}
