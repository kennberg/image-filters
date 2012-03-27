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
    MAX_FILTERTYPES
};

@interface ImageFilters : NSObject

+ (void)applyFilterToPixel:(enum FilterType)filterType withPixel:(double (*)[3])pixel;

@end
