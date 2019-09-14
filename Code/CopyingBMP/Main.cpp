#include <stdio.h>
#include <stdlib.h>

// BMP IMAGE
// Image header
// Color table
// Image data

typedef unsigned char BYTE;

class BMPImage {
private: 
    FILE* imageFile;
    int width, height, bitDepth;
    BYTE header[54], colorTable[1024];
    BYTE* buffer;
public:
    BMPImage(const char* filePath) {
        imageFile = fopen(filePath, "rb");

        if(imageFile != (FILE*)0) {
            for(int i = 0; i < sizeof(header); i++)
                header[i] = getc(imageFile);

            width = *(int*)&header[18];
            height = *(int*)&header[22];
            bitDepth = *(int*)&header[28];

            if(bitDepth <= 8) 
                fread(colorTable, sizeof(BYTE), 1024, imageFile);

            buffer = (BYTE*)malloc(width * height);

            if(buffer != (BYTE*)0) 
                fread(buffer, sizeof(BYTE), width * height, imageFile);        
        }
    }

    void Duplicate(const char* filePath) const {
        FILE* copyImage = fopen(filePath, "wb");

        if(copyImage != (FILE*)0) {
            fwrite(header, sizeof(BYTE), 54, copyImage);

            if(bitDepth <= 8) 
                fwrite(colorTable, sizeof(BYTE), 1024, copyImage);

            fwrite(buffer, sizeof(BYTE), width * height, copyImage);

            fclose(copyImage);
        }
    }

    const int GetWidth() const { return width; }
    const int GetHeight() const { return height; }
    const int GetBitDepth() const { return bitDepth; }

    ~BMPImage() {
        if(buffer = (BYTE*)0)
            free(buffer);

        fclose(imageFile);
    }
};

int main() {
    BMPImage myImage("../Resources/SourceImages/cameraman.bmp");
    myImage.Duplicate("../Resources/MyImages/cameraman.bmp");

    printf("Width: %d, Height: %d\n", myImage.GetWidth(), myImage.GetHeight());

    system("pause");
    return 0;
}
