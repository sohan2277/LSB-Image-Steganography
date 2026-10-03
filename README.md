# 🔐 LSB Image Steganography

<p align="left">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C"/>
  <img src="https://img.shields.io/badge/LSB_Steganography-6A1B9A?style=for-the-badge" alt="LSB Steganography"/>
  <img src="https://img.shields.io/badge/BMP-37474F?style=for-the-badge" alt="BMP"/>
  <img src="https://img.shields.io/badge/GCC-00599C?style=for-the-badge&logo=gnu&logoColor=white" alt="GCC"/>
  <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="Linux"/>
  <img src="https://img.shields.io/badge/Bitwise_Operations-455A64?style=for-the-badge" alt="Bitwise Operations"/>
  <img src="https://img.shields.io/badge/File_Handling-00897B?style=for-the-badge" alt="File Handling"/>
</p>

> A C-based implementation of **LSB Image Steganography** for hiding and extracting secret data inside compatible BMP images.

This project demonstrates practical use of **C programming, bitwise operations, binary file handling, pointers, structures, and command-line arguments** through an encoding and decoding workflow.

---

## 📑 Table of Contents

1. [Overview](#1-overview)
2. [Key Features](#2-key-features)
3. [How It Works](#3-how-it-works)
4. [LSB Concept](#4-lsb-concept)
5. [Tech Stack](#5-tech-stack)
6. [Project Structure](#6-project-structure)
7. [Compilation](#7-compilation)
8. [Usage](#8-usage)
9. [Complete Workflow](#9-complete-workflow)
10. [Testing](#10-testing)
11. [Limitations](#11-limitations)
12. [Learning Outcomes](#12-learning-outcomes)
13. [Author](#13-author)

---

# 1. Overview

**LSB Image Steganography** is a C-based project that hides secret data inside an image by modifying the **Least Significant Bits (LSB)** of image data.

The application supports two main operations:

| Operation | Purpose |
|---|---|
| 🔒 Encoding | Hide a secret file inside a compatible BMP image |
| 🔓 Decoding | Extract the hidden file from a stego image |

During encoding, information such as the **magic string, secret file extension, file size, and file data** is embedded into the image.

During decoding, the same information is extracted to reconstruct the original secret file.

---

# 2. Key Features

- 🔐 Hide secret data using LSB steganography
- 🔓 Extract hidden data from a stego image
- 🖼️ BMP-based data hiding
- 📦 Store secret file extension and size
- 🔑 Magic-string verification during decoding
- 💾 Binary file processing
- ⚙️ Command-line interface
- 🧩 Bitwise data manipulation
- 💻 Implemented entirely in C
- 🐧 Designed for Linux / Unix-based environments

---

# 3. How It Works

## 🔒 Encoding

During encoding, the application:

1. Opens the source image.
2. Opens the secret file.
3. Copies the image header to the output image.
4. Encodes a predefined magic string.
5. Encodes the secret file extension.
6. Encodes the secret file size.
7. Encodes the secret file data into the image using LSB.
8. Copies the remaining image data.

The resulting image is generated as the **stego image**.

```text
Source Image + Secret File
          │
          ▼
    ┌───────────────┐
    │ LSB Encoding  │
    └───────┬───────┘
            │
            ▼
        stego.bmp
```

---

## 🔓 Decoding

During decoding, the application:

1. Opens the stego image.
2. Extracts and verifies the magic string.
3. Extracts the secret file extension.
4. Extracts the secret file size.
5. Extracts the hidden secret data.
6. Creates the output file.
7. Writes the recovered data into the output file.

```text
     stego.bmp
          │
          ▼
    ┌───────────────┐
    │ LSB Decoding  │
    └───────┬───────┘
            │
            ▼
      Extracted File
```

---

# 4. LSB Concept

**Least Significant Bit (LSB)** steganography stores information by modifying the least significant bits of image data.

For example:

```text
Original image byte : 10110110
Secret bit          :        1
Modified image byte : 10110111
```

Only the least significant bit is changed.

A byte of secret data contains **8 bits**, which can be distributed across 8 bytes of image data.

This allows information to be embedded while keeping the visual change to the image very small.

---

# 5. Tech Stack

| Technology | Purpose |
|---|---|
| **C** | Core application development |
| **LSB Steganography** | Data hiding technique |
| **BMP** | Image format used for embedding |
| **GCC** | Compilation |
| **Linux / Unix** | Development and execution environment |
| **Bitwise Operations** | LSB manipulation |
| **File Handling** | Binary image and secret-file processing |
| **Command-Line Arguments** | Encoding / decoding operation selection |
| **Pointers & Structures** | Data and file management |

---

# 6. Project Structure

```text
Steganography/
│
├── main.c
├── encode.c
├── encode.h
├── decode.c
├── decode.h
├── types.h
├── common.h
├── beautiful.bmp
├── secret.txt
└── README.md
```

> File names may vary depending on the final source structure.

---

# 7. Compilation

Compile all C source files using GCC:

```bash
gcc *.c
```

This generates the executable:

```text
a.out
```

---

# 8. Usage

## 🔒 Encoding

To hide `secret.txt` inside `beautiful.bmp`:

```bash
./a.out -e beautiful.bmp secret.txt
```

### Command Format

```text
./a.out -e <source_image> <secret_file>
```

### Example

```bash
./a.out -e beautiful.bmp secret.txt
```

The program generates the stego image:

```text
stego.bmp
```

---

## 🔓 Decoding

To extract the hidden data from `stego.bmp`:

```bash
./a.out -d stego.bmp output
```

### Command Format

```text
./a.out -d <stego_image> <output_filename>
```

### Example

```bash
./a.out -d stego.bmp output
```

The decoded file is generated using the specified output name along with the original secret-file extension.

---

# 9. Complete Workflow

```text
                         ENCODING
                            │
                            ▼
                  ┌──────────────────┐
                  │  beautiful.bmp   │
                  └────────┬─────────┘
                           │
                           │ + secret.txt
                           ▼
                  ┌──────────────────┐
                  │  LSB Encoding    │
                  └────────┬─────────┘
                           │
                           ▼
                      stego.bmp
                           │
                           ▼
                  ┌──────────────────┐
                  │  LSB Decoding    │
                  └────────┬─────────┘
                           │
                           ▼
                    Extracted File
```

### Typical Command Sequence

```bash
gcc *.c
./a.out -e beautiful.bmp secret.txt
./a.out -d stego.bmp output
```

---

# 10. Testing

The complete encoding and decoding process can be tested using the following steps.

### Step 1 — Compile

```bash
gcc *.c
```

### Step 2 — Encode

```bash
./a.out -e beautiful.bmp secret.txt
```

### Step 3 — Decode

```bash
./a.out -d stego.bmp output
```

### Step 4 — Verify

The recovered file can be compared with the original `secret.txt` to verify that the hidden data was successfully extracted.

---

# 11. Limitations

| Limitation | Description |
|---|---|
| **Image Format** | Designed for compatible BMP images |
| **Image Capacity** | Source image must have sufficient capacity to store the secret data |
| **Image Modification** | Modifying the stego image may affect the hidden data |
| **Compression** | Image compression may destroy embedded data |
| **Compatibility** | Decoding depends on using an image compatible with the implementation |

---

# 12. Learning Outcomes

This project provided practical experience with:

- C programming
- File handling
- Binary file operations
- Bitwise operations
- LSB manipulation
- Image data processing
- Command-line arguments
- Pointers
- Structures
- Encoding and decoding techniques
- Data hiding concepts

---

# 13. Author

### Sohan K

**Embedded Systems & IoT Developer**

<p align="left">
  <a href="https://github.com/sohan2277">
    <img src="https://img.shields.io/badge/GitHub-sohan2277-181717?style=for-the-badge&logo=github" alt="GitHub"/>
  </a>
  <a href="https://www.linkedin.com/in/sohan2277/">
    <img src="https://img.shields.io/badge/LinkedIn-Sohan%20K-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn"/>
  </a>
</p>

---

<p align="center">
  <b>🔐 C • Bitwise Operations • File Handling • LSB Steganography</b>
</p>
