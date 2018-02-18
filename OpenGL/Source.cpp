#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Shape.h"


void process_input(GLFWwindow *window);


int main() {
	
	GLFW::get().init();
	
	const string name = "Sample Window";
	Window w(1000, 600, name);
	
	GLAD::get().init();

	VertexShader simple_vs;
	FragmentShader simple_fs;
	w.shader.link(simple_vs, simple_fs);

	Triangle t1(0, 0, 200, 0, 100, 200);
	Triangle t2(-300, 0, -100, 0, -200, 200);
	t1.draw_on(w);
	t2.draw_on(w);

	GLFWwindow* window = w.get_window();
	
	/* hide render loop into a member function of Window */

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		process_input(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(w.shader.get());
		for (auto vao : w.vaos.get()) {
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	GLFW::get().terminate();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


