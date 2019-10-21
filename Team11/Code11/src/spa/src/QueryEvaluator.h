#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <PKB.h>
#include <PQLParser.h>
#include <QueryUtility.h>
#include <FollowsEvaluator.h>
#include <FollowsStarEvaluator.h>
#include <ParentEvaluator.h>
#include <ParentStarEvaluator.h>
#include <ModifiesEvaluator.h>
#include <UsesEvaluator.h>
#include <AssignEvaluator.h>
#include <CallsEvaluator.h>
#include <CallsStarEvaluator.h>
#include <NextEvaluator.h>
#include <NextStarEvaluator.h>
#include <WhileEvaluator.h>
#include <IfEvaluator.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/With.h>

class QueryEvaluator
{
public:
    static unordered_set<string> get_result(string &query, PKB &PKB);
    static unordered_set<string> merge(vector<pql_dto::Entity> &select_clause,
            unordered_map<string, vector<string>> &select_list,
            unordered_map<string, vector<string>> &such_that_list,
            unordered_map<string, vector<string>> &pattern_list,
            bool visited_such_that);
    static unordered_set<string> get_common_synonyms(unordered_map<string, vector<string>> &map_1,
            unordered_map<string, vector<string>> &map_2);
    static bool is_empty_map(unordered_map<string, vector<string>> &map);
    static unordered_map<string, vector<string>> merge_two_maps(unordered_map<string, vector<string>> map_1,
            unordered_map<string, vector<string>> map_2, unordered_set<string> common_synonym);
    static unordered_set<string> get_common_part(vector<string> &str_vec_1, vector<string> &str_vec_2);
};
