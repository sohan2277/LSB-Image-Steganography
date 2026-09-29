/*
NAME : SOHAN K
DATE : 04 - 09 - 2026
DESCRIPTION : LSB IMAGE STEGANOGRAPHY (PROJECT)
*/


#include <stdio.h>
#include <string.h>

#include "encode.h"
#include "decode.h"
#include "types.h"
#include "common.h"


OperationType check_operation_type(char *symbol);


int main(int argc, char *argv[])
{
    /* Check minimum arguments */

    if(argc < 2)
    {
        printf("ERROR: Invalid arguments\n");
        return 1;
    }


    /*  ENCODE  */

    if(check_operation_type(argv[1]) == e_encode)
    {
        EncodeInfo encInfo;


        /* Minimum: ./a.out -e source.bmp secret.txt */

        if(argc < 4)
        {
            printf("ERROR: Insufficient arguments for encoding\n");
            return 1;
        }


        if(read_and_validate_encode_args(
                argv,
                &encInfo) == e_success)
        {
            if(do_encoding(&encInfo)
               == e_success)
            {
                printf("Encoding successful\n");
            }
            else
            {
                printf("ERROR: Unable to encode\n");
                return 1;
            }
        }
        else
        {
            printf("ERROR: Invalid arguments\n");
            return 1;
        }
    }


    /*  DECODE  */

    else if(check_operation_type(argv[1]) == e_decode)
    {
        DecodeInfo decInfo;


        /* Minimum:./a.out -d stego.bmp */

        if(argc < 3)
        {
            printf("ERROR: Insufficient arguments for decoding\n");
            return 1;
        }


        if(read_and_validate_decode_args(
                argv,
                &decInfo) == e_success)
        {
            if(do_decoding(&decInfo)
               == e_success)
            {
                printf("Decoding successful\n");
            }
            else
            {
                printf("ERROR: Unable to decode\n");
                return 1;
            }
        }
        else
        {
            printf("ERROR: Invalid arguments\n");
            return 1;
        }
    }


    /* UNSUPPORTED  */

    else
    {
        printf("ERROR: Unsupported operation\n");
        return 1;
    }


    return 0;
}


/* Check operation type */

OperationType check_operation_type(char *symbol)
{
    if(strcmp(symbol, "-e") == 0)
    {
        return e_encode;
    }

    else if(strcmp(symbol, "-d") == 0)
    {
        return e_decode;
    }

    return e_unsupported;
}