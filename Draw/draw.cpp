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
        for (int j = 0; ENV_START_DEPTH + j * (LINE_DEPTH + LINE_SPACE) <= 2 * DRAW_ROAD_DEPTH; j++) {
            glVertex3f((WINDOW_WIDTH - ROAD_WIDTH) / 2 + i * LINE_WIDTH, 0, ENV_START_DEPTH + j * (LINE_DEPTH + LINE_SPACE));
            glVertex3f((WINDOW_WIDTH - ROAD_WIDTH) / 2 + i * LINE_WIDTH, 0, ENV_START_DEPTH + j * (LINE_DEPTH + LINE_SPACE) + LINE_DEPTH);
        }
    glVertex3f(WINDOW_WIDTH / 2, 0, EYE_DEPTH);
    glVertex3f(WINDOW_WIDTH / 2, 0, PERSPECTIVE_DEPTH);
    glEnd();

    // DEBUG
    //for (double depth = -2 * TREE_DISTANCE; depth <= 2 * DRAW_ROAD_DEPTH + ENV_START_DEPTH; depth += TREE_DISTANCE) {
    for (double depth = 2 * DRAW_ROAD_DEPTH + ENV_START_DEPTH; depth >= -2 * TREE_DISTANCE; depth -= TREE_DISTANCE) {
        DrawTree(TREE_X, depth);
        DrawTree(WINDOW_WIDTH - TREE_X, depth);
    }
}

void DrawSky(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    SetColor(SKY_COLOR);
    glBegin(GL_QUADS);
    glVertex2f(           0, 0.5 * WINDOW_HEIGHT);
    glVertex2f(           0,       WINDOW_HEIGHT);
    glVertex2f(WINDOW_WIDTH,       WINDOW_HEIGHT);
    glVertex2f(WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT);
    glEnd();
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
    sprintf(printText, "FPS: %d", OLD_FPS);
    DrawText(0, WINDOW_HEIGHT - 3 * FONT_SIZE, printText, LIGHT_RED);
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
    // xLeft and xRight fixed to use with gluPerspective
    double xLeft = (WINDOW_WIDTH + ROAD_WIDTH - CAR_WIDTH) / 2 - x;
    double drawDepth = double(depth + CAR_DEPTH / 2.0) / ROAD_DEPTH * DRAW_ROAD_DEPTH;
    SetColor(carColor);
    glPushMatrix();
    glTranslatef(xLeft + CAR_WIDTH / 2.0, 0.0, drawDepth);
    if (!isPlayer)
        glRotatef(180.0, 0.0, 1.0, 0.0);
    //glScalef(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH);
    glScalef(CAR_SCALE.x / double(BASE_WINDOW_WIDTH) * WINDOW_WIDTH, CAR_SCALE.y / double(BASE_WINDOW_HEIGHT) * WINDOW_HEIGHT, CAR_SCALE.z / double(BASE_WINDOW_WIDTH) * WINDOW_WIDTH); // because of rotation
    glCallList(DRAW_CAR_BODY_LIST);

    //SetColor(lineColor);
    //glCallList(DRAW_CAR_LINES_LIST);
    glPopMatrix();
}

void DrawTree(int x, int depth) {
    glPushMatrix();
    glTranslatef(x, 0, depth);
    //glScalef(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH);
    glScalef(TREE_SCALE, TREE_SCALE, TREE_SCALE);
    SetColor(TREE_COLOR);
    glCallList(3);
    SetColor(LEAVES_COLOR);
    glCallList(4);
    glPopMatrix();
}

void DrawText(int x, int y, const char *text, Color textColor) {
    SetColor(textColor);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void Display(void) {
    glClearColor(0, 0.75, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawSky();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0, width, 0, height, -1.0, 1000.0);
    gluPerspective(120.0, double(WINDOW_WIDTH) / double(WINDOW_HEIGHT),
                   1.0, PERSPECTIVE_DEPTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt((WINDOW_WIDTH + ROAD_WIDTH) / 2.0 - hero.GetX() * WINDOW_WIDTH, 2 * CAR_HEIGHT, EYE_DEPTH,
              (WINDOW_WIDTH + ROAD_WIDTH) / 2.0 - hero.GetX() * WINDOW_WIDTH, 2 * CAR_HEIGHT, 10.0,
              0, 1, 0);

    // EXPERIMENTAL. Doesn't work yet:(
    // glDepthRange(0, PERSPECTIVE_DEPTH);

    DrawRoad();
    int i = enemyEnd - 1;
    while (i >= 0 && enemy[i].GetDepth() > 0) { // it's not the best way, but for some time
        enemy[i].Draw();
        i--;
    }
    hero.Draw();
    while (i >= 0) {
        enemy[i].Draw();
        i--;
    }

    DrawHUD();

    glutSwapBuffers();
    glFinish();
}
