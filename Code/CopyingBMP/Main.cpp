#include <stdio.h>
#include <stdlib.h>

// BMP IMAGE
// Image header
// Color table
// Image data

typedef unsigned char BYTE;

int main() {
    FILE* sourceImage = fopen("../Resources/SourceImages/cameraman.bmp", "rb");
    
    if(sourceImage == (FILE*)0) {
        printf("Failed to open source image for reading.\n");
        system("pause");
        return 1;
    }

    FILE* myImage = fopen("../Resources/MyImages/man_with_camera.bmp", "wb");

    if(myImage == (FILE*)0) {
        printf("Failed to create copy image.\n");
        system("pause");
        return 1;
    }

    BYTE header[54]; // BMP Header
    BYTE colorTable[1024]; // BMP Colortable

    // Reading image header
    for(int i = 0; i < sizeof(header); i++) 
        header[i] = getc(sourceImage);
    

    // Extracting width, height, bitDepth
    const int width = *(int*)&header[18];
    const int height = *(int*)&header[22];
    const int bitDepth = *(int*)&header[28];

    if(bitDepth <= 8)  // If valid bitdepth
        fread(colorTable, sizeof(BYTE), 1024, sourceImage); // Store color information into colorTable
    
    BYTE* buffer = (BYTE*)malloc(width * height);

    if(buffer == (BYTE*)0) {
        printf("Failed to allocate buffer.\n");
        return 1;
    }

    fread(buffer, sizeof(BYTE), width * height, sourceImage);
    
    // Writes the header into copy image
    fwrite(header, sizeof(BYTE), 54, myImage); 

    if(bitDepth <= 8)
        fwrite(colorTable, sizeof(BYTE), 1024, myImage);

    fwrite(buffer, sizeof(BYTE), width * height, myImage);

    fclose(sourceImage);
    fclose(myImage);
    free(buffer);

    printf("Width: %d, Height: %d\n", width, height);

    system("pause");
    return 0;
}