#pragma once
#include "ImageCommand.h"
#include "Rotator.h"
#include "myString.h"
class RotateCommand : public ImageCommand {
public:
    RotateCommand(Rotator* rotator, Direction dir);
    RotateCommand(Rotator* rotator, const myString& dir);

    void execute(Image* image) override;
    void undo() override;

private:
    Rotator* rotator;
    Direction direction;
    Direction previousDirection;
    Image* modifiedImage = nullptr;
};