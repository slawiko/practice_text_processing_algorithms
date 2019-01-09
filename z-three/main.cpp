#include <iostream>
#include <fstream>
#include <vector>

unsigned int min(unsigned int a, unsigned int b) {
    return a <= b ? a : b;
}

void minimize(unsigned int* v, int n) {
    for (int i = 0; i < n; ++i) {
        v[i] = v[i] <= i ? v[i] : i;
    }
}

unsigned int getmax(const unsigned int* v, int n) {
    unsigned int max = 0;
    for (int i = 0; i < n; ++i) {
        max = v[i] > max ? v[i] : max;
    }
    return max;
}

void z_function_wo_overlap(unsigned int* z, std::string &s, int n) {
    for (unsigned int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    minimize(z, n);
}

void bufferize(const unsigned int* z, unsigned int* buffer, int n, int start) {
    for (int i = 0; i < n - start; ++i) {
        buffer[i + start] = z[i] > buffer[i + start] ? z[i] : buffer[i + start];
    }
}

std::string three(std::string &s) {
    unsigned int n = s.length();
    unsigned int* z = new unsigned int[n];
    unsigned int* buffer = new unsigned int[n];
    for (int i = 0; i < n; ++i) {
        buffer[i] = 0;
        z[i] = 0;
    }
    unsigned int l, size, max = 0;
    unsigned int max_l = 0, max_size = 0;
    std::string suffix;
    for (unsigned int i = 0; i < n; ++i) {
        suffix = s.substr(i);
        z_function_wo_overlap(z, suffix, n - i);
        max = getmax(z, n - i);
        l = i;
        size = buffer[i] < max ? buffer[i] : max;
        if (size > max_size) {
            max_l = l;
            max_size = size;
        }
        bufferize(z, buffer, n, i);
        for (int j = 0; j < n; ++j) {
            z[j] = 0;
        }
    }

    delete[] buffer;
    delete[] z;

    return s.substr(max_l, max_size);
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string s;
    std::getline(in, s);
    in.close();

    out << three(s);
    out.close();
    return 0;
}