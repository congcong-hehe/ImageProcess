#include "process.h"
#include "math/vec3.h"

const float kernel[3] = { 0.307801f, 0.384397f, 0.307801f };

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

static void gaussianBlurX(int height_begin, int height_end, int width, const Image& src, Image& dst, int r)
{
	for (int y = height_begin; y < height_end; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Math::Vec3f color;
			for (int i = -r; i <= r; ++i)
			{
				int inx = edge(x, i, width);
				color += src.getColor<3>(y, inx) *= kernel[r + i];
			}
			dst.setColor(y, x, color);
		}
	}
}

static void gaussianBlurY(int height_begin, int height_end, int width, int height, const Image& src, Image& dst, int r)
{
	for (int y = height_begin; y < height_end; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Math::Vec3f color;
			for (int i = -r; i <= r; ++i)
			{
				int iny = edge(y, i, height);
				color += src.getColor<3>(iny, x) *= kernel[r + i];
			}
			dst.setColor(y, x, color);
		}
	}
}

Image gaussianBlurMultiThread(const Image& src, int num_thread, ThreadPool& pool)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, src.getChannels());
	Image temp(width, height, src.getChannels());

	int offset = height / num_thread;
	std::vector<std::future<void>> results;

	int r = 1;

	for (int i = 0; i < num_thread; ++i)
	{
		int height_begin = i * offset;
		int height_end = (i + 1) * offset > height ? height : (i + 1) * offset;
		results.push_back(pool.enqueue(gaussianBlurX, height_begin, height_end, width, std::ref(src), std::ref(dst), r));
	}

	for (int i = 0; i < num_thread; ++i)
		results[i].get();

	results.clear();

	for (int i = 0; i < num_thread; ++i)
	{
		int height_begin = i * offset;
		int height_end = (i + 1) * offset > height ? height : (i + 1) * offset;
		results.push_back(pool.enqueue(gaussianBlurY, height_begin, height_end, width, height, std::ref(src), std::ref(dst), r));
	}

	for (int i = 0; i < num_thread; ++i)
		results[i].get();

	return dst;
}
