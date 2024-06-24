#include "createInputFile.h"
#include <fstream>
void createFile::createPPMFile(const char* filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open())
        throw std::logic_error("Invalid argument!\n");

    int width = 3;
    int height = 3;
    int maxColorValue = 255;

    ofs << "P3\n" << width << " " << height << "\n" << maxColorValue << "\n";
    ofs << "255 0 0   0 255 0   0 0 255\n";
    ofs << " 255 255 255   255 255 255   0 0 0\n";
    ofs << " 128 128 128   0 255 255   255 0 255";

    ofs.close();
}
void createFile::createPGMFile(const char* filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open())
        throw std::logic_error("Invalid argument!\n");

    int width = 4;
    int height = 4;
    int maxColorValue = 15;

    ofs << "P2\n" << width << " " << height << "\n" << maxColorValue << "\n";
    ofs << "0 0 0 115 \n"
        "0 0 215 15 \n"
        "0 15 15 15 \n"
        "15 105 15 45";

    ofs.close();
}

void createFile::createPBMFile(const char* filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open())
        throw std::logic_error("Invalid argument!\n");

    int width = 3;
    int height = 2;
    ofs << "P1\n" << width << " " << height << "\n";
    ofs << "0 0 0 \n";
    ofs << "1 0 0 \n";
    
    ofs.close();
}