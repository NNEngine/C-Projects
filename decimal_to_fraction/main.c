#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    long long numerator;
    long long denominator;
} Fraction;

long long gcd(long long a, long long b) {
    return b==0 ? a : gcd(b, a % b);
}

Fraction decimal_to_fraction(const char *str) {
    Fraction f = {0, 1};

    int negative = 0;
    int decimal_seen = 0;

    if (*str == '-') {
        negative = 1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str) {
        if (*str == '.') {
            if (decimal_seen) {
                printf("Error: Invalid number.\n");
                exit(EXIT_FAILURE);
            }
            decimal_seen = 1;
        }
        else if (isdigit((unsigned char)*str)) {
            f.numerator = f.numerator * 10 + (*str - '0');

            if (decimal_seen) f.denominator *= 10;
        }
        else {
            printf("Error: Invalid character '%c'\n", *str);
            exit(EXIT_FAILURE);
        }

        str++;
    }

    if (negative) f.numerator = -f.numerator;
    return f;
}

Fraction simplify_fraction(Fraction f){
	long long g = gcd(f.numerator < 0 ? -f.numerator : f.numerator, f.denominator);
    f.numerator /= g;
    f.denominator /= g;

    Fraction f_ = {f.numerator, f.denominator};

    return f_;
}

int main(void) {
    char input[100];

    printf("Enter a decimal number: ");
    scanf("%99s", input);

    Fraction f = decimal_to_fraction(input);

    printf("Fraction = %lld/%lld\n", f.numerator, f.denominator);

    Fraction f_ = simplify_fraction(f);

    printf("Fraction = %lld/%lld\n", f_.numerator, f_.denominator);

    return 0;
}
