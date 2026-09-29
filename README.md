# LSB Image Steganography

## 📌 Project Overview

**LSB Image Steganography** is a C-based project that allows secret data to be hidden inside an image without visibly changing its appearance.

The project uses the **Least Significant Bit (LSB) steganography** technique, where the least significant bits of image data are modified to store secret information.

The hidden data can later be extracted from the stego image using the decoding process.

---

## 🎯 Objectives

- Hide a secret file inside an image.
- Extract hidden data from a stego image.
- Implement steganography using the LSB technique.
- Understand bitwise operations and binary data processing in C.
- Practice file handling and command-line arguments in C.

---

## ⚙️ How It Works

The project provides two main operations:

### 1. Encoding

During encoding, the program:

1. Opens the source image.
2. Opens the secret file.
3. Copies the image header to the output image.
4. Encodes a predefined magic string.
5. Encodes the secret file extension.
6. Encodes the secret file size.
7. Encodes the secret file data into the image data using LSB.
8. Copies the remaining image data.

The resulting image is called the **stego image**.

### 2. Decoding

During decoding, the program:

1. Opens the stego image.
2. Extracts and verifies the magic string.
3. Extracts the secret file extension.
4. Extracts the secret file size.
5. Extracts the hidden secret data.
6. Creates the output file.
7. Writes the recovered data into the output file.

---

## 🧠 LSB Steganography

**Least Significant Bit (LSB)** steganography hides information by modifying the least significant bits of image data.

For example:

```text
Image byte:        10110110
Secret bit:                         1
Modified byte:    10110111
```

Only the least significant bit is changed. Because the change is very small, it is generally not noticeable when viewing the image.

A byte of secret data contains 8 bits, so the bits can be stored across 8 bytes of image data.

---

## 🛠️ Technologies Used

- **Programming Language:** C
- **Steganography Technique:** Least Significant Bit (LSB)
- **Image Format:** BMP
- **Compiler:** GCC
- **Operating System:** Linux / Unix-based systems

---

## 📁 Project Structure

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

> File names may vary depending on the project source files.

---

## 🔧 Compilation

Compile the source files using GCC:

```bash
gcc *.c
```

This generates the executable:

```text
a.out
```

---

## 🚀 Execution

### Encoding

To hide `secret.txt` inside `beautiful.bmp`:

```bash
./a.out -e beautiful.bmp secret.txt
```

The program generates the stego image:

```text
stego.bmp
```

Command format:

```text
./a.out -e <source_image> <secret_file>
```

Example:

```bash
./a.out -e beautiful.bmp secret.txt
```

---

### Decoding

To extract the hidden data from `stego.bmp`:

```bash
./a.out -d stego.bmp output
```

Command format:

```text
./a.out -d <stego_image> <output_filename>
```

Example:

```bash
./a.out -d stego.bmp output
```

The decoded file will be generated using the specified output name along with the original secret file extension.

---

## 📌 Example Workflow

### Step 1: Compile

```bash
gcc *.c
```

### Step 2: Encode

```bash
./a.out -e beautiful.bmp secret.txt
```

The secret data is hidden inside the image and the stego image is generated as:

```text
stego.bmp
```

### Step 3: Decode

```bash
./a.out -d stego.bmp output
```

The hidden data is extracted from the stego image.

---

## ✅ Features

- LSB-based image steganography.
- Hide secret data inside an image.
- Extract hidden data from an image.
- Supports encoding and decoding operations.
- Preserves the image header.
- Stores secret file information along with the hidden data.
- Command-line interface.
- Implemented in C.

---

## ⚠️ Limitations

- The implementation is designed for compatible BMP images.
- The source image must have sufficient capacity to store the secret data.
- The stego image should remain in its original image format.
- Image compression or modification may destroy the hidden data.
- Successful decoding depends on using an image compatible with the implementation.

---

## 🔍 Testing

The complete encoding and decoding process can be tested using:

```bash
gcc *.c
./a.out -e beautiful.bmp secret.txt
./a.out -d stego.bmp output
```

After decoding, the recovered file can be compared with the original `secret.txt` to verify that the hidden data was successfully recovered.

---

## 🎓 Learning Outcomes

This project provides practical understanding of:

- File handling in C
- Binary file operations
- Bitwise operations
- Least Significant Bit manipulation
- Image data processing
- Command-line arguments
- Pointers and structures
- Encoding and decoding techniques
- Data hiding using steganography

---

## 📜 Conclusion

The **LSB Image Steganography** project demonstrates how secret information can be embedded into an image using the Least Significant Bit technique.

The project provides practical experience with **C programming, bit manipulation, file handling, binary data processing, and encoding/decoding techniques**.