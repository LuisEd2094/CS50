#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    char *infile = argv[1];

    const int BLOCK_SIZE = 512;

    //Open File

    FILE *inf = fopen(infile, "r");
    if (inf == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[BLOCK_SIZE];

    // PTR to OUT FILE

    FILE *outf = NULL;

    // NEW FILE NAME
    char image [8];

    // NUMBER OF FILES SO FAR

    int n = 0;
    //SEARCH FOR JPG
    while (fread(buffer, 1, BLOCK_SIZE, inf) == BLOCK_SIZE)
    {
        // Find start of JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //close first file if opened
            if (n > 0)
            {
                fclose(outf);
            }
            // maka name of jpg
            sprintf(image, "%03i.jpg", n);

            // open file
            outf = fopen(image, "w");
            if (outf == NULL)
            {
                printf("Could not creat %s.\n", image);
                return 3;
            }
            n++;
        }

        // write to file if it exists
        if (outf != NULL)
        {
            //write to imagie
            fwrite(buffer, 1, BLOCK_SIZE, outf);
        }
    }
    // close image
    fclose(outf);

    fclose(inf);

    return 0;

}