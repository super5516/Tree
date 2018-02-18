#pragma once
#include "Window.h"

class Point {
private:
	float x, y;
public:
	Point(float x, float y);
	float get_x() const;
	float get_y() const;
};

class Shape {
	virtual void draw_on(Window& w) = 0;
};

class Triangle : public Shape {
private:
	Point p1, p2, p3;
	float vertices[9];
	int vao_id, vbo_id;
public:
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
	void draw_on(Window& w) override;
};