#include "elevation_dataset.hpp"
ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs(filename);

  if (ifs.fail()) {
    throw std::runtime_error("Invalid filename");
  }

  int datum = 0;
  std::vector<int> row;
  size_t cn = 0;
  size_t rn = 0;

  max_ele_ = std::numeric_limits<int>::min();
  min_ele_ = std::numeric_limits<int>::max();
  while (ifs >> datum) {
    if (max_ele_ < datum) {
      max_ele_ = datum;
    }

    if (min_ele_ > datum) {
      min_ele_ = datum;
    }

    row.push_back(datum);
    cn++;
    if (cn == width_) {
      cn = 0;
      rn++;
      data_.push_back(row);
      row.clear();
    }
  }

  if (rn * width_ + cn != width_ * height_) {
    throw std::runtime_error("Invalid file");
  }

  ifs.close();
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_[row][col];
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}
