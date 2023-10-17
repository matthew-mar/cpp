#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

unsigned int cur = 0;

unsigned int nextRand24(int a, int b) {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32(int x, int y) {
    unsigned int a = nextRand24(x, y), b = nextRand24(x, y);
    return (a << 8) ^ b;
}

void radix_sort(unsigned int *A, int N)
{
    unsigned int *a0 = new unsigned int[N];
    unsigned int *a1 = new unsigned int[N];
    
    for(int radix = 0; radix < 32; radix++) {
        int a0_size = 0;
        int a1_size = 0;
        for(int i = 0; i < N; i++) {
            if ((A[i] & (1 << radix)) == 0)
                a0[a0_size++] = A[i];
            else
                a1[a1_size++] = A[i];
        }
        for(int i = 0; i < a0_size; i++)
            A[i] = a0[i];
        for(int i = 0; i < a1_size; i++)
            A[a0_size + i] = a1[i];
    }
    delete[] a0;
    delete[] a1;
}

int main() {
    std::ifstream inputFile("input.txt");

    int t;
    inputFile >> t;

    int n;
    inputFile >> n;

    int a;
    inputFile >> a;

    int b;
    inputFile >> b;

    for (int testCount = 0; testCount < t; testCount++) {
        unsigned int A[n];
        for (int i = 0; i < n; i++) {
            A[i] = nextRand32(a, b);
        }

        radix_sort(A, n);

        long long s = 0;
        for (int i = 0; i < n; i++) {
            s = s + (long long)A[i] * (i + 1);
        }

        std::cout << s << std::endl;
    }
}
