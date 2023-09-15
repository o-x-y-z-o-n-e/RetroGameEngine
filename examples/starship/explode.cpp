#include "explode.hpp"

explode::explode() {
    transform = rge::transform::create();
    sprite = rge::sprite::create();
    sprite->transform->parent = transform;
    sprite->pixels_per_unit = 16;
}

explode::~explode() {
    
}

void explode::reset() {
    
}

void explode::update(float delta_time) {
    counter += delta_time;
    if(counter >= 1.0F) {
        counter -= 1.0F;
        index++;
    }

    if(index >= textures.size()) {
        // destroy(this);
    }
}

void explode::draw() {
    sprite->texture = textures[index];
    // TODO
}