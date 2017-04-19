#ifndef __SAT_H__
#define __SAT_H__

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Separate Axis Theorem implemented via C99
typedef struct {float x, y;} vec;
typedef struct {vec p0, dir;} ray;
typedef struct {vec p0, p1, dir;} seg;
typedef struct {int n; vec *vertices; seg *edges;} polygon; // Assumption: Simply connected => chain vertices together

class SAT {
    public:
        polygon new_polygon(int nvertices, vec *vertices);
        vec v(float x, float y);
        vec perp(vec v);
        seg segment(vec p0, vec p1);
        polygon Polygon(int nvertices, ...);
        vec normalize(vec v);
        float dot(vec a, vec b);
        float* project(polygon a, vec axis);
        int contains(float n, float* range);
        int overlap(float* a_, float* b_);
        int sat(polygon a, polygon b);

};
#endif
