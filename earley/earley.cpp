#include "parser.hpp"

class Earley : public IParser {
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

    // IParser
    // return if grammar contains word
    virtual bool parse(const string& word) override {
        // not implemented
        return false;
    }

private:
    // scan, predict, complete, etc

private:
    CFG grammar_;
    // ???
};

IParser* make_parser(CFG grammar) {
    return new Earley(std::move(grammar));
}
