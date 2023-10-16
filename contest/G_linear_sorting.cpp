#include <cmath>
#include <vector>
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

void radixSort(std::vector<int>& numbers, int N)
{
    std::vector<int> zeros(N);
    std::vector<int> ones(N);

    for (int radix = 0; radix < 32; radix++) {
        int z_i = 0;
        int o_i = 0;

        for (int i = 0; i < N; i++) {
            if ((numbers[i] & (1 << radix)) == 0) {
                zeros[z_i++] = numbers[i];
            } else {
                ones[o_i++] = numbers[i];
            }
        }

        for (int i = 0; i < z_i; i++) {
            numbers[i] = zeros[i];
        }

        for (int i = 0; i < o_i; i++) {
            numbers[i] = ones[i];
        }
    }

    zeros.clear();
    ones.clear();
}

int main() {
    int t;
    int n;

    std::cin >> t;
    std::cin >> n;

    int a;
    int b;

    std::cin >> a;
    std::cin >> b;

    for (int i = 0; i < t; i++) {
        // fill array
        std::vector<int> numbers(n);
        for (int i = 0; i < n; i++) {
            numbers[i] = nextRand32(a, b);
        }

        radixSort(numbers, n);

        int sum = 0;
        for (int k = 1; k < n; k++) {
            sum += numbers[k] * k;
        }

        std::cout << sum << std::endl;
    }

    return 0;
}
