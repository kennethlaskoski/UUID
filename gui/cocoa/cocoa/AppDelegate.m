//
//  AppDelegate.m
//  cocoa
//
//  Created by Kenneth Laskoski on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window = _window;
@synthesize textField = _textField;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
}

- (IBAction)generateNIL:(id)sender {
    [self.textField setStringValue:@"NIL"];
}

- (IBAction)generateV4:(id)sender {
    [self.textField setStringValue:@"V4"];
}
@end
