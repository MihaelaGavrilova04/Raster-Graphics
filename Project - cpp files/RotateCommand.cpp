#include "RotateCommand.h"

RotateCommand::RotateCommand(Rotator* rotator, Direction dir) : rotator(rotator), direction(dir), previousDirection(dir){ }
RotateCommand::RotateCommand(Rotator* rotator, const myString& dir): rotator(rotator)
{
    if (dir == "LEFT" || dir == "Left" || dir == "left") {
        direction = Direction::LEFT;
    }
    else {
        direction = Direction::RIGHT;
    }
    previousDirection = direction;
}

void RotateCommand::execute(Image* image)
{
    modifiedImage = image;
    rotator->rotate(image, direction);

}

void RotateCommand::undo()
{
    rotator->rotate(modifiedImage, previousDirection);
}
