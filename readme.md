# PLOTTER

make generative art directly into SVG, using __stdio.h__ `FILE`

# trace a line with a pen

* begin a polyline `fprintf(file, "<polyline points=\"");`
* fill it with a sequence of (x,y) pairs. close the polyline

![example](https://cdn.rawgit.com/robbykraft/SVG/master/00-randomwalker/out/random_walker.svg)