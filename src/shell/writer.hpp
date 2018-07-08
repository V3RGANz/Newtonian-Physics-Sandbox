#ifndef NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP

#include <libgeodecomp.h>
using namespace LibGeoDecomp;

//#include "cell.hpp"
#include "physics/body/collisionBody.hpp"


class NPSCam
{
public:
    explicit NPSCam(
        FloatCoord<3> location = FloatCoord<3>(-10, 25, -30),
        FloatCoord<3> look_at = FloatCoord<3>(5, 10, 20),
        FloatCoord<2> right = FloatCoord<2>(16, 9));

    const FloatCoord<3> &getLocation() const;
    void setLocation(const FloatCoord<3> &location);
    const FloatCoord<3> &getLook_at() const;
    void setLook_at(const FloatCoord<3> &look_at);
    const FloatCoord<2> &getRight() const;
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
