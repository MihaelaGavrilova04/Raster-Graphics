#pragma once

#include <iostream>
#include <stdexcept>
#include "CommandProcessor.h"
#include "Session.hpp"
#include "SessionHolder.hpp"
#include "ImageReader.h"
#include "PPM_Reader.h"
#include "PGM_Reader.h"
#include "PBM_Reader.h"
#include "PPM_Writer.h"
#include "GrayscaleConverter.h"
#include "MonochromeConverter.h"
#include "NegativeConverter.h"
#include "Rotator.h"
#include "ImageConverter.h"
#include "GrayscaleCommand.h"
#include "NegativeCommand.h"
#include "MonochromeCommand.h"
#include "RotateCommand.h"
#include "Collage.h"
#include "createInputFile.h" 

/*
EXAMPLE COMMANDS:
processCommand("load INPUT.ppm");
processCommand("load grayFILE.pgm");
processCommand("load PBM_file.pbm");

processCommand("monochrome"); //the first command should be executed 2 times, not on the new image
processCommand("grayscale"); 
processCommand("rotate left");
processCommand("save");
processCommand("session info");
*/

class Executor 
{
public:
 Executor();

void executeProgram();

private:
SessionHolder<numSessions> sessionHolder;
CommandProcessor processor;
int activeSessionId;

void processCommand(const myString& command);
void createExampleImageFiles();

static constexpr int MAX_BUFF_SIZE = 1024;
};
