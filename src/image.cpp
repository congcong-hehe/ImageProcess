// make by hyq
// 2021/11/16

#define _CRT_SECURE_NO_WARNINGS
#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <string>
#include "math/vec3.h"

using namespace std;
using namespace Math;

Image::Image() {
    
}

Image::~Image() {
    if(data_ != nullptr)
        stbi_image_free(data_);
}

bool Image::read(const string &file_path) {
    int channels = 0;
    // 读取image的时候，分配的内存是按照自己设置的channels来分配的，channels输出的是image的位深度
    data_ = stbi_load(file_path.c_str(), &width_, &height_, &channels, channels_);
    if(!data_) {
        printf("ERROR: Could not read image file %s\n", file_path.c_str());
        return false;
    } else {
        printf("LOG: Load image file %s\n", file_path.c_str());
        return true;
    }
}

// 暂时全部保存为png形式
bool Image::write(const string &file_path) const {
    if (data_ == nullptr) {
        printf("ERROR: Could not write image file %s\n", file_path.c_str());
        return false;
    }
    int tag = stbi_write_png(file_path.c_str(), width_, height_, channels_, data_, width_ * channels_);
    if(0 == tag) {
        printf("ERROR: Could not write image file %s\n", file_path.c_str());
        return false;
    } else {
        printf("LOG: Write image file %s\n", file_path.c_str());
        return true;
    }
}

Vec3f Image::getColor(const int u, const int v) const {
    assert(u < height_ && u >= 0);
    assert(v < width_ && v >= 0);

    float scale = 1/255.0f;
    int index = u * channels_ * width_ + v * channels_;
    return Vec3f(scale * data_[index], scale * data_[index + 1], scale * data_[index + 2]);
}

void Image::setColor(const int u, const int v, const Vec3f &color) const {
    assert(u < height_ && u >= 0);
    assert(v < width_ && v >= 0);

    float scale = 255.0f;
    int index = u * channels_ * width_ + v * channels_;
    data_[index] = (unsigned char)(color.r * scale);
    data_[index + 1] = (unsigned char)(color.g * scale);
    data_[index + 2] = (unsigned char)(color.b * scale);
}

void Image::setBackColor(const Math::Vec3f &color) const
{
    for(int i = 0; i < height_; ++i) {
        for(int j = 0; j < width_; ++j)
            setColor(i, j, color);
    }
}

bool Image::init() {
    data_  = (unsigned char*)stbi__malloc(width_ * height_ * channels_);
    if(!data_) {
        printf("ERROR: Could not malloc memory for image\n");
        return false;
    } else {
        memset(data_, 0, width_ * height_ * channels_);
        return true;
    }
}