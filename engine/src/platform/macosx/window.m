#ifdef SYS_MACOSX
#include "api/rge.h"
#include "platform/window.h"
#include "platform/system.h" // TEMP
#include "core/core.h"
#include "core/input.h"
#include "core/renderer.h"

#include <stdlib.h>

#include <Cocoa/Cocoa.h>
#include <CoreGraphics/CoreGraphics.h>

static void create_frame_buffer();

static NSApplication* app;
static NSWindow* window;
static NSView* view;

static uint16_t window_width = 640;
static uint16_t window_height = 400;


//------------------------------------------------------------------------------


@interface AppDelegate : NSObject<NSApplicationDelegate, NSWindowDelegate>
@end


//------------------------------------------------------------------------------


@implementation AppDelegate

-(void)windowDidResize:(NSNotification*)notification {
    NSSize window_size = [[window contentView] frame].size;
    window_width = (uint16_t)window_size.width;
    window_height = (uint16_t)window_size.height;
    create_frame_buffer();
}

-(void)windowWillClose:(NSNotification*)notification {
    rge_core_close();
}  

@end


@interface View : NSView
@end

@implementation View

-(bool)acceptsFirstResponder {
    return YES;
}

-(void)keyDown:(NSEvent*)event {
    if(event.type == NSEventTypeKeyDown) {
        uint8_t key = rge_system_parse_key(event.keyCode);
        rge_input_set_state(key, true);
    }
}

-(void)keyUp:(NSEvent*)event {
    if(event.type == NSEventTypeKeyUp) {
        uint8_t key = rge_system_parse_key(event.keyCode);
        rge_input_set_state(key, false);
    }
}

@end


//------------------------------------------------------------------------------


static AppDelegate* delegate;
static CGContextRef gc;

struct {
	viewport_t viewport;
	uint16_t x_offset;
	uint16_t y_offset;
} static frame;


//------------------------------------------------------------------------------


static void create_frame_buffer() {
    uint16_t w_scale = window_width / frame.viewport.width;
	uint16_t h_scale = window_height / frame.viewport.height;

	frame.viewport.scale = w_scale;
	if(h_scale < w_scale)
		frame.viewport.scale = h_scale;

	if(frame.viewport.scale == 0)
		frame.viewport.scale = 1;

	uint16_t frame_width = frame.viewport.width * frame.viewport.scale;
	uint16_t frame_height = frame.viewport.height * frame.viewport.scale;

	frame.x_offset = (window_width - frame_width) / 2;
	frame.y_offset = (window_height - frame_height) / 2;

    CGContextRelease(gc);

    CGColorSpaceRef rgb = CGColorSpaceCreateWithName(kCGColorSpaceLinearSRGB);
    gc = CGBitmapContextCreate(NULL, frame_width, frame_height, 8, 0, rgb, kCGImageByteOrder32Big | kCGImageAlphaPremultipliedLast);
    CGColorSpaceRelease(rgb);

    size_t pitch = CGBitmapContextGetBytesPerRow(gc);
    frame.viewport.buffer = CGBitmapContextGetData(gc);
}


//------------------------------------------------------------------------------


// TEMP: move to system.m
int rge_system_init() {
    app = [NSApplication sharedApplication];

    delegate = [[AppDelegate alloc] init];
    [app setDelegate:delegate];

    [app setActivationPolicy:NSApplicationActivationPolicyRegular];

    [app finishLaunching];

    return 1;
}


//------------------------------------------------------------------------------


int rge_window_create() {
    NSUInteger windowStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

    NSRect screenRect = [[NSScreen mainScreen] frame];
    NSRect viewRect = NSMakeRect(0, 0, window_width, window_height);
    NSRect windowRect = NSMakeRect(
        NSMidX(screenRect) - NSMidX(viewRect),
        NSMidY(screenRect) - NSMidY(viewRect),
        viewRect.size.width,
        viewRect.size.height
    );

    window = [
        [NSWindow alloc]
        initWithContentRect:windowRect
		styleMask:windowStyle
		backing:NSBackingStoreBuffered
		defer:NO
    ];

    NSWindowController* windowController = [[NSWindowController alloc] initWithWindow:window];
	[windowController autorelease];

    //view = [[[View alloc] initWithFrame:viewRect] autorelease];
    view = [[View alloc] initWithFrame:NSMakeRect(0, 0, 100, 200)];
    //[window setContentView:view];
    [[window contentView] addSubview:view];

    [window setDelegate:delegate];

    //[window setAcceptsMouseMovedEvents:YES];
    [window orderFrontRegardless];
    //[window makeKeyAndOrderFront:nil];

    [view setNeedsDisplay:YES];

    [NSApp activateIgnoringOtherApps:YES];

    create_frame_buffer();
    
    return 1;
}


//------------------------------------------------------------------------------


void rge_window_close() {
    [window close];
    [window release];
}


//------------------------------------------------------------------------------


void rge_window_set_viewport(uint16_t width, uint16_t height) {
    frame.viewport.width = width;
	frame.viewport.height = height;

    create_frame_buffer();
}


//------------------------------------------------------------------------------


void rge_window_poll_events() {
    @autoreleasepool {
        NSEvent* ev;
        do {
            ev = [NSApp nextEventMatchingMask: NSEventMaskAny
                                    untilDate: nil
                                       inMode: NSDefaultRunLoopMode
                                      dequeue: YES];
            if (ev) {
                // handle events here
                [NSApp sendEvent: ev];
            }
        } while (ev);
    }
}


//------------------------------------------------------------------------------


void rge_window_refresh() {
    CGImageRef image = CGBitmapContextCreateImage(gc);
    window.contentView.wantsLayer = YES;
    window.contentView.layer.contents = (__bridge id)image;
    CGImageRelease(image);
}


//------------------------------------------------------------------------------


viewport_t* rge_window_get_viewport() {
	return &frame.viewport;
}


//------------------------------------------------------------------------------


void rge_window_set_title(const char* title) {
    [window setTitle:@(title)];
}

#endif