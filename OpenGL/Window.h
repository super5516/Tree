#pragma once
#include <iostream>
#include <vector>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class GLFW {
private:
	GLFW() = default;
	~GLFW();
public:
	GLFW(GLFW const&) = delete;
	GLFW& operator=(GLFW const&) = delete;
	static GLFW& get();
	void terminate();
	void init();
};

class GLAD {
private:
	GLAD() = default;
public:
	GLAD(GLAD const&) = delete;
	GLAD& operator=(GLAD const&) = delete;
	static GLAD& get();
	void init();
};

class VertexShader {
private:
	int vertex_shader, success;
	char log[512];
public:
	VertexShader();
	int get_vertex_shader() const;
	void delete_vertex_shader() const;
};

class FragmentShader {
private:
	int fragment_shader, success;
	char log[512];
public:
	FragmentShader();
	int get_fragment_shader() const;
	void delete_fragment_shader() const;
};

class Window {
private:
	int width, height;
	string name;
	GLFWwindow* window;
	class VertexArrayObject {
	private:
		vector<unsigned int> vertex_array_objects;
	public:
		int create_vertex_array_object();
		unsigned int& get_vertex_array_object_at(const int pos);
		vector<unsigned int> get() const;
	};
	class VertexBufferObject {
	private:
		vector<unsigned int> vertex_buffer_objects;
	public:
		int create_vertex_buffer_object();
		unsigned int& get_vertex_buffer_object_at(const int pos);
		vector<unsigned int> get() const;
	};
	class Shader {
	private:
		int shader_program, success;
		char log[512];
	public:
		void link(VertexShader& vs, FragmentShader& fs);
		int get() const;
	};
public:
	VertexArrayObject vaos;
	VertexBufferObject vbos;
	Shader shader;
	Window(int width, int height, const string& name);
	int get_width() const;
	int get_height() const;
	string get_name() const;
	GLFWwindow* get_window() const;
};



