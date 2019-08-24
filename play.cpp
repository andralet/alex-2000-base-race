class Car {
   private:
    double x, depth;
   public:
    Car(void):
        x(double((rand() % (int((ROAD_WIDTH - CAR_WIDTH) / LINE_WIDTH) + 1)) * LINE_WIDTH + LINE_WIDTH / 2.0) / double(WINDOW_WIDTH)),
        depth(ROAD_DEPTH - CAR_DEPTH)
        {}

    void ReInit(void) {
        x = double((rand() % (int((ROAD_WIDTH - CAR_WIDTH) / LINE_WIDTH) + 1)) * LINE_WIDTH + LINE_WIDTH / 2.0) / double(WINDOW_WIDTH);
        depth = ROAD_DEPTH - CAR_DEPTH;
    }

    void Move(void) {
        if (depth >= -CAR_DEPTH) {
            depth -= CAR_SPEED; // * GetScale(depth);
            if (depth < -CAR_DEPTH)
                score++;
        }
    }

    void Draw(void) {
        if (depth >= -CAR_DEPTH)
            DrawCar(x * WINDOW_WIDTH, depth, ENEMY_COLOR, ENEMY_LINE_COLOR);
    }

    bool isDangerous(void) {
        return (depth >= -CAR_DEPTH);
    }

    inline double GetX(void) const {
        return x;
    }

    inline double GetDepth(void) const {
        return depth;
    }

    bool Bumps(const Hero &hero) {
        return (depth >= -CAR_DEPTH && depth <= CAR_DEPTH &&
                x + CAR_WIDTH_K / 2.0 >= hero.GetX() - CAR_WIDTH_K / 2.0 &&
                x - CAR_WIDTH_K / 2.0 <= hero.GetX() + CAR_WIDTH_K / 2.0);
    }

    bool Bumps(const Car &car) {
        return (car.GetDepth() - depth >= -CAR_DEPTH && car.GetDepth() - depth <= CAR_DEPTH &&
                x + CAR_WIDTH_K / 2.0 >= car.GetX() - CAR_WIDTH_K / 2.0 &&
                x - CAR_WIDTH_K / 2.0 <= car.GetX() + CAR_WIDTH_K / 2.0);
    }
} enemy[MAX_ENEMY];

void FreeCarSpace(void) {
    int firstDangerous = 0;
    while (firstDangerous < enemyEnd && !enemy[firstDangerous].isDangerous())
        firstDangerous++;
    for (int i = 0; i + firstDangerous < enemyEnd; i++)
        enemy[i] = enemy[i + firstDangerous];
    enemyEnd -= firstDangerous;
}

void AddCar(void) {
    if (enemyEnd > MAX_ENEMY)
        FreeCarSpace();
    if (enemyEnd <= MAX_ENEMY) {
        bool isBump = 0;
        int notCycleProgramCounter = ENEMY_CREATE_UNSUCCESSFUL_CYCLE_LIMIT;
        do {
            enemy[enemyEnd].ReInit();
            isBump = 0;
            for (int i = enemyEnd - 1; i >= 0 && enemy[i].GetDepth() + CAR_DEPTH >= ROAD_DEPTH - CAR_DEPTH; i--)
                if (enemy[enemyEnd].Bumps(enemy[i])) {
                    isBump = 1;
                    break;
                }
            notCycleProgramCounter--;
        } while (isBump && notCycleProgramCounter > 0);
        if (!isBump) // <=> notCicleProgramCounter > 0
            enemyEnd++;
    }
}

inline bool CanPlay(void) {
    return (!PAUSED && !CRASHED);
}

void Play(void) {
    if (ENABLE_FPS_LIMIT) {
        double targetFpsTime = 1.0 / TARGET_FPS;
        double sleepTimeSec = targetFpsTime - (double(clock() - LAST_PLAY) / double(CLOCKS_PER_SEC));
        if (sleepTimeSec > 0) {
            FPS_TARGET_REACHED = 1;
            usleep(USEC_IN_SEC * sleepTimeSec);
        }
        else
            FPS_TARGET_REACHED = 0;
        LAST_PLAY = clock();
    }

    if (CanPlay()) {
        if (double(rand() % RAND_PARTS + 1) / double(RAND_PARTS) <= CAR_CHANCE) {
            AddCar();
        }
        for (int i = enemyEnd - 1; i >= 0; i--) {
            enemy[i].Move();
            if (enemy[i].Bumps(hero)) {
                CRASHED = 1;
                glutPostRedisplay();
                return;
            }
        }
        CAR_CHANCE += CHANCE_ADD;
        CAR_SPEED += SPEED_ADD;
        ENV_START_DEPTH_K -= ENV_MOVE_SPEED;
        while (ENV_START_DEPTH_K <= -2 * TREE_DISTANCE_K)
            ENV_START_DEPTH_K += TREE_DISTANCE_K;
        MOVE_AVIABLE = 1;
        glutPostRedisplay();
    }
};
