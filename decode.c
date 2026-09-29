#include <stdio.h>
#include <string.h>

#include "decode.h"
#include "types.h"
#include "common.h"

/* Read and validate decode arguments */

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    /* Check stego image */
    if (strstr(argv[2], ".bmp") == NULL)
    {
        printf("ERROR: Invalid stego image\n");
        return e_failure;
    }

    /* Store stego image name */
    decInfo->stego_image_fname = argv[2];

    /* Check output file name */

    if (argv[3] != NULL)
    {
        strcpy(decInfo->output_fname, argv[3]);
    }
    else
    {
        strcpy(decInfo->output_fname, "output");
    }

    return e_success;
}

/* Open stego image */

Status open_decode_files(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image =
        fopen(decInfo->stego_image_fname, "rb");

    if (decInfo->fptr_stego_image == NULL)
    {
        perror("fopen");

        printf("ERROR: Unable to open stego image %s\n",
               decInfo->stego_image_fname);

        return e_failure;
    }

    return e_success;
}

/* Decode magic string */

Status decode_magic_string(const char *magic_string,
                           DecodeInfo *decInfo)
{
    char buffer[8];
    char decoded_char;

    for (int i = 0; i < strlen(magic_string); i++)
    {
        /* Read 8 image bytes */
        fread(buffer, sizeof(char), 8,
              decInfo->fptr_stego_image);

        /* Decode one character */
        decoded_char = decode_byte_from_lsb(buffer);

        /* Compare with magic string */
        if (decoded_char != magic_string[i])
        {
            return e_failure;
        }
    }

    return e_success;
}

/* Decode extension size */

Status decode_secret_file_extn_size(int *size,
                                    DecodeInfo *decInfo)
{
    char buffer[32];

    /* Read 32 image bytes */
    fread(buffer, sizeof(char), 32,
          decInfo->fptr_stego_image);

    /* Decode size */
    *size = decode_size_from_lsb(buffer);

    return e_success;
}

/* Decode extension */

Status decode_secret_file_extn(char *file_extn,
                               int size,
                               DecodeInfo *decInfo)
{
    char buffer[8];

    for (int i = 0; i < size; i++)
    {
        /* Read 8 image bytes */
        fread(buffer, sizeof(char), 8,
              decInfo->fptr_stego_image);

        /* Decode one character */
        file_extn[i] =
            decode_byte_from_lsb(buffer);
    }

    /* Add NULL character */
    file_extn[size] = '\0';

    return e_success;
}

/* Decode secret file size */

Status decode_secret_file_size(long *file_size,
                               DecodeInfo *decInfo)
{
    char buffer[32];

    /* Read 32 image bytes */
    fread(buffer, sizeof(char), 32,
          decInfo->fptr_stego_image);

    /* Decode size */
    *file_size = decode_size_from_lsb(buffer);

    return e_success;
}

/* Decode secret file data */

Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char buffer[8];
    char decoded_char;

    for (long i = 0;
         i < decInfo->size_secret_file;
         i++)
    {
        /* Read 8 image bytes */
        fread(buffer, sizeof(char), 8,
              decInfo->fptr_stego_image);

        /* Decode one character */
        decoded_char =
            decode_byte_from_lsb(buffer);

        /* Write character to output file */
        fwrite(&decoded_char,
               sizeof(char),
               1,
               decInfo->fptr_output);
    }

    return e_success;
}

/* Decode one byte from 8 LSBs */

char decode_byte_from_lsb(char *image_buffer)
{
    char data = 0;

    for (int i = 0; i < 8; i++)
    {
        data = (data << 1) |
               (image_buffer[i] & 1);
    }

    return data;
}

/* Decode 32-bit integer from LSBs */

int decode_size_from_lsb(char *image_buffer)
{
    int size = 0;

    for (int i = 0; i < 32; i++)
    {
        size = (size << 1) |
               (image_buffer[i] & 1);
    }

    return size;
}

/* Perform decoding */

Status do_decoding(DecodeInfo *decInfo)
{
    /* Step 1: Open stego image */

    if (open_decode_files(decInfo) != e_success)
    {
        printf("ERROR: Unable to open files\n");
        return e_failure;
    }

    printf("Stego image opened successfully\n");

    /* Step 2: Skip BMP header */

    fseek(decInfo->fptr_stego_image,
          54,
          SEEK_SET);

    /* Step 3: Decode magic string */

    if (decode_magic_string(MAGIC_STRING,
                            decInfo) != e_success)
    {
        printf("ERROR: Magic string mismatch\n");

        fclose(decInfo->fptr_stego_image);

        return e_failure;
    }

    printf("Magic string decoded successfully\n");

    /* Step 4: Decode extension size */

    if (decode_secret_file_extn_size(
            &decInfo->extn_size,
            decInfo) != e_success)
    {
        printf("ERROR: Unable to decode extension size\n");

        fclose(decInfo->fptr_stego_image);

        return e_failure;
    }

    printf("Extension size = %d\n",
           decInfo->extn_size);

    /* Step 5: Decode extension */

    if (decode_secret_file_extn(
            decInfo->extn_secret_file,
            decInfo->extn_size,
            decInfo) != e_success)
    {
        printf("ERROR: Unable to decode extension\n");

        fclose(decInfo->fptr_stego_image);

        return e_failure;
    }

    printf("Secret file extension = %s\n",
           decInfo->extn_secret_file);

    /*
     * Step 6:
     * Merge output filename
     * with decoded extension
     */

    strcat(decInfo->output_fname,
           decInfo->extn_secret_file);

    printf("Output file = %s\n",
           decInfo->output_fname);

    /* Step 7: Decode secret file size */

    if (decode_secret_file_size(
            &decInfo->size_secret_file,
            decInfo) != e_success)
    {
        printf("ERROR: Unable to decode secret file size\n");

        fclose(decInfo->fptr_stego_image);

        return e_failure;
    }

    printf("Secret file size = %ld\n",
           decInfo->size_secret_file);

    /* Step 8: Open output file */

    decInfo->fptr_output =
        fopen(decInfo->output_fname, "wb");

    if (decInfo->fptr_output == NULL)
    {
        perror("fopen");

        printf("ERROR: Unable to create output file\n");

        fclose(decInfo->fptr_stego_image);

        return e_failure;
    }

    printf("Output file opened successfully\n");

    /* Step 9: Decode secret data */

    if (decode_secret_file_data(decInfo) != e_success)
    {
        printf("ERROR: Unable to decode secret data\n");

        fclose(decInfo->fptr_stego_image);
        fclose(decInfo->fptr_output);

        return e_failure;
    }

    printf("Secret data decoded successfully\n");

    /* Close files */

    fclose(decInfo->fptr_stego_image);
    fclose(decInfo->fptr_output);

    return e_success;
}