Loading your .obj HowTo
1) Just basic .obj format is supported for loading (you can look for examples in Draw/Models). In Blender options are: Apply Modifiers, Objects as OBJ Objects, Scale - 1.0 (generating later with 'make config'/'make auto-config', I think, is better), Path Mode - Auto, Forward - -Z Forward, Up - Y Up
2) Make sure, that you have right parts in the right order:
    2.a) For car you should have (in this order): case of the car, wheels, windows. Totally there are 3 parts.
    2.b) For tree you should have (in this order): tree trunk, leaves. Totally there are 2 parts.
3) If you have less parts, that required, image should still be correct (I hope:)). If you have more parts, not all of them will be displayed. If the order is different, there will be some errors with colors. If you want to change anything in .obj drawing, look in 'Draw/compile.cpp'.
4) Run 'make auto-config'.
4.b) If you don't like models' scaling, you can run 'make config' and change scaling manually (or change it rewriting .scaleinfo files but it's not the best idea).
5) Enjoy.
