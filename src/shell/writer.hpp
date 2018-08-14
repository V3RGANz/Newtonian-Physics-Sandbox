#ifndef NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP

#include <libgeodecomp.h>
using namespace LibGeoDecomp;

//#include "cell.hpp"
#include "physics/body/collisionBody.hpp"

/**
 * This interface allows to modify camera position and rotation of system visualisation
 */
class NPSCam
{
public:
    explicit NPSCam(
        FloatCoord<3> location = FloatCoord<3>(-10, 25, -30),
        FloatCoord<3> look_at = FloatCoord<3>(5, 10, 20),
        FloatCoord<2> right = FloatCoord<2>(16, 9));

    /**
     * @return camera position
     */
    const FloatCoord<3> &getLocation() const;

    /**
     * set camera position
     * @param location new camera position
     */
    void setLocation(const FloatCoord<3> &location);

    /**
     * @return the point at which the camera is aimed
     */
    const FloatCoord<3> &getLook_at() const;

    /**
     * set the point at which camera is aimed
     * @param look_at
     */
    void setLook_at(const FloatCoord<3> &look_at);

    /**
     * @return aspect ratio
     */
    const FloatCoord<2> &getRight() const;

    /**
     * set aspect ratio
     * @param right
     */
    void setRight(const FloatCoord<2> &right);

private:
    FloatCoord<3> location;
    FloatCoord<3> look_at;
    FloatCoord<2> right;
};

std::ostream &operator<<(std::ostream &os, const NPSCam &npsCam);

class NPSWriter: public Clonable<Writer<NPSCell>, NPSWriter>
{
public:
    typedef APITraits::SelectTopology<NPSCell>::Value Topology;
    static const int DIM = Topology::DIM;
    typedef GridBase<NPSCell, DIM> GridType;

    explicit NPSWriter(
        const std::string &prefix,
        unsigned period = 1);

    void stepFinished(const GridType &grid, unsigned step, WriterEvent event) override;
    NPSCam &getCamera();
private:
    NPSCam camera;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP
