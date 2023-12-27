#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "rge.hpp"

class entity {
	
public:
	entity();
	~entity();

    virtual void draw();
	virtual void update(float delta_time);

	inline rge::rect get_bounds() const { return bounds; }

protected:
	rge::rect bounds;

};

#endif /* _ENTITY_HPP_ */