//
//  uuid.h
//  cocoa
//
//  Created by Kenneth Laskoski on 3/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface UUID

+ (NSString *) generateNIL;
+ (NSString *) generateV4;

+ (NSString *) serialize;

@end
