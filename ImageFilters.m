//
//  ImageFilters.m
//
//  Copyright (c) 2012 Alex Kennberg. Reference "LICENSE" file.
//

#import "ImageFilters.h"

@implementation ImageFilters


+ (void)applyFilterToPixel:(enum FilterType)filterType withPixel:(double (*)[3])color {
    int c;
    switch (filterType) {
        case FT_BLACKANDWHITE: {
            double grey = color[0][0] * 0.3 + color[0][1] * 0.59 + color[0][2] * 0.11;
            for (c = 0; c < 3; c++)
                color[0][c] = grey;
            break;
        }
            
        case FT_RETRO: {
            /* reduce saturation */
            double grey = color[0][0] * 0.3 + color[0][1] * 0.59 + color[0][2] * 0.11;
            double saturationValue = 0.6;
            for (c = 0; c < 3; c++)
                color[0][c] = color[0][c] * (1. - saturationValue) + grey * saturationValue;
            
            /* multiply with yellow */
            color[0][0] *= 0.97;
            color[0][1] *= 0.99;
            color[0][2] *= 0.52;
            break;
        }
            
        case FT_VINTAGE: {
            /* boost contrast */
            double contrast = 1.45;
            for (c = 0; c < 3; c++) {
                color[0][c] = (color[0][c] - 0.5) * contrast + 0.5;
                if (color[0][c] > 1.)
                    color[0][c] = 1.;
                else if (color[0][c] < 0.)
                    color[0][c] = 0.;
            }
            
            /* multiply with yellow */
            color[0][0] *= 0.97;
            color[0][1] *= 0.99;
            color[0][2] *= 0.52;
            
            /* lighten with blue */
            double blueHue[3] = { 0.11, 0.2, 0.9 };
            double greyColor = color[0][0] * 0.3 + color[0][1] * 0.59 + color[0][2] * 0.11;
            double greyBlueHue = blueHue[0] * 0.3 + blueHue[1] * 0.59 + blueHue[2] * 0.11;
            if (greyColor < greyBlueHue)
                for (c = 0; c < 3; c++)
                    color[0][c] = color[0][c] * 0.8 + blueHue[c] * 0.2;
            break;
        }
            
        default:
            break;
    }
}

@end
