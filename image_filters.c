// Image Filters
// Copyright 2012 Alex Kennberg
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>
#include <math.h>

#include "image_filters.h"

void applyFilterToPixel(enum FilterType filterType, double (*color)[3]) {
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

    case FT_SEPIA: {
      color[0][0] = CLAMP(color[0][0] * 0.393 + color[0][1] * 0.769 + color[0][2] * 0.189, 0., 1.);
      color[0][1] = CLAMP(color[0][0] * 0.349 + color[0][1] * 0.686 + color[0][2] * 0.168, 0., 1.);
      color[0][2] = CLAMP(color[0][0] * 0.272 + color[0][1] * 0.534 + color[0][2] * 0.131, 0., 1.);
      break;
    }

    case FT_POSTERIZE: {
      const double step = 25.;
      for (c = 0; c < 3; c++)
        color[0][c] = CLAMP(floor(color[0][c] * 255. / step) / 255. * step, 0, 1);
      break;
    }

    default:
      break;
  }
}

