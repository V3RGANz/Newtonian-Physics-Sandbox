#include "axisalignedboundingbox.hpp"
void AxisAlignedBoundingBox::updatePosition(FloatCoord<3> externalBodyPos)
{
    position = attachmentPoint + externalBodyPos;
}
bool AxisAlignedBoundingBox::operator==(const AxisAlignedBoundingBox &other)
{
    return axes == other.axes && attachmentPoint == other.attachmentPoint;
}
