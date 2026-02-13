#include <unistd.h>
#include <termios.h>
#include <cstdlib>
#include <csignal>

#include "tui.h"

termios g_orig_termios; 

void reset_termios() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig_termios);
}
void signal_handler(int sig) {
    g_Running = 0;
    std::exit(1);
}
                
TuiConfig::TuiConfig() {
    // COPIES ORIGINAL TERMIOS TO GLOBAL OBJ
    tcgetattr(STDIN_FILENO, &g_orig_termios);

    // HANLDING EARLY EXITS AND UNEXPECTED TERMINATIONS
    std::atexit(reset_termios);
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGSEGV, signal_handler);

    // Configuring terminal
    termios raw_termios = g_orig_termios;
    raw_termios.c_lflag &= ~(ECHO | ICANON /*| ISIG */ );
    raw_termios.c_cc[VMIN] = 1;
    raw_termios.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
}

