#include <string>
#include <sstream>
#include "utils.h"

std::vector<std::string> splitStringByDelimiter(std::string sourceString, char delimiter) {
    std::vector<std::string> chunks { };
    std::istringstream stringParser(sourceString);
    std::string chunk { "" };
    while (std::getline(stringParser, chunk, delimiter)) {
        chunks.push_back(chunk);
    }
    return chunks;
}

