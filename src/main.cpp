#include "image.h"
#include "process.h"
#include "utility.h"
#include <iostream>

int main()
{
	Image src;
	src.read("D:\\study_data\\pro\\mypro\\image_process\\ImageProcess\\image\\0.png");
	Image ans = gaussianBlurOneThread(src);
	ans.write("D:\\study_data\\pro\\mypro\\image_process\\ImageProcess\\image\\1.png");
}