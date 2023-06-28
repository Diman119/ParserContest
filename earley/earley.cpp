#include <iostream>
#include "grammar.hpp"
#include "input.hpp"

class Earley {
public:
    struct State {

        // usage in unordered_set: std::unordered_set<State, State::Hash> state_set;
        struct Hash {
            // calculate hash of state
            size_t operator()(const State& state) const {
                // not implemented
                return 0;
            }
        };

        bool operator==(const State& other) const {
            // not implemented
            return false;
        }

        // ???
    };

    Earley(CFG grammar)
        : grammar_(std::move(grammar)) {

    }

    // return if grammar contains word
    bool parse(const string& word) {
        // not implemented
        return false;
    }

private:
    // scan, predict, complete, etc

private:
    CFG grammar_;
    // ???
};

int main() {
    CFG grammar;
    std::cin >> grammar;

    Earley parser(std::move(grammar));
    string word;
    for (;;) {
        std::getline(std::cin, word);
        if (word.empty()) {
            break;
        }
        std::cout << (parser.parse(word) ? "YES\n" : "NO\n");
    }
}
