#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  std::vector<Color> row;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      int elevation_point = dataset.DatumAt(i, j);
      int shade_of_gray = 0;
      if (dataset.MinEle() != dataset.MaxEle()) {
        shade_of_gray = int(std::round(
            double(elevation_point - dataset.MinEle()) /
            double(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue));
      }

      row.push_back(Color(shade_of_gray, shade_of_gray, shade_of_gray));
    }
    image_.push_back(row);
    row.clear();
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset(filename, width, height);
  width_ = dataset.Width();
  height_ = dataset.Height();
  std::vector<Color> row;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      int elevation_point = dataset.DatumAt(i, j);

      int shade_of_gray = 0;
      if (dataset.MinEle() != dataset.MaxEle()) {
        shade_of_gray = int(std::round(
            double(elevation_point - dataset.MinEle()) /
            double(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue));
      }

      row.push_back(Color(shade_of_gray, shade_of_gray, shade_of_gray));
    }
    image_.push_back(row);
    row.clear();
  }
}

size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_[row][col];
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);

  if (ofs.fail()) {
    throw std::runtime_error("Invalid filename");
  }

  ofs << "P3\n";
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      Color c = image_[i][j];
      ofs << c.Red() << " " << c.Green() << " " << c.Blue() << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}
