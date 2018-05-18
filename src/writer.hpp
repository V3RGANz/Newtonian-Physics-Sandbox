#ifndef NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP

#include <libgeodecomp.h>
using namespace LibGeoDecomp;

#include "cell.hpp"
#include "collisionBody.hpp"


class NPS_Writer : public Clonable<Writer<NPScell>, NPS_Writer>
{
public:
  typedef APITraits::SelectTopology<NPScell>::Value Topology;
  static const int DIM = Topology::DIM;
  typedef GridBase<NPScell, DIM> GridType;

  explicit NPS_Writer(
          const std::string& prefix,
          const unsigned period = 1) :
          Clonable<Writer<NPScell>, NPS_Writer>(prefix, period)
  {}

  virtual void stepFinished(const GridType& grid, unsigned step, WriterEvent event)
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
         << "camera { \n"
         << "  location <-10, 25, -30> \n"
         << "  look_at  <5, 10,  20> \n"
         << "  right 16/9*x\n"
         << "} \n"
         << "light_source { <20, 30, -30> color White}\n\n";

    CoordBox<3> box = grid.boundingBox();
    for (CoordBox<3>::Iterator j = box.begin(); j != box.end(); ++j) {
      const NPScell& container = grid.get(*j);

      for (std::size_t i = 0; i < container.size(); ++i) {
        file << container[i];
      }
    }
  }
};



#endif //NEWTONIAN_PHYSICS_SANDBOX_WRITER_HPP
