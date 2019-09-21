#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* sourceFile = fopen("../Resources/SourceImages/lena_color.bmp", "rb");
    
    if(sourceFile == (FILE*)0) {
        printf("Failed to open source file\n");
        system("pause");
        return 1;
    } 

    FILE* destinationFile = fopen("../Resources/MyImages/lena_color.bmp", "wb");

    if(sourceFile == (FILE*)0) {
        printf("Failed to open destination file\n");
        system("pause");
        return 1;
    }

    unsigned char header[54];
    unsigned char colorTable[1024];

    for(int i = 0; i < sizeof(header); i++) {
        header[i] = getc(sourceFile);
    }

    const int width = *(int*)(&header[18]);
    const int height = *(int*)(&header[22]);
    const int bitDepth = *(int*)(&header[28]);

    unsigned char buffer[width * height][3]; // One for RGB.

    fwrite(header, sizeof(unsigned char), 54, destinationFile);

    for(int i = 0; i < width * height; i++) {
        buffer[i][0] = getc(sourceFile); // Red
        buffer[i][1] = getc(sourceFile); // Green
        buffer[i][2] = getc(sourceFile); // Blue  

        // Gray scale 
        int gray = (buffer[i][0] * 0.3) + (buffer[i][1] * 0.59) + (buffer[i][2] * 0.11); 

        putc(gray, destinationFile); // Red
        putc(gray, destinationFile); // Green
        putc(gray, destinationFile); // Blue 
    }

    fclose(destinationFile);
    fclose(sourceFile);

    system("pause");
    return 0;
}