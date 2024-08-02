#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

// Function to run a command and capture its output
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    // String containing all printable ASCII characters
    std::string printableChars = " !\"#$%&'()+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    std::string commandBase = "keygen.exe ";
    std::vector<std::string> output(printableChars.size());
    std::vector<char> badChars = {'&', '^', '|', '<', '?', '>'};

    for (int i = 0; i < printableChars.size(); ++i) {
        std::string command = commandBase;
        if(std::find(badChars.begin(), badChars.end(), printableChars[i]) != badChars.end())
        {
            command += "\"";
            command += printableChars[i];
            command += "\"";
        }
        else if(printableChars[i] == '\"')
        {
            command += "\\\"";
        }
        else if(printableChars[i] == ' ')
        {
            command += "\" \"";
        }
        else
        {
            command += printableChars[i];
        }
        output[i] = exec(command.c_str());
    }

    // Create a mapping between output and printableChars
    std::map<std::string , char> charMapping;
    for (size_t i = 0; i < printableChars.size() && i < output.size(); ++i) {
        charMapping[output[i]] = printableChars[i];
    }

    // String to be transformed
    std::string inputString = "7VLV8OM84T9CKKMQ";
    std::string transformedString;

    // Transform the inputString using the mapping
    for (char c : inputString) {
        if(charMapping[std::string (1, c)] != NULL)
        {
            transformedString += charMapping[std::string (1, c)];
        }
    }

    // Print the transformed string
    std::cout << "Site access password: 7VLV8OM84T9CKKMQ\n" << "Page access password: " << transformedString << std::endl;

    return 0;
}


