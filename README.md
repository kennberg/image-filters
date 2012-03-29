ios-image-filters
======================
Beautiful image filters that can be applied to an image. These filters are popular in many great photo apps in the market today.

How to use
======================
Drop these files into your project, and call the static method. Here is a sample, which assumes that you have a UIImage called 'image' and an enum FilterType called 'filterType' already declared:

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

License
======================
Apache v2. See the LICENSE file.
