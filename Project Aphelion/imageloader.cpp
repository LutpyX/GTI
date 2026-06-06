#include <fstream>
#include <stdio.h>
#include "imageloader.h"
using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {}
Image::~Image() { delete[] pixels; }

namespace {
    int toInt(const char* bytes) {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    short toShort(const char* bytes) {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    int readInt(ifstream &input) {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    short readShort(ifstream &input) {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
}

Image* loadBMP(const char* filename) {
    ifstream input;
    input.open(filename, ifstream::binary);
    if (input.fail()) {
        printf("ERROR: File %s tidak ditemukan!\n", filename);
        return NULL;
    }

    char buffer[2];
    input.read(buffer, 2);
    if (!(buffer[0] == 'B' && buffer[1] == 'M')) {
        printf("ERROR: Bukan file BMP!\n");
        return NULL;
    }

    input.ignore(8);
    int dataOffset = readInt(input);
    int headerSize = readInt(input);

    int width = 0, height = 0;
    if (headerSize == 40) {
        width  = readInt(input);
        height = readInt(input);
        input.ignore(2);
        short bpp         = readShort(input);
        short compression = readShort(input);
        if (bpp != 24) {
            printf("ERROR: Bukan 24-bit! (%d bit)\n", bpp);
            return NULL;
        }
        if (compression != 0) {
            printf("ERROR: BMP dikompres!\n");
            return NULL;
        }
    } else {
        printf("ERROR: Header BMP tidak didukung (size=%d)\n", headerSize);
        return NULL;
    }

    // Fix height negatif (top-down BMP)
    if (height < 0) height = -height;

    printf("DEBUG: width=%d height=%d dataOffset=%d\n", width, height, dataOffset);
    fflush(stdout);

    int bytesPerRow = ((width * 3 + 3) / 4) * 4;
    int size = bytesPerRow * height;

    char* pixels = new char[size];
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels, size);

    char* pixels2 = new char[width * height * 3];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < 3; c++) {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    delete[] pixels;
    input.close();

    printf("Load BMP berhasil! %dx%d\n", width, height);
    fflush(stdout);

    return new Image(pixels2, width, height);
}