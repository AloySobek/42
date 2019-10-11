///////////////////////////////////////////////////////////////////////////////
// ViewControllerMain.mm
// =====================
// main controller component of matrixModeView
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2018-03-14
// UPDATED: 2018-04-16
//
// Copyright (c)) 2012 - 2018 Song Ho Ahn. All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#import "ViewControllerMain.h"
#import <sstream>
#import <iomanip>

@interface ViewControllerMain ()

@end

@implementation ViewControllerMain

@synthesize modelGL;
@synthesize viewGL;
@synthesize sliderViewPosX;
@synthesize sliderViewPosY;
@synthesize sliderViewPosZ;
@synthesize sliderViewRotX;
@synthesize sliderViewRotY;
@synthesize sliderViewRotZ;
@synthesize sliderModelPosX;
@synthesize sliderModelPosY;
@synthesize sliderModelPosZ;
@synthesize sliderModelRotX;
@synthesize sliderModelRotY;
@synthesize sliderModelRotZ;
@synthesize labelViewPosX;
@synthesize labelViewPosY;
@synthesize labelViewPosZ;
@synthesize labelViewRotX;
@synthesize labelViewRotY;
@synthesize labelViewRotZ;
@synthesize labelModelPosX;
@synthesize labelModelPosY;
@synthesize labelModelPosZ;
@synthesize labelModelRotX;
@synthesize labelModelRotY;
@synthesize labelModelRotZ;
@synthesize textViewGL;
@synthesize textModelGL;



///////////////////////////////////////////////////////////////////////////////
- (void)viewDidLoad
{
    [super viewDidLoad];
    //printf("ViewControllerMain: viewDidLoad\n");

    // pass ptr to model
    viewGL.model = &modelGL;

    // init UI controls
    [self resetView:nil];
    [self resetModel:nil];
}



///////////////////////////////////////////////////////////////////////////////
- (IBAction)updateViewParameter:(id)sender
{
    NSSlider* slider = (NSSlider*)sender;
    int value = slider.intValue;
    slider.intValue = value;

    if(slider == sliderViewPosX)
    {
        labelViewPosX.intValue = value;
        modelGL.setCameraX(value);
    }
    else if(slider == sliderViewPosY)
    {
        labelViewPosY.intValue = value;
        modelGL.setCameraY(value);
    }
    else if(slider == sliderViewPosZ)
    {
        labelViewPosZ.intValue = value;
        modelGL.setCameraZ(value);
    }
    else if(slider == sliderViewRotX)
    {
        labelViewRotX.intValue = value;
        modelGL.setCameraAngleX(value);
    }
    else if(slider == sliderViewRotY)
    {
        labelViewRotY.intValue = value;
        modelGL.setCameraAngleY(value);
    }
    else if(slider == sliderViewRotZ)
    {
        labelViewRotZ.intValue = value;
        modelGL.setCameraAngleZ(value);
    }

    [self updateViewMatrixElements];
    [self updateModelViewMatrixElements];
    [self updateViewMatrixCalls];
    [viewGL setNeedsDisplay:YES];
}



///////////////////////////////////////////////////////////////////////////////
- (IBAction)updateModelParameter:(id)sender
{
    NSSlider* slider = (NSSlider*)sender;
    int value = slider.intValue;
    slider.intValue = value;

    if(slider == sliderModelPosX)
    {
        labelModelPosX.intValue = value;
        modelGL.setModelX(value);
    }
    else if(slider == sliderModelPosY)
    {
        labelModelPosY.intValue = value;
        modelGL.setModelY(value);
    }
    else if(slider == sliderModelPosZ)
    {
        labelModelPosZ.intValue = value;
        modelGL.setModelZ(value);
    }
    else if(slider == sliderModelRotX)
    {
        labelModelRotX.intValue = value;
        modelGL.setModelAngleX(value);
    }
    else if(slider == sliderModelRotY)
    {
        labelModelRotY.intValue = value;
        modelGL.setModelAngleY(value);
    }
    else if(slider == sliderModelRotZ)
    {
        labelModelRotZ.intValue = value;
        modelGL.setModelAngleZ(value);
    }

    [self updateModelMatrixElements];
    [self updateModelViewMatrixElements];
    [self updateModelMatrixCalls];
    [viewGL setNeedsDisplay:YES];
}



