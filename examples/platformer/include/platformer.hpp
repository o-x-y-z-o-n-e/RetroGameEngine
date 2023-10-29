#ifndef _PLATFORMER_HPP_
#define _PLATFORMER_HPP_

#include "rge.hpp"

class platformer : public rge::engine {

public:
	static platformer* get() { return (platformer*)get_instance(); }
};

#endif /* _PLATFORMER_HPP_ */