#include "image.h"
#include "process.h"
#include "utility.h"
#include <iostream>
#include <time.h>
#include "ThreadPool.h"

void f(int i)
{
	std::cout << i << std::endl;
}

int main()
{
	time_t begin, end;
	
	begin = clock();

	ThreadPool pool(4);

	Image src;
	src.read("D:\\study_data\\pro\\mypro\\image_process\\ImageProcess\\image\\0.png");
	Image ans = gaussianBlurMultiThread(src, 4, pool);
	ans.write("D:\\study_data\\pro\\mypro\\image_process\\ImageProcess\\image\\1.png");

	end = clock();
	std::cout << "DONE: cost " << end - begin << " ms.";
}