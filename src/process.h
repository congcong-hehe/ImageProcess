#pragma once

#include <thread>
#include "image.h"
#include <vector>
#include "ThreadPool.h"

Image gaussianBlurOneThread(const Image& image);
Image gaussianBlurMultiThread(const Image& src, int num_thread, ThreadPool& pool);

Image brightExtractOneThread(const Image& src, const float threshold);
Image brightExtractMultiThread(const Image& src, const float threshold, int num_thread, ThreadPool& pool);

Image sobelEdgeDetectionOneThread(const Image& src, const float threshold);
Image sobelEdgeDetectionMultiThread(const Image& src, const float threshold, int num_thread, ThreadPool& pool);


