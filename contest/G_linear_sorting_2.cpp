#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

unsigned int cur = 0;

unsigned int nextRand24(int a, int b) {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32(int x, int y) {
    unsigned int a = nextRand24(x, y), b = nextRand24(x, y);
    return (a << 8) ^ b;
}

void radix_sort(std::vector<unsigned int>& A, int N) {
    const int BITS_PER_BYTE = 8;
    const int RADIX = 256; // Assuming 8 bits per byte

    std::vector<unsigned int> count(RADIX, 0);
    std::vector<unsigned int> temp(N);

    for (int shift = 0; shift < sizeof(unsigned int) * BITS_PER_BYTE; shift += BITS_PER_BYTE) {
        count.assign(RADIX, 0);

        // Counting sort based on the current digit
        for (int i = 0; i < N; i++) {
            unsigned int digit = (A[i] >> shift) & 0xFF;
            count[digit]++;
        }

        // Calculating cumulative counts
        for (int i = 1; i < RADIX; i++) {
            count[i] += count[i - 1];
        }

        // Rearranging the elements based on the current digit
        for (int i = N - 1; i >= 0; i--) {
            unsigned int digit = (A[i] >> shift) & 0xFF;
            temp[count[digit] - 1] = A[i];
            count[digit]--;
        }

        // Copying the sorted elements back to the original array
        for (int i = 0; i < N; i++) {
            A[i] = temp[i];
        }
    }
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

    std::vector<unsigned int> A(n);

    for (int testCount = 0; testCount < t; testCount++) {
        for (int i = 0; i < n; i++) {
            A[i] = nextRand32(a, b);
        }

        radix_sort(A, n);

        long long s = 0;
        for (int i = 0; i < n; i++) {
            s = s + static_cast<long long>(A[i]) * (i + 1);
        }

        std::cout << s << std::endl;
    }
}
