# Plotter

generate polyline coordinates directly into an SVG, using `<stdio>` __FILE__

* begin polyline `fprintf(file, "<polyline points=\"");`
* fill it with a sequence of `x,y` pairs. close the polyline.

# mind the sequential order of the geometry

imagine a pen drawing the shape. a new polyline is a pen up / pen down. it takes time to move across the entire canvas

![example](https://cdn.rawgit.com/robbykraft/SVG/master/00-randomwalker/out/random_walker.svg)
![example](https://cdn.rawgit.com/robbykraft/SVG/master/02-spiral-dual/out/003-dual-phyllotaxic-2.svg)
![example](https://cdn.rawgit.com/robbykraft/SVG/master/01-spiral-archimedean/out/002-polygons.svg)