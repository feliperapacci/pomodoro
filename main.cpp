#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

#include "inputs.h"
#include "fonts.h"
#include "tui.h"


const int INTERVAL_TIME = 1;
std::string g_time_text;  // stores time to be printed in hh::mm:ss format

int main() {
    
    // SETUP TUI
    TuiConfig tuicfg;

    // SELECT WORK TIME

    // auto selector = std::chrono::seconds(0);
    Keys key; 
    TimeSelector selector {};
    std::cout << "\033[2J"; // clears screen
    while (1) {
        duration_to_string(std::chrono::seconds(selector.getSeconds()), g_time_text);
        print_digital_clock(g_time_text); 

        key = read_key();
        switch (key) {
            case Keys::Up:
                selector.increase();
                continue;
            case Keys::Down:
                selector.decrease();
                continue;
            case Keys::Left:
                selector.move_left();
                continue;
            case Keys::Right:
                selector.move_right();
                continue;
            case Keys::Enter:
                break;
            default:
                continue;
        }

        break;
    }
    

    // now & end are of type std::chrono::time_point<std::chrono::steady_clock>
    auto now = std::chrono::steady_clock::now();
    auto end = now + std::chrono::seconds{ selector.getSeconds() };

    // interval & time_remaining are of type std::chrono::duration<...>
    auto interval = std::chrono::seconds{ INTERVAL_TIME };
    auto time_remaining = end - now;


    while (time_remaining.count() >= 1){
        time_remaining = end - now;
        duration_to_string(time_remaining, g_time_text);

        print_digital_clock(g_time_text);
        // std::endl necessary to flush cout to stdout
        std::cout << std::endl; 
        std::this_thread::sleep_until(now += interval);
    }    

    std::cout << "Done!\a\a\a\a\n";
}

