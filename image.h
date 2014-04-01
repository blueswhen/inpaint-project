#ifndef inpaint_image_H_
#define inpaint_image_H_

#include <stdio.h>
#include <malloc.h>
#include <cstring>
#define GetRValue(rgb) ((U8)(rgb))  
#define GetGValue(rgb) ((U8)(((U16)(rgb)) >> 8)) 
#define GetBValue(rgb) ((U8)((rgb)>>16)) 
#pragma pack(push, 1)
 
typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;
typedef unsigned int COLORREF;

typedef struct {
 
 U16 bfType;
 U32 bfSize;
 U16 bfReserved1;
 U16 bfReserved2;
 U32 bfOffBits;
}BITMAPFILEHEADER;
 
typedef struct {
 U32 biSize;
 U32 biWidth;
 U32 biHeight;
 U16 biPlanes;
 U16 biBitCount;
 U32 biCompression;
 U32 biSizeImage;
 U32 biXPelsPerMeter;
 U32 biYPelsPerMeter;
 U32 biClrUsed;
 U32 biClrImportant;
}BITMAPINFOHEADER;
 
typedef struct {
 U8 rgbBlue;
 U8 rgbGreen;
 U8 rgbRed;
 U8 rgbReserved;
}RGBQUAD;
 
typedef struct {
 BITMAPINFOHEADER bmiHeader;
 RGBQUAD bmiColors[1];
}BITMAPINFO;
 
 
typedef struct {
 BITMAPFILEHEADER bfHeader;
 BITMAPINFO biInfo;
}BITMAPFILE;
 #pragma pack(pop)
class CImage {
 public:
    CImage();
    ~CImage();
    bool Load(char* name);
    bool Save(char* name);
    bool GetPixel(int x, int y, COLORREF &value);
    bool SetPixel(int x, int y, const COLORREF &value);
    U32 GetWith();
    U32 GetHeight();
 private:
  BITMAPFILE bmpfile; 
  U8 bitCountPerPix; 
  U32 width, height;
  U8 *pdata;
  U32 bmppicth;
  U8 *pEachLinBuf;
  U8 BytePerPix;
  U32 pitch;

};
#endif
