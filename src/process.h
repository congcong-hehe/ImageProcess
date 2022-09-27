#pragma once

#include <thread>
#include "image.h"
#include <vector>

Image gaussianBlurOneThread(const Image& image);

Image brightExtractOneThread(const Image& src, const float threshold);
Image brightExtractMultiThread(const Image& src, const float threshold, int num_thread);

Image sobelEdgeDetection(const Image& src, const float threshold);

