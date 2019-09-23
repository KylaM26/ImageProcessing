#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

#define WHITE 255
#define BLACK 0
#define THRESHOLD 150

int main() {
    FILE* sourceFile = fopen("../Resources/SourceImages/lighthouse.bmp", "rb");
    FILE* destinationFile = fopen("../Resources/MyImages/lighthouse_black_white.bmp", "wb");

    if(sourceFile == (FILE*)0 || destinationFile == (FILE*)0) {
        printf("Failed to open source file or destination file.\n");
        return 1; 
    }


    BYTE header[54];
    for(int i = 0; i < sizeof(header); i++) 
        header[i] = getc(sourceFile);

    const int width = *(int*)(&header[18]);
    const int height = *(int*)(&header[22]);
    const int bitDepth = *(int*)(&header[28]);

    BYTE colorTable[1024];
    if(bitDepth <= 8) 
        fread(colorTable, sizeof(BYTE), sizeof(colorTable), sourceFile);

    BYTE buffer[width * height];
    fread(buffer, sizeof(BYTE), sizeof(buffer), sourceFile);

    fwrite(header, sizeof(BYTE), sizeof(header), destinationFile);
    
    if(bitDepth <= 8)
        fwrite(colorTable, sizeof(BYTE), sizeof(colorTable), destinationFile);

    // Converting to black and white
    for(int i = 0; i < width * height; i++) 
        buffer[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;

    fwrite(buffer, sizeof(BYTE), sizeof(buffer), destinationFile);    

    printf("Width: %d, Height: %d\n", width, height);
    
    fclose(destinationFile);
    fclose(sourceFile);

    system("pause");
    return 0;
}