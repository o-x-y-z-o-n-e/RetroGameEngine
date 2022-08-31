#ifdef SYS_MACOSX
#include "platform/window.h"
#include "core/core.h"
#include "video/renderer.h"
#include "util/debug.h"

#import <Cocoa/Cocoa.h>

static NSAutoreleasePool* pool;
static NSWindow* window;

static viewport_t viewport;


//------------------------------------------------------------------------------


int init_system() {
    
    return 1;
}


//------------------------------------------------------------------------------


int create_window() {
    pool = [[NSAutoreleasePool alloc] init];

    [NSApplication sharedApplication];

    NSUInteger windowStyle = NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask;

    NSRect windowRect = NSMakeRect(100, 100, 640, 400);

    window = [
        [NSWindow alloc]
        initWithContentRect:windowRect
		styleMask:windowStyle
		backing:NSBackingStoreBuffered
		defer:NO
    ];

    [window autorelease];

    NSWindowController* windowController = [[NSWindowController alloc] initWithWindow:window]; 
	[windowController autorelease];

    [window orderFrontRegardless];
	[NSApp run];
    
    return 1;
}


//------------------------------------------------------------------------------


void close_window() {

    [pool drain];
}


//------------------------------------------------------------------------------


void set_viewport(uint16_t width, uint16_t height) {
    viewport.width = width;
	viewport.height = height;

    // TODO: Update window frame.
}


//------------------------------------------------------------------------------


void poll_window_events() {

}


//------------------------------------------------------------------------------


void refresh_window() {

}


//------------------------------------------------------------------------------


viewport_t* get_viewport() {
	return &viewport;
}


//------------------------------------------------------------------------------


void set_title_window(const char* title) {
    
}

#endif