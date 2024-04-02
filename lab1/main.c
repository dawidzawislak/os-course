#include <stdio.h>

#ifdef DLL
#include <dlfcn.h>
#else
extern int test_collatz_convergence(int input, int max_iter);
#endif


int main(int argc, char** argv) {
    #ifdef DLL
    void* handle = dlopen("./libcollatz.so", RTLD_LAZY);
    if (!handle) {
        printf("Failed to open libcollatz.so!\n");
        return -1;
    }

    int (*test_collatz_convergence)(int, int);
    test_collatz_convergence = dlsym(handle, "test_collatz_convergence");
    if (dlerror() != 0) {
        printf("Failed to load test_collatz_convergence() pointer!\n");
        return -2;
    }
    #endif

    printf("123 (100) - %d\n", test_collatz_convergence(123, 100));
    printf("4576 (100) - %d\n", test_collatz_convergence(4576, 100));
    printf("432 (10) - %d\n", test_collatz_convergence(432, 10));
    printf("236745 (1000) - %d\n", test_collatz_convergence(236745, 1000));

    return 0;
}