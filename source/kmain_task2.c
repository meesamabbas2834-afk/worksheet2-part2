int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

int multiply_numbers(int a, int b) {
    return a * b;
}

int check_valid(int num) {
    if (num == 0x1234) {
        return 1;
    }
    return 0;
}

int kmain(void) {
    int sum = sum_of_three(1, 2, 3);
    int product = multiply_numbers(10, 5);
    int validation = check_valid(0x1234);

    return sum + product + validation;
}

