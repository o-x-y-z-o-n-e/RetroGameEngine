#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "rge.hpp"

namespace physics {

    struct ray {

    };

    struct cast_hit {

    };

    class collider_group {

    public:
        cast_hit circle_cast(rge::vec2 center, float radius);

    private:
        
        std::vector<rge::rect*> colliders;
        
    };

}

#endif /* _PHYSICS_HPP_ */