#pragma once

#include "image.h"

Image gaussianBlurOneThread(const Image& image);

Image brightExtractOneThread(const Image& src, const double threshold);

Image sobelEdgeDetection(const Image& src, const double threshold);

