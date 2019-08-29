void DrawRoad(void) {
    SetColor(BLACK);
    glBegin(GL_QUADS);
    glVertex3f((WINDOW_WIDTH - ROAD_WIDTH) / 2, 0, EYE_DEPTH);
    glVertex3f((WINDOW_WIDTH - ROAD_WIDTH) / 2, 0, PERSPECTIVE_DEPTH);
    glVertex3f((WINDOW_WIDTH + ROAD_WIDTH) / 2, 0, PERSPECTIVE_DEPTH);
    glVertex3f((WINDOW_WIDTH + ROAD_WIDTH) / 2, 0, EYE_DEPTH);
    glEnd();
    SetColor(WHITE);
    glBegin(GL_LINES);
    for (int i = 1; i < ROAD_WIDTH / LINE_WIDTH; i++)
        for (int j = 0; ENV_START_DEPTH + j * (LINE_DEPTH + LINE_SPACE) <= 2 * DRAW_ROAD_DEPTH; j++)
            if (i != int(ROAD_WIDTH / LINE_WIDTH) / 2) {
                glVertex3f((WINDOW_WIDTH - ROAD_WIDTH) / 2 + i * LINE_WIDTH, SMALL_COORD, ENV_START_DEPTH + j * (LINE_DEPTH + LINE_SPACE));
                glVertex3f((WINDOW_WIDTH - ROAD_WIDTH) / 2 + i * LINE_WIDTH, SMALL_COORD, ENV_START_DEPTH + j * (LINE_DEPTH + LINE_SPACE) + LINE_DEPTH);
            }
    glVertex3f(WINDOW_WIDTH / 2, SMALL_COORD, EYE_DEPTH);
    glVertex3f(WINDOW_WIDTH / 2, SMALL_COORD, PERSPECTIVE_DEPTH);
    glEnd();
}

void DrawTrees(void) {
    for (double depth = 2 * DRAW_ROAD_DEPTH + ENV_START_DEPTH; depth >= -2 * TREE_DISTANCE; depth -= TREE_DISTANCE) {
        DrawTree(TREE_X, depth);
        DrawTree(WINDOW_WIDTH - TREE_X, depth);
    }
}

void DrawGround(void) {
    if (ENABLE_FOG)
        glDisable(GL_FOG);
    SetColor(GROUND_COLOR);
    glBegin(GL_QUADS);
    glVertex3f(-INF_COORD, -SMALL_COORD, EYE_DEPTH);
    glVertex3f(-INF_COORD, -SMALL_COORD, PERSPECTIVE_DEPTH);
    glVertex3f( INF_COORD, -SMALL_COORD, PERSPECTIVE_DEPTH);
    glVertex3f( INF_COORD, -SMALL_COORD, EYE_DEPTH);
    glEnd();
    if (ENABLE_FOG)
        glEnable(GL_FOG);
}

void DrawHelp(Color textColor, double startY) {
    for (int i = 0; i < HELP_LINES_NUM; i++) {
        DrawText(WINDOW_WIDTH / 2 - HELP_MESSAGE_SPACE[i] * FONT_SIZE, startY - i * FONT_SIZE,
                 HELP_MESSAGE[i], textColor);
    }
}

