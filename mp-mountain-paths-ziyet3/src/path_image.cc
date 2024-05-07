#include "path_image.hpp"

size_t PathImage::MinEleRow(int r,
                            int c,
                            const ElevationDataset& dataset,
                            int prev) {
  int middle_ele_change = std::abs(dataset.DatumAt(r, c) - prev);
  int top_ele_change = middle_ele_change + 1;
  if (r - 1 >= 0) {
    top_ele_change = std::abs(dataset.DatumAt(r - 1, c) - prev);
  }

  int bot_ele_change = middle_ele_change + 1;
  if (r + 1 < int(dataset.Height())) {
    bot_ele_change = std::abs(dataset.DatumAt(r + 1, c) - prev);
  }

  if (middle_ele_change == top_ele_change) {
    if (middle_ele_change <= bot_ele_change) {
      return r;
    }
    return r + 1;
  }

  if (middle_ele_change < top_ele_change) {
    if (middle_ele_change <= bot_ele_change) {
      return r;
    }
    return r + 1;
  }

  if (top_ele_change >= bot_ele_change) {
    return r + 1;
  }
  return r - 1;
}

void PathImage::InitPathImage(const GrayscaleImage& image) {
  width_ = image.Width();
  height_ = image.Height();

  std::vector<Color> row;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      Color c(image.ColorAt(int(i), int(j)).Red(),
              image.ColorAt(int(i), int(j)).Green(),
              image.ColorAt(int(i), int(j)).Blue());
      row.push_back(c);
    }
    path_image_.push_back(row);
    row.clear();
  }
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  InitPathImage(image);

  const Color kRed(252, 25, 63);
  const Color kGreen(31, 253, 13);
  for (size_t i = 0; i < height_; i++) {
    Path p(width_, i);
    path_image_[i][0] = kRed;
    int prev = dataset.DatumAt(i, 0);
    size_t nextrow = i;
    for (size_t col = 1; col < width_; col++) {
      nextrow = MinEleRow(int(nextrow), int(col), dataset, prev);
      path_image_[nextrow][col] = kRed;
      p.IncEleChange(std::abs(dataset.DatumAt(nextrow, col) - prev));
      prev = dataset.DatumAt(nextrow, col);
      p.SetLoc(col, nextrow);
      // std::cout << nextrow << " ";
    }
    // std::cout << p.EleChange() << "\n";

    if (best_path_row_ == -1 || ele_in_best_path_ > int(p.EleChange())) {
      best_path_row_ = int(i);
      ele_in_best_path_ = int(p.EleChange());
    }

    paths_.push_back(p);
  }
  // std::cout << best_path_row_ << " " << ele_in_best_path_ << "\n";
  std::vector<size_t> best_path = paths_[best_path_row_].GetPath();

  for (size_t i = 0; i < best_path.size(); i++) {
    path_image_[best_path[i]][i] = kGreen;
  }
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);

  if (ofs.fail()) {
    throw std::runtime_error("Invalid filename");
  }

  ofs << "P3\n";
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      Color c = path_image_[i][j];
      ofs << c.Red() << " " << c.Green() << " " << c.Blue() << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}