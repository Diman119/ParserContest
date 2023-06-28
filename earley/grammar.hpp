#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector;

class CFG {
public:
    struct Symbol {

        // usage in unordered_set: std::unordered_set<Symbol, Symbol::Hash> symbol_set;
        struct Hash {
            size_t operator()(const Symbol& sym) const {
                return sym.is_term ?
                    std::hash<char>()(sym.term) :
                    std::hash<string>()(sym.nonterm);
            }
        };

        Symbol() :
            Symbol('\0') {}

        explicit Symbol(string str) :
            nonterm(std::move(str)),
            term('\0'),
            is_term(false) {}

        explicit Symbol(char c) :
            nonterm(""),
            term(c),
            is_term(true) {}

        bool operator==(const CFG::Symbol& other) const {
            if (is_term != other.is_term) {
                return false;
            }
            return is_term ? term == other.term : nonterm == other.nonterm;
        }

        bool operator!=(const CFG::Symbol& other) const {
            return !(*this == other);
        }

        string nonterm;
        char term;
        bool is_term;
    };

    using GeneralizedString = vector<Symbol>;

    struct Rule {
        Rule(Symbol left, GeneralizedString right) :
            left(std::move(left)),
            right(std::move(right)) {}

        size_t size() const {
            return right.size();
        }

        const Symbol& operator[](size_t pos) const {
            return right[pos];
        }

        Symbol left;
        GeneralizedString right;
    };

    CFG() = default;

    CFG(Symbol start, vector<Rule> rules) :
        start_symbol_(std::move(start)),
        rules_(std::move(rules)) {}

    const Symbol& start_symbol() const {
        return start_symbol_;
    }

    const Rule& operator[](size_t index) const {
        return rules_[index];
    }

    size_t size() const {
        return rules_.size();
    }

    void add_rule(Rule rule) {
        rules_.push_back(std::move(rule));
    }

    vector<Rule>& data() {
        return rules_;
    }

    friend class Input;

private:
    Symbol start_symbol_;
    vector<Rule> rules_;
};
