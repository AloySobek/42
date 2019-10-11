///////////////////////////////////////////////////////////////////////////////
// AppDelegate.m
// =============
// matrixModelView
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2012-06-15
// UPDATED: 2018-03-05
//
// Copyright (c) 2012-2018 Song Ho Ahn. All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate



///////////////////////////////////////////////////////////////////////////////
- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    printf("===== Application is launched. =====\n");
}



///////////////////////////////////////////////////////////////////////////////
- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    printf("===== Application is terminated. =====\n");
}



///////////////////////////////////////////////////////////////////////////////
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)application
{
    return YES;
}

@end
