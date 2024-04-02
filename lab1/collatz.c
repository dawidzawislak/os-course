int collatz_conjecture(int input) {
    return (input % 2 == 0) ? input/2 : 3*input+1;
}

int test_collatz_convergence(int input, int max_iter) {
    int cnt = 0;
    int n = input;
    while (cnt < max_iter) {
        cnt++;

        n = collatz_conjecture(n);

        if (n == 1) return cnt;
    }
    return -1;
}