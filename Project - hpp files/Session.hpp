#pragma once

#include "Image.h"
#include "ImageCommand.h"
#include "myVector.hpp"
#include "myStack.hpp"
#include <iostream>
#include "myString.h"
#include <sstream>
#include "PGM_Writer.h"
#include "PBM_Writer.h"
#include "PPM_Writer.h"
#include "ImageWriter.h"

template <const int S>
class Session
{
public:
    explicit Session(int id);

    void addImage(Image* image);
    void addTransformation(ImageCommand* command); 
    void undoLastTransformation();
    void applyTransformations();

    void sessionInfo() const;
    int getSessionId() const;
    int getNumImages() const;

    void saveImage(Image* image, const myString& filename); 
    void saveSession();

    Image* getImageAtIndex(int index) const; 

    myString generateFilename(int index, PictureType type) const;
private:
    int sessionId;
    myVector<Image*> images; 
    myVector<ImageCommand*> transformations;
    myStack<ImageCommand*, S> undoStack;

    bool newImageAdded = false;
};

template <const int S>
Session<S>::Session(int id) : sessionId(id) {}

template <const int S>
void Session<S>::addImage(Image* image) {
    Image* newImage = new Image(*image); 
    images.pushBack(newImage);
    newImageAdded = true;
}

// add transformation
template <const int S>
void Session<S>::addTransformation(ImageCommand* command) {
    if (!newImageAdded) {
        for (int i = 0; i < images.getSize(); i++) {
            command->execute(images[i]);
        }
    }
    else {
        for (int i = 0; i < images.getSize() - 1; i++) {
            command->execute(images[i]);
        }
        newImageAdded = false;
    }

    transformations.pushBack(command);
    undoStack.push(command);
}

// undo last action
template <const int S>
void Session<S>::undoLastTransformation() {
    if (!undoStack.isEmpty()) {
        ImageCommand* lastCommand = undoStack.peek();
        lastCommand->undo();
        undoStack.pop();
    }
    else {
        std::cout << "Nothing to undo." << std::endl;
    }
}

// print session
template <const int S>
void Session<S>::sessionInfo() const {
    std::cout << "\n -INFORMATION- \n";
    std::cout << "Session ID: " << sessionId << std::endl;
    std::cout << "Number of transformations: " << transformations.getSize() << std::endl;
    std::cout << "Number of images: " << images.getSize() << std::endl;
    for (int i = 0; i < images.getSize(); i++) {
        std::cout << "Type of picture #" << i + 1 << " : ";
        std::cout << images[i]->getTypeString(images[i]->getType()) << std::endl;
    }
}

template <const int S>
int Session<S>::getSessionId() const {
    return sessionId;
}

template <const int S>
int Session<S>::getNumImages() const {
    return images.getSize();
}

template <const int S>
Image* Session<S>::getImageAtIndex(int index) const {
    if (index >= images.getSize()) {
        throw std::logic_error("Invalid index!\n");
    }
    return images[index];
}

// save session
template <const int S>
void Session<S>::saveSession() {
    for (int i = 0; i < images.getSize(); i++) {
        saveImage(images[i], generateFilename(i, images[i]->getType()));
    }
}

template <const int S>
myString Session<S>::generateFilename(int index, PictureType type) const {
    std::stringstream ss;
    ss << "session_" << sessionId << "_image_" << index;
    switch (type) {
    case PictureType::PPM:
        ss << ".ppm";
        break;
    case PictureType::PGM:
        ss << ".pgm";
        break;
    case PictureType::PBM:
        ss << ".pbm";
        break;
    default:
        ss << ".ppm";
        break;
    }

    return myString(ss.str().c_str());
}

template <const int S>
void Session<S>::saveImage(Image* image, const myString& filename) {
    ImageWriter* writer = nullptr;
    switch (image->getType()) {
    case PictureType::PPM:
        writer = new PPM_Writer(filename.c_str(), image);
        writer->saveImage();
        break;
    case PictureType::PGM:
        writer = new PGM_Writer(filename.c_str(), image);
        writer->saveImage();
        break;
    case PictureType::PBM:
        writer = new PBM_Writer(filename.c_str(), image);
        writer->saveImage();
        break;
    default:
        std::cout << "Unknown image type!" << std::endl;
        return;
    }
    delete writer;
}

// apply transformations to all images
template <const int S>
void Session<S>::applyTransformations() {
    for (int i = 0; i < transformations.getSize(); i++) {
        for (int j = 0; j < images.getSize(); j++) {
            transformations[i]->execute(images[j]);
        }
    }
}
