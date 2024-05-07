#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

const ImagePPM& SeamCarver::GetImage() const { return image_; }

int SeamCarver::GetHeight() const { return height_; }

int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  int rcol =
      image_.GetPixel(row, ((col - 1) % width_ + width_) % width_).GetRed() -
      image_.GetPixel(row, ((col + 1) % width_ + width_) % width_).GetRed();
  int gcol =
      image_.GetPixel(row, ((col - 1) % width_ + width_) % width_).GetGreen() -
      image_.GetPixel(row, ((col + 1) % width_ + width_) % width_).GetGreen();
  int bcol =
      image_.GetPixel(row, ((col - 1) % width_ + width_) % width_).GetBlue() -
      image_.GetPixel(row, ((col + 1) % width_ + width_) % width_).GetBlue();

  int rrow =
      image_.GetPixel(((row - 1) % height_ + height_) % height_, col).GetRed() -
      image_.GetPixel(((row + 1) % height_ + height_) % height_, col).GetRed();
  int grow = image_.GetPixel(((row - 1) % height_ + height_) % height_, col)
                 .GetGreen() -
             image_.GetPixel(((row + 1) % height_ + height_) % height_, col)
                 .GetGreen();
  int brow =
      image_.GetPixel(((row - 1) % height_ + height_) % height_, col)
          .GetBlue() -
      image_.GetPixel(((row + 1) % height_ + height_) % height_, col).GetBlue();

  int delta_col_square = rcol * rcol + gcol * gcol + bcol * bcol;
  int delta_row_square = rrow * rrow + grow * grow + brow * brow;
  return delta_col_square + delta_row_square;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** dp = new int*[height_];
  for (int i = 0; i < height_; i++) {
    dp[i] = new int[width_];
  }

  for (int r = 0; r < height_; r++) {
    dp[r][width_ - 1] = GetEnergy(r, width_ - 1);
  }

  for (int c = width_ - 2; c >= 0; c--) {
    for (int r = 0; r < height_; r++) {
      int mid = dp[r][c + 1];
      int top = mid + 1;
      int bottom = mid + 1;

      if (r > 0) {
        top = dp[r - 1][c + 1];
      }
      if (r < height_ - 1) {
        bottom = dp[r + 1][c + 1];
      }

      dp[r][c] = GetEnergy(r, c) + std::min(std::min(top, bottom), mid);
    }
  }

  int* seam = TraceHorizontalSeam(dp);
  for (int i = 0; i < height_; i++) {
    delete[] dp[i];
  }
  delete[] dp;
  return seam;
}

int* SeamCarver::TraceHorizontalSeam(int** dp) const {
  int* seam = new int[width_];
  int startrow = 0;
  for (int i = 1; i < height_; i++) {
    if (dp[startrow][0] > dp[i][0]) {
      startrow = i;
    }
  }

  seam[0] = startrow;

  int prevrow = startrow;
  for (int c = 1; c < width_; c++) {
    prevrow = NextRow(dp, prevrow, c);
    seam[c] = prevrow;
  }
  return seam;
}

int SeamCarver::NextRow(int** dp, int prevrow, int c) const {
  int mid = dp[prevrow][c];
  int top = mid + 1;
  int bottom = mid + 1;
  if (prevrow > 0) {
    top = dp[prevrow - 1][c];
  }
  if (prevrow < height_ - 1) {
    bottom = dp[prevrow + 1][c];
  }

  if (mid <= top) {
    if (mid <= bottom) {
      return prevrow;
    }
    return prevrow + 1;
  }

  if (top <= bottom) {
    return prevrow - 1;
  }
  return prevrow + 1;
}

int* SeamCarver::GetVerticalSeam() const {
  int** dp = new int*[height_];
  for (int i = 0; i < height_; i++) {
    dp[i] = new int[width_];
  }

  for (int c = 0; c < width_; c++) {
    dp[height_ - 1][c] = GetEnergy(height_ - 1, c);
  }

  for (int r = height_ - 2; r >= 0; r--) {
    for (int c = 0; c < width_; c++) {
      int mid = dp[r + 1][c];
      int left = mid + 1;
      int right = mid + 1;

      if (c > 0) {
        left = dp[r + 1][c - 1];
      }
      if (c < width_ - 1) {
        right = dp[r + 1][c + 1];
      }

      dp[r][c] = GetEnergy(r, c) + std::min(std::min(left, right), mid);
    }
  }

  int* seam = TraceVerticalSeam(dp);
  for (int i = 0; i < height_; i++) {
    delete[] dp[i];
  }
  delete[] dp;
  return seam;
}

int* SeamCarver::TraceVerticalSeam(int** dp) const {
  int* seam = new int[height_];
  int startcol = 0;
  for (int i = 1; i < width_; i++) {
    if (dp[0][startcol] > dp[0][i]) {
      startcol = i;
    }
  }

  seam[0] = startcol;

  int prevcol = startcol;
  for (int r = 1; r < height_; r++) {
    prevcol = NextCol(dp, prevcol, r);
    seam[r] = prevcol;
  }
  return seam;
}

int SeamCarver::NextCol(int** dp, int prevcol, int r) const {
  int mid = dp[r][prevcol];
  int left = mid + 1;
  int right = mid + 1;
  if (prevcol > 0) {
    left = dp[r][prevcol - 1];
  }
  if (prevcol < width_ - 1) {
    right = dp[r][prevcol + 1];
  }

  if (mid <= left) {
    if (mid <= right) {
      return prevcol;
    }
    return prevcol + 1;
  }

  if (left <= right) {
    return prevcol - 1;
  }
  return prevcol + 1;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* seam = GetHorizontalSeam();
  image_.RemoveHSeam(seam);
  height_--;
  delete[] seam;
}

void SeamCarver::RemoveVerticalSeam() {
  int* seam = GetVerticalSeam();
  image_.RemoveVSeam(seam);
  width_--;
  delete[] seam;
}