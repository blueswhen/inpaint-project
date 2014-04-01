#ifndef inpaint_inpainting_H_
#define inpaint_inpainting_H_

#include "image.h"
 
#define PAINT_COLOR  RGB(0,255,0)
#define SOURCE 0
#define TARGET -1
#define BOUNDARY -2
#define winsize 4
#define save_path "result"

typedef struct {
  double grad_x;
  double grad_y;
}gradient;

typedef struct {
  double norm_x;
  double norm_y;
}norm;

class inpainting {
 public:
    CImage *Image;
    bool Process();
    inpainting(char * name);
 private :
  int max_height;
  int max_width;
  int m_width;
  int m_height;
  int *number_to_fill_x;
  int *number_to_fill_y;
  bool bOpen;

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
  void DrawBoundary();
  double ComputeConfidence(int i, int j);
  double ComputePriority(int x, int y);
  double ComputeData(int i, int j);
  void Convert2Gray(void);
  gradient GetGradient(int i, int j);
  norm GetNorm(int i, int j);
  bool DrawSource(void);
  bool PatchTexture(int x, int y,int &patch_x,int &patch_y);
  bool FillTarget(int target_x, int target_y, int source_x, int source_y, double confid);
  bool TargetExist(void);
  void UpdateBoundary(int i, int j);
  void UpdatePriority(int i, int j);
  int *CountCR();
};
#endif

