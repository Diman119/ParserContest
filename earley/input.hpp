#pragma once

#include "grammar.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class Input{
public:
    explicit Input(std::istream& stream) :
        source_(stream) {}

    void read_grammar(CFG& grammar) {
        get_next_line();

        grammar.start_symbol_ = read_nonterminal();

        grammar.rules_.clear();

        for (;;) {
            get_next_line();

            if (buffer_.empty()) {
                continue;
            }
            if (buffer_ == "end") {
                break;
            }

            auto nonterm = read_nonterminal();

            read_separator();

            while (pos_ != string::npos) {
                grammar.rules_.emplace_back(nonterm, read_generalized_string());
            }
        }
    }

private:
    void get_next_line() {
        pos_ = 0;
        std::getline(source_, buffer_);
    }

    CFG::Symbol read_nonterminal() {
        size_t start = buffer_.find('<', pos_) + 1;
        size_t end = buffer_.find('>', start);
        pos_ = end;

        return CFG::Symbol(buffer_.substr(start, end - start));
    }

    void read_separator() {
        pos_ = buffer_.find("::=", pos_ + 1);
        if (pos_ == string::npos) {
            throw std::runtime_error("Error: no ::= found");
        }
        pos_ += 2;
    }

    CFG::GeneralizedString read_generalized_string() {
        CFG::GeneralizedString str;
        for (;;) {
            pos_ = buffer_.find_first_of("<\"'|", pos_ + 1);

            if (pos_ == string::npos || buffer_[pos_] == '|') {
                return str;
            }

            if (buffer_[pos_] == '<') {
                ++pos_;
                size_t end = buffer_.find('>', pos_);
                if (end == string::npos) {
                    throw std::runtime_error("Error: incomplete nonterminal");
                }

                str.emplace_back(buffer_.substr(pos_, end - pos_));
                pos_ = end;

            } else if (buffer_[pos_] == '"' || buffer_[pos_] == '\'') {
                size_t end = buffer_.find(buffer_[pos_], pos_ + 1);
                if (end == string::npos) {
                    throw std::runtime_error("Error: incomplete terminal sequence");
                }

                ++pos_;
                for (; pos_ != end; ++pos_) {
                    str.emplace_back(buffer_[pos_]);
                }
            }
        }
    }

    std::istream& source_;
    string buffer_;
    size_t pos_ = 0;
};

std::istream& operator>>(std::istream& stream, CFG& grammar) {
    Input input(stream);
    input.read_grammar(grammar);
    return stream;
}
