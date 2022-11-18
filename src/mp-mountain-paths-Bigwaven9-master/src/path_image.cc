#include "path_image.hpp"

#include <iostream>

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  path_image_ = image.GetImage();
  for (size_t i = 0; i < height_; ++i) {
    Path temp(width_, i);
    for (size_t j = 1; j < width_; ++j) {
      size_t last = temp.GetPath()[j - 1];
      int prev = dataset.DatumAt(last, j - 1);
      size_t cur = last - 1;
      for (size_t d = 0; d < 2; ++d) {
        if (abs(dataset.DatumAt(last + dy_[d], j) - prev) <=
            abs(dataset.DatumAt(cur, j) - prev)) {
          cur = last + dy_[d];
        }
      }
      temp.SetLoc(j, cur);
      temp.IncEleChange(abs(dataset.DatumAt(cur, j) - prev));
    }
    paths_.push_back(temp);
  }
  const Color kRed = Color(252, 25, 63);
  const Color kGreen = Color(31, 253, 13);
  Path path = paths_[0];
  for (const auto& i : paths_) {
    if (i.EleChange() < path.EleChange()) {
      path = i;
    }
    for (size_t j = 0; j < i.Length(); ++j) {
      path_image_[i.GetPath()[j]][j] = kRed;
    }
  }
  for (size_t i = 0; i < width_; ++i)
    path_image_[path.GetPath()[i]][i] = kGreen;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3\n";
  ofs << width_ << ' ' << height_ << "\n";
  ofs << "255\n";
  for (const auto& i : path_image_) {
    for (const auto& j : i) {
      ofs << j.Red() << ' ' << j.Green() << ' ' << j.Blue() << ' ';
    }
    ofs << '\n';
  }
}