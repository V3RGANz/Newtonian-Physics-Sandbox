#include <libgeodecomp.h>
#include <list>
#include "collision.hpp"

class Tensor
{
};

template<class Shape>
class CollisionBody
{
  public:
    typedef Shape myShape;
    template <typename HOOD>
    void update(const HOOD &hood, const int nanoStep) = delete;
    // template <typename ITERATOR>
    // virtual void searchCollisions(const ITERATOR &begin, const ITERATOR &end);
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

template<class Shape>
class ComposedSpheresCB : public CollisionBody<Shape>
{
  private:
    std::list<Shape> spheres;
};