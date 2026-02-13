#include <unistd.h>
#include "inputs.h"

Keys read_key() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1)
        return Keys::Invalid;

    switch (c) {
    case ' ':
        return Keys::Space;
    case 'R':
        return Keys::R;
    case '\n':
        return Keys::Enter;
    case 27:        // BEGINNING OF ESCAPE SEQUENCE
        char sequence[2];
        if (read(STDIN_FILENO, sequence, 2) != 2)
            return Keys::Invalid;
        
        if (sequence[0] == '[') {
            switch (sequence[1]) {
            case 'A': 
                return Keys::Up;    // ESC [ A
            case 'B':
                return Keys::Down;  // ESC [ B
            case 'C':
                return Keys::Right; // ESC [ C
            case 'D':
                return Keys::Left;  // ESC [ D
            default:
                return Keys::Invalid;
            }
        }
        return Keys::Invalid;
    default:
        return Keys::Invalid;
    }
}

void TimeSelector::increase() {
    // function will wrap. 59 minutes + 1 minute = 0 minute
    switch (time_field) {
        case 0:             // Seconds
            if (seconds % 60 < 59)
                ++seconds;              // 1 second
            else
                seconds -= 59;          // 59 seconds
            return;
        case 1:             // Minutes
            if ((seconds % 3600) / 60 < 59)
                seconds += 60;          // 1 minute
            else
                seconds -= 3540;        // 59 minutes
            return;
        case 2:             // Hours
            if ((seconds / 3600) < 99)
                seconds += 3600;        // 1 hour
            else
                seconds -= 356400;       // 99 hours
            return;
        default:                        // SHOULD NEVER HAPPEN
            return;     
    }
}

void TimeSelector::decrease() {
    // function will wrap. 0 minute - 1 minute = 59 minutes
    switch (time_field) {
        case 0:             // Seconds
            if (seconds % 60 > 0)
                --seconds;              // 1 second
            else
                seconds += 59;          // 59 seconds
            return;
        case 1:             // Minutes
            if ((seconds % 3600) / 60 > 0)
                seconds -= 60;          // 1 minute
            else
                seconds += 3540;        // 59 minutes
            return;
        case 2:             // Hours
            if ((seconds / 3600) > 0)
                seconds -= 3600;        // 1 hour
            else
                seconds += 356400;       // 99 hours
            return;
        default:                        // SHOULD NEVER HAPPEN
            return;     
    }
}

void TimeSelector::move_right() {
    if (time_field == 0)
        return;
    else
        --time_field;
    return;
}

void TimeSelector::move_left() {
    if (time_field == 2)
        return;
    else
        ++time_field;
    return;
}

int TimeSelector::getSeconds() {
    return seconds;
}

int TimeSelector::getField() {
    return time_field;
}
