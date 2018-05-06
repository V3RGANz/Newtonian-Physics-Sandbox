## Newtonian Physics Sandbox GSoC'18 Page

There will be project description and blog

### Abstract
Developing a tool for modeling Newtonian physics processes based
on the LibGeoDecomp library and using HPX for parallel execution.
Tool should be easy for use, it should enable end users the 
creation of simulations with a minimal amount of code. (user can
model scene in Blender, export it in text format and pass as 
argument to the command). The user uses domain terms, rather than 
writing a large number of irrelevant code.

### Result Demo
 _there will be result_

### Progress blog

#### Upcoming deadline: May 20:
```
Basic design of the sandbox. 
Bodies classes, initializers, writer. 
Just interfaces with logical base with minimal 
implementation.
``` 
##### Logic development

**Interfaces** : Shape, CollisionBody, BoundingObject, BoundingObjectTree
```c++
Shape  // at this stage it may seem that there is no point in this
       // but it is for more complex bodies which shapes != bounding Objects
       // philosophical reasoning : maybe we should make boundingObjectTree 		
       // contain bounding of any shape and then this class really will lose
       // relevance.

BoundingObject // unit of collisions detection (with other bounding objects)

BoundingObjectTree // template class with BoundingObject parameter
		   // made for searching collisions (going down the tree narrowing the margin of error)       

CollisionBody  // Contains BoundingObjectTree and Shape, as well as all physical quantities (e.g. velocity, pos and
	       // other mentioned in proposal)
```
**Implementations** : Shpere, BoundingSphere, ComposedSphereCB
```c++
Shpere           : public Shape
BoundingSphere   : public BoundingObject 
ComposedSphereCB : public CollisionBody
```
