#include <pql_dto/Entity.h>
#include "QueryUtility.h"

/*
Checks if the entity is a statement number
 */
bool QueryUtility::is_statement_num(pql_dto::Entity &entity)
{
    return !entity.is_entity_declared() && (entity.get_entity_type() == EntityType::STMT || entity.get_entity_attr() == AttributeType::STMTNUM);
}

/*
Checks if the entity is a program line
 */
bool QueryUtility::is_program_line(pql_dto::Entity &entity)
{
    return !(entity.is_entity_declared() || entity.get_entity_type() != EntityType::PROG_LINE);
}

bool QueryUtility::is_constant(pql_dto::Entity &entity)
{
    return !entity.is_entity_declared() && entity.get_entity_type() == EntityType::CONSTANT;
}

/*
Checks if the entity is a procedure undeclared
*/
bool QueryUtility::is_proc_name(pql_dto::Entity &entity)
{
    return !entity.is_entity_declared() && (entity.get_entity_type() == EntityType::PROCEDURE || entity.get_entity_attr() == AttributeType::PROCNAME);
}

/*
Checks if the entity is a procedure declared
*/
bool QueryUtility::is_proc_declared(pql_dto::Entity &entity)
{
    return (entity.is_entity_declared() && entity.get_entity_type() == EntityType::PROCEDURE);
}

/*
Checks if the entity is a variable undeclared
*/
bool QueryUtility::is_var_name(pql_dto::Entity &entity)
{
    return !entity.is_entity_declared() && (entity.get_entity_type() == EntityType::VARIABLE || entity.get_entity_attr() == AttributeType::VARNAME);
}

string QueryUtility::get_entity_type_name(pql_dto::Entity entity)
{
    string result;
    EntityType entity_type = entity.get_entity_type();
    if (entity_type == EntityType::IF)
    {
        result = "If";
    }
    if (entity_type == EntityType::WHILE)
    {
        result = "While";
    }
    if (entity_type == EntityType::ASSIGN)
    {
        result = "Assign";
    }
    if (entity_type == EntityType::PROG_LINE)
    {
        result = "ProgLine";
    }
    if (entity_type == EntityType::PRINT)
    {
        result = "Print";
    }
    if (entity_type == EntityType::CALL)
    {
        result = "Call";
    }
    if (entity_type == EntityType::ANY)
    {
        result = "_";
    }
    if (entity_type == EntityType::CONSTANT)
    {
        result = "Constant";
    }
    if (entity_type == EntityType::PROCEDURE)
    {
        result = "Procedure";
    }
    if (entity_type == EntityType::READ)
    {
        result = "Read";
    }
    if (entity_type == EntityType::STMT)
    {
        result = "Statement";
    }
    if (entity_type == EntityType::VARIABLE)
    {
        result = "Variable";
    }
    return result;
}

string QueryUtility::get_clause_type_name(pql_dto::Relationships relation)
{
    string result;
    RelationshipType relation_type = relation.get_relationship_type();
    if (relation_type == RelationshipType::FOLLOWS)
    {
        if (!relation.is_relationship_star())
        {
            result = "Follows";
        }
        else
        {
            result = "FollowsStar";
        }
    }
    if (relation_type == RelationshipType::PARENT)
    {
        if (!relation.is_relationship_star())
        {
            result = "Parent";
        }
        else
        {
            result = "ParentStar";
        }
    }
    if (relation_type == RelationshipType::USES)
    {
        result = "Uses";
    }
    if (relation_type == RelationshipType::MODIFIES)
    {
        result = "Modifies";
    }
    if (relation_type == RelationshipType::CALLS)
    {
        if (!relation.is_relationship_star())
        {
            result = "Calls";
        }
        else
        {
            result = "CallsStar";
        }
    }
    if (relation_type == RelationshipType::NEXT)
    {
        if (!relation.is_relationship_star())
        {
            result = "Next";
        }
        else
        {
            result = "NextStar";
        }
    }
    if (relation_type == RelationshipType::NEXTBIP)
    {
        if (!relation.is_relationship_star())
        {
            result = "NextBip";
        }
        else
        {
            result = "NextBipStar";
        }
    }
    if (relation_type == RelationshipType::AFFECTS)
    {
        if (!relation.is_relationship_star())
        {
            result = "Affects";
        }
        else
        {
            result = "AffectsStar";
        }
    }
    if (relation_type == RelationshipType::AFFECTSBIP)
    {
        if (!relation.is_relationship_star())
        {
            result = "AffectsBip";
        }
        else
        {
            result = "AffectsBipStar";
        }
    }
    return result;
}

string QueryUtility::get_clause_type_name(pql_dto::Pattern pattern)
{
    string result;
    EntityType pattern_type = pattern.get_pattern_entity().get_entity_type();
    if (pattern_type == EntityType::ASSIGN)
    {
        result = "Assign";
    }
    if (pattern_type == EntityType::WHILE)
    {
        result = "While";
    }
    if (pattern_type == EntityType::IF)
    {
        result = "If";
    }
    return result;
}

string QueryUtility::get_clause_type_name(pql_dto::With with)
{
    return "With";
}

vector<string> QueryUtility::change_to_attributes(pql_dto::Entity &select_entity,
        vector<string> temp_vec, PKB &PKB)
{
    vector<string> result;
    if (select_entity.get_entity_attr() == AttributeType::NONE || select_entity.get_entity_attr() == AttributeType::STMTNUM || select_entity.get_entity_attr() == AttributeType::VALUE)
    {
        return temp_vec;
    }
    if (select_entity.get_entity_type() == EntityType::CALL)
    {
        for (const auto& iter : temp_vec)
        {
            result.push_back(PKB.get_called_by_statement(stoi(iter)));
        }
    }
    else if (select_entity.get_entity_type() == EntityType::READ)
    {
        for (const auto& iter : temp_vec)
        {
            result.push_back(PKB.get_modified_by_statement(stoi(iter)).at(0));
        }
    }
    else if (select_entity.get_entity_type() == EntityType::PRINT)
    {
        for (const auto& iter : temp_vec)
        {
            result.push_back(PKB.get_used_by_statement(stoi(iter)).at(0));
        }
    }
    else
    {
        return temp_vec;
    }
    return result;
}

/*
 * Returns the string list of certain type
 */
vector<string> QueryUtility::get_certain_type_str_list(EntityType &type, PKB &PKB)
{
    unordered_set<string> type_list;
    unordered_set<string> :: iterator iter;
    vector<string> result;
    if (type == EntityType::VARIABLE)
    {
        type_list = PKB.get_all_variables();
    }

    if (type == EntityType::PROCEDURE)
    {
        type_list = PKB.get_all_procedures();
    }

    if (type == EntityType::CONSTANT)
    {
        return PKB.get_all_constants();
    }

    if (type == EntityType::BOOLEAN)
    {
        return vector<string> {"true", "false"};
    }

    for (iter = type_list.begin(); iter != type_list.end(); iter++)
    {
        result.push_back(*iter);
    }

    return result;
}

/*
 * Returns the int list of certain type
 */
vector<string> QueryUtility::get_certain_type_int_list(EntityType &type, PKB &PKB)
{
    vector<int> type_list;
    vector<string> result;
    if (type == EntityType::ASSIGN)
    {
        type_list = PKB.get_all_assigns();
    }

    if (type == EntityType::STMT || type == EntityType::PROG_LINE)
    {
        type_list = PKB.get_all_statement_nums();
    }

    if (type == EntityType::WHILE)
    {
        type_list = PKB.get_all_whiles();
    }

    if (type == EntityType::IF)
    {
        type_list = PKB.get_all_ifs();
    }

    if (type == EntityType::READ)
    {
        type_list = PKB.get_all_reads();
    }

    if (type == EntityType::PRINT)
    {
        type_list = PKB.get_all_prints();
    }

    if (type == EntityType::CALL)
    {
        type_list = PKB.get_all_calls();
    }

    result.reserve(type_list.size());
    for (auto iter : type_list)
    {
        result.push_back(to_string(iter));
    }

    return result;
}

bool QueryUtility::is_same_type(EntityType type_1, EntityType type_2)
{
    if (type_1 == EntityType::STMT)
    {
        if (type_2 == EntityType::STMT || type_2 == EntityType::ASSIGN || type_2 == EntityType::CALL ||
            type_2 == EntityType::IF || type_2 == EntityType::PRINT || type_2 == EntityType::READ ||
            type_2 == EntityType::WHILE)
        {
            return true;
        }
    }
    if (type_2 == EntityType::STMT)
    {
        if (type_1 == EntityType::STMT || type_1 == EntityType::ASSIGN || type_1 == EntityType::CALL ||
            type_1 == EntityType::IF || type_1 == EntityType::PRINT || type_1 == EntityType::READ ||
            type_1 == EntityType::WHILE)
        {
            return true;
        }
    }
    if (type_1 == EntityType::PROG_LINE || type_2 == EntityType::PROG_LINE)
    {
        return true;
    }
    return type_1 == type_2;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity &key, vector<int> &int_vec, PKB &PKB)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    for (auto &iter : int_vec)
    {
        if (QueryUtility::is_same_type(PKB.get_statement_type(iter), key.get_entity_type()))
        {
            key_value.push_back(to_string(iter));
        }
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity &key, vector<string> &str_vec)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    key_value.reserve(str_vec.size());
    for (auto &iter : str_vec)
    {
        key_value.push_back(iter);
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity &key, int n, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    std::vector<std::string> key_value;
    if (QueryUtility::is_same_type(PKB.get_statement_type(n), key.get_entity_type()))
    {
        key_value.push_back(to_string(n));
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity &key_1, pql_dto::Entity &key_2,
        unordered_map<int, vector<int>> &int_map, PKB &PKB)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto &iter : int_map)
    {
        int first = iter.first;
        vector<int> second = iter.second;
        if (QueryUtility::is_same_type(PKB.get_statement_type(first), key_1.get_entity_type()))
        {
            for (auto &it : second)
            {
                if (QueryUtility::is_same_type(PKB.get_statement_type(it), key_2.get_entity_type()))
                {
                    key_value_1.push_back(to_string(first));
                    key_value_2.push_back(to_string(it));
                }
            }
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity &key_1, pql_dto::Entity &key_2,
        string &name_1, string &name_2, unordered_map<int, vector<int>> &int_map, PKB &PKB)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto &iter : int_map)
    {
        int first = iter.first;
        vector<int> second = iter.second;
        if (QueryUtility::is_same_type(PKB.get_statement_type(first), key_1.get_entity_type()))
        {
            for (auto &it : second)
            {
                if (QueryUtility::is_same_type(PKB.get_statement_type(it), key_2.get_entity_type()))
                {
                    if (first == it)
                    {
                        key_value_1.push_back(to_string(first));
                        key_value_2.push_back(to_string(it));
                    }
                }
            }
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity &key_1, pql_dto::Entity &key_2,
        unordered_map<string, vector<string>> &str_map)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto &iter : str_map)
    {
        string first = iter.first;
        vector<string> second = iter.second;
        for (const auto &it : second)
        {
            key_value_1.push_back(first);
            key_value_2.push_back(it);
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity &key_1, pql_dto::Entity &key_2,
        unordered_map<int, vector<string>> &int_str_map, PKB &PKB)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto &iter : int_str_map)
    {
        int first = iter.first;
        vector<string> second = iter.second;
        if (QueryUtility::is_same_type(PKB.get_statement_type(first), key_1.get_entity_type()))
        {
            for (auto &it : second)
            {
                key_value_1.push_back(to_string(first));
                key_value_2.push_back(it);
            }
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(string &str, vector<int> &int_vec)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    key_value.reserve(int_vec.size());
    for (auto &iter : int_vec)
    {
        key_value.push_back(to_string(iter));
    }
    result[str] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(string &str_1, string &str_2,
        vector<int> &int_vec, PKB &PKB)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    for (auto &iter : int_vec)
    {
        if (PKB.assign_to_variable(iter) == str_2)
        {
            key_value.push_back(to_string(iter));
        }
    }
    result[str_1] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(string &str, pql_dto::Entity &key,
        vector<int> &int_vec, PKB &PKB)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto &iter : int_vec)
    {
        key_value_1.push_back(to_string(iter));
        key_value_2.push_back(PKB.assign_to_variable(iter));
    }
    result[str] = key_value_1;
    result[key.get_entity_name()] = key_value_2;
    return result;
}
