#include "image.h"
#include<iostream>

using namespace std;
#define RGB(r,g,b) ((COLORREF)(((U8)(r)|((U16)((U8)(g))<<8))|((U32)(U8)(b)<<16)))
					

CImage::CImage(){
}
bool CImage::Save(char* name) 
{ 
    FILE *fp = fopen(name, "wb"); 
    if(!fp) 
    { 
        printf("fopen failed : %s, %d\n", __FILE__, __LINE__); 
        return 0; 
    } 
  
    U32 bmppitch = ((width*(bitCountPerPix) + 31) >> 5) << 2; 
    U32 filesize = bmppitch*height; 
  
    BITMAPFILE bmpfilesave; 
  
    bmpfilesave.bfHeader.bfType = 0x4D42; 
    bmpfilesave.bfHeader.bfSize = filesize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
    bmpfilesave.bfHeader.bfReserved1 = 0; 
    bmpfilesave.bfHeader.bfReserved2 = 0; 
    bmpfilesave.bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
  
    bmpfilesave.biInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    bmpfilesave.biInfo.bmiHeader.biWidth = width; 
    bmpfilesave.biInfo.bmiHeader.biHeight = height; 
    bmpfilesave.biInfo.bmiHeader.biPlanes = 1; 
    bmpfilesave.biInfo.bmiHeader.biBitCount =bitCountPerPix; 
    bmpfilesave.biInfo.bmiHeader.biCompression = 0; 
    bmpfilesave.biInfo.bmiHeader.biSizeImage = 0; 
    bmpfilesave.biInfo.bmiHeader.biXPelsPerMeter = 0; 
    bmpfilesave.biInfo.bmiHeader.biYPelsPerMeter = 0; 
    bmpfilesave.biInfo.bmiHeader.biClrUsed = 0; 
    bmpfilesave.biInfo.bmiHeader.biClrImportant = 0; 
  
    fwrite(&(bmpfilesave.bfHeader), sizeof(BITMAPFILEHEADER), 1, fp); 
    fwrite(&(bmpfilesave.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, fp); 
  
    U8 *pEachLinBufsave = (U8*)malloc(bmppitch); 
    memset(pEachLinBufsave, 0, bmppitch); 
    U8 BytePerPixsave = bitCountPerPix >> 3; 
    U32 pitchsave = width * BytePerPixsave;
    if(pEachLinBufsave) 
    { 
        int h,w; 
        for(h = height-1; h >= 0; h--) 
        { 
            for(w = 0; w < width; w++) 
            { 
                //copy by a pixel 
                pEachLinBufsave[w*BytePerPixsave+0] = pdata[h*pitchsave + w*BytePerPixsave + 0]; 
                pEachLinBufsave[w*BytePerPixsave+1] = pdata[h*pitchsave + w*BytePerPixsave + 1]; 
                pEachLinBufsave[w*BytePerPixsave+2] = pdata[h*pitchsave + w*BytePerPixsave + 2]; 
            } 
            fwrite(pEachLinBufsave, bmppitch, 1, fp); 
              
        } 
        free(pEachLinBufsave); 
    } 
  
    fclose(fp); 
  
    return 1; 
} 

bool CImage::Load(char* name){
	FILE* pf=fopen(name,"rb");
	if(!pf){
		printf("File Load Failed");
		return false;
	}
	 cout<<"*"<<endl;
    fread(&(bmpfile.bfHeader), sizeof(BITMAPFILEHEADER), 1, pf); 
    fread(&(bmpfile.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, pf); 
  

    if(&bitCountPerPix) 
    { 
        bitCountPerPix = bmpfile.biInfo.bmiHeader.biBitCount; 
    } 
    if(&width) 
    { 
        width = bmpfile.biInfo.bmiHeader.biWidth; 
cout<<"* "<<bmpfile.biInfo.bmiHeader.biWidth<<endl;
    } 
    if(&height) 
    { 
        height = bmpfile.biInfo.bmiHeader.biHeight; 
    } 
  cout<<"*"<<endl;
    bmppicth = (((width)*(bitCountPerPix) + 31) >> 5) << 2; 
    pdata = (U8*)malloc((height)*bmppicth); 
       
    pEachLinBuf = (U8*)malloc(bmppicth); 
    memset(pEachLinBuf, 0, bmppicth); 
    BytePerPix = (bitCountPerPix) >> 3; 
    pitch = (width) * BytePerPix;
    if(pdata && pEachLinBuf) 
    { 
        int w, h; 
        for(h = (height) - 1; h >= 0; h--) 
        { 
            fread(pEachLinBuf, bmppicth, 1, pf); 
            for(w = 0; w < (width); w++) 
            { 
                pdata[h*pitch + w*BytePerPix + 0] = pEachLinBuf[w*BytePerPix+0]; 
                pdata[h*pitch + w*BytePerPix + 1] = pEachLinBuf[w*BytePerPix+1]; 
                pdata[h*pitch + w*BytePerPix + 2] = pEachLinBuf[w*BytePerPix+2]; 
            } 
        } 
        free(pEachLinBuf); 
    } 
    fclose(pf);
	return true;
}

bool CImage::GetPixel(int x, int y, COLORREF &value)
{

	U8* pData = &pdata[(height-y-1)*pitch + x*BytePerPix ];

	value = RGB(pData[2], pData[1], pData[0]);

	return true;
}

bool CImage::SetPixel(int x, int y, const COLORREF &value)
{
	U8* pData;

	if(!(x < width && x >= 0 && y < height && y >= 0))printf(" x , y has gone beyond width/height./n");
	
        pData = &pdata[(height-y-1)*pitch + x*BytePerPix ];
		
	pData[0] = GetBValue(value);
	pData[1] = GetGValue(value);
	pData[2] = GetRValue(value);

	return true;
}
