#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <array>
#include <unordered_map>


const int INTERVAL_TIME = 1;
const int FONT_DIMENSION = 5;   // 5x5
const std::array<std::array<std::string, 5>, 11> SYMBOLS {{
    // 5x5 ascii arts of each character in a digital clock [0-9:]

    // 0
    {
        " ███ ",
        "█   █",
        "█   █",
        "█   █",
        " ███ "
    },
    // 1
    {
        "  █  ",
        " ██  ",
        "  █  ",
        "  █  ",
        " ███ "
    },
    // 2
    {
        " ███ ",
        "█   █",
        "   █ ",
        "  █  ",
        "█████"
    },
    // 3
    {
        "████ ",
        "    █",
        " ███ ",
        "    █",
        "████ "
    },
    // 4
    {
        "█   █",
        "█   █",
        "█████",
        "    █",
        "    █"
    },
    // 5
    {
        "█████",
        "█    ",
        "████ ",
        "    █",
        "████ "
    },
    // 6
    {
        " ███ ",
        "█    ",
        "████ ",
        "█   █",
        " ███ "
    },
    // 7
    {
        "█████",
        "    █",
        "   █ ",
        "  █  ",
        "  █  "
    },
    // 8
    {
        " ███ ",
        "█   █",
        " ███ ",
        "█   █",
        " ███ "
    },
    // 9
    {
        " ███ ",
        "█   █",
        " ████",
        "    █",
        " ███ "
    },
    // :
    {
        "     ",
        "  █  ",
        "     ",
        "  █  ",
        "     "
    }
}};
std::unordered_map<char, int> char_symbol_lut = 
{
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {':', 10}
};


template <class Rep, class Period>
void duration_to_string(const std::chrono::duration<Rep, Period> &duration, std::string &time_text);
void print_digital_clock(std::string_view time);


int main() {
    
    // now & end are of type std::chrono::time_point<std::chrono::steady_clock>
    auto now = std::chrono::steady_clock::now();
    auto end = now + std::chrono::seconds{ 10 };

    // interval & time_remaining are of type std::chrono::duration<...>
    auto interval = std::chrono::seconds{ INTERVAL_TIME };
    auto time_remaining = end - now;

    std::string time_text;


    std::cout << "\033[2J"; // clears screen

    
    while (time_remaining.count() >= 1){
        std::this_thread::sleep_until(now += interval);
        time_remaining = end - now;
        duration_to_string(time_remaining, time_text);

        print_digital_clock(time_text);
        // std::endl necessary to flush cout to stdout
        std::cout << std::endl; 
    }    

    std::cout << "Done!\n";
}

template <class Rep, class Period>
void duration_to_string(const std::chrono::duration<Rep, Period> &duration, std::string &time_text) {

    std::cout << "\033[H";                                  // moves cursor to beginning
    
#if __cplusplus >= 202002L                                  // this code for C++20 or later
    std::chrono::hh_mm_ss time { duration };
    //std::cout << "C++20+\n";
    auto h = time.hours();
    auto m = time.minutes();
    auto s = time.seconds();
    
    time_text = std::format("{:02}:{:02}:{:02}", h.count(), m.count(), s.count());

#else                                                       // this code for C++17 or previous
    //std::cout << "C++17-\n";
    auto h = std::chrono::duration_cast<std::chrono::hours>(duration);
    auto m = std::chrono::duration_cast<std::chrono::minutes>(duration - h);
    auto s = std::chrono::duration_cast<std::chrono::seconds>(duration - h - m);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h.count() << ":"
        << std::setw(2) << std::setfill('0') << m.count() << ":"
        << std::setw(2) << std::setfill('0') << s.count();

    time_text = oss.str();

#endif

}

void print_digital_clock(std::string_view time) {
    // Will always print in hh:mm:ss format
    // Printing will be done row by row, so it will start by printing the top row of every character and go down until it prints the bottom row

    for (int row = 0; row < FONT_DIMENSION; ++row) {
        for (char ch : time) {
            std::cout << SYMBOLS[char_symbol_lut[ch]][row];         
        }
        std::cout << '\n';
    }
}
