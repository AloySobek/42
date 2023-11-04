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

#import <Cocoa/Cocoa.h>
#import "ModelGL.h"

@interface ViewGL : NSOpenGLView

@property (nonatomic) ModelGL* model;

// set model component
- (void)setModel:(ModelGL*)model;

@end
