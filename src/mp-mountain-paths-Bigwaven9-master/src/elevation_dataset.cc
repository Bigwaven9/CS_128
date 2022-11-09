#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t w,
                                   size_t h):
    width_(w), height_(h), max_ele_(kMi), min_ele_(kMa) {
  std::ifstream ifs{filename};
  int t = 0;
  for (size_t i = 0; i < h; ++i) {
    std::vector<int> temp;
    for (size_t j = 0; j < w; ++j) {
      if (ifs.good())
        ifs >> t;
      else
        throw std::runtime_error("");
      temp.push_back(t);
      max_ele_ = std::max(max_ele_, t);
      min_ele_ = std::min(min_ele_, t);
    }
    data_.push_back(temp);
  }
  ifs >> t;
  if (!ifs.fail()) throw std::runtime_error("");
}