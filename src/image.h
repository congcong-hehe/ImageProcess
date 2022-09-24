#pragma once

#include <string>
#include "math/vec3.h"

class Image {
public:
    Image();
    ~Image();
    bool read(const std::string &file_path);
    bool write(const std::string &file_path) const;
    Math::Vec3f getColor(const int u, const int v) const;
    void setColor(const int u, const int v, const Math::Vec3f &color) const;
    void setBackColor(const Math::Vec3f &color) const;
    bool init(); 

    int getHeight() const { return height_; }
    int getWidth() const { return width_; }
    int getChannels() const { return channels_; } 
    void setWidth(const int w) { width_ = w; }
    void setHeight(const int h) { height_ = h; }
    void setChannels(const int c) { channels_ = c; }
    bool empty() const {return !data_; };

private:
    int width_ = 512;
    int height_ = 512;
    int channels_ = 4;
    unsigned char *data_ = nullptr;
};