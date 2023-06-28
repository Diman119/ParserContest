#include "parser.hpp"
#include "grammar.hpp"
#include "input.hpp"

int main() {
    CFG grammar;
    std::cin >> grammar;

    auto parser = make_parser(std::move(grammar));

    string word;
    for (;;) {
        std::getline(std::cin, word);
        if (word.empty()) {
            break;
        }
        std::cout << (parser->parse(word) ? "YES\n" : "NO\n");
    }

    delete parser;
}
