#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

// Represents an image
class Image {
public:
    Image(char* ps, int w, int h);
    ~Image();

    /* 
     * Array pixel dengan format:
     * (R1, G1, B1, R2, G2, B2, ...)
     */

    char* pixels;
    int width;
    int height;
};

// Membaca file bitmap
Image* loadBMP(const char* filename);

#endif
