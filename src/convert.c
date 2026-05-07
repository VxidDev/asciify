#include "../include/convert.h"
#include <stdio.h>

void convert(const int height, const int width, const int outputWidth, const char *charset, const int charsetLength, unsigned char *img) {
  if (!img) return;

  float aspect = (float)height / width;
  int outputHeight = outputWidth * aspect * 0.5f;

  for (int y = 0; y < outputHeight; y++) {
    for (int x = 0; x < outputWidth; x++) {
      int srcX = x * width / outputWidth;
      int srcY = y * height / outputHeight;

      int index = srcY * width + srcX;
      unsigned char brightness = img[index];
      
      int idx = brightness * (charsetLength - 1) / 255; 

      putchar(charset[idx]);
    }

    putchar('\n');
  }
}
