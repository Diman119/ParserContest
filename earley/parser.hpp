#include "grammar.hpp"

struct IParser {
    virtual bool parse(const string& word) = 0;
    virtual ~IParser() {};
};

IParser* make_parser(CFG grammar);
