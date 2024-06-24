#pragma once
#include "Session.hpp"
#include "SessionHolder.hpp"
#include "Image.h"
#include "myString.h"
#include <stdexcept>
#include <sstream>
#include "ImageReader.h"
#include "PPM_Reader.h"
#include "PGM_Reader.h"
#include "PBM_Reader.h"
#include "imageFormat.h"
#include "UniquePtr.hpp"
#include "GrayscaleConverter.h"
#include "NegativeConverter.h"
#include "MonochromeConverter.h"
#include "Rotator.h"
#include "GrayscaleCommand.h"
#include "NegativeCommand.h"
#include "MonochromeCommand.h"
#include "RotateCommand.h"
#include "Collage.h"

static constexpr int numSessions = 10;
static constexpr int sessionCapacity = 10;

class CommandProcessor
{
public:
    CommandProcessor(SessionHolder<numSessions>& holder);

    void processCommand(const myString& currentCommand);

    static void help();//public to be used outside the class

private:
    SessionHolder<numSessions>& sessionHolder;
    int activeSessionId = -1;


    Image* getImage(const char* filename);
    void closeSession(int sessionId);
    void saveas(const myString& filename)const;

    void grayscale(int sessionId);
    void monochrome(int sessionId);
    void negative(int sessionId);
    void rotate(const myString& direction, int sessionId);
    void undo();
    void add(int sessionId, const myString& filename);
    void sessionInfo(int sessionId) const;
    void switchSession(int sessionId);
    void collage(const myString& direction, int sessionId, const myString& firstImFilename, const myString& secImFilename, const myString& outImage);
};

