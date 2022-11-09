#include "seam_carver.hpp"

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

int Mod(int x, int n) { return (x % n + n) % n; }

int Pow(int x) { return x * x; }

int SeamCarver::GetEnergy(int row, int col) {
  Pixel left = image_.GetPixel(Mod(row, height_), Mod(col - 1, width_));
  Pixel right = image_.GetPixel(Mod(row, height_), Mod(col + 1, width_));
  Pixel up = image_.GetPixel(Mod(row - 1, height_), Mod(col, width_));
  Pixel down = image_.GetPixel(Mod(row + 1, height_), Mod(col, width_));
  return Pow(left.GetRed() - right.GetRed()) +
         Pow(left.GetGreen() - right.GetGreen()) +
         Pow(left.GetBlue() - right.GetBlue()) +
         Pow(up.GetRed() - down.GetRed()) +
         Pow(up.GetGreen() - down.GetGreen()) +
         Pow(up.GetBlue() - down.GetBlue());
}

int* SeamCarver::GetHorizontalSeam() {
  int **f = new int *[height_], **from = new int *[height_];
  for (int i = 0; i < height_; ++i) {
    f[i] = new int[width_];
    from[i] = new int[width_];
  }
  for (int i = 0; i < height_; ++i) f[i][width_ - 1] = GetEnergy(i, width_ - 1);

  int* ret = new int[width_];
  for (int j = width_ - 2; j >= 0; --j)
    for (int i = 0; i < height_; ++i) {
      f[i][j] = kM;
      for (int d = 0; d < 3; ++d) {
        int x = i + d_[d];
        if (x < 0 || x >= height_) continue;
        int sum = f[x][j + 1] + GetEnergy(i, j);
        if (sum < f[i][j]) {
          f[i][j] = sum;
          from[i][j] = x;
        }
      }
    }

  int index = 0;
  for (int i = 0; i < height_; ++i)
    if (f[i][0] < f[index][0]) index = i;
  for (int i = 0; i < width_ - 1; ++i) {
    ret[i] = index;
    index = from[index][i];
  }
  ret[width_ - 1] = index;
  for (int i = 0; i < height_; ++i) {
    delete[] f[i];
    delete[] from[i];
  }
  delete[] f;
  delete[] from;
  return ret;
}

int* SeamCarver::GetVerticalSeam() {
  int **f = new int *[height_], **from = new int *[height_];
  for (int i = 0; i < height_; ++i) {
    f[i] = new int[width_];
    from[i] = new int[width_];
  }
  for (int i = 0; i < width_; ++i)
    f[height_ - 1][i] = GetEnergy(height_ - 1, i);

  int* ret = new int[height_];
  for (int j = height_ - 2; j >= 0; --j)
    for (int i = 0; i < width_; ++i) {
      f[j][i] = kM;
      for (int d = 0; d < 3; ++d) {
        int x = i + d_[d];
        if (x < 0 || x >= width_) continue;
        int sum = f[j + 1][x] + GetEnergy(j, i);
        if (sum < f[j][i]) {
          f[j][i] = sum;
          from[j][i] = x;
        }
      }
    }

  int index = 0;
  for (int i = 0; i < width_; ++i)
    if (f[0][i] < f[0][index]) index = i;
  for (int i = 0; i < height_ - 1; ++i) {
    ret[i] = index;
    index = from[i][index];
  }
  ret[height_ - 1] = index;
  for (int i = 0; i < height_; ++i) {
    delete[] f[i];
    delete[] from[i];
  }
  delete[] f;
  delete[] from;
  return ret;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* remove = GetHorizontalSeam();
  image_.Remove(remove, true);
  height_--;
  delete[] remove;
}

void SeamCarver::RemoveVerticalSeam() {
  int* remove = GetVerticalSeam();
  image_.Remove(remove, false);
  width_--;
  delete[] remove;
}