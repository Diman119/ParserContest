#include <list>
#include <cstdlib>

#include "grammar.hpp"

using std::list;

// simple generator of random word derivable in a grammar
string generate_word(const CFG& g, unsigned seed) {
    list<CFG::Symbol> word_as_list;
    word_as_list.push_back(g.start_symbol());

    vector<size_t> rules;
    std::srand(seed);

    for (;;) {
        int subs = 0;
        for (auto it = word_as_list.begin(); it != word_as_list.end();) {
            if (it->is_term) {
                ++it;
                continue;
            }

            ++subs;

            rules.clear();
            for (size_t i = 0; i < g.size(); ++i) {
                if (g[i].left == *it) {
                    rules.push_back(i);
                }
            }

            auto& rule = g[rules[rand() % rules.size()]];

            for (auto& sym : rule.right) {
                word_as_list.insert(it, sym);
            }

            it = word_as_list.erase(it);
        }
        if (subs == 0) {
            break;
        }
    }

    string word;
    for (auto& sym : word_as_list) {
        word += sym.term;
    }
    return word;
}
