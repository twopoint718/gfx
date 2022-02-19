# GFX

This is a dumping ground of various mostly 1-bit image drawing code.
It focuses on functions used in my [pomodoro timer](https://github.com/twopoint718/pomodoro-timer) project for which this is a sort of proving-ground.

There's a little bit of architecture:

- main
    - draw
        - gfx
        - _fonts_
        - pbm

In other words, I attempted to make the drawing code abstract with respect to
what sort of canvas it's drawing onto.
From _main_, you should be able to import _draw_ and just talk about things like lines, circles, etc.
A future improvement would be to create a canvas struct to reify this context.
