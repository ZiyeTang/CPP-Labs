#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;

private:
  size_t MinEleRow(int r, int c, const ElevationDataset& dataset, int prev);
  void InitPathImage(const GrayscaleImage& image);
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  int best_path_row_ = -1;
  int ele_in_best_path_ = -1;
};

#endif