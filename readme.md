# Plotter

generate polyline coordinates directly into an SVG, using __stdio.h__ `FILE`

# draw the line like a pen would

* begin polyline `fprintf(file, "<polyline points=\"");`
* fill it with a sequence of (x,y) pairs. close the polyline.

![example](https://cdn.rawgit.com/robbykraft/SVG/master/00-randomwalker/out/random_walker.svg)