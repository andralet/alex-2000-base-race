void Reshape(int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    glViewport(0, 0, width, height);
    if (ENABLE_FOG)
        glFogf(GL_FOG_DENSITY, FOG_DENSITY);
}

void InitGlut(int argc, char *argv[]) {
    glutInit(&argc, argv);
    if (ENABLE_DOUBLE_BUFFER) {
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    }
    else {
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    }
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_NAME);

    glutDisplayFunc(Display);
    glutIdleFunc(Play);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyboardNormalHandler);
    glutSpecialFunc(KeyboardSpecialHandler);
    // no glutMouseFunc

    glutSetCursor(GLUT_CURSOR_NONE); // hiding mouse pointer inside the window

    if (ENABLE_FOG) {
        GLfloat FogColor[4]={FOG_COLOR.r, FOG_COLOR.g, FOG_COLOR.b, 1};
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_EXP2);
        glFogf(GL_FOG_DENSITY, FOG_DENSITY);
        glFogfv(GL_FOG_COLOR, FogColor);
    }

    glEnable(GL_DEPTH_TEST);

    if (INTERPOLATION_ENABLED)
        glShadeModel(GL_SMOOTH); // It is default option, so command added just for reading comfort
    else
        glShadeModel(GL_FLAT);

    CompileDrawCar();
    CompileDrawTree();

	InitKeyboard();
}
