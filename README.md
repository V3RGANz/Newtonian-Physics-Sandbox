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


<script type="text/javascript">
function showSpoiler(obj)
    {
    var inner = obj.parentNode.getElementsByTagName("div")[0];
    if (inner.style.display == "none")
        inner.style.display = "";
    else
        inner.style.display = "none";
    }
    </script>
<div class="spoiler">
    <input type="button" onclick="showSpoiler(this);" value="Logic development" />
    <div class="inner" style="display:none;">
    <code>
Interfaces : Shape, CollisionBody, BoundingObject
Shape 	// at this stage it may seem that there is no point in this
       // but it is for more complex bodies which shapes != bounding Objects
       // philosophical reasoning : maybe we should make boundingObjectTree 		
       // contain bounding of any shape and then this class really will lose
       // relevance.

template<class _BoundingObject>
BoundingObjectTree
    Contains:
        class Node { _BoundingObject current; list<_BoundingObject> childs }; // the tree itself
        Node // head of tree
    usability:
        searching collisions (going down the tree narrowing the margin of error)

CollisionBody
    Contains:
	       BoundingObjectTree<BoundingObject>
	       Shape

BoundingObject
    usability:
	       gives collisions with other bounding objects, if any

Implementations: Shpere, BoundingSphere, ComposedSphereCB

Shpere : public Shape
BoundingSphere : public BoundingObject 
ComposedSphereCB : public CollisionBody
        </code>
    </div>
