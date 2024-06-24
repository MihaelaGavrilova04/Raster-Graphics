#include "Executor.h"
Executor::Executor() : sessionHolder(), processor(sessionHolder), activeSessionId(-1) {}

void Executor::executeProgram() {
CommandProcessor::help();
char input[MAX_BUFF_SIZE];
while (true) {
    std::cin.getline(input, sizeof(input));
    try {
        myString command(input);
        if (command == "stop" || command == "Stop" || command == "STOP")
            break;
        processCommand(command);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
}

void Executor::processCommand(const myString& command) {
    processor.processCommand(command);
}

void Executor::createExampleImageFiles() {
    createFile::createPPMFile("image1.ppm");
    createFile::createPGMFile("image2.pgm");
    createFile::createPBMFile("image3.pbm");
}