#pragma once
#ifndef AUTOTESTER_DESIGNEXTRACTOR_H
#define AUTOTESTER_DESIGNEXTRACTOR_H

#include <stack>

#include "Bank.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "ParentBank.h"
#include "ParentStarBank.h"
#include "UsesBank.h"
#include "ModifiesBank.h"
#include "CallsBank.h"
#include "CallsStarBank.h"
#include "PKB.h"

class PKB;
class DesignExtractor
{
public:
    /**
     * Extract Follows* relationships and populate into PKB.
     * This method should only be called after all insertion have been done so that the method
     * can extract all possible relationships based on the inserts.
     * @param &bank_in reference to FollowsBank.
     * @param &bank_out reference to FollowsStarBank.
     * @return true if extraction and insertion process is successful. return false if there is nothing to extract and insert.
     */
    static bool extract_follows_star(FollowsBank &bank_in, FollowsStarBank &bank_out);
    /**
     * Extract Parent* relationships and populate into PKB.
     * This method also populate new Uses and Modifies relationship created during the extraction process of Parent* relationship into the PKB.
     * This method should only be called after all insertion have been done so that the method
     * can extract all possible relationships based on the inserts.
     * @param &bank_in reference to ParentBank.
     * @param &bank_out reference to ParentStarBank.
     * @param &uses_bank reference to UsesBank.
     * @param &modifies_bank reference to ModifiesBank.
     * @return true if extraction and insertion process is successful. return false if there is nothing to extract and insert.
     */
    static bool extract_parent_star(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank);
    /**
     * Extract Calls* relationships and populate into PKB.
     * This method also populate new Uses and Modifies relationship created during the extraction process of Calls* relationship into the PKB.
     * This method should only be called after all insertion have been done so that the method.
     * This method to be called after Design Extractor extracted all Parent* relationship.
     * can extract all possible relationships based on the inserts.
     * @param &bank_in reference to CallsBank.
     * @param &bank_out reference to CallsStarBank.
     * @param &uses_bank reference to UsesBank.
     * @param &modifies_bank reference to ModifiesBank.
     * @param &parent_star_bank reference to ParentStarBank.
     * @return true if extraction and insertion process is successful. return false if there is nothing to extract and insert.
     */
    static bool extract_calls_star(CallsBank &bank_in, CallsStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank, ParentStarBank &parent_star_bank);
    
    static bool extract_next_bip(PKB &pkb);

private:
    static void extract_further_parents_child(ParentBank &bank_in, ParentStarBank &bank_out,
            UsesBank &uses_bank, ModifiesBank &modifies_bank, std::vector<int> parents, int child);
    static void extract_next_bip_helper(PKB& pkb, int previous, std::vector<int> next_of_old_previous);
};

#endif //AUTOTESTER_DESIGNEXTRACTOR_H
