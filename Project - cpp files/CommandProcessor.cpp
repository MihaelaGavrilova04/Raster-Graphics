#include "CommandProcessor.h"

CommandProcessor::CommandProcessor(SessionHolder<numSessions>& holder): sessionHolder(holder) {}

void CommandProcessor::processCommand(const myString& currentCommand) 
{
    std::stringstream ss(currentCommand.c_str());
    myString command;
    ss >> command;

    if (command == "load") 
    {
        myString filename;
        ss >> filename;

        Image* image = getImage(filename.c_str());
        if (image) 
        {
            if (activeSessionId == -1) 
                activeSessionId = sessionHolder.createSession();
            
            sessionHolder.getSession(activeSessionId)->addImage(image);
        } 
        else 
        throw std::runtime_error("Can't load image from file!\n");
    } 
    else if (command == "close") 
    {
        int sessionId;
        ss >> sessionId;
        closeSession(sessionId);
        if (sessionId == activeSessionId)
            activeSessionId = -1;

    } 
    else if (command == "save")
    {
        sessionHolder.saveAllSessions();

    } 
    else if (command == "saveas") 
    {
        myString filename;
        ss >> filename;
        saveas(filename);
    } 
    else if (command == "help") 
    {
        help();
    } 
    else if (command == "grayscale") 
    {
        grayscale(activeSessionId);

    } else if (command == "monochrome")
    {
        monochrome(activeSessionId);
    } 
    else if (command == "negative")
    {
        negative(activeSessionId);
    }
    else if (command == "rotate") 
    {
        myString direction;
        ss >> direction;
        rotate(direction, activeSessionId);
    } 
    else if (command == "undo") 
    {
        undo();
    }
    else if (command == "add") 
    {
        myString filename;
        ss >> filename;
        add(activeSessionId, filename);
    } 
    else if (command == "session")
    {
        sessionInfo(activeSessionId);
    } 
    else if (command == "switch") 
    {
        int sessionId;
        ss >> sessionId;
        switchSession(sessionId);
        activeSessionId = sessionId;
    } 
    else if (command == "collage") 
    {
        myString direction, image1, image2, outImage;
        ss >> direction >> image1 >> image2 >> outImage;
        collage(direction, activeSessionId, image1, image2, outImage);
    } 
    else if (command == "exit") 
    {
        std::exit(0);
    } 
    else 
    {
        throw std::logic_error("Invalid command\n ");
    }
}

Image* CommandProcessor::getImage(const char* filename) 
{
    Image* image = nullptr;
    myString file(filename);
    imageFormat format(file);

    if (format.getExtension() == ".ppm") 
    {
        PPM_Reader reader(filename);
        image = reader.getImage();
    } 
    else if (format.getExtension() == ".pgm")
    {
        PGM_Reader reader(filename);
        image = reader.getImage();
    } 
    else if (format.getExtension() == ".pbm") {
        PBM_Reader reader(filename);
        image = reader.getImage();
    }

    if (!image)
        throw std::logic_error("Invalid extension!\n");

    return image;
}

void CommandProcessor::closeSession(int sessionId) 
{
    if (sessionHolder.sessionExists(sessionId))
        sessionHolder.removeSession(sessionId);
    else
        throw std::logic_error("No such sessionId\n");
}

void CommandProcessor::saveas(const myString& filename) const 
{
    if (sessionHolder.sessionExists(0))
    {
        Image* image = sessionHolder.getSession(0)->getImageAtIndex(0);
        sessionHolder.getSession(0)->saveImage(image, filename);
    }
    else
        throw std::logic_error("No image available!\n");
}

void CommandProcessor::help() {
    std::cout << "-Available commands-\n";
    std::cout << "  load <filename> - Loads an image into new session\n";
    std::cout << "  close <sessionId> - Closes the session with sessionID\n";
    std::cout << "  save - Saves all loaded images in the current session\n";
    std::cout << "  saveas <filename> - Saves the first loaded image\n";
    std::cout << "  grayscale <sessionId> - Converts images to grayscale\n";
    std::cout << "  monochrome <sessionId> - Converts images to monochrome\n";
    std::cout << "  negative <sessionId> - Converts images to negativee\n";
    std::cout << "  rotate <direction> <sessionId> - Rotates images \n";
    std::cout << "  undo - Undo last action\n";
    std::cout << "  add <sessionId> <filename> - Adds an image to session\n";
    std::cout << "  session <sessionId> - Information about the session\n";
    std::cout << "  switch <sessionId> - Switches to another session\n";
    std::cout << "  collage <direction> <sessionId> <firstImage> <secondImage> <outputImage> - Creates collage\n";
    std::cout << "  exit - Exit the application\n";
}

