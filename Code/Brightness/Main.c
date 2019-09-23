#include <stdio.h>
#include <stdlib.h>

#define BRIGHTNESS_FACTOR 100
#define MAX_COLOR 255

typedef unsigned char BYTE;

int main() {

    FILE* sourceFile = fopen("../Resources/SourceImages/lena512.bmp", "rb");
    FILE* destinationFile = fopen("../Resources/MyImages/lena_bright.bmp", "wb");

    if(sourceFile == (FILE*)0 || destinationFile == (FILE*)0) {
        printf("Failed to open source file or destination file.\n");
        return 1;
    }

    BYTE header[54];
    for(int i = 0; i < sizeof(header); i++) 
        header[i] = getc(sourceFile);

    fwrite(header, sizeof(BYTE), sizeof(header), destinationFile);

    const int width = *(int*)&header[18];
    const int height = *(int*)&header[22];
    const int bitDepth = *(int*)&header[28];

    BYTE colorTable[1024];
    
    if(bitDepth <= 8) {
        fread(colorTable, sizeof(BYTE), sizeof(colorTable), sourceFile);
        fwrite(colorTable, sizeof(BYTE), sizeof(colorTable), destinationFile);
    }

    BYTE buffer[width * height];
    fread(buffer, sizeof(BYTE), sizeof(buffer), sourceFile);

    int temp = 0;
    for(int i = 0; i < width * height; i++) {
        temp = buffer[i] + BRIGHTNESS_FACTOR;
        buffer[i] = (temp > MAX_COLOR) ? MAX_COLOR : temp;
    }

    fwrite(buffer, sizeof(BYTE), sizeof(buffer), destinationFile);

    fclose(destinationFile);
    fclose(sourceFile);

    printf("Width: %d, Height: %d, bitDepth: %d\n", width, height, bitDepth);

    system("pause");

    return 0;
}