#ifndef MACOSX_H
#define MACOSX_H

#include "rge.hpp"

namespace rge {

class macosx : public rge::platform {
private:
	int window_width;
	int window_height;
	bool has_init;
	bool has_window;

public:
	macosx();
	rge::result init(rge::engine* engine) override;
	rge::result create_window(const std::string& title, int width, int height, bool fullscreen) override;
	void set_window_title(const std::string& title) override;
	void set_window_size(int width, int height) override;
	void set_fullscreen(bool fullscreen) override;
	void poll_gamepads() override;
	void poll_events() override;
	void refresh_window() override;
	bool is_focused() const override;
	void clean_up() override;
};

}

#endif /* MACOSX_H */