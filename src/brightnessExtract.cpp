#include "process.h"

Image brightExtractOneThread(const Image& src, const double threshold)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, 1);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Math::Vec3f color = src.getColor<3>(y, x);
			double lumen = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
			if(lumen > threshold)
				dst.setColor(y, x, lumen);
		}
	}

	return dst;
}