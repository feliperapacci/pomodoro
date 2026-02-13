#include <array>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

#include "fonts.h"

const int FONT_DIMENSION = 5;   // 6x5

const std::array<std::array<std::string, 5>, 11> SYMBOLS {{
    // 5x5 ascii arts of each character in a digital clock [0-9:]

    // 0
    {
        "  ███ ",
        " █   █",
        " █   █",
        " █   █",
        "  ███ "
    },
    // 1
    {
        "   █  ",
        "  ██  ",
        "   █  ",
        "   █  ",
        "  ███ "
    },
    // 2
    {
        "  ███ ",
        " █   █",
        "    █ ",
        "   █  ",
        " █████"
    },
    // 3
    {
        " ████ ",
        "     █",
        "  ███ ",
        "     █",
        " ████ "
    },
    // 4
    {
        " █   █",
        " █   █",
        " █████",
        "     █",
        "     █"
    },
    // 5
    {
        " █████",
        " █    ",
        " ████ ",
        "     █",
        " ████ "
    },
    // 6
    {
        "  ███ ",
        " █    ",
        " ████ ",
        " █   █",
        "  ███ "
    },
    // 7
    {
        " █████",
        "     █",
        "    █ ",
        "   █  ",
        "   █  "
    },
    // 8
    {
        "  ███ ",
        " █   █",
        "  ███ ",
        " █   █",
        "  ███ "
    },
    // 9
    {
        "  ███ ",
        " █   █",
        "  ████",
        "     █",
        "  ███ "
    },
    // :
    {
        "      ",
        "   █  ",
        "      ",
        "   █  ",
        "      "
    }
}};

// a lookup table mapping the characters to their indices in SYMBOLS
std::unordered_map<char, int> char_symbol_lut 
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


void print_digital_clock(std::string_view time) {
    // Will always print in hh:mm:ss format
    // Printing will be done row by row, so it will start by printing the top row of every character and go down until it prints the bottom row

    std::cout << "\033[H";                                  // moves cursor to beginning

    for (int row = 0; row < FONT_DIMENSION; ++row) {
        for (char ch : time) {
            std::cout << SYMBOLS[char_symbol_lut[ch]][row];         
        }
        std::cout << '\n';
    }
}
