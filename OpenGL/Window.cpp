#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

const char *vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

GLFW::~GLFW() {
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

GLFW& GLFW::get() {
	static GLFW glfw;
	return glfw;
}

void GLFW::terminate() {
	GLFW::~GLFW();
}

void GLFW::init() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLAD& GLAD::get() {
	static GLAD glad;
	return glad;
}

void GLAD::init() {
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
	}
}

Window::Window(int width, int height, const string& name): width(width),
                                                           height(height),
                                                           name(name) {
	// glfw window creation
	// --------------------
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

int Window::get_width() const {
	return width;
}

int Window::get_height() const {
	return height;
}

string Window::get_name() const {
	return name;
}

GLFWwindow* Window::get_window() const {
	return window;
}

int Window::VertexArrayObject::create_vertex_array_object() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	vertex_array_objects.push_back(VAO);
	return vertex_array_objects.size() - 1;
}

unsigned& Window::VertexArrayObject::get_vertex_array_object_at(const int pos) {
	return vertex_array_objects[pos];
}

vector<unsigned> Window::VertexArrayObject::get() const {
	return vertex_array_objects;
}

int Window::VertexBufferObject::create_vertex_buffer_object() {
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	vertex_buffer_objects.push_back(VBO);
	return vertex_buffer_objects.size() - 1;
}

unsigned& Window::VertexBufferObject::get_vertex_buffer_object_at(const int pos) {
	return vertex_buffer_objects[pos];
}

vector<unsigned> Window::VertexBufferObject::get() const {
	return vertex_buffer_objects;
}

void Window::Shader::link(VertexShader& vs, FragmentShader& fs) {
	// link shaders
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vs.get_vertex_shader());
	glAttachShader(shader_program, fs.get_fragment_shader());
	glLinkProgram(shader_program);
	// check for linking errors
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, log);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << endl;
	}
	vs.delete_vertex_shader();
	fs.delete_fragment_shader();
}

int Window::Shader::get() const {
	return shader_program;
}

VertexShader::VertexShader() {
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	// check for shader compile errors
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, log);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << endl;
	}
}

int VertexShader::get_vertex_shader() const {
	return vertex_shader;
}

void VertexShader::delete_vertex_shader() const {
	glDeleteShader(vertex_shader);
}

FragmentShader::FragmentShader() {
	// build and compile our shader program
	// ------------------------------------
	// fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	// check for shader compile errors
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, log);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << endl;
	}
}

int FragmentShader::get_fragment_shader() const {
	return fragment_shader;
}

void FragmentShader::delete_fragment_shader() const {
	glDeleteShader(fragment_shader);
}

