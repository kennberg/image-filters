image-filters
======================
Beautiful image filters that can be applied to an image. These filters are popular in many great photo apps in the market today.

I encourage you to fork to contribute new filters and help port this to other languages!

How to use in iOS
======================
Drop ImageFilters.\* into your project, and call the static method. Here is a sample, which assumes that you have a UIImage called 'image' and an enum FilterType called 'filterType' already declared:

    CGImageRef imageRef = [image CGImage];
    CGSize imageSize = CGSizeMake(CGImageGetWidth(imageRef), CGImageGetHeight(imageRef));
    CGRect imageRect = CGRectMake(0, 0, imageSize.width, imageSize.height);
    CGContextRef bitmap = CGBitmapContextCreate(NULL,
                                                imageSize.width, imageSize.height,
                                                CGImageGetBitsPerComponent(imageRef),
                                                CGImageGetBytesPerRow(imageRef),
                                                CGImageGetColorSpace(imageRef),
                                                CGImageGetBitmapInfo(imageRef));
    CGContextDrawImage(bitmap, imageRect, imageRef);

    UInt8 *data = (UInt8 *)CGBitmapContextGetData(bitmap);
    int c;
    double color[3];
    for (int y = 0; y < imageSize.height; y++) {
        for (int x = 0; x < imageSize.width; x++) {
            int i = ((y * imageSize.width) + x) * 4;

            for (c = 0; c < 3; c++)
                color[c] = data[i + 2 - c] / 255.;
            
            if (filterType != FT_NONE)
                [ImageFilters applyFilterToPixel:filterType withPixel:&color];
            
            for (c = 0; c < 3; c++)
                data[i + 2 - c] = color[c] * 255.;
        } // for x
    } // for y

    imageRef = CGBitmapContextCreateImage(bitmap);
    image = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    
    CGContextRelease(bitmap);

How to use in C
======================
Drop image\_filters.\* into your project, and call the static method. Here is a sample function to process a RGB buffer.

    void processBuffer(enum FilterType filterType, uint8_t *pBuffer, int width, int height) {
      int x, y, i, c;
      double color[3];

      for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
          i = ((y * width) + x) * 3;

          for (c = 0; c < 3; c++)
            color[c] = pBuffer[i + c] / 255.;

          applyFilterToPixel(filterType, &color);

          for (c = 0; c < 3; c++)
            pBuffer[i + c] = color[c] * 255.;
        }   
      }
    }

License
======================
Apache v2. See the LICENSE file.
