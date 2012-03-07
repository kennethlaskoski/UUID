//
//  AppDelegate.h
//  cocoa
//
//  Created by Kenneth Laskoski on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (weak) IBOutlet NSTextField *textField;
- (IBAction)generateNIL:(id)sender;
- (IBAction)generateV4:(id)sender;

@end
