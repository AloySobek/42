///////////////////////////////////////////////////////////////////////////////
// ViewGL.h
// ========
// matrixModelView
// Controller & View component of OpenGL window
// We only implement mouse event handlers.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2012-04-17
// UPDATED: 2018-03-05
//
// Copyright (c) 2012-2018 Song Ho Ahn. All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#import "ViewGL.h"

@implementation ViewGL

@synthesize model;


///////////////////////////////////////////////////////////////////////////////
- (void)awakeFromNib
{
    [super awakeFromNib];
    //printf("ViewGL: awakeFromNib\n");
}



///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL states here
- (void)prepareOpenGL
{
    [super prepareOpenGL];
    //printf("ViewGL: prepareOpenGL\n");

    // OpenGL RC is active at this moment, initialize OpenGL/GLSL
    model->init();
    printf("OpenGL is initialized.\n");

    bool glslSupported = model->initShaders();
    if(glslSupported)
        printf("GLSL is initialized.\n");
    else
        printf("[ERROR] Failed to initialize GLSL.\n");

    // draw first time
    model->draw();
    [self.openGLContext flushBuffer];
}



///////////////////////////////////////////////////////////////////////////////
- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    //printf("ViewGL: drawRect\n\n");

    if(!model)
        return;

    model->draw();
    [self.openGLContext flushBuffer];
}



///////////////////////////////////////////////////////////////////////////////
- (void)reshape
{
    if(!model)
        return;

    int width = (int)self.bounds.size.width;
    int height = (int)self.bounds.size.height;
    model->setWindowSize(width, height);
    [self setNeedsDisplay:YES];

    printf("OpenGL window is resized: %d x %d\n", width, height);
}



///////////////////////////////////////////////////////////////////////////////
// override this function returns YES, so, the class can receive mouse event
- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)acceptsFirstMouse:(NSEvent*)event
{
    return YES;
}



///////////////////////////////////////////////////////////////////////////////
// handle mouse events
- (void)mouseDown:(NSEvent*)event
{
    if(!model)
        return;

    NSPoint pos = [NSEvent mouseLocation];
    model->setMousePosition((int)pos.x, (int)-pos.y);
}

- (void)mouseUp:(NSEvent*)event
{
    if(!model)
        return;

    NSPoint pos = [NSEvent mouseLocation];
    model->setMousePosition((int)pos.x, (int)-pos.y);
}

- (void)rightMouseDown:(NSEvent*)event
{
    if(!model)
        return;

    NSPoint pos = [NSEvent mouseLocation];
    model->setMousePosition((int)pos.x, (int)-pos.y);
}

- (void)rightMouseUp:(NSEvent*)event
{
    if(!model)
        return;

    NSPoint pos = [NSEvent mouseLocation];
    model->setMousePosition((int)pos.x, (int)-pos.y);
}

- (void)mouseDragged:(NSEvent*)event
{
    if(!model)
        return;

    NSPoint pos = [NSEvent mouseLocation];

    model->rotateCamera((int)pos.x, (int)-pos.y);
    [self setNeedsDisplay:YES];
}

- (void)rightMouseDragged:(NSEvent*)theEvent
{
    if(!model)
        return;

    NSPoint pos = [NSEvent mouseLocation];

    model->zoomCamera((int)-pos.y);
    [self setNeedsDisplay:YES];
}

- (void)scrollWheel:(NSEvent*)event
{
    if(!model)
        return;

    NSPoint pos = [NSEvent mouseLocation];
    int delta = (int)[event deltaY];

    model->setMousePosition((int)pos.x, (int)-pos.y);
    model->zoomCamera((int)-pos.y + delta);
    [self setNeedsDisplay:YES];
}

@end
