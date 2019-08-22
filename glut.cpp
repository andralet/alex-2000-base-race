void Reshape(int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    glViewport(0, 0, width, height);
    glFogf(GL_FOG_DENSITY, FOG_DENSITY);
}

void InitGlut(int argc, char *argv[]) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_NAME);

    glutDisplayFunc(Display);
    glutIdleFunc(Play);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyboardNormalHandler);
    glutSpecialFunc(KeyboardSpecialHandler);
    // no glutMouseFunc

    glutSetCursor(GLUT_CURSOR_NONE); // hiding mouse pointer inside the window

    GLfloat FogColor[4]={0.5, 0.5, 0.5, 1};
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, FOG_DENSITY);
    glFogfv(GL_FOG_COLOR, FogColor);

    glEnable(GL_DEPTH_TEST);

    CompileDrawCar();
    CompileDrawTree();

	InitKeyboard();
}
