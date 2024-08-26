//
// Created by 19254 on 24-8-26.
//
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <vector>

void bin2c(const std::string &inputFilePath, const std::string &arrayName, const std::string &outputFilePath, bool existentialSkip) {
  std::ifstream inputFile(inputFilePath, std::ios::binary);
  if (!inputFile.is_open()) {
    std::cerr << "Could not open the input file: " << inputFilePath << std::endl;
    return;
  }
  auto outputFilePathCPP = outputFilePath + ".cpp";
  if (!(existentialSkip&&std::filesystem::exists(outputFilePathCPP))) {
    std::ofstream outputFile(outputFilePathCPP);
    if (!outputFile.is_open()) {
      std::cerr << "Could not open the output file: " << outputFilePathCPP << std::endl;
      return;
    }

    outputFile << "#include \"" << arrayName << ".h\"\n";
    outputFile << "const unsigned char " << arrayName << "[] = {\n";
    outputFile << std::hex << std::setw(2) << std::setfill('0');

    const size_t bufferSize = 1024;
    std::vector<unsigned char> buffer(bufferSize);
    size_t bytesRead;
    size_t totalSize = 0;

    while ((bytesRead = inputFile.read(reinterpret_cast<char *>(buffer.data()), bufferSize).gcount()) > 0) {
      for (size_t i = 0; i < bytesRead; ++i, ++totalSize) {
        if (totalSize % 12 == 0) {
          outputFile << "    ";
        }
        outputFile << "0x" << static_cast<int>(buffer[i]);
        if (totalSize % 12 == 11 || totalSize == bytesRead - 1) {
          outputFile << ",\n";
        } else {
          outputFile << ", ";
        }
      }
    }

    outputFile << "};\n\n";
    outputFile << "unsigned int " << arrayName << "_len = 0x" << totalSize << ";\n";

    inputFile.close();
    outputFile.close();

    std::cout << "Conversion complete: " << outputFilePathCPP << std::endl;
  }
  auto outputFilePathH = outputFilePath + ".h";
  if (!(existentialSkip&&std::filesystem::exists(outputFilePathH))) {
    std::ofstream outputFile(outputFilePathH);
    if (!outputFile.is_open()) {
      std::cerr << "Could not open the output file: " << outputFilePathH << std::endl;
      return;
    }
    outputFile << "#ifndef _DEF_SRATIC_" << arrayName << "_H_\n";
    outputFile << "#define _DEF_SRATIC_" << arrayName << "_H_\n";
    outputFile << "extern const unsigned char " << arrayName << "[];\n";
    outputFile << "extern unsigned int " << arrayName << "_len;\n";
    outputFile << "#endif\n";
    outputFile.close();
    std::cout << "Header file created: " << outputFilePathH << std::endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " <input_file> <array_name> <output_file> <existential_skip(0/1)>" << std::endl;
    return 1;
  }
  std::cout << "Convert " << argv[1] << " to " << argv[3] << " with array name " << argv[2] << std::endl;
  std::string inputFilePath = argv[1];
  std::string arrayName = argv[2];
  std::string outputFilePath = argv[3];
  std::string existentialSkip = argv[4];

  bin2c(inputFilePath, arrayName, outputFilePath, existentialSkip != "0");

  return 0;
}
