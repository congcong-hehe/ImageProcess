#include "image.h"
#include "process.h"
#include "utility.h"
#include <iostream>
#include <time.h>
#include "ThreadPool.h"
#include <io.h>

void execute(const std::string path, const std::string mode, int num_thread, ThreadPool& pool, float edge_threshold, float bright_threshold)
{
	_finddata_t file;
	intptr_t HANDLE;
	std::string Onepath = path + mode;
	HANDLE = _findfirst(Onepath.c_str(), &file);
	if (HANDLE == -1L)
	{
		printf("ERROR: can not match the folder path\n");
		system("pause");
	}
	do {
		//判断是否有子目录  
		if (file.attrib & _A_SUBDIR)
		{
			//判断是否为"."当前目录，".."上一层目录
			if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0))
			{
				std::string newPath = path + "\\" + file.name;
				execute(newPath, mode, num_thread, pool, edge_threshold, bright_threshold);
			}
		}
		else
		{
			Image src;
			if (src.read(path + "\\" + file.name))
			{
				std::string name(file.name);
				name = name.substr(0, name.size() - 4);

				Image gauss = gaussianBlurMultiThread(src, num_thread, pool).resize(src.getWidth() / 2, src.getHeight() / 2);
				Image bright = brightExtractMultiThread(src, bright_threshold, num_thread, pool);
				Image edge = sobelEdgeDetectionMultiThread(src, edge_threshold, num_thread, pool);

				gauss.write(path + "\\" + name + "_gauss" + ".png");
				edge.write(path + "\\" + name + "_edge" + ".png");
				bright.write(path + "\\" + name + "_bright" + ".png");
			}
		}
	} while (_findnext(HANDLE, &file) == 0);
	_findclose(HANDLE);
}

int main()
{
	int num_thread = 4;
	float edge_threshold = 0.5f, bright_threshold = 0.5f;
	std::string path = "image";

	time_t begin, end;
	
	begin = clock();

	ThreadPool pool(num_thread);

	execute(path, "\\*.png", num_thread, pool, edge_threshold, bright_threshold);

	end = clock();
	std::cout << "DONE: cost " << end - begin << " ms.";
}