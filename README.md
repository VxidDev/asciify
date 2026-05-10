# asciify

A lightweight C CLI tool that converts images and videos into ASCII art with configurable output size and format support.

---

## Features

- **Image & Video Support**: Convert common image formats and video files into ASCII art.
- **Real-time Video Playback**: Play videos as ASCII art directly in your terminal.
- **ANSI Color Support**: Optional colored output for a more detailed representation.
- **Configurable Output**: Adjustable width and custom charsets to fine-tune the result.
- **Fast & Efficient**: Written in C, leveraging `stb_image` for images and FFmpeg for video processing.

---

## Prerequisites

To build and run `asciify`, you need the following dependencies installed:

- **GCC** (or any C11 compliant compiler)
- **Make**
- **FFmpeg libraries** (`libavformat`, `libavcodec`, `libswscale`, `libavutil`)

On Debian/Ubuntu, you can install the FFmpeg libraries with:
```bash
sudo apt-get install libavformat-dev libavcodec-dev libswscale-dev libavutil-dev
```

---

## Build

Clone the repository and run `make`:

```bash
make
```

This produces the executable: `./asciify`

---

## Usage

### Basic usage

Convert an image:
```bash
./asciify image.png
```

Play a video:
```bash
./asciify video.mp4
```

### Options

| Option | Long Option | Description | Default |
|--------|-------------|-------------|---------|
| `-h` | `--help` | Show help message | - |
| `-w` | `--width` | Output width in characters | 50 |
| `-c` | `--color` | Enable ANSI color formatting | Off |
| `-C` | `--charset` | Use a custom charset string | (Standard) |
| `-f` | `--fps` | Output framerate for videos | 30 |

### Examples

**Colored output with custom width:**
```bash
./asciify image.png -w 120 -c
```

**Custom charset:**
```bash
./asciify image.png -C " .:-=+*#%@"
```

**Video with specific framerate:**
```bash
./asciify video.mp4 -f 24 -c
```

---

## How it works

1. **Loading**: Uses `stb_image` for images and FFmpeg's `libavformat`/`libavcodec` for video frames.
2. **Processing**: Converts pixels to grayscale or retains RGB values if color is enabled.
3. **Mapping**: Maps pixel brightness to characters in the charset.
4. **Scaling**: Scales the output based on the target width while maintaining aspect ratio (adjusting for terminal character height).
5. **Rendering**: Prints the ASCII result to the terminal, using ANSI escape codes for color.

---

## Roadmap

- [ ] `.ascii` binary format for storing/sharing captures
- [ ] Improved scaling and anti-aliasing algorithms
- [ ] Dithering support for better grayscale representation
- [ ] Audio support for video playback

---

## License

GPL 3.0
