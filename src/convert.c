#include "../include/convert.h"
#include <stdio.h>

void convert(const int height, const int width, const int outputWidth, const char *charset, const int charsetLength, unsigned char *img, const int color) {
  if (!img) return;

  float aspect = (float)height / width;
  int outputHeight = outputWidth * aspect * 0.5f;

  for (int y = 0; y < outputHeight; y++) {
    for (int x = 0; x < outputWidth; x++) {
      int srcX = x * width / outputWidth;
      int srcY = y * height / outputHeight;
      
      int index = srcY * width + srcX;
      int idx;
      unsigned char brightness;

      if (color) {
        index *= 4;
      
        unsigned char r = img[index];
        unsigned char g = img[index + 1];
        unsigned char b = img[index + 2];

        brightness = 0.299 * r + 0.587 * g + 0.114 * b;

        idx = brightness * (charsetLength - 1) / 255; 
        printf("\33[38;2;%d;%d;%dm%c", r, g, b, charset[idx]);

        continue;
      }
      
      brightness = img[index];
      idx = brightness * (charsetLength - 1) / 255;
      putchar(charset[idx]);
    }

    putchar('\n');
  }

  printf("\033[0m");
}
