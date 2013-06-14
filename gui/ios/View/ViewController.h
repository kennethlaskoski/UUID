//
//  ViewController.h
//  uuid
//
//  Created by Kenneth Laskoski on 3/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *nameTextField;
@property (weak, nonatomic) IBOutlet UITextField *nTextField;
@property (weak, nonatomic) IBOutlet UITextView *textView;

- (IBAction)generateNIL:(id)sender;
- (IBAction)generateNS:(id)sender;
- (IBAction)generateV3:(id)sender;
- (IBAction)generateV4:(id)sender;
- (IBAction)generateV5:(id)sender;
- (IBAction)clearContent:(id)sender;

@end
