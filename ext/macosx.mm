#include "macosx.hpp"
#include <Cocoa/Cocoa.h>

namespace rge {

static NSApplication* app;

static macosx* get_instance() {
	return (macosx*)rge::engine::get_platform();
}

macosx::macosx() : platform() {
	window_width = 0;
	window_height = 0;
	has_init = false;
	has_window = false;
}

rge::result macosx::init(rge::engine* engine) {
    return rge::FAIL;
}

rge::result macosx::create_window(const std::string& title, int width, int height, bool fullscreen) {
	window_width = width;
	window_height = height;
	return rge::FAIL;
}

void macosx::set_window_title(const std::string& title) {
	
}

void macosx::set_window_size(int width, int height) {

}

void macosx::set_fullscreen(bool fullscreen) {

}

void macosx::poll_gamepads() {
	
}

void macosx::poll_events() {
	
}

void macosx::refresh_window() {
	
}

bool macosx::is_focused() const {
	return true;
}

void macosx::clean_up() {
	
}

}