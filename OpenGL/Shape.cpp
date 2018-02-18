#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shape.h"

Point::Point(float x, float y): x(x),
                                y(y) {
}

float Point::get_x() const {
	return x;
}

float Point::get_y() const {
	return y;
}

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) : p1{x1, y1},
																			  p2{x2, y2},
																			  p3{x3, y3} {
}

void Triangle::draw_on(Window& w) {
	vertices[0] = p1.get_x() / w.get_width();
	vertices[1] = p1.get_y() / w.get_height();
	vertices[2] = 0.0f;
	vertices[3] = p2.get_x() / w.get_width();
	vertices[4] = p2.get_y() / w.get_height();
	vertices[5] = 0.0f;
	vertices[6] = p3.get_x() / w.get_width();
	vertices[7] = p3.get_y() / w.get_height();
	vertices[8] = 0.0f;

	vao_id = w.vaos.create_vertex_array_object();
	vbo_id = w.vbos.create_vertex_buffer_object();

	unsigned int& VAO = w.vaos.get_vertex_array_object_at(vao_id);
	unsigned int& VBO = w.vbos.get_vertex_buffer_object_at(vbo_id);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}
