#include "catch.hpp"
#include "PQLParser.h"
#include "Optimizer.h"

TEST_CASE("Optimizer split no synonym clause correctly.")
{
    std::vector<pql_dto::Entity> select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;
    std::deque<pql_dto::Constraint> no_synonym_clauses;
    std::deque<pql_dto::Constraint> synonym_clauses;

    SECTION("3 synonym clauses and 2 no synonym such that clauses.")
    {
        std::string test_query = "variable v; Select v such that Modifies(6, v) and Follows(1,2) and Uses(6, v) and Parent(3, 4) such that Modifies(5,v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 5);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 2);
        REQUIRE(synonym_clauses.size() == 3);
    }

    SECTION("2 synonym clauses and 3 no synonym such that clauses.")
    {
        std::string test_query = "variable v; Select v such that Modifies(6, \"v\") and Follows(1,2) and Uses(6, v) and Parent(3, 4) such that Modifies(5,v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 5);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 3);
        REQUIRE(synonym_clauses.size() == 2);
    }

    SECTION("5 pattern clauses.")
    {
        std::string test_query = "assign a; if ifs; while w; Select a pattern a(_,_) and ifs (_,_,_) and w (_,_) pattern w (\"v\", _) pattern a (\"x\", _\"x+u\"_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 5);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 5);
    }

    SECTION("5 with clauses.")
    {
        std::string test_query = "assign a, a1; if ifs; procedure proc; variable v; Select a with a.stmt# = 6 and ifs.stmt# = 5 with a1.stmt# = 1 and v.varName = \"y\" and proc.procName = \"main\"";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 5);

        error = Optimizer::split_clauses_with_no_synonyms(such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 5);
    }
}