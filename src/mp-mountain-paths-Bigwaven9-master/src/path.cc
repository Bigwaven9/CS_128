#include "path.hpp"

Path::Path(size_t length, size_t starting_row) {
  length_ = length;
  starting_row_ = starting_row;
  path_ = std::vector<size_t>(length, starting_row);
  ele_change_ = 0;
}