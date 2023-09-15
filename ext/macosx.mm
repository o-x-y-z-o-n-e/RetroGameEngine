#include "macosx.hpp"
#include <Cocoa/Cocoa.h>
#include <OpenGL/OpenGL.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@interface RGEView : NSOpenGLView

@end

@interface RGEWindow : NSWindow

@end

@interface RGEWindowListener : NSObject
- (BOOL)windowShouldClose:(id)sender;
@end

static NSApplication* app = nil;
static RGEWindow* window = nil;
static RGEView* view = nil;

static uint64_t s_move_hack = 0;

namespace rge {

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
    return rge::OK;
}

rge::result macosx::create_window(const std::string& title, int width, int height, bool fullscreen) {
	window_width = width;
	window_height = height;

	NSRect rect;
	rect.origin.x = 0;
    rect.origin.y = 0;
    rect.size.width = width;
    rect.size.height = height;

	NSUInteger style = 0;

	@try {
        window = [[RGEWindow alloc] initWithContentRect:rect styleMask:style backing:NSBackingStoreBuffered defer:NO];
    } @catch(NSException *e) {
    	rge::log::error("%s", [[e reason] UTF8String]);
		return rge::FAIL;
    }

    [window setColorSpace:[NSColorSpace sRGBColorSpace]];

	rect = [window contentRectForFrameRect:[window frame]];
    view = [[RGEView alloc] initWithFrame:rect];
	// [contentView setSDLWindow:window];
	
	[window setContentView:view];
	return rge::OK;
}

void macosx::set_window_title(const std::string& title) {
	const char *c_title = title.c_str();
	NSString *string = [[NSString alloc] initWithUTF8String:c_title];
    [window setTitle:string];
}

void macosx::set_window_size(int width, int height) {
	window_width = width;
	window_height = height;

	@autoreleasepool {
        NSRect rect = [window contentRectForFrameRect:[window frame]];
        uint64_t move_hack;

        rect.size.width = window_width;
        rect.size.height = window_height;

        move_hack = s_move_hack;
        s_move_hack = 0;
        [window setFrame:[window frameRectForContentRect:rect] display:YES];
        s_move_hack = move_hack;
    }
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

@implementation RGEView

@end

@implementation RGEWindow : NSWindow

@end

@implementation RGEWindowListener : NSObject
- (BOOL)windowShouldClose:(id)sender {
    rge::window_close_requested_event e;
	rge::engine::get_instance()->post_event(e);
    return NO;
}

- (void)windowDidResize:(NSNotification *)aNotification {
    NSRect rect = [window contentRectForFrameRect:[window frame]];

	{
		rge::window_moved_event e;
		e.x = (int)rect.origin.x;
		e.y = (int)rect.origin.y;
		rge::engine::get_instance()->post_event(e);
	}

	{
		rge::window_resized_event e;
		e.width = (int)rect.size.width;
		e.height = (int)rect.size.height;
		rge::engine::get_instance()->post_event(e);
	}
}
@end

#pragma clang diagnostic pop