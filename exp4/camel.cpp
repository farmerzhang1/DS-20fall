#include <string>


std::string to_camel_case(std::string text) {
    std::string result;
    bool up = false;
    for (auto it = text.begin(); it != text.end(); ++it) {
        if (*it == '_' || *it == '-') {
            up = true;
            continue;
        }
        if (up) { result.push_back(toupper(*it)); up = false; }
        else result.push_back (*it);
    }
}