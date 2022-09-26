#include "process.h"
#include "math/vec3.h"

const double kernel[3] = { 0.307801, 0.384397, 0.307801 };

inline static int edge(int x, int i, int w)
{
	int inx = x + i;
	if (inx < 0 || inx >= w)
		return x - i;
	return inx;
}

Image gaussianBlurOneThread(const Image& src)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, src.getChannels());
	Image temp(width, height, src.getChannels());

	int r = 1;

	// 在横向进行一次滤波, 结果存储在temp中
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Math::Vec3f color;
			for (int i = -r; i <= r; ++i)
			{
				int inx = edge(x, i, width);
				color += src.getColor<3>(y, inx) *= kernel[r + i];
			}
			temp.setColor(y, x, color);
		}
	}

	// 在竖向进行一次滤波
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Math::Vec3f color;
			for (int i = -r; i <= r; ++i)
			{
				int iny = edge(y, i, height);
				color += temp.getColor<3>(iny, x) *= kernel[r + i];
			}
			dst.setColor(y, x, color);
		}
	}

	return dst;
}
