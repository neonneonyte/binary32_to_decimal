#include <stdlib.h> // exit()
#include <math.h> // pow()

float cvtbd(const char* const str, int* error) {
    float exponent  = .0;
    float fraction  = .0;
    int idx         = 0;
    _Bool sign      = 0;

    switch (str[idx++]) {
        case '1':
            sign = 1;
            break;
        case '0':
            break;
        default:
            *error = 1;
            return 0;
    }

    for (int count = 0; count < 8; ++count, ++idx) {
        switch (str[idx]) {
            case '1':
                exponent *= 2.0;
                exponent += 1.0;
                break;
            case '0':
                exponent *= 2.0;
                break;
            default:
                *error = 1;
                return 0;
        }
    }

    for (int count = 1; count < 24; ++count, ++idx) {
        if (str[idx] == '1')
            fraction += (1.0 / (double)(1 << count));
        else if (str[idx] == '0')
            continue;
        else
            break;
    }
    if (fraction)
        fraction += 1.0;
    return ((sign ? -1.0 : 1.0) * (pow(2.0, exponent - 127.0)) * fraction);
}