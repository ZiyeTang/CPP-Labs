#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"
using namespace std;
int main() {
  size_t width = 51;
  size_t height = 55;
  ElevationDataset ed(
      "example-data/ex_input_data/map-input-w51-h55.dat", width, height);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  gi.ToPpm("pfile.txt");
  pi.ToPpm("pathimg.txt");
}