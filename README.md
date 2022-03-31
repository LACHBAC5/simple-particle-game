# simple-particle-game

This projects is about making simplistic rules to
moving 1d circular objects regarding their movenment,
collisions with walls and other objects.

The project's aim is in no way realism and more of a challenge.

The control parts of the program are typed as macros{

scrwidth, scrheight

boxoffsetx -> how much pixels after x=0 and how much pixels before x=scrwidth is the box's x located
boxoffsety -> how much pixels after y=0 and how much pixels before y=scrheight is the box's y located

windowupdate -> or fps

calcupdate -> time between updates of the position of each object

circlespd -> speed of each object

ccd (circle collicion detection) -> if you want to see colliding circles

wcd (wall collision detection) -> if you want to see colliding with walls (box)

}

How the obj to obj detection works:

**To have a collision 2 objs need to be (obj.r+obj1.r) length apart**

The distance between 2 objs is calculated using the Pythagorean theorem

1. pow(AB,2) = pow(AC,2) + pow(BC,2)

where **AB** is the distance between the objects

where **AC** is the distance between the x cords of the objects

where **BC** is the distance between the y cords of the objects

But we need to calculate AB for the next n seconds.
To do this we need to calculate how far apart our objects will be
at second n from now...

2. pow(AB,2) = pow(change_in(AC), 2) + pow(change_in(BC), 2)
3. pow(AB,2) = pow((obj0.x+cos(obj0.angle).**time**) - (obj1.x+cos(obj1.angle).**time**), 2) + pow(change_in(BC), 2)
4. pow(AB,2) = pow((obj0.x+cos(obj0.angle).**time**) - (obj1.x+cos(obj1.angle).**time**), 2) + pow((obj0.x-sin(obj0.angle).**time**) - (obj1.x-sin(obj1.angle).**time**), 2)

Here comes the real question whose answer our program needs:
After how much **TIME** 2 objs are going to collide?

We now take the formula apart and solve for **TIME**

5. The formula is written in the main.c++. (a+b+c)

The steps are not written because it is lengthy (3 pages) and solving it require basic arithmetics.

It is seperated because it is a [quadratic formula](https://en.wikipedia.org/wiki/Quadratic_formula)

CODE PROBLEMS:
The drawing of the circles kills one core (at least on my pc)

obj to obj detection is unreliable (though concept works)
