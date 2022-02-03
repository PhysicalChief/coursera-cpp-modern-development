#include "condition_parser.h"
#include <iostream>

std::shared_ptr<Node> ParseCondition(std::istream& is) {
    auto tokens = Tokenize(is);
    auto current = tokens.begin();
    auto top_node = ParseExpression(current, tokens.end(), 0u);

    if (!top_node) {
        top_node = std::make_shared<EmptyNode>();
    }

    if (current != tokens.end()) {
        throw std::logic_error("Unexpected tokens after condition");
    }

    return top_node;
}
