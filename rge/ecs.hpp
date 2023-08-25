/* RetroGameEngine (RGE) ECS Extension
   Author: Jeremy Kiel
   Version: 0.00.1
   License: N/A
*/

#ifndef RGE_ECS
#define RGE_ECS

#include <rge/rge.hpp>

namespace rge {
namespace ecs {

struct entity {
    std::string name;
};

class registry {
public:
	entity* create();
    bool destroy(entity* entity);
};

}
}

#endif /* RGE_ECS */