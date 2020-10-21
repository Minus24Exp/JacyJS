#include "translator/Translator.h"

Translator::Translator() {
    code = "use strict;";
}

std::string Translator::translate(const StmtList & tree) {
    for (const auto & stmt : tree) {
        stmt->accept(*this);
        add(";");
    }
    return code;
}

void Translator::add(const std::string & c) {
    code += c;
}

void Translator::visit(ExprStmt * expr_stmt) {
    expr_stmt->expr->accept(*this);
}

////////////////
// Statements //
////////////////
void Translator::visit(Block * block) {
    add("{");
    for (const auto & stmt : block->stmts) {
        stmt->accept(*this);
    }
    add("}");
}

void Translator::visit(VarDecl * var_decl) {
    if (var_decl->kind == VarDeclKind::Val) {
        add("const");
    } else {
        add("let");
    }
    add(" "+ var_decl->id->get_name());

    if (var_decl->assign_expr) {
        add("=");
        var_decl->assign_expr->accept(*this);
    }
}

void Translator::visit(FuncDecl * func_decl) {
    add("function ");
    add(func_decl->id->get_name());
    add("(");
    for (const auto & param : func_decl->params) {
        add(param.id->get_name());
        if (param.default_val) {
            add("=");
            param.default_val->accept(*this);
        }
    }
    add(")");
    func_decl->body->accept(*this);
}

void Translator::visit(ReturnStmt * return_stmt) {
    add("return ");
    return_stmt->expr->accept(*this);
}

void Translator::visit(WhileStmt * while_stmt) {
    add("while(");
    while_stmt->cond->accept(*this);
    add(")");
    while_stmt->body->accept(*this);
}

void Translator::visit(ForStmt * for_stmt) {
    add("for(");
    for_stmt->For->accept(*this);
    add(" in ");
    for_stmt->In->accept(*this);
    add(")");
    for_stmt->body->accept(*this);
}

void Translator::visit(ClassDecl * class_decl) {
    add("class ");
    add(class_decl->id->get_name());
    if (class_decl->super) {
        add(" extends ");
        class_decl->super->accept(*this);
    }
    add("{");
    for (const auto & field : class_decl->fields) {
        field->accept(*this);
    }
    add("}");
}

void Translator::visit(Import * import) {}

void Translator::visit(TypeDecl * type_decl) {}

/////////////////
// Expressions //
/////////////////
void Translator::visit(Literal * literal) {
    add(literal->token.val);
}

void Translator::visit(Identifier * id) {
    add(id->get_name());
}

void Translator::visit(Infix * infix) {
    infix->left->accept(*this);
    // TODO: Replace with overriding
    add(op_to_str(infix->op.type));
    infix->right->accept(*this);
}

void Translator::visit(Prefix * prefix) {
    // TODO: Replace with overriding
    add(op_to_str(prefix->op.type));
    prefix->right->accept(*this);
}

void Translator::visit(Assign * assign) {
    assign->id->accept(*this);
    add("=");
    assign->value->accept(*this);
}

void Translator::visit(SetExpr * set_expr) {
    set_expr->left->accept(*this);
    add(".");
    set_expr->id->accept(*this);
    add("=");
    set_expr->value->accept(*this);
}

void Translator::visit(GetExpr * get_expr) {
    get_expr->left->accept(*this);
    add(".");
    get_expr->id->accept(*this);
}

void Translator::visit(FuncCall * func_call) {
    func_call->left->accept(*this);
    add("(");
    for (std::size_t i = 0; i < func_call->args.size(); i++) {
        func_call->args[i]->accept(*this);
        if (i < func_call->args.size() - 1) {
            add(",");
        }
    }
    add(")");
}

void Translator::visit(IfExpr * if_expr) {
    add("if(");
    if_expr->cond->accept(*this);
    add(")");
    if_expr->if_branch->accept(*this);
    add("else");
    if_expr->else_branch->accept(*this);
}

void Translator::visit(ListExpr * list) {
    add("[");
    for (std::size_t i = 0; i < list->elements.size(); i++) {
        list->elements[i]->accept(*this);
        if (i < list->elements.size() - 1) {
            add(",");
        }
    }
    add("]");
}

void Translator::visit(GetItem * get_item) {
    // TODO: Add operator overloading
    get_item->left->accept(*this);
    add("[");
    get_item->index->accept(*this);
    add("]");
}

void Translator::visit(SetItem * set_item) {
    set_item->left->accept(*this);
    add("[");
    set_item->index->accept(*this);
    add("]=");
    set_item->value->accept(*this);
}

void Translator::visit(DictExpr * dict) {
    // TODO: THIS )))
}
