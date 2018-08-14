#include "boundingSphere.hpp"

BoundingSphere::BoundingSphere(double radius, const FloatCoord<3> &attachmentPoint)
    : radius(radius), attachmentPoint(attachmentPoint)
{
}
void BoundingSphere::updatePosition(FloatCoord<3> externalBodyPos)
{
    position = attachmentPoint + externalBodyPos;
}
FloatCoord<3> BoundingSphere::getPosition(void) const
{
    return position;
}
double BoundingSphere::getRadius() const
{
    return radius;
}
void BoundingSphere::rotate(AngularVTensor<3, 3> dW)
{
    attachmentPoint = dW * attachmentPoint;
}
