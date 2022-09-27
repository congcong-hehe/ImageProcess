#include "process.h"

Image sobelEdgeDetection(const Image& src, const double threshold)
{
	int width = src.getWidth(), height = src.getHeight();

	Image dst(width, height, 1);
	
	Image temp = brightExtractOneThread(src, 0.0);	// µÃµ½»Ò¶ÈÍ¼Ïñ

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
			float g = sqrt(gx * gx + gy * gy);
			if (g > threshold)
				dst.setColor(y, x, 1.0);
		}
	}
	return dst;
}