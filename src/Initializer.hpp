#ifndef NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP

#include "cell.hpp"

//TODO should import from Blender

/**
 * Starting point for every simulation.
 * Initializer take objects and their initial
 * condition from user data
 */

class NPSInitializer : public SimpleInitializer<NPScell>
{
public:

    NPSInitializer(const Coord<3>& dimensions, unsigned steps) :
        SimpleInitializer<NPScell>(dimensions, steps)
    {}


    virtual void grid(GridBase<NPScell, 3>* target)
    {

    }
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP
