// inpaint.cpp : Defines the entry point for the console application.
//
#include "inpainting.h"
int main(int argc, char* argv[]) {
  inpainting test("pix.bmp");
  test.process();
  return 0;
}

