#include <iostream>
#include <fstream>


int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string s;
    std::getline(in, s);
    in.close();

    out.close();

    return 0;
}