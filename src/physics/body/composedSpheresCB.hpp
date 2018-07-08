#ifndef NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP

//#include <ntphyssbox.hpp>
#include <utility>
#include "collisionBody.hpp"
#include <cmath>
//#include "shape.hpp"


//!!! FIXME
#define DELTA_T 0.1

class ComposedSpheresCB: public CollisionBody
{
public:
    struct Sphere
    {
        Sphere(FloatCoord<3> pos, double radius)
            : pos(pos), radius(radius)
        {
        }

        FloatCoord<3> pos;
        double radius;
    };

    explicit ComposedSpheresCB(double density = 1);

    explicit ComposedSpheresCB(const std::list<Sphere>& spheres, double density = 1);

//    ComposedSpheresCB(const ComposedSpheresCB& other);

    void addSphere(FloatCoord<3> pos, double radius);
    std::string toPOV() const override;
    void addVelocity(const FloatCoord<3>& addDeltaV) override;
    inline void applyVelocity(void)
    {
        velocity += deltaV;
        deltaV = FloatCoord<3>(0);
    }
    inline void applyAngularVelocity(void)
    {
        angularVelocity += deltaW;
        deltaW = AngularVTensor<3, 3>(0);
    }

    ~ComposedSpheresCB() override
    {
        spheres.clear();
    }

    void addAngularVelocity(const AngularVTensor<3, 3> &tensor) override;

//    void update(const NPSCell &hood, const int nanostep) override ;

    //FIXME Collision not allows copying so currentCollisions commented
    template<typename HOOD>
    void update(const HOOD &hood, const int nanostep)
    {
        //FIXME: redundant update of boundingObjectTree
        //It'd be good to update-on-use, but we have constant copy
        //It's not a big problem to optimize, but left for later work
        boundingObjectTree.updateBoundingsPositions(position);

        for (auto& collisionBody : hood){
            detectCollision(collisionBody);
        }
//    for (auto& collision : currentCollisions){
//        CollisionResolve collisionResolve(collision);
//    }
        position += velocity * DELTA_T;

        applyVelocity();
        applyAngularVelocity();
    }

    void rotate(FloatCoord<3> rotationVector) override;

    void detectCollision(const CollisionBody &cBody) override ;

    void resolveCollision(Collision &collision) override ;

    bool wasConsidered() const override ;

    FloatCoord<3> getPos() const override ;

    FloatCoord<3> getVelocity() const override ;

    FloatCoord<3> getAcceleration() const override ;

    const BoundingObjectTree<BoundingSphere>& getBoundingObjectTree() const override ;

    double getMass() const override ;

    AxisAlignedBoundingBox getAABB() const override ;

    Matrix<3, 3> getOrientation() const override ;

    AngularVTensor<3, 3> getAngVelocity() const override ;

    InertiaTensor<3, 3> getInertialTensor() const override ;

    void getCollison(CollisionBody& me) const override;

    CollisionBody* copy() const override;

//    ComposedSpheresCB& operator=(const ComposedSpheresCB& other);
//    ComposedSpheresCB& operator=(ComposedSpheresCB&& other) noexcept;

    friend std::ostream &operator<<(std::ostream &, const CollisionBody &);
private:
    typedef BoundingObjectTree<BoundingSphere> MyBoundingTree;
    void computeMass(double density){
        //TODO: this is hard process to consider all intersections of spheres
        //TODO: check this example https://github.com/severinstrobl/overlap
        //FIXME: actually works only with spheres
        double radius = spheres.back().radius;
        mass = 4 * density * M_PI * radius * radius * radius / 3;
    }
public:
    void setPosition(FloatCoord<3> position) override;
private:

    double                  mass;
    AxisAlignedBoundingBox  EmptyAABB       = AxisAlignedBoundingBox(FloatCoord<3>(0), FloatCoord<3>(0), FloatCoord<3>(0));
    //FIXME : ADD EMPTY AABB
    AxisAlignedBoundingBox  myAABB          = EmptyAABB;
    MyBoundingTree          boundingObjectTree;
    FloatCoord<3>           position        = FloatCoord<3>(0);
    FloatCoord<3>           velocity        = FloatCoord<3>(0);
    FloatCoord<3>           acceleration    = FloatCoord<3>(0);
    AngularVTensor<3, 3>    angularVelocity = AngularVTensor<3, 3>(0);
    InertiaTensor<3, 3>     inertialTensor;
    //FIXME: fits to sphere case only
    Matrix<3, 3>            orientation     = Matrix<3, 3>(FloatCoord<3>(1));
    FloatCoord<3>           deltaV;
    AngularVTensor<3, 3>    deltaW;
public:
    void setVelocity(FloatCoord<3> velocityVector) override;
private:
    std::list<Sphere>       spheres;
//    std::list<Collision>    currentCollisions;
//    std::map<CollisionBody*,
//             Collision>     consideredCollisions;
};

class NPSCell : public BoxCell<std::vector<ComposedSpheresCB> >
{
public:
    typedef MyAPI API;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP