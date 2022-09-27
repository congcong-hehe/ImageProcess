#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <string>

Image::Image() : width_(512), height_(512), channels_(3), data_(nullptr) {

}

Image::Image(int width, int height, int channels) : width_(width), height_(height), channels_(channels) {
    init();
}

Image::~Image() {
    if (data_ != nullptr)
        stbi_image_free(data_);
}

Image::Image(const Image& image) {
    width_ = image.width_;
    height_ = image.height_;
    channels_ = image.channels_;
    if (image.data_ != nullptr)
        memcpy(data_, image.data_, width_ * height_ * channels_);
    else data_ = nullptr;
}

Image::Image(Image&& image) noexcept {
    width_ = image.width_;
    height_ = image.height_;
    channels_ = image.channels_;
    data_ = image.data_;
    image.data_ = nullptr;
}

bool Image::init() {
    data_ = (unsigned char*)stbi__malloc(width_ * height_ * channels_);
    if (!data_) {
        printf("ERROR: Could not malloc memory for image\n");
        return false;
    }
    else {
        memset(data_, 0, width_ * height_ * channels_);
        return true;
    }
}

bool Image::read(const std::string& file_path) {
    int channels = 0;
    // 读取image的时候，分配的内存是按照自己设置的channels来分配的，channels输出的是image的位深度
    data_ = stbi_load(file_path.c_str(), &width_, &height_, &channels, channels_);
    if (!data_) {
        printf("ERROR: Could not read image file %s\n", file_path.c_str());
        return false;
    }
    else {
        printf("LOG: Load image file %s\n", file_path.c_str());
        return true;
    }
}

bool Image::write(const std::string& file_path) const {
    if (data_ == nullptr) {
        printf("ERROR: Could not write image file %s\n", file_path.c_str());
        return false;
    }
    int tag = stbi_write_png(file_path.c_str(), width_, height_, channels_, data_, width_ * channels_);
    if (0 == tag) {
        printf("ERROR: Could not write image file %s\n", file_path.c_str());
        return false;
    }
    else {
        printf("LOG: Write image file %s\n", file_path.c_str());
        return true;
    }
}

float Image::getColor(const int u, const int v) const {
    assert(u < height_&& u >= 0);
    assert(v < width_&& v >= 0);

    static float scale = 1 / 255.0f;
    int index = u * channels_ * width_ + v * channels_;

    return data_[index] * scale;
}

void Image::setColor(const int u, const int v, float gray) const
{
    assert(u < height_&& u >= 0);
    assert(v < width_&& v >= 0);

    static float scale = 255.0f;
    int index = u * channels_ * width_ + v * channels_;

    data_[index] = (unsigned char)(gray * scale);
}