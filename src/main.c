#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../include/convert.h"
#include "../include/convert-video.h"

#include <stdio.h>
#include <string.h>

const char *ascii = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
size_t ASCII_LENGTH;

#define MIN_ARG_AMOUNT 1

const char *filename = NULL;
unsigned int outputWidth = 50;
unsigned int fps = 30;
int color = 0;

void parseArgs(const int argc, const char **argv) {
  if (argc < (MIN_ARG_AMOUNT + 1)) {
    printf("asciify: file name required.\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      if (filename == NULL) {
        filename = argv[i];
        continue;
      }

      printf("asciify: unexpected positional argument \"%s\"\n", argv[i]);
      exit(1);
    } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
      if (i + 1 >= argc) {
        printf("asciify: number expected.\n");
        exit(1);
      }

      i++;

      char *end;

      outputWidth = strtoul(argv[i], &end, 10);

      if (*end != '\0') {
        printf("asciify: invalid number \"%s\"\n", argv[i]);
        exit(1);
      }
    } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fps") == 0) {
      if (i + 1 >= argc) {
        printf("asciify: number expected.\n");
        exit(1);
      }

      i++;

      char *end;

      fps = strtoul(argv[i], &end, 10);

      if (*end != '\0') {
        printf("asciify: invalid number \"%s\"\n", argv[i]);
        exit(1);
      } 
    } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--color") == 0) {
      color = 1;
    } else if (strcmp(argv[i], "-C") == 0 || strcmp(argv[i], "--charset") == 0){
      if (i + 1 >= argc) {
        printf("asciify: string expected.\n");
        exit(1);
      }

      i++;

      ascii = argv[i];
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf(
        "Usage: %s [file] [options]\n\n"
        "  Options:\n"
        "     -h, --help              Show this help message\n"
        "     -w, --width <num>       ASCII art's output width in chars (default: 50)\n"
        "     -c, --color             Enable ANSI color formatting\n"
        "     -C, --charset <str>     Use custom charset\n"
        "     -f, --fps <num>         Output framerate\n"
        , argv[0]
      );
      exit(0);
    }
  }
}

int main(const int argc, const char **argv) {
  parseArgs(argc, argv);

  if (!filename) {
    printf("asciify: file name required.\n");
    return 1;
  }
  
  int width, height, channels;
  ASCII_LENGTH = strlen(ascii);

  if (convertVideo(filename, ASCII_LENGTH, ascii, color, outputWidth, fps)) return 0;

  unsigned char* img = stbi_load(filename, &width, &height, &channels, color ? 4 : 1);

  if (!img) {
    printf("asciify: failed to load image.\n");
    return 1;
  } 

  convert(height, width, outputWidth, ascii, ASCII_LENGTH, img, color, 4);

  stbi_image_free(img);

  return 0;
}
