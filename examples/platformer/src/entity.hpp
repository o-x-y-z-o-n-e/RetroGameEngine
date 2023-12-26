#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

class entity {
	
public:
	entity();
	~entity();

    virtual void draw();
	virtual void update(float delta_time);

};

#endif /* _ENTITY_HPP_ */