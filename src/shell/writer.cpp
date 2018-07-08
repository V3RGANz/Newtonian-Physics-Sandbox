#include "physics/body/composedSpheresCB.hpp"
#include "writer.hpp"
NPSCam::NPSCam(FloatCoord<3> location, FloatCoord<3> look_at, FloatCoord<2> right)
    : location(location), look_at(look_at), right(right)
{}
const FloatCoord<3> &NPSCam::getLocation() const
{
    return location;
}
void NPSCam::setLocation(const FloatCoord<3> &location)
{
    NPSCam::location = location;
}
const FloatCoord<3> &NPSCam::getLook_at() const
{
    return look_at;
}
void NPSCam::setLook_at(const FloatCoord<3> &look_at)
{
    NPSCam::look_at = look_at;
}
const FloatCoord<2> &NPSCam::getRight() const
{
    return right;
}
void NPSCam::setRight(const FloatCoord<2> &right)
{
    NPSCam::right = right;
}

std::ostream &operator<<(std::ostream &os, const NPSCam &npsCam)
{
    os << "camera { \n"
       << "  location <" << npsCam.getLocation()[0] <<", "<< npsCam.getLocation()[1] <<", "<< npsCam.getLocation()[2] <<"> \n"
       << "  look_at  <" << npsCam.getLook_at()[0] <<", "<< npsCam.getLook_at()[1] <<", "<< npsCam.getLook_at()[2] <<"> \n"
       << "  right " << npsCam.getRight()[0] << "/" << npsCam.getRight()[1] << "*x\n"
       << "} \n";
    return os;
}
NPSWriter::NPSWriter(const std::string &prefix, const unsigned int period)
    :
    Clonable<Writer<NPSCell>, NPSWriter>(prefix, period)
{}
void NPSWriter::stepFinished(const NPSWriter::GridType &grid, unsigned step, WriterEvent event)
{
    if ((event == WRITER_STEP_FINISHED) && (step % period != 0)) {
        return;
    }

    std::stringstream filename;
    filename << prefix << "_" << std::setfill('0') << std::setw(6)
             << step << ".pov";
    std::ofstream file(filename.str().c_str());

    file << "#include \"colors.inc\"\n"
         << "background { color Black }\n"
         << "plane {\n"
         << "  <0, 1, 0>, 0 \n"
         << "  pigment { color Red }\n"
         << "} \n"
         << camera
         << "light_source { <20, 30, -30> color White}\n\n";

    CoordBox<3> box = grid.boundingBox();
    for (CoordBox<3>::Iterator j = box.begin(); j != box.end(); ++j) {
        const NPSCell &container = grid.get(*j);

        for (std::size_t i = 0; i < container.size(); ++i) {
            file << container[i];
        }
    }
}
NPSCam &NPSWriter::getCamera()
{
    return camera;
}
