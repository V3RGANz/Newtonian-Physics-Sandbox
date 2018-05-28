#ifndef NEWTONIAN_PHYSICS_SANDBOX_AXISALIGNEDBOUNDEDBOX_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_AXISALIGNEDBOUNDEDBOX_HPP


#include "boundingObject.hpp"
class AxisAlignedBoundingBox : public BoundingObject
{
public:
    AxisAlignedBoundingBox(const FloatCoord<3> &axes,
                           const FloatCoord<3> &position,
                           const FloatCoord<3> &attachmentPoint)
        : axes(axes), position(position), attachmentPoint(attachmentPoint)
    {}
    static const AxisAlignedBoundingBox EmptyAABB = {FloatCoord<3>(0), FloatCoord<3>(0), FloatCoord<3>(0)};

    bool operator==(const AxisAlignedBoundingBox& other){
        return axes == other.axes && attachmentPoint == other.attachmentPoint;
    }

private:

    void updatePosition(FloatCoord<3> externalBodyPos) override
    {
        position = attachmentPoint + externalBodyPos;
    }

    inline double getX(){
        return axes[0];
    }

    inline double getY(){
        return axes[1];
    }

    inline double getZ(){
        return axes[2];
    }

    inline void setX(double x){
        axes[0] = x;
    }

    inline void setY(double y){
        axes[1] = y;
    }

    inline void setZ(double z){
        axes[2] = z;
    }

    inline FloatCoord<3> getAxes(){
        return axes;
    }

    inline void setAxes(FloatCoord<3> axesNew){
        axes = axesNew;
    }

private:
    FloatCoord<3> axes;
    FloatCoord<3> position;
    // relative location in Object's reference system
    FloatCoord<3> attachmentPoint;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_AXISALIGNEDBOUNDEDBOX_HPP
