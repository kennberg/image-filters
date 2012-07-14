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

#ifndef __IMAGE_FILTERS_H__
#define __IMAGE_FILTERS_H__

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

void applyFilterToPixel(enum FilterType filterType, double (*color)[3]);

#endif // __IMAGE_FILTERS_H__
