//
//  uuid.mm
//  cocoa
//
//  Created by Kenneth Laskoski on 3/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "uuid.h"

#include "kashmir/uuid.h"
#include "kashmir/devrand.h"

#include <sstream>

@implementation UUID

+ (NSString *) generateNIL
{
    /* static memory should be zeroed */
    static const kashmir::uuid_t null;
    assert(!null);
    
    std::stringstream buffer;
    buffer << null;

    return [NSString stringWithUTF8String:buffer.str().c_str()];
}

+ (NSString *) generateV4
{
    static kashmir::system::DevRand devrandom;
    static kashmir::uuid_t uuid;

    devrandom >> uuid;
    
    std::stringstream buffer;
    buffer << uuid;
    
    return [NSString stringWithUTF8String:buffer.str().c_str()];
}

@end