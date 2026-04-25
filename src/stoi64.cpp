
#include <stoi64.h>

int64_t stoi64(const char *str, int *errorCode) {
    int64_t result = 0;
    int64_t sign = 1;
    int i = 0;

    if (errorCode != NULL) *errorCode = 0;

    if (str[0] == '\0') {
        if (errorCode != NULL) *errorCode = 1;
        return 0;
    }

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    for (; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            if (errorCode != NULL) *errorCode = 2;
            return 0;
        }

        if (result > INT64_MAX / 10 || 
           (result == INT64_MAX / 10 && str[i] - '0' > INT64_MAX % 10)) {
            if (errorCode != NULL) *errorCode = 3;
            return (sign == 1) ? INT64_MAX : INT64_MIN;
        }

        result = result * 10 + (str[i] - '0');
    }

    return result * sign;
}
