#ifndef COLLISION_BODY_HEADER
#define COLLISION_BODY_HEADER

#include <libgeodecomp.h>
#include <list>
#include "collision.hpp"
#include "cell.hpp"
using namespace LibGeoDecomp;

/**
 * 3x3 matrix  
 */
class Tensor
{
};



template<class Shape>
class CollisionBody
{
  public:
    typedef Shape myShape;
<<<<<<< HEAD
    
    virtual void update(const NPScell& hood, const int nanostep);

=======
    template <typename HOOD>
    void update(const HOOD &hood, const int nanoStep);
    // template <typename ITERATOR>
    // virtual void searchCollisions(const ITERATOR &begin, const ITERATOR &end);
>>>>>>> 962afab767278ee5aa8d5c387e637c85f1b44a85
    virtual void detectCollision(CollisionBody &cBody) = delete;
    virtual void resolveCollision(Collision& collision) = delete;
    virtual bool wasConsidered() = delete;
    virtual FloatCoord<3> getPosition() = delete;
    virtual FloatCoord<3> getVelocity() = delete;
    virtual FloatCoord<3> getAcceleration() = delete;
    virtual double getMass() = delete;
    virtual Tensor getOrientation() = delete;
    virtual Tensor getAngVelocity() = delete;
};

<<<<<<< HEAD
#endif // !COLLISION_BODY_HEADER
=======
template<class Shape>
class ComposedSpheresCB : public CollisionBody<Shape>
{
  private:
    std::list<Shape> spheres;
};
>>>>>>> 962afab767278ee5aa8d5c387e637c85f1b44a85
