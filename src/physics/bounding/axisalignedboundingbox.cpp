#include "axisalignedboundingbox.hpp"
void AxisAlignedBoundingBox::updatePosition(FloatCoord<3> externalBodyPos)
{
    position = attachmentPoint + externalBodyPos;
}
bool AxisAlignedBoundingBox::operator==(const AxisAlignedBoundingBox &other)
{
    return axes == other.axes && attachmentPoint == other.attachmentPoint;
}
FloatCoord<3> AxisAlignedBoundingBox::getPosition() const
{
    return position;
}
void AxisAlignedBoundingBox::rotate(AngularVTensor<3, 3> dW)
{

}
