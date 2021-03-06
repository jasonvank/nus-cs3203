#ifndef AUTOTESTER_USESBANK_H
#define AUTOTESTER_USESBANK_H

#include "Bank.h"

class UsesBank
{
public:
    /**
     * Insert a Uses relationship between the input statement and the input variable into stmt_bank.
     * @param statement
     * @param variable
     * @return Return true if there is a Uses relationship between the input statement and the input variable.
     */
    bool insert_uses(int statement, std::string variable);

    /**
     * Insert a Uses relationship between the input procedure and the input variable into proc_bank.
     * @param procedure
     * @param variable
     * @return Return true if there is a Uses relationship between the input procedure and the input variable.
     */
    bool insert_uses(std::string procedure, std::string variable);

    /**
     * Insert Uses relationships of callee procedure to caller procedure
     * @param caller caller procedure
     * @param callee callee procedure
     * @return Return true if the relationships are inserted successfully, otherwise false
     */
    bool insert_uses_for_call(std::string caller, std::string callee);

    /**
     * Get all statements that uses the input variable.
     * @param variable
     * @return Return an integer vector of all statement that uses the variable.
     */
    std::vector<int> get_statements_uses(std::string variable);

    /**
     * Get all procedures that uses the input variable.
     * @param variable
     * @return Return an integer vector of all procedure that uses the variable.
     */
    std::vector<std::string> get_procedures_uses(std::string variable);

    /**
     * Get all variables used by the input statement.
     * @param statement
     * @return Return a string vector of variables used by the statement.
     */
    std::vector<std::string> get_used_by_statement(int statement);

    /**
     * Get all variables used by the input procedure.
     * @param procedure
     * @return Return a string vector of variables used by the procedure.
     */
    std::vector<std::string> get_used_by_procedure(std::string procedure);

    /**
     * Return true if there is a Uses relationship between the input procedure and the input variable.
     * @param procedure
     * @param variable
     * @return Return true if there is a Uses relationship between the input procedure and the input variable.
     */
    bool is_uses(std::string procedure, std::string variable);

    /**
     * Return true if there is a Uses relationship between the input statement and the input variable.
     * @param statement
     * @param variable
     * @return Return true if there is a Uses relationship between the input statement and the input variable.
     */
    bool is_uses(int statement, std::string variable);

    /**
     * Get all statements having one or more Uses relationships.
     * @return Return an integer vector of statements having one or more Uses relationships.
     */
    std::vector<int> get_all_uses_statements();

    /**
     * Get all procedures having one or more Uses relationships.
     * @return Return a string vector of procedures having one or more Uses relationships.
     */
    std::vector<std::string> get_all_uses_procedures();

    /**
     * Get all procedure-variable Uses relationships.
     * @return Return an unordered_map<string, vector<string>> with procedure name as key and variable(s) as value.
     */
    std::unordered_map<std::string, std::vector<std::string>> get_all_uses_procedures_relationship();

    /**
     * Get all statement-variable Uses relationships.
     * @return Return an unordered_map<int, vector<string>> with statement number as key and variable(s) as value.
     */
    std::unordered_map<int, std::vector<std::string>> get_all_uses_statements_relationship();

    /**
     * Return true if the UsesBank is empty.
     * @return Return true if the UsesBank is empty.
     */
    bool does_uses_exist();

private:
    Bank<int, std::string> stmt_bank;
    Bank<std::string, std::string> proc_bank;
};

#endif //AUTOTESTER_USESBANK_H
