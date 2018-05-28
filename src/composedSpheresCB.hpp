#ifndef NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP

//#include <ntphyssbox.hpp>
#include "collisionBody.hpp"
//#include "shape.hpp"

class ComposedSpheresCB: public CollisionBody
{
public:
    ComposedSpheresCB() = default;
    void addSphere(FloatCoord<3> pos, double radius);
    std::string toPOV() const override;
    void addVelocity(const FloatCoord<3>& addDeltaV) override;
    inline void applyVelocity(void);
    inline void applyAngularVelocity(void);
    ~ComposedSpheresCB() override;

    void update(const NPScell &hood, const int nanostep) override ;

    void detectCollision(const CollisionBody &cBody) override ;

    void resolveCollision(Collision &collision) override ;

    bool wasConsidered() const override ;

    FloatCoord<3> getPosition() const override ;

    FloatCoord<3> getVelocity() const override ;

    FloatCoord<3> getAcceleration() const override ;

    BoundingObjectTree<BoundingSphere>& getBoundingObjectTree() const override ;

    double getMass() const override ;

    AxisAlignedBoundingBox getAABB() override ;

    Matrix<3, 3> getOrientation() const override ;

    AngularVTensor<3, 3> getAngVelocity() const override ;

    InertialTensor<3, 3> getInertialTensor() const override ;

private:
    typedef BoundingObjectTree<BoundingSphere> MyBoundingTree;
    void computeMass(){
        //TODO: this is hard process to consider all intersections of spheres
        //TODO: check this example https://github.com/severinstrobl/overlap
    }
    struct Sphere
    {
        Sphere(FloatCoord<3> pos, double radius)
            : pos(pos), radius(radius)
        {}

        FloatCoord<3> pos;
        double radius;
    };

    double                  mass;
    AxisAlignedBoundingBox  myAABB          = AxisAlignedBoundingBox::EmptyAABB;
    MyBoundingTree          boundingObjectTree;
    FloatCoord<3>           position        = FloatCoord<3>(0);
    FloatCoord<3>           velocity        = FloatCoord<3>(0);
    FloatCoord<3>           acceleration    = FloatCoord<3>(0);
    AngularVTensor<3, 3>    angularVelocity = AngularVTensor<3, 3>(0);
    InertialTensor<3, 3>    inertialTensor  = InertialTensor<3, 3>(0);
    Matrix<3, 3>            orientation     = Matrix<3, 3>(0);
    FloatCoord<3> deltaV;
    AngularVTensor<3, 3> deltaW;
    std::list<Sphere> spheres;
    std::map<CollisionBody,
             Collision>     consideredCollisions;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP