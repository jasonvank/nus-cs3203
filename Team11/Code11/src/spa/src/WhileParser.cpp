#include "WhileParser.h"

WhileParser::WhileParser(PKB &pkb, Statement statement, std::string parent_prog_line)
{
    std::string condition = statement.get_condition();
    std::vector<Statement> loop_part = statement.get_first_block();

    if (!CheckerUtil::is_condition_valid(condition))
    {
        throw std::runtime_error(error_messages::invalid_while_statement);
    }

    // Insert const
    std::vector<std::string> all_const = StringUtil::get_all_const(condition);
    for (const std::string &spa_constant : all_const)
    {
        pkb.insert_constant(spa_constant);
    }

    std::vector<std::string> all_variables = StringUtil::get_all_var(condition);
    int num_of_control_var = all_variables.size();
    for (int i = 0; i < num_of_control_var; i++)
    {
        pkb.insert_variable(all_variables[i]);
        pkb.insert_uses(statement.get_prog_line(), all_variables[i]);
        pkb.insert_uses(statement.get_procedure(), all_variables[i]);
    }

    pkb.insert_while(statement.get_prog_line(), all_variables);

    int num_of_stmt_loop = loop_part.size();

    if (CheckerUtil::is_const_valid(parent_prog_line))
    {
        pkb.insert_parent(std::stoi(parent_prog_line), statement.get_prog_line());
    }

    // Update parent relationship for while statement

    for (int i = 0; i < num_of_stmt_loop; i++)
    {
        Statement this_stmt = loop_part[i];
        pkb.insert_parent(statement.get_prog_line(), this_stmt.get_prog_line());
    }

    ParserInvoker loop_invoker = ParserInvoker(pkb, loop_part, std::to_string(statement.get_prog_line()));
    loop_invoker.invoke_parser();
}
