#ifndef ELEVATION_DATASET_H
#define ELEVATION_DATASET_H

#include <cstdlib>  // for size_t
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class ElevationDataset {
public:
  // write behavior declarations here; define in elevation_dataset.cc.
  ElevationDataset(const std::string& filename, size_t w, size_t h);
  size_t Width() const { return width_; }
  size_t Height() const { return height_; }
  int MaxEle() const { return max_ele_; }
  int MinEle() const { return min_ele_; }
  int DatumAt(size_t row, size_t col) const {
    if (row < 0 || col < 0 || row >= height_ || col >= width_) {
      return kMa;
    }
    return data_[row][col];
  }
  const std::vector<std::vector<int>>& GetData() const { return data_; }

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<int>> data_;
  int max_ele_;
  int min_ele_;
  static const int kMa = 2e9, kMi = -2e9;
};

#endif