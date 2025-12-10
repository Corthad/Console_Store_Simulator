#include "utils.h"

#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <windows.h>


using namespace std;

void clean_screen() {
    cout << "\033c";
}

void pause_screen() {
    system("pause");
    clean_screen();
}

void print_table_cell(int width, const char* value) {
    int pos[2] = {0, 0};
    for(int i = 0; value[i] != '\0'; ++i) {
        char ch = value[i];
        if(pos[0] % width == 0 && pos[0] != 0) {
            cout << " \033[B" << "\033[" << pos[0] << "D";
            pos[0] = 0;
            ++pos[1];
        }
        pos[0] += static_cast<int>(ch != -48 && ch != -47);
        cout << value[i];
    }

    int padding = max(0, width - pos[0]);
    for(int i = 0; i < padding; ++i) {
        cout << " ";
    }

    if(pos[1] != 0) {
        cout << "\033[" << pos[1] << "A";
    }
}

void print_table_row(int n, const int* widths, const char** data) {
    for(int i = 0; i < n; ++i) {
        print_table_cell(widths[i], data[i]);
    }
    cout << endl;
}

size_t utf_len(const char* str) {
    size_t len = 0;
    for(size_t i = 0; str[i] != '\0'; ++i) {
        if(str[i] != -48 && str[i] != -47) {
            ++len;
        }
    }
    return len;
}

int num_len(long long num) {
    num = abs(num);
    int len = 0;
    do {
        num /= 10;
        ++len;
    }
    while(num > 0);

    return len;
}

char* longlong2str(long long num) {
    char* str = new char[num_len(LLONG_MAX) + 1]{0};
    int len = num_len(num);
    int idx = 0;
    do {
        str[len - idx - 1] = static_cast<char>(num % 10 + 48);
        ++idx;
        num /= 10;
    }
    while(num > 0);

    return str;
}

char* double2str(double dnum) {
    long long integer = static_cast<long long>(dnum);
    long long fraction = static_cast<long long>(dnum * 100);
    char* str = new char[__DBL_DECIMAL_DIG__ + 1]{0};

    int point = 0;
    char* buffer = longlong2str(integer);
    for(point; buffer[point] != '\0'; ++point) {
        str[point] = buffer[point];
    }
    delete[] buffer;

    str[point] = '.';
    ++point;
    if(fraction == 0) {
        str[point + 1] = '0';
        str[point + 2] = '0';
    }
    else {
        buffer = longlong2str(fraction);
        for(point; buffer[point] != '\0'; ++point) {
            str[point] = buffer[point];
        }
        delete[] buffer;
    }

    return str;
}

long long str2longlong(char* str) {
    long long num = 0;
    int sign = 1;
    for(int i = 0; str[i] != '\0'; ++i) {
        char ch = str[i];
        switch(ch) {
            case '-':
                sign = -1;
                break;
            case '.':
                return sign * num;
            default:
                int digit = static_cast<int>(ch - 48);
                if(0 <= digit && digit <= 9) {
                    num = num * 10 + digit;
                }
                else {
                    throw invalid_argument(
                        "Значение не является числом!"
                    );
                }
                break;
        }
    }
    return sign * num;
}

double str2double(char* str) {
    size_t point = -1;
    for(size_t i = 0; str[i] != '\0'; ++i) {
        if(str[i] == '.') {
            point = i;
            break;
        }
    }

    long long integer = str2longlong(str);
    int frac_len = 0;
    long long frac_num = 0;
    if(point != static_cast<size_t>(-1)) {
        frac_len = utf_len(str + point + 1);
        frac_num = str2longlong(str + point + 1);
    }
    
    double dnum = (
        integer >= 0 ?
        integer + frac_num / pow(10.0, frac_len) :
        integer - frac_num / pow(10.0, frac_len)
    );
    return dnum;
}

void input(char* str, size_t max_size) {
    char ch;
    int size = 0;
    while(true) {
        cin.get(ch);
        ++size;

        if(ch == '\n' || size == max_size) {
            str[size - 1] = '\0';
            while(ch != '\n') {
                cin.get(ch);
            }
            return;
        }
        str[size - 1] = ch;
    }
}

void input(int& num) {
    int len = num_len(INT_MAX) + 1;
    char* str = new char[len + 1]{0};
    while(true) {
        input(str, len + 1);
        try {
           num = str2longlong(str);
           return;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void input(long long& num) {
    int len = num_len(LLONG_MAX) + 1;
    char* str = new char[len + 1]{0};
    while(true) {
        input(str, len + 1);
        try {
           num = str2longlong(str);
           return;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void input(float& dnum) {
    int len = __FLT_DIG__ + 1;
    char* str = new char[len + 1]{0};
    while(true) {
        input(str, len + 1);
        try {
           dnum = str2double(str);
           return;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void input(double& dnum) {
    int len = __DBL_DECIMAL_DIG__ + 1;
    char* str = new char[len + 1]{0};
    while(true) {
        input(str, len + 1);
        try {
           dnum = str2double(str);
           return;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

int randint(int min, int max) {
    return min + rand() % (max - min + 1);
}

long long randint(long long min, long long max) {
    return min + rand() % (max - min + 1);
}

float randfrac(float min, float max) {
    return min + rand() / static_cast<float>(RAND_MAX / (max - min));
}
double randfrac(double min, double max) {
    return min + rand() / static_cast<double>(RAND_MAX / (max - min));
}