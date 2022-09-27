#include "process.h"

Image sobelEdgeDetectionOneThread(const Image& src, const float threshold)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, 1);
	
	Image temp = brightExtractOneThread(src, 0.0);	// 得到灰度图像

	for (int y = 1; y < height - 1; ++y)
	{
		for (int x = 1; x < width - 1; ++x)
		{
			float gray00 = temp.getColor(y - 1, x - 1);
			float gray01 = temp.getColor(y - 1, x - 0);
			float gray02 = temp.getColor(y - 1, x + 1);
			float gray10 = temp.getColor(y - 0, x - 1);
			float gray12 = temp.getColor(y - 0, x + 1);
			float gray20 = temp.getColor(y + 1, x - 1);
			float gray21 = temp.getColor(y + 1, x - 0);
			float gray22 = temp.getColor(y + 1, x + 1);

			float gx = gray00 + 2 * gray10 + gray20 - (gray02 + 2 * gray12 + gray22);
			float gy = gray00 + 2 * gray01 + gray02 - (gray20 + 2 * gray21 + gray22);
			float g = sqrtf(gx * gx + gy * gy);
			if (g > threshold)
				dst.setColor(y, x, 1.0);
		}
	}
	return dst;
}

static void sobelEdgeDetection(int height_begin, int height_end, int width, const Image& temp, Image& dst, float threshold)
{
	for (int y = height_begin; y < height_end; ++y)
	{
		for (int x = 1; x < width - 1; ++x)
		{
			float gray00 = temp.getColor(y - 1, x - 1);
			float gray01 = temp.getColor(y - 1, x - 0);
			float gray02 = temp.getColor(y - 1, x + 1);
			float gray10 = temp.getColor(y - 0, x - 1);
			float gray12 = temp.getColor(y - 0, x + 1);
			float gray20 = temp.getColor(y + 1, x - 1);
			float gray21 = temp.getColor(y + 1, x - 0);
			float gray22 = temp.getColor(y + 1, x + 1);

			float gx = gray00 + 2 * gray10 + gray20 - (gray02 + 2 * gray12 + gray22);
			float gy = gray00 + 2 * gray01 + gray02 - (gray20 + 2 * gray21 + gray22);
			float g = sqrtf(gx * gx + gy * gy);
			if (g > threshold)
				dst.setColor(y, x, 1.0);
		}
	}
}

Image sobelEdgeDetectionMultiThread(const Image& src, const float threshold, int num_thread, ThreadPool& pool)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, 1);

	Image temp = brightExtractMultiThread(src, 0.0, num_thread, pool);	// 得到灰度图像

	int offset = (height - 2) / num_thread;

	std::vector<std::future<void>> results;

	for (int i = 0; i < num_thread; ++i)
	{
		int height_begin = i * offset;
		int height_end = (i + 1) * offset > height - 2 ? height - 2 : (i + 1) * offset;
		results.push_back(pool.enqueue(sobelEdgeDetection, height_begin + 1, height_end + 1, width, std::ref(temp), std::ref(dst), threshold));
	}

	for (int i = 0; i < num_thread; ++i)
		results[i].get();

	return dst;
}