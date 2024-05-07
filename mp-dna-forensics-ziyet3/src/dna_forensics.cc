#include <fstream>
#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::string file_name = argv[1];
  std::string dna_strand = argv[2];
  std::ifstream ifs{file_name};
  std::vector<std::vector<std::string>> data;
  for (std::string line; std::getline(ifs, line); line = "") {
    data.push_back(utilities::GetSubstrs(line, ','));
  }

  std::string match = Match(data, dna_strand);
  std::cout << match << std::endl;
  return 0;
}