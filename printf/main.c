#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <stdio.h>

#define STDOUT 1

void custom_printf(const char* input, ...);
char char_of_digit(uint8_t digit);
int write_char(char arg);
int write_int(int64_t arg);
int write_double(double arg);

int main() {
    custom_printf("Char: %c\n", 'a');
    custom_printf("Char: %c\n", 'b');
    custom_printf("+Int: %d\n", 10);
    custom_printf("-Int: %d\n", -10);
    custom_printf("+Float: %f\n", 10.123);
    custom_printf("-Float: %f\n", -10.123);
    custom_printf("LargeFloat: %f\n", 2.232E100); // doesn't work
    custom_printf("String: %s\n", "string");
    custom_printf("Hello, World\n");
    custom_printf("%c %d %f %s\n", 'a', 232, 566.77777, "wow it works");
    printf("LargeFloat: %f\n", 2.232E100);
    return 0;
}

void custom_printf(const char* input, ...) {
    int i = 0;
    int err = 0;
    va_list ap;

    va_start(ap, input);
    while(1) {
        char current_char = input[i];
        
        if (current_char == '\0') break;

        if (current_char != '%') write_char(current_char);

        char char_arg = '*';
        int int_arg = 0;
        double double_arg = 0.0;
        const char* string;
        if (current_char == '%') {
            i += 1;

            char pattern = input[i];
            switch(pattern) {
                case 'c':
                    char_arg = (char) va_arg(ap, int32_t);
                    err = write_char(char_arg);
                    break;
                case 'd':
                    int_arg = (int32_t) va_arg(ap, int32_t);
                    err = write_int(int_arg);
                    break;
                case 'f':
                    double_arg = (double) va_arg(ap, double);
                    err = write_double(double_arg);
                    break;
                case 's': 
                    string = va_arg(ap, char*);
                    int j = 0;
                    while (string[j] != '\0') {
                        err = write_char(string[j]);
                        j += 1;
                    }
                    break;
                default: 
                    break;
            }
        }

        i += 1;
    }
    va_end(ap);
}

char char_of_digit(uint8_t digit) {
    char char_digit = '*';

    if      (digit == 0) char_digit = '0';
    else if (digit == 1) char_digit = '1';
    else if (digit == 2) char_digit = '2';
    else if (digit == 3) char_digit = '3';
    else if (digit == 4) char_digit = '4';
    else if (digit == 5) char_digit = '5';
    else if (digit == 6) char_digit = '6';
    else if (digit == 7) char_digit = '7';
    else if (digit == 8) char_digit = '8';
    else if (digit == 9) char_digit = '9';

    return char_digit;
}

int write_char(char arg) {
    int err = 0;

    char output[] = {arg, '\0'};
    err = write(STDOUT, output, 2);

    return err;
}

int write_int(int64_t arg) {
    int err = 0;
    uint8_t is_neg = 0;

    if (arg < 0) {
        is_neg = 1;
        arg *= -1;
    }

    char char_digit = '*';
    char string_digit[20];

    int digit_len = 0;
    while (1) {
        uint8_t digit = arg % 10;

        char_digit = char_of_digit(digit);

        string_digit[digit_len] = char_digit;

        arg /= 10;
        digit_len += 1;

        if (arg == 0) break;
    }

    if (is_neg) write_char('-');
    for (int i = digit_len - 1; i > -1; i--) {
        err = write_char(string_digit[i]);
    }

    return err;
}

int write_double(double arg) {
    int err = 0;

    int64_t whole_num = (int64_t) arg;

    err = write_int(whole_num);

    err = write_char('.');

    for (int i = 0; i < 6; i++) {
        arg = arg * 10;
        err = write_int((int64_t) arg % 10);
    }

    return err;
}
