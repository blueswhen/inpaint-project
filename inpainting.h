#ifndef inpaint_inpainting_H_
#define inpaint_inpainting_H_

#include "image.h"
 
#define PAINT_COLOR  RGB(0,255,0)
#define SOURCE 0
#define TARGET -1
#define BOUNDARY -2
#define winsize 4
#define save_path "result"

typedef struct
{
	double grad_x;
	double grad_y;
}gradient;

typedef struct
{
	double norm_x;
	double norm_y;
}norm;
class inpainting{
	public :
		CImage *Image;
		bool bOpen;
                int m_width;
        int m_height;
	U8 m_pDIBBits;
	U32	m_dwBytesPerLine;
	double * m_r;
	double * m_g;
	double * m_b;
	
        int * m_mark;
        double * m_confid;
        double * m_pri;
        double * m_gray;
        bool * m_source;
	int m_top, m_bottom, m_left, m_right;
	COLORREF *m_color;
	inpainting(char * name);
        bool process();
        void DrawBoundary();

        double ComputeConfidence(int i, int j);
        double priority(int x, int y);
        double ComputeData(int i, int j);
        void Convert2Gray(void);
        gradient GetGradient(int i, int j);
        norm GetNorm(int i, int j);
        bool draw_source(void);
        bool PatchTexture(int x, int y,int &patch_x,int &patch_y);
        bool update(int target_x, int target_y, int source_x, int source_y, double confid);
        bool TargetExist(void);
        void UpdateBoundary(int i, int j);
        void UpdatePri(int i, int j);
	int *CountCR();
};
#endif

