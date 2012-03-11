//
//  AppDelegate.m
//  cocoa
//
//  Created by Kenneth Laskoski on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

#import "uuid.h"

@implementation AppDelegate

@synthesize window = _window;
@synthesize textField = _textField;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
}

- (IBAction)generateNIL:(id)sender
{
    NSMutableString *tmp = [self.textField.stringValue mutableCopy];
    [tmp appendString:[UUID generateNIL]];
    [tmp appendString:@"\n"];
    [self.textField setStringValue:tmp];
}

- (IBAction)generateV4:(id)sender
{
    NSMutableString *tmp = [self.textField.stringValue mutableCopy];
    [tmp appendString:[UUID generateV4]];
    [tmp appendString:@"\n"];
    [self.textField setStringValue:tmp];
}

@end