///////////////////////////////////////////////////////////////////////////////
- (IBAction)resetView:(id)sender
{
    sliderViewPosX.intValue = 0;
    sliderViewPosY.intValue = 0;
    sliderViewPosZ.intValue = 10;
    sliderViewRotX.intValue = 0;
    sliderViewRotY.intValue = 0;
    sliderViewRotZ.intValue = 0;

    labelViewPosX.intValue = 0;
    labelViewPosY.intValue = 0;
    labelViewPosZ.intValue = 10;
    labelViewRotX.intValue = 0;
    labelViewRotY.intValue = 0;
    labelViewRotZ.intValue = 0;

    modelGL.setViewMatrix(0, 0, 10, 0, 0, 0);
    [self updateViewMatrixElements];
    [self updateModelViewMatrixElements];
    [self updateViewMatrixCalls];

    // redraw opengl scene
    [viewGL setNeedsDisplay:YES];
}



///////////////////////////////////////////////////////////////////////////////
- (IBAction)resetModel:(id)sender
{
    sliderModelPosX.intValue = 0;
    sliderModelPosY.intValue = 0;
    sliderModelPosZ.intValue = 0;
    sliderModelRotX.intValue = 0;
    sliderModelRotY.intValue = 0;
    sliderModelRotZ.intValue = 0;

    labelModelPosX.intValue = 0;
    labelModelPosY.intValue = 0;
    labelModelPosZ.intValue = 0;
    labelModelRotX.intValue = 0;
    labelModelRotY.intValue = 0;
    labelModelRotZ.intValue = 0;

    modelGL.setModelMatrix(0, 0, 0, 0, 0, 0);
    [self updateModelMatrixElements];
    [self updateModelViewMatrixElements];
    [self updateModelMatrixCalls];
}



///////////////////////////////////////////////////////////////////////////////
- (void)updateViewMatrixElements
{
    // get view matrix and set label by tag ID starting from 100 to 115
    const float* m = modelGL.getViewMatrixElements();
    for(int i = 0, tag = 100; i < 16; ++i, ++tag)
    {
        NSTextField* label = (NSTextField*)[self.view viewWithTag:tag];
        label.stringValue = [NSString stringWithFormat:@"%.2f", m[i]];
    }
}

- (void)updateModelMatrixElements
{
    // get model matrix and set  label by tag ID starting from 200 to 215
    const float* m = modelGL.getModelMatrixElements();
    for(int i = 0, tag = 200; i < 16; ++i, ++tag)
    {
        NSTextField* label = (NSTextField*)[self.view viewWithTag:tag];
        label.stringValue = [NSString stringWithFormat:@"%.2f", m[i]];
    }
}

- (void)updateModelViewMatrixElements
{
    // get modelview matrix and set  label by tag ID starting from 300 to 315
    const float* m = modelGL.getModelViewMatrixElements();
    for(int i = 0, tag = 300; i < 16; ++i, ++tag)
    {
        NSTextField* label = (NSTextField*)[self.view viewWithTag:tag];
        label.stringValue = [NSString stringWithFormat:@"%.2f", m[i]];
    }
}



///////////////////////////////////////////////////////////////////////////////
- (void)updateViewMatrixCalls
{
    // update OpenGL function calls
    std::stringstream ss;
    //ss << std::fixed << std::setprecision(0);
    ss << "glRotatef(" << modelGL.getCameraAngleZ() << ",0,0,1);\n"
       << "glRotatef(" << -modelGL.getCameraAngleY() << ",0,1,0);\n"
       << "glRotatef(" << modelGL.getCameraAngleX() << ",1,0,0);\n"
       << "glTranslatef(" << -modelGL.getCameraX() << "," << -modelGL.getCameraY() << "," << -modelGL.getCameraZ() << ");\n"
       << std::ends;
    textViewGL.stringValue = [NSString stringWithUTF8String:ss.str().c_str()];

    // unset floating format
    //ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
}

- (void)updateModelMatrixCalls
{
    std::stringstream ss;
    ss << "glTranslatef(" << modelGL.getModelX() << "," << modelGL.getModelY() << "," << modelGL.getModelZ() << ");\n"
       << "glRotatef(" << modelGL.getModelAngleX() << ",1,0,0);\n"
       << "glRotatef(" << modelGL.getModelAngleY() << ",0,1,0);\n"
       << "glRotatef(" << modelGL.getModelAngleZ() << ",0,0,1);\n"
       << std::ends;
    textModelGL.stringValue = [NSString stringWithUTF8String:ss.str().c_str()];
}


@end