void DrawHUD(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    char printText[MAX_DRAW_TEXT];
    sprintf(printText, "Score: %d", score);
    DrawText(0, WINDOW_HEIGHT - FONT_SIZE, printText, LIGHT_RED);
    sprintf(printText, "Speed: %.1lf kmph", CAR_SPEED * SPEED_DRAW_MUL);
    DrawText(0, WINDOW_HEIGHT - 2 * FONT_SIZE, printText, LIGHT_RED);
    if (SHOW_FPS) {
        REDRAWS_PER_SEC++;
        if (time(NULL) != LAST_TIME) {
            if (!WAS_PAUSED) {
                OLD_FPS = REDRAWS_PER_SEC;
            }
            if (!PAUSED)
                WAS_PAUSED = 0;
            REDRAWS_PER_SEC = 0;
            LAST_TIME = time(NULL);
        }
        if (ENABLE_FPS_LIMIT)
            sprintf(printText, "FPS: %d (%s)", OLD_FPS, ((FPS_TARGET_REACHED) ? "Target" : "Low"));
        else
            sprintf(printText, "FPS: %d", OLD_FPS);
        DrawText(0, WINDOW_HEIGHT - 3 * FONT_SIZE, printText, LIGHT_RED);
    }

    if (CRASHED) {
        sprintf(printText, "CRASHED");
        DrawText(WINDOW_WIDTH / 2 - 2.25 * FONT_SIZE, WINDOW_HEIGHT / 2, printText, LIGHT_RED);
        DrawHelp(RED, WINDOW_HEIGHT / 2.0 - FONT_SIZE);
    }
    else if (PAUSED) {
        sprintf(printText, "PAUSED");
        DrawText(WINDOW_WIDTH / 2 - 4 * FONT_SIZE / 2, WINDOW_HEIGHT / 2, printText, WHITE);
        DrawHelp(GRAY, WINDOW_HEIGHT / 2.0 - FONT_SIZE);
    }
}

void DrawCar(int x, int depth, Color carColor, Color lineColor, bool isPlayer) {
    double xCenter = (WINDOW_WIDTH + ROAD_WIDTH) / 2 - x;
    double drawDepth = double(depth + CAR_DEPTH / 2.0) / ROAD_DEPTH * DRAW_ROAD_DEPTH;
    SetColor(carColor);
    //PushColor(carColor);
    glPushMatrix();
    glTranslatef(xCenter, 0.0, drawDepth);
    if (!isPlayer)
        glRotatef(180.0, 0.0, 1.0, 0.0);
    if (depth < LOW_CAR_DEPTH) {
        ScaleModel(CAR_SCALE);
        glCallList(DRAW_CAR_LIST);
    }
    else {
        ScaleModel(LOW_CAR_SCALE);
        glCallList(DRAW_LOW_CAR_LIST);
    }

    //SetColor(lineColor);
    //glCallList(DRAW_CAR_LINES_LIST);
    glPopMatrix();
}

void DrawTree(int x, int depth) {
    glPushMatrix();
    glTranslatef(x, 0, depth);
    if (depth < LOW_TREE_DEPTH) {
        ScaleModel(TREE_SCALE);
        glCallList(DRAW_TREE_LIST);
    }
    else {
        ScaleModel(LOW_TREE_SCALE);
        glCallList(DRAW_LOW_TREE_LIST);
    }
    glPopMatrix();
}

void DrawText(int x, int y, const char *text, Color textColor) {
    SetColor(textColor);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void Display(void) {
    glClearColor(SKY_COLOR.r, SKY_COLOR.g, SKY_COLOR.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, double(WINDOW_WIDTH) / double(WINDOW_HEIGHT),
                   1.0, PERSPECTIVE_DEPTH);
    // Be careful: X axis is inverted now!

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt((WINDOW_WIDTH + ROAD_WIDTH) / 2.0 - hero.GetX() * WINDOW_WIDTH, EYE_HEIGHT, EYE_DEPTH,
              (WINDOW_WIDTH + ROAD_WIDTH) / 2.0 - hero.GetX() * WINDOW_WIDTH, EYE_HEIGHT, EYE_DEPTH + SMALL_COORD,
              0, 1, 0);

    glDisable(GL_DEPTH_TEST);
    DrawGround();
    DrawRoad();
    glEnable(GL_DEPTH_TEST);
    DrawTrees();

    for (int i = enemyEnd - 1; i >= 0; i--)
        enemy[i].Draw();
    hero.Draw();

    DrawHUD();

    if (ENABLE_DOUBLE_BUFFER)
        glutSwapBuffers();
    glFinish();
}
