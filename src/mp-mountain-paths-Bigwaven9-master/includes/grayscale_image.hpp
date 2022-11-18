#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

class GrayscaleImage {
public:
  GrayscaleImage(const ElevationDataset& dataset);
  GrayscaleImage(const std::string& filename, size_t width, size_t height);
  size_t Width() const { return width_; }
  size_t Height() const { return height_; }
  unsigned int MaxColorValue() const { return kMaxColorValue; }
  const Color& ColorAt(int row, int col) const { return image_[row][col]; }
  const std::vector<std::vector<Color>>& GetImage() const { return image_; }
  void ToPpm(const std::string& name) const;

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int kMaxColorValue = 255;
};

#endif