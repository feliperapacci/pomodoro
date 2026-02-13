#pragma once

#include <sstream>
#include <iomanip>
#include <iostream>

void print_digital_clock(std::string_view time);

template <class Rep, class Period>
void duration_to_string(const std::chrono::duration<Rep, Period> &duration, std::string &time_text) {

    
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
