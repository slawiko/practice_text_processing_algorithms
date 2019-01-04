#include <iostream>
#include <fstream>
#include <vector>

bool is_char(char &c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

std::string calculate_diff(std::string &s1, std::string &s2, int n) {
    char diff = 0;
    int skipped = 0;
    char* result = new char[n];
    for (int i = 0; i < n; i++) {
        if (!is_char(s2[i])) {
            skipped++;
            continue;
        }
        diff = s2[i] - s1[i];
        if (diff < 0) {
            diff += 26;
        }

        result[i - skipped] = diff + 'a' - 1;
    }

    return std::string(result);
}

std::string min_cyclic_shift(std::string s) {
    s += s;
    int n = (int) s.length();
    int i=0, ans=0;
    while (i < n/2) {
        ans = i;
        int j=i+1, k=i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i;
            }
            else {
                ++k;
            }
            ++j;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    return s.substr(ans, n/2);
}

void readlines(int n, std::string &s, std::ifstream &in) {
    int read = 0;
    std::string buffer;

    while(n - read > 0) {
        std::getline(in, buffer);
        s += buffer;
        read += buffer.size();
    }
}

int main() {
    std::ifstream in("littera.in");
    std::ofstream out("littera.out");

    int n;
    in >> n;

    std::string s1, s2;

    readlines(n, s1, in);
    readlines(n, s2, in);
    in.close();

    std::string diff = calculate_diff(s1, s2, n);
    std::string shift = min_cyclic_shift(diff);

    out.close();

    return 0;
}