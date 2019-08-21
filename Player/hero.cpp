class Hero {
   private:
    double x;
   public:
    Hero(void):
        x(double(ROAD_WIDTH) / 2.0 / double(WINDOW_WIDTH))
        {}

    void Move(Key key) {
        if (HasUsage(key, KEY_LEFT) && x >= (MOVE_SPEED + CAR_WIDTH / 2) / WINDOW_WIDTH)
            x -= MOVE_SPEED / WINDOW_WIDTH;
        else if (HasUsage(key, KEY_RIGHT) && x <= double(ROAD_WIDTH - (MOVE_SPEED + CAR_WIDTH / 2)) / WINDOW_WIDTH)
            x += MOVE_SPEED / WINDOW_WIDTH;
    }

    void Draw(void) {
        DrawCar(x * WINDOW_WIDTH, 0, HERO_COLOR, HERO_LINE_COLOR, 1);
    }

    inline double GetX(void) const {
        return x;
    }
} hero;

inline bool CanMoveHero(void) {
    return (!PAUSED && !CRASHED && MOVE_AVIABLE);
}
