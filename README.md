# simple-particle-game

> The main aim of this project is to implement simple physics for collisions between circular 2D objects when calculating their position on the window accounting  for time and succession of collisions.

## inner workings

1. There is two threads. The first working on user input and drawing and the second updating the position of the objects every n seconds.
2. To capture user input and to draw the objects on the screen [sfml](https://www.sfml-dev.org/) library is used.
3. To store the arguments of a circle an obj of class circle is used. It stores position and angle among other things.
4. Updating the position is done by starting from second 0 and adding the time needed for the nearest collision to happen while the total time is not equal to n.
5. For every collision new travel angles are calculated for both circles but their speed remains constant.

## how to use

All obvious settings are defined as macros:

```
// dimensions of window
#define scrwidth 450
#define scrheight 450

// Those settings are used to define the position of the walls. 
// if they are set to 0 and 0 then the window borders are used else they form a square inside the window.
#define boxoffsetx 30
#define boxoffsety 30

// fps of window
#define windowupdate 30

// how much time is there between each update of the positions of the circle (second)
#define calcupdate 0.5

// the speed of every circle (pixels/second)
#define circlespd 10

// Whether you want the circles colliding with eachother (circle collision detection)
#define ccd true

// Whether you want the circles collidiing the walls (wall collision detection)
#define wcd true
```

Compilation is as follows:

```
g++ -c main.c++

g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

./main
```

## more on CCD

Firstly for a collision to happen the distance between two circles needs to be the total of boths radiuses.

If the position of one circle is named "A" and the other one "B" then we need to find when "AB" is equal to the total.

We can find "AB" for any point in time by viewing it as the hypotenuse of a triangle where "AC" is the difference between the y axis
of the circles and "BC" is the difference between the x axis of the circles.

So to find "AC" for any point in time we use the Pythagorean theorem 

-> pow(AB, 2) = pow(BC, 2) + pow(AC, 2)

or -> pow(AB, 2) = pow(circle1.x - circle2.x, 2) + pow(circle1.y - circle2.y, 2)


In our case we have to calculate the position of each circle in the next n seconds because we need to find how long "AB" will be in the next n seconds.

Both circles will contribute to the change in both x and y because they both move through space during that time.

-> pow(AB,2) = pow((circle1.x+cos(circle1.angle).time) - (circle2.x+cos(circle2.angle).time), 2) + pow(change_in(BC), 2)


-> pow(AB,2) = pow((circle1.x+cos(circle1.angle).time) - (circle2.x+cos(circle2.angle).time), 2) + 

pow((circle1.y-sin(circle1.angle).time) - (circle2.y-sin(circle2.angle).time), 2)

Now we have time in seconds written to the formula and because this is how aquations work we can find the exact time a collision will happen given we know all other values which we actually do.

Now we need to solve for time using basic arithmetics which is though lengthy. The formula which is obtained can be found by adding variables a, b and c from main.c++. The cause of seperation is that the formula is [quadratic](https://en.wikipedia.org/wiki/Quadratic_formula).

## problems

The drawing core is dying. (at least on my pc)

Circle to circle collision is unreliable when having multiple collisions at one. (some are skipped)