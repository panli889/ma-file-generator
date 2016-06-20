MA File Generator
=====================

# Background

>Q-MAT([homepage](http://cgcad.thss.tsinghua.edu.cn/wangbin/qmat/qmat.html), [acm dl](http://dl.acm.org/citation.cfm?id=2753755)), uses quadratic error minimization to compute a structurally simple, geometrically accurate, and compact representation of the MAT.



# Introduction

> This repo introduces two ways to generate the initial medial axis transform file of Q-MAT.

As described in the paper of Q-MAT, there are two kinds of the initial medial axis transform files in it:

- the initial medial axis files of [scale axis transform](http://www.balintmiklos.com/scale-axis/algorithm_siggraph_2010.html)

- the adjustment of output of [Surface reconstruction by Voronoi filtering](http://dl.acm.org/citation.cfm?id=276889)

## Scale axis transform

1. Download the execuable program of [scale axis transform](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/mesecina/3d-scale-axis-r2.zip). As described in Readme file, it's input is off file, if not, may use Meshlab transform the format to off file. 

1. Take the dolphin.off file as input, run `scale-axis.bat dolphin 0.01 1.1`, and get two output files `scale-1.1-dolphin-0.01.off` and `scale-1.1-dolphin-0.01.moff` in result folder `dolphin-0.01`

1. Run `sat_to_mat.exe scale-1.1-dolphin-0.01.off scale-1.1-dolphin-0.01.moff scale-1.1-dolphin-0.01.ma`, get the result ma file `scale-1.1-dolphin-0.01.ma`

Codes used to generate sat_to_mat.exe includes:

- LineInputStream.h is a file used to read and parse the needed .off and .moff files;

- vec.h is used to store the information of vertexes in the .off and .moff files;

- sat_to_mat.cpp is used to read the .off and .moff files to generated the .ma file the experiment needed.


## Surface reconstruction by Voronoi filtering(TO Complete)

While the method described in Surface reconstruction by Voronoi filtering provides a way of filtering the Voronoi diagram using the “poles” of the Voronoi cells to improve the stability of the MAT, we take the original Voronoi cells without using any filtering, since we wish to test how Q-MAT can handle highly complex initial MAT with many spikes. 

The Voronoi diagram is computed by first getting the Delaunay triangulation of the sample points using the CGAL package “Delaunay Triangulation 3” and then taking its dual. In this way, we get the initial medial mesh with the medial spheres connected to its neighbors.



