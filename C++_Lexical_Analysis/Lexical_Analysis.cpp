#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>


const std::vector<std::string> reservedWords = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
        "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
        "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
        "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
        "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
        "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
        "requires", "return", "short", "signed", "sizeof", "static", "static_assert",
        "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
};

const std::vector<std::string> operators = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "++", "--", "+=", "-=",
        "*=", "/=", "%=", "<<", ">>", "&=", "|=", "^=", "~", "!", "&&", "&", "|", "||", "?", ":", "::",
        "->", "[", "]","(", ")", "{", "}", "&", "*"
};

const std::vector<std::string> separators = { ";", ",", "." };

bool isReservedWords(const std::string& token) {
    auto is = find(reservedWords.begin(), reservedWords.end(), token);
    return is != reservedWords.end();
}

bool isOperator(const std::string& token) {
    auto is = find(operators.begin(), operators.end(), token);
    return is != operators.end();
}

bool isSeparator(const std::string& token) {
    auto is = find(separators.begin(), separators.end(), token);
    return is != separators.end();
}


int main() {
    std::unordered_map<std::string, int> identifiersCount, operatorsCount, reservedWordsCount, separatorsCount;
    std::string currentToken = "";
    std::cout << "Enter the source file directory + file name (e.g., C:\\CSE0405\\Group1.cpp): ";
    std::string filename;
    getline(std::cin, filename);
    std::cout << "Entered file directory + file name: " << filename << '\n';
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << '\n';
        return 1;
    }
    std::string line;
    int lineCount = 0;
    auto start_time = std::chrono::high_resolution_clock::now();

    while (getline(inputFile, line)) {
        lineCount++;

        if (line[0] == '#') continue;
        for (size_t i = 0; i < line.length(); ++i) {
            char ch = line[i];
            //Comment handling '//'
            if (ch == '/' && line[i + 1] == '/') {
                break;
            }
            // Multi-line comment handling /* */
            if (ch == '/' && line[i + 1] == '*') {
                i += 2;  // Skip the '/*'

                while (true) {
                    size_t found = line.find("*/", i);
                    if (found != std::string::npos) {
                        i = found + 2;  // Skip the '*/'
                        break;  // Exit the loop once the end of the multiline comment is found
                    }
                    if (!getline(inputFile, line)) {
                        std::cerr << "Error" << '\n';
                        return 1;
                    }
                    lineCount++;
                    i = 0;
                }
                continue;
            }
            //String Handling
            if (ch == '"') {
                i += 1;
                while (line[i] != '"') {
                    if (line[i] == '\'') {
                        i++;
                        break;
                    }
                    i++;
                }
                ch = line[i];
            }

            //Single comma handling
            if (ch == '\'') {
                i += 1;
                if (line[i + 1] == '\'' && line[i + 2] == '\'') {
                    i += 3;
                }
                else if (line[i + 1] == '\'') {
                    i += 2;
                }
                ch = line[i];
            }
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
                continue;
            }
            else if (isOperator(std::string(1, ch)) || isSeparator(std::string(1, ch))) {
                if (isSeparator(std::string(1, ch))) {
                    separatorsCount[std::string(1, ch)]++;
                }
                /*else if (isReservedWords(string(1, ch))) {
                    reservedWordsCount[string(1, ch)]++;
                }*/
                else if (isOperator(std::string(1, ch))) {
                    std::string chNext = "";
                    chNext += line[i + 1];
                    currentToken += std::string(1, ch) + chNext;
                    if (isOperator(currentToken)) {
                        operatorsCount[currentToken]++;
                        i++;
                        currentToken = "";
                        continue;
                    }
                    currentToken = "";
                    operatorsCount[std::string(1, ch)]++;
                }
            }
            else {
                currentToken += ch;
                if (i + 1 < line.length() && (isalnum(line[i + 1]) || line[i + 1] == '_')) {
                    continue;
                }
                if (isReservedWords(currentToken)) {
                    reservedWordsCount[currentToken]++;
                }
                else if (isalpha(currentToken[0])) {
                    identifiersCount[currentToken]++;
                }
                currentToken = "";
            }
        }
    }

    int subTotal = 0, grandTotal = 0;
    std::cout << "------------------------------\n" << '\n';
    std::cout << "********* Identifiers *********\n" << '\n';
    for (const auto& pair : identifiersCount) {
        std::cout << pair.first << " : " << pair.second << '\n';
        subTotal += pair.second;
    }
    std::cout << "\nSubtotal: " << subTotal << '\n';
    grandTotal += subTotal;
    subTotal = 0;
    std::cout << "\n------------------------------\n" << '\n';
    std::cout << "********* Reserved Words *********\n" << '\n';
    for (const auto& pair : reservedWordsCount) {
        std::cout << pair.first << " : " << pair.second << '\n';
        subTotal += pair.second;
    }
    std::cout << "\nSubtotal: " << subTotal << '\n';
    grandTotal += subTotal;
    subTotal = 0;
    std::cout << "\n------------------------------\n" << '\n';
    std::cout << "********* Operators *********\n" << '\n';
    for (const auto& pair : operatorsCount) {
        std::cout << pair.first << " : " << pair.second << '\n';
        subTotal += pair.second;
    }
    std::cout << "\nSubtotal: " << subTotal << '\n';
    grandTotal += subTotal;
    subTotal = 0;
    std::cout << "\n------------------------------\n" << '\n';
    std::cout << "********* Seperators *********\n" << '\n';
    for (const auto& pair : separatorsCount) {
        std::cout << pair.first << " : " << pair.second << '\n';
        subTotal += pair.second;
    }
    std::cout << "\nSubtotal: " << subTotal << '\n';
    std::cout << "\n------------------------------\n" << '\n';
    grandTotal += subTotal;
    std::cout << "Total Number of Lines: " << lineCount << '\n';
    std::cout << "Lexemes Grand Total: " << grandTotal << '\n';
    std::cout << "\n------------------------------\n" << '\n';
    subTotal = 0;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Runtime: " << duration.count() << " ms\n";

    return 0;
}
