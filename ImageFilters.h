//
//  ImageFilters.h
//
//  Copyright (c) 2012 Alex Kennberg. Reference "LICENSE" file.
//

#import <UIKit/UIKit.h>

enum FilterType {
    FT_NONE,
    FT_BLACKANDWHITE,
    FT_RETRO,
    FT_VINTAGE,
    FT_SEPIA,
    FT_POSTERIZE,
    MAX_FILTERTYPES
};

#ifndef CLAMP
#define CLAMP(x, minx, maxx) ((x) < (minx) ? (minx) : ((x) > (maxx) ? (maxx) : (x)))
#endif

@interface ImageFilters : NSObject

+ (void)applyFilterToPixel:(enum FilterType)filterType withPixel:(double (*)[3])pixel;

@end
