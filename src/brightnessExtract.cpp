#include "process.h"

Image brightExtractOneThread(const Image& src, const float threshold)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, 1);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Math::Vec3f color = src.getColor<3>(y, x);
			float lumen = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
			if(lumen > threshold)
				dst.setColor(y, x, lumen);
		}
	}

	return dst;
}

static void brightExtract(int height_begin, int height_end, int width, const Image& src, Image& dst, const float threshold)
{
	for (int y = height_begin; y < height_end; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Math::Vec3f color = src.getColor<3>(y, x);
			float lumen = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
			if (lumen > threshold)
				dst.setColor(y, x, lumen);
		}
	}
}

Image brightExtractMultiThread(const Image& src, const float threshold, int num_thread, ThreadPool& pool)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, 1);
	int offset = height / num_thread;

	std::vector<std::future<void>> results;

	for (int i = 0; i < num_thread; ++i)
	{
		int height_begin = i * offset;
		int height_end = (i + 1) * offset > height ? height : (i + 1) * offset;
		results.push_back(pool.enqueue(brightExtract, height_begin, height_end, width, std::ref(src), std::ref(dst), threshold));
	}

	for (int i = 0; i < num_thread; ++i)
		results[i].get();

	return dst;
}