void CommandProcessor::grayscale(int sessionId) 
{
    if (sessionHolder.sessionExists(sessionId)) 
    {
        Session<sessionCapacity>* session = sessionHolder.getSession(sessionId);
        int imagesInSession = session->getNumImages();
        GrayscaleConverter grayscaleConverter;

        ImageCommand* command = new GrayscaleCommand(&grayscaleConverter);
        session->addTransformation(command);
    } 
    else
    throw std::logic_error("Session doesn't exist!\n");
}

void CommandProcessor::monochrome(int sessionId) 
{
    if (sessionHolder.sessionExists(sessionId)) 
    {
        Session<sessionCapacity>* session = sessionHolder.getSession(sessionId);
        int imagesInSession = session->getNumImages();
        MonochromeConverter monochromeConverter;

        ImageCommand* command = new MonochromeCommand(&monochromeConverter);
        session->addTransformation(command);
    } 
    else
    throw std::logic_error("Session doesn't exist!\n");
}

void CommandProcessor::negative(int sessionId) 
{
    if (sessionHolder.sessionExists(sessionId)) 
    {
        Session<sessionCapacity>* session = sessionHolder.getSession(sessionId);
        int imagesInSession = session->getNumImages();
        NegativeConverter negativeConverter;

        ImageCommand* command = new NegativeCommand(&negativeConverter);
        session->addTransformation(command);
    } 
    else
    throw std::logic_error("Session doesn't exist!\n");
}

void CommandProcessor::rotate(const myString& direction, int sessionId) {
    if (sessionHolder.sessionExists(sessionId)) 
    {
        Session<sessionCapacity>* session = sessionHolder.getSession(sessionId);
        int imagesInSession = session->getNumImages();
        Rotator rotator;

        ImageCommand* command = new RotateCommand(&rotator, direction);
        session->addTransformation(command);
    } 
    else
    throw std::logic_error("Session doesn't exist!\n");
}

void CommandProcessor::undo()
{
    sessionHolder.getSession(activeSessionId)->undoLastTransformation();
}

void CommandProcessor::add(int sessionId, const myString& filename) 
{
    if (sessionHolder.sessionExists(sessionId)) 
    {
        Image* image = getImage(filename.c_str());
        if (image) 
            sessionHolder.getSession(sessionId)->addImage(image);
        else 
        throw std::runtime_error("Can't load image from file!\n");
       
    }   
    else
    throw std::logic_error("Session doesn't exist!\n");
}

void CommandProcessor::sessionInfo(int sessionId) const 
{
    if (sessionHolder.sessionExists(sessionId))
        sessionHolder.getSession(sessionId)->sessionInfo();
    else
        throw std::logic_error("Session doesn't exist!\n");
}

void CommandProcessor::switchSession(int sessionId) 
{
    if (sessionHolder.sessionExists(sessionId))
        sessionHolder.setCurrentSession(sessionId);
    else
        throw std::logic_error("Session doesn't exist!\n");
}

void CommandProcessor::collage(const myString& dir, int sesId, const myString& firstFile, const myString& secFile, const myString& OutputFile)
{
    if (sessionHolder.sessionExists(sesId))
    {
        Image* img1 = getImage(firstFile.c_str());
        Image* img2 = getImage(secFile.c_str());

        if (img1 && img2)
        {
            Image* collage = nullptr;
            if (dir == "horizontal")
            {
                collage = Collage::horizontalCollage(img1, img2);
            }
            else if (dir == "vertical")
            {
                collage = Collage::verticalCollage(img1, img2);
            }
            else
            {
                throw std::logic_error("Invalid direction!\n");
            }

            sessionHolder.getSession(activeSessionId)->saveImage(collage, OutputFile);
        }
        else
            throw std::runtime_error("Can't create collage!\n");
    }
    else
        throw std::logic_error("Session doesn't exist!\n");
}

