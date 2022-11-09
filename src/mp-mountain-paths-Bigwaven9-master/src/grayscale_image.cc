#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  auto min_ele = dataset.MinEle();
  auto max_ele = dataset.MaxEle();
  for (size_t i = 0; i < height_; ++i) {
    std::vector<Color> temp;
    for (size_t j = 0; j < width_; ++j) {
      int t = 0;
      if (max_ele != min_ele)
        t = std::round((double)(dataset.DatumAt(i, j) - min_ele) /
                       (max_ele - min_ele) * kMaxColorValue);
      temp.push_back(Color(t, t, t));
    }
    image_.push_back(temp);
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset = ElevationDataset(filename, width, height);
  width_ = dataset.Width();
  height_ = dataset.Height();
  auto min_ele = dataset.MinEle();
  auto max_ele = dataset.MaxEle();
  for (size_t i = 0; i < height_; ++i) {
    std::vector<Color> temp;
    for (size_t j = 0; j < width_; ++j) {
      int t = 0;
      if (max_ele != min_ele)
        t = std::round((double)(dataset.DatumAt(i, j) - min_ele) /
                       (max_ele - min_ele) * kMaxColorValue);
      temp.push_back(Color(t, t, t));
    }
    image_.push_back(temp);
  }
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3\n";
  ofs << width_ << ' ' << height_ << "\n";
  ofs << "255\n";
  for (const auto& i : image_) {
    for (const auto& j : i) {
      ofs << j.Red() << ' ' << j.Green() << ' ' << j.Blue() << ' ';
    }
    ofs << '\n';
  }
}