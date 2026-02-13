#pragma once

inline bool g_Running = 1;

void reset_termios();
void signal_handler();

class TuiConfig {
public:
    TuiConfig();
};
