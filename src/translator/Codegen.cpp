#include "translator/Codegen.h"

Codegen::Codegen() = default;

str Codegen::literal(Literal * literal) {
    switch (literal->token.type) {
        case TokenType::Int: {
            return "new Jacy.Int("+ literal->token.val +")";
        }
        case TokenType::Float: {
            return "new Jacy.Float("+ literal->token.val +")";
        }
        case TokenType::String: {
            return "new Jacy.String('"+ literal->token.val +"')";
        }
        default: {
            throw DevError("Unexpected literal token type");
        }
    }
}

str Codegen::op_method(const Token & token) {
    switch (token.type) {
        case TokenType::Add: {
            return "[op_add]";
        }
        case TokenType::Sub: {
            return "[op_sub]";
        }
        default: {
            throw DevError("Unexpected operator token type");
        }
    }
}


