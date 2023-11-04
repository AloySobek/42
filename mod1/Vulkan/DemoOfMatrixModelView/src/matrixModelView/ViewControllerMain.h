///////////////////////////////////////////////////////////////////////////////
// ViewControllerMain.h
// ====================
// main controller component of matrixModeView
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2018-03-14
// UPDATED: 2018-03-15
//
// Copyright (c)) 2012 - 2018 Song Ho Ahn. All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#import <Cocoa/Cocoa.h>
#import "ModelGL.h"
#import "ViewGL.h"

@interface ViewControllerMain : NSViewController

@property (nonatomic) ModelGL modelGL;
@property (weak) IBOutlet ViewGL* viewGL;

@property (weak) IBOutlet NSSlider* sliderViewPosX;
@property (weak) IBOutlet NSSlider* sliderViewPosY;
@property (weak) IBOutlet NSSlider* sliderViewPosZ;
@property (weak) IBOutlet NSSlider* sliderViewRotX;
@property (weak) IBOutlet NSSlider* sliderViewRotY;
@property (weak) IBOutlet NSSlider* sliderViewRotZ;

@property (weak) IBOutlet NSSlider* sliderModelPosX;
@property (weak) IBOutlet NSSlider* sliderModelPosY;
@property (weak) IBOutlet NSSlider* sliderModelPosZ;
@property (weak) IBOutlet NSSlider* sliderModelRotX;
@property (weak) IBOutlet NSSlider* sliderModelRotY;
@property (weak) IBOutlet NSSlider* sliderModelRotZ;

@property (weak) IBOutlet NSTextField* labelViewPosX;
@property (weak) IBOutlet NSTextField* labelViewPosY;
@property (weak) IBOutlet NSTextField* labelViewPosZ;
@property (weak) IBOutlet NSTextField* labelViewRotX;
@property (weak) IBOutlet NSTextField* labelViewRotY;
@property (weak) IBOutlet NSTextField* labelViewRotZ;

@property (weak) IBOutlet NSTextField* labelModelPosX;
@property (weak) IBOutlet NSTextField* labelModelPosY;
@property (weak) IBOutlet NSTextField* labelModelPosZ;
@property (weak) IBOutlet NSTextField* labelModelRotX;
@property (weak) IBOutlet NSTextField* labelModelRotY;
@property (weak) IBOutlet NSTextField* labelModelRotZ;

@property (weak) IBOutlet NSTextField* textViewGL;
@property (weak) IBOutlet NSTextField* textModelGL;

- (IBAction)updateViewParameter:(id)sender;
- (IBAction)updateModelParameter:(id)sender;
- (IBAction)resetView:(id)sender;
- (IBAction)resetModel:(id)sender;
- (void)updateViewMatrixElements;
- (void)updateModelMatrixElements;
- (void)updateModelViewMatrixElements;
- (void)updateViewMatrixCalls;
- (void)updateModelMatrixCalls;

@end
