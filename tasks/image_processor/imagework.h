#pragma once

#include <string>
#include <vector>
#include <string_view>

template <typename T>
T SwapEndian(T u) {
    T dest;

    char *source_c = reinterpret_cast<char *>(&u);
    char *dest_c = reinterpret_cast<char *>(&dest);

    for (size_t k = 0; k < sizeof(T); k++) {
        dest_c[k] = source_c[sizeof(T) - k - 1];
    }

    return dest;
}

struct Pixel {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

#pragma pack(push, 1)

struct BMPHeaderFile {
    uint16_t magic_bytes;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data;
};

struct BMPHeaderInfo {
    uint32_t size = 0;
    int32_t width = 0;
    int32_t height = 0;

    uint16_t planes = 1;
    uint16_t bits_per_pixel = 0;
    uint32_t compression = 0;
    uint32_t image_size = 0;
    int32_t x_pixels_per_m = 0;
    int32_t y_pixels_per_m = 0;
    uint32_t colors_used = 0;
    uint32_t colors_important = 0;
};

#pragma pack(pop)

class Image {
public:
    explicit Image(const std::string_view &path);

    void WriteBMP(const std::string_view &path);
    void Resize(int32_t width, int32_t height);
    Pixel GetPixel(int32_t x, int32_t y);
    void ChangePixel(int32_t x, int32_t y, Pixel new_pixel);

    std::vector<uint8_t> pixels;
    BMPHeaderFile bmp_file_header;
    BMPHeaderInfo bmp_info_header;

    const uint16_t BMP_MAGIC_BYTES = 0x4d42;
    const int32_t BMP_INFO_HEADER_SIZE = 40;
    constexpr static const int RgbMaxI = 255;
    constexpr static const double RgbMaxD = 255.0;
};
