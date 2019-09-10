#include "Relationships.h"

namespace pql_dto
{
    class FollowsRelationship : public Relationships
    {
    public:
        FollowsRelationship(Entity first_param, Entity second_param, bool is_star)
        {
            set_relationship(FOLLOWS);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void set_first_param(Entity param)
        {

        }

        void set_second_param(Entity param)
        {

        }
    };
}
