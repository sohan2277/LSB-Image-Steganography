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

A **C-based LSB Image Steganography project** that hides secret data inside an image by modifying the **Least Significant Bits (LSB)** of image data.

The project supports both **encoding** secret data into an image and **decoding** the hidden data from the generated stego image.

---

## 🚀 Project Overview

The application provides two primary operations:

* **Encoding** — Hide a secret file inside a BMP image.
* **Decoding** — Extract the hidden secret file from a stego image.

The implementation provides hands-on experience with **C programming, bitwise operations, binary file handling, pointers, structures, and command-line arguments**.

---

## ✨ Key Features

* 🔐 Hide secret data inside an image using LSB steganography
* 🔓 Extract hidden data from a stego image
* 🖼️ BMP image-based data hiding
* 📦 Stores secret file extension and size
* 🔑 Uses a predefined magic string for decoding verification
* 💾 Binary file handling
* ⚙️ Command-line interface
* 💻 Implemented entirely in C
* 🐧 Designed for Linux / Unix-based environments

---

## 🧠 How It Works

### 🔒 Encoding

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
    LSB Encoding
          │
          ▼
       stego.bmp
```

---

### 🔓 Decoding

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
    LSB Decoding
          │
          ▼
    Extracted Data
```

---

## 🔍 Understanding LSB Steganography

**Least Significant Bit (LSB)** steganography stores information by modifying the least significant bits of image data.

For example:

```text
Original image byte : 10110110
Secret bit          :        1
Modified image byte : 10110111
```

Only the least significant bit is changed.

A byte of secret data contains **8 bits**, which can be stored across 8 bytes of image data.

This allows data to be embedded while keeping the visual change to the image very small.

---

## 🛠️ Tech Stack

| Technology                 | Purpose                                 |
| -------------------------- | --------------------------------------- |
| **C**                      | Application development                 |
| **LSB Steganography**      | Data hiding technique                   |
| **BMP**                    | Image format used for embedding data    |
| **GCC**                    | Compilation                             |
| **Linux / Unix**           | Development and execution environment   |
| **Bitwise Operations**     | LSB manipulation                        |
| **File Handling**          | Binary image and secret file processing |
| **Command-Line Arguments** | Program operation selection             |

---

## 📂 Project Structure

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
---

## ⚙️ Compilation

Compile all C source files using GCC:

```bash
gcc *.c
```

This generates the executable:

```text
a.out
```

---

## 🚀 Usage

### 🔒 Encoding

To hide `secret.txt` inside `beautiful.bmp`:

```bash
./a.out -e beautiful.bmp secret.txt
```

The program generates:

```text
stego.bmp
```

### Command Format

```text
./a.out -e <source_image> <secret_file>
```

### Example

```bash
./a.out -e beautiful.bmp secret.txt
```

---

### 🔓 Decoding

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

The decoded file is generated using the specified output name along with the original secret file extension.

---

## 🔄 Complete Workflow

```text
                 ENCODING
                     │
                     ▼
          ┌─────────────────────┐
          │   beautiful.bmp     │
          └──────────┬──────────┘
                     │
                     │
              + secret.txt
                     │
                     ▼
             ┌───────────────┐
             │  LSB Encoding │
             └───────┬───────┘
                     │
                     ▼
                stego.bmp
                     │
                     │
                     ▼
             ┌───────────────┐
             │  LSB Decoding │
             └───────┬───────┘
                     │
                     ▼
              Extracted File
```

---

## 🧪 Testing

The complete encoding and decoding process can be tested using:

### 1. Compile

```bash
gcc *.c
```

### 2. Encode

```bash
./a.out -e beautiful.bmp secret.txt
```

### 3. Decode

```bash
./a.out -d stego.bmp output
```

The recovered file can then be compared with the original `secret.txt` to verify successful data extraction.

---

## ⚠️ Limitations

* The implementation is designed for compatible **BMP images**.
* The source image must have sufficient capacity to store the secret data.
* The stego image should remain in its original image format.
* Image compression or modification may destroy the hidden data.
* Successful decoding depends on using an image compatible with the implementation.

---

## 📚 Learning Outcomes

This project provides practical experience with:

* C programming
* File handling
* Binary file operations
* Bitwise operations
* LSB manipulation
* Image data processing
* Command-line arguments
* Pointers and structures
* Encoding and decoding techniques
* Data hiding using steganography

---

## 👨‍💻 Author

**Sohan K**

Embedded Systems & IoT Developer

🔗 **GitHub:**
https://github.com/sohan2277

🔗 **LinkedIn:**
https://www.linkedin.com/in/sohan2277/
