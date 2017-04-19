#include "SAT.h"

polygon SAT::new_polygon(int nvertices, vec *vertices){
	seg *edges = (seg*)malloc(sizeof(seg)*(nvertices));
	int i;
	for (i = 0; i < nvertices-1; i++){
		vec dir = {vertices[i+1].x-vertices[i].x, vertices[i+1].y-vertices[i].y};seg cur = {vertices[i], vertices[i+1], dir};
		edges[i] = cur;
	}
	vec dir = {vertices[0].x-vertices[nvertices-1].x, vertices[0].y-vertices[nvertices-1].y};seg cur = {vertices[nvertices-1], vertices[0], dir};
	edges[nvertices-1] = cur;
	polygon shape = {nvertices, vertices, edges};
	return shape;
}

vec SAT::v(float x, float y){
	vec a = {x, y};
	return a;
}

vec SAT::perp(vec v){
	vec b = {v.y, -v.x};
	return b;
}

seg SAT::segment(vec p0, vec p1){
	vec dir = {p1.x-p0.x, p1.y-p0.y};
	seg s = {p0, p1, dir};
	return s;
}

polygon SAT::Polygon(int nvertices, ...){
	va_list args;
	va_start(args, nvertices);
	vec *vertices = (vec*)malloc(sizeof(vec)*nvertices);
	int i;
	for (i = 0; i < nvertices; i++){
		vertices[i] = va_arg(args, vec);
	}
	va_end(args);
	return new_polygon(nvertices, vertices);
}

vec SAT::normalize(vec v){
	float mag = sqrt(v.x*v.x + v.y*v.y);
	vec b = {v.x/mag, v.y/mag};
	return b;
}

float SAT::dot(vec a, vec b){
	return a.x*b.x+a.y*b.y;
}

float* SAT::project(polygon a, vec axis){
	axis = normalize(axis);
	int i;
	float min = dot(a.vertices[0],axis); float max = min;
	for (i=0;i<a.n;i++){
		float proj = dot(a.vertices[i],axis);
		if (proj < min) min = proj; if (proj > max) max = proj;
	}
	float* arr = (float*)malloc(2*sizeof(float));
	arr[0] = min; arr[1] = max;
	return arr;
}

int SAT::contains(float n, float* range){
	float a = range[0], b = range[1];
	if (b<a) {a = b; b = range[0];}
	return (n >= a && n <= b);
}

int SAT::overlap(float* a_, float* b_){
	if (contains(a_[0],b_)) return 1;
	if (contains(a_[1],b_)) return 1;
	if (contains(b_[0],a_)) return 1;
	if (contains(b_[1],a_)) return 1;
	return 0;
}

int SAT::sat(polygon a, polygon b){
	int i;
	for (i=0;i<a.n;i++){
		vec axis = a.edges[i].dir;
		axis = perp(axis);
		float *a_ = project(a,axis), *b_ = project(b,axis);
		if (!overlap(a_,b_)) return 0;
	}
	for (i=0;i<b.n;i++){
		vec axis = b.edges[i].dir;
		axis = perp(axis);
		float *a_ = project(a,axis), *b_ = project(b,axis);
		if (!overlap(a_,b_)) return 0;
	}
	return 1;
}
