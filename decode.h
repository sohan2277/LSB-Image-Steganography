#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include "types.h"

typedef struct _DecodeInfo
{
    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

    /* Output File Info */
    char output_fname[100];
    FILE *fptr_output;

    /* Secret File Info */
    int extn_size;
    char extn_secret_file[5];

    long size_secret_file;

} DecodeInfo;

/* Read and validate Decode arguments */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Open files */
Status open_decode_files(DecodeInfo *decInfo);

/* Decode magic string */
Status decode_magic_string(const char *magic_string,
                           DecodeInfo *decInfo);

/* Decode secret file extension size */
Status decode_secret_file_extn_size(int *size,
                                    DecodeInfo *decInfo);

/* Decode secret file extension */
Status decode_secret_file_extn(char *file_extn,
                               int size,
                               DecodeInfo *decInfo);

/* Decode secret file size */
Status decode_secret_file_size(long *file_size,
                               DecodeInfo *decInfo);

/* Decode secret file data */
Status decode_secret_file_data(DecodeInfo *decInfo);

/* Decode one byte from LSB */
char decode_byte_from_lsb(char *image_buffer);

/* Decode 32-bit size from LSB */
int decode_size_from_lsb(char *image_buffer);

#endif