#pragma once

enum class Keys {
    Up,
    Down,
    Left,
    Right,
    Enter,
    Space,
    R,
    Invalid
};

Keys read_key();


class TimeSelector {
    public:
        void increase();
        void decrease();
        void move_right();
        void move_left();
        int getSeconds();
        int getField();

    private:
        int seconds {};
        int time_field {};        // 0 = Seconds, 1 = minutes, 2 = hours
};
