struct example1 {
    int a;
    char b;
};
int main() {
    volatile struct example1 test1 = { .a = 3, .b = '1'};

    return 0;
}
