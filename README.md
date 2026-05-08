# asciify

A lightweight C CLI tool that converts images and videos into ASCII art with configurable output size and format support.

---

## Features

- Convert images to ASCII art
- Adjustable output width
- CLI-based interface
- Built with C for performance and low-level control
- Uses stb_image for image loading
- Colored ASCII output
- Custom charset support

Planned features:
- Video to ASCII conversion
- Custom `.ascii` binary format
- Improved scaling and dithering

---

## Project Structure

```

.
├── include
│   ├── convert.h
│   └── stb_image.h
├── src
│   ├── convert.c
│   └── main.c
├── image.png
├── README.md
├── LICENSE
└── makefile
````

---

## Build

```bash
make
````

This produces the executable:

```bash
./asciify
```

---

## Usage

### Basic usage

```bash
./asciify image.png
```

### With options

```bash
./asciify image.png -w 100
```

### Help

```bash
./asciify --help
```

---

## Options

```
-h, --help            Show help message
-w, --width <num>     Output width (default: 100)
-c, --color           Enable ANSI color formatting
-C, --charset         Use custom charset 
```

---

## How it works

1. Load image using stb_image
2. Convert pixels to grayscale 
3. Map brightness to ASCII characters
4. Scale output based on target width
5. Print result to terminal

---

## Roadmap

* Video support via frame extraction
* `.ascii` binary format
* Improved scaling algorithms
* Dithering support

---

## License

GPL 3.0
