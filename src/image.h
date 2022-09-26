#pragma once

#include <string>
#include "math/vec3.h"
#include <assert.h>

class Image {
public:
    Image();
    Image(int width, int height, int channels);
    ~Image();
    Image(const Image& image);
    Image(Image&& image) noexcept;

    bool read(const std::string& file_path);
    bool write(const std::string& file_path) const;

    template<int N> Math::Vec<N, float> getColor(const int u, const int v) const {
        assert(u < height_&& u >= 0);
        assert(v < width_&& v >= 0);

        static float scale = 1 / 255.0f;
        int index = u * channels_ * width_ + v * channels_;

        Math::Vec<N, float> color;

        for (int i = 0; i < channels_; ++i)
        {
            color[i] = scale * data_[index + i];
        }

        return color;
    }

    template<int N> void setColor(const int u, const int v, const Math::Vec<N, float> &color) const {
        assert(u < height_&& u >= 0);
        assert(v < width_&& v >= 0);

        static float scale = 255.0f;
        int index = u * channels_ * width_ + v * channels_;

        for (int i = 0; i < channels_; ++i)
        {
            data_[index + i] = (unsigned char)(color[i] * scale);
        }
    }

    template<int N> void setBackColor(const Math::Vec<N, float> &color)  const
    {
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j)
                setColor(i, j, color);
        }
    }

    bool init();

    int getHeight() const { return height_; }
    int getWidth() const { return width_; }
    int getChannels() const { return channels_; } 
    void setWidth(const int w) { width_ = w; }
    void setHeight(const int h) { height_ = h; }
    void setChannels(const int c) { channels_ = c; }
    bool empty() const {return !data_; };

private:
    int width_;
    int height_;
    int channels_;
    unsigned char *data_;
};