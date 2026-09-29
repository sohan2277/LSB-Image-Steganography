#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include "common.h"
/* Function Definitions */

/* Get image size */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

uint get_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);

    uint size = ftell(fptr);

    rewind(fptr);

    return size;
}

/* Get File pointers for i/p and o/p files */

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    // step 1 -> check argv[2] is having .bmp or not
    if(strstr(argv[2], ".bmp") == NULL){
        printf("ERROR: Invalid arguments\n");
        return e_failure;
    }
    encInfo->src_image_fname = argv[2];
    

    // step 2 -> check argv[3] is having extn there or not
    if(strstr(argv[3], ".") == NULL){
        printf("ERROR: Invalid arguments\n");
        return e_failure;
    }
    encInfo->secret_fname = argv[3];
    strcpy(encInfo->extn_secret_file, strstr(argv[3], "."));

    
    // step 3 -> check argv[4] is NULL or not

    if(argv[4] != NULL){
        if(strstr(argv[4], ".bmp") == NULL){
        printf("ERROR: Invalid arguments\n");
        return e_failure;
        }
        encInfo->stego_image_fname = argv[4];
    }
    else{
        encInfo->stego_image_fname = "stego.bmp";
    }
    return e_success;
}

Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);
    if(encInfo->image_capacity >=
   16 + 32 +
   (strlen(encInfo->extn_secret_file) * 8) +
   32 +
   (encInfo->size_secret_file * 8))
{
    return e_success;
}

return e_failure;

}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char buffer[54];
    rewind(fptr_src_image);
    fread(buffer,sizeof(char),54,fptr_src_image);
    fwrite(buffer,sizeof(char),54,fptr_dest_image);
    return e_success;

}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    //char buffer[8];
    char buffer[8];

    for(int i = 0; i < strlen(magic_string); i++){
        fread(buffer, sizeof(char),8, encInfo->fptr_src_image);
        encode_byte_to_lsb(magic_string[i], buffer);
        fwrite(buffer,sizeof(char),8, encInfo->fptr_stego_image);
    }

  



    return e_success;

}
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
    char buffer[32];
        fread(buffer, sizeof(char),32, encInfo->fptr_src_image);
        encode_size_to_lsb(size, buffer);
        fwrite(buffer,sizeof(char),32, encInfo->fptr_stego_image);

    return e_success;

}

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    char buffer[8];
    for(int i = 0; i < strlen(file_extn); i++){
        fread(buffer, sizeof(char),8, encInfo->fptr_src_image);
        encode_byte_to_lsb(file_extn[i], buffer);
        fwrite(buffer,sizeof(char),8, encInfo->fptr_stego_image);
    }
    return e_success;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
        fread(buffer, sizeof(char),32, encInfo->fptr_src_image);
    encode_size_to_lsb(file_size, buffer);
    fwrite(buffer,sizeof(char),32, encInfo->fptr_stego_image);

     return e_success;

}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char ch;
    char buffer[8];
    
    for(long i = 0; i < encInfo->size_secret_file; i++)
    {
        fread(&ch, sizeof(char), 1, encInfo->fptr_secret);

        fread(buffer, sizeof(char), 8, encInfo->fptr_src_image);

        encode_byte_to_lsb(ch, buffer);

        fwrite(buffer, sizeof(char), 8, encInfo->fptr_stego_image);
    }

    return e_success;
}

   

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char buffer[8];
    size_t bytes_read;

    while((bytes_read = fread(buffer, sizeof(char), 8, fptr_src)) > 0)
    {
        fwrite(buffer, sizeof(char), bytes_read, fptr_dest);
    }

    return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    //write logic to encode the char
    for(int i = 0; i < 8; i++){
        int bit=(data>>(7-i))&1;
        image_buffer[i] = (image_buffer[i] & 254) | bit;

    }
    return e_success;
}

Status encode_size_to_lsb(int size, char *imageBuffer)
{
    for(int i = 0; i < 32; i++)
    {
        int bit = (size >> (31-i)) & 1;

        imageBuffer[i] = (imageBuffer[i] & 254) | bit;
    }

    return e_success;
}

Status do_encoding(EncodeInfo *encInfo)
{
    if(open_files(encInfo) == e_success){
        if(check_capacity(encInfo) == e_success){
            printf("Success\n");
        }
        else{
            printf("ERROR: Insufficient capacity\n");
            return e_failure;
        }
    }
    else{
        printf("ERROR: Unable to open files\n");
        return e_failure;
    }

        if(copy_bmp_header(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success){
            printf("Success\n");
        }
        else{
            printf("ERROR: Unable to copy bmp header\n");
            return e_failure;
        }
    if(encode_magic_string(MAGIC_STRING, encInfo) == e_success){
        printf("Success\n");
    }
    else{
        printf("ERROR: Unable to encode magic string\n");
        return e_failure;
    }

    

    if(encode_secret_file_extn_size(strlen(encInfo -> extn_secret_file), encInfo) == e_success){
        printf("Success\n");
    }
    else{
        printf("ERROR: Unable to encode secret file extension\n");
        return e_failure;
    }
    
    if(encode_secret_file_extn(encInfo -> extn_secret_file, encInfo) == e_success){
        printf("Success\n");
    }
    else{
        printf("ERROR: Unable to encode secret file extension\n");
        return e_failure;
    }
    
    if(encode_secret_file_size(encInfo -> size_secret_file, encInfo) == e_success){
        printf("Success\n");
    }
    else{
        printf("ERROR: Unable to encode secret file size\n");
        return e_failure;
    }
    
    if(encode_secret_file_data(encInfo) == e_success){
        printf("Success\n");
    }
    else{
        printf("ERROR: Unable to encode secret file data\n");
        return e_failure;
    }
   

    if(copy_remaining_img_data(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success){
        printf("Success\n");
    }
    else{
        printf("ERROR: Unable to copy remaining image data\n");
        return e_failure;
    }
    return e_success;
   
}