#include <iostream>
#include <string>
#include <unordered_map>

char mostFrequent(const std::string& s) {
    std::unordered_map<char, int> m;
    for(char c : s) {
        m[c] ++;
    }
    int max = 0;
    char max_c = '\0';

    for(const auto& pair: m) {
        if (pair.second > max) {
            max = pair.second;
            max_c = pair.first;
        }
    }

    return max_c;
}

int main() {
    std::cout << mostFrequent("aabbbc") << "\n";
    return 0;
}
