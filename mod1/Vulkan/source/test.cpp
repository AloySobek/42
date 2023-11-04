/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 12:35:48 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/12 12:52:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes.cpp"

glm::vec3	eyePos(0.0f, 0.0f, 5.0f);
glm::vec3	target(0.0f, 0.0f, -1.0f);

glm::vec3	lightPosition(10.0f, 10.0f, 0.0f);

float		lastX = 1920.0f;
float		lastY = 1080.0f;

GLfloat		yaw = -90.0f;
GLfloat		pitch = 0.0f;

int		keys[1024];

int		first_mouse = true;

void	keys_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, 1);
	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE)
		keys[key] = false;
}

void	keys_handler(void)
{
	float	cameraSpeed;

	cameraSpeed = 0.007f;
	if (keys[GLFW_KEY_W])
		eyePos += cameraSpeed * target;
	if (keys[GLFW_KEY_S])
		eyePos -= cameraSpeed * target;
	if (keys[GLFW_KEY_A])
		eyePos -= cameraSpeed * glm::normalize(glm::cross(target, glm::vec3(0.0f, 1.0f, 0.0f)));
	if (keys[GLFW_KEY_D])
		eyePos += cameraSpeed * glm::normalize(glm::cross(target, glm::vec3(0.0f, 1.0f, 0.0f)));
	if (keys[GLFW_KEY_KP_4])
		lightPosition.x -= 0.01f;
	if (keys[GLFW_KEY_KP_6])
		lightPosition.x += 0.01f;
	if (keys[GLFW_KEY_KP_8])
		lightPosition.z -= 0.01f;
	if (keys[GLFW_KEY_KP_2])
		lightPosition.z += 0.01f;
	if (keys[GLFW_KEY_KP_9])
		lightPosition.y += 0.01f;
	if (keys[GLFW_KEY_KP_3])
		lightPosition.y -= 0.01f;
}

void	mouse_callback(GLFWwindow *window, double x_pos, double y_pos)
{
	glm::vec3	direction;
	GLfloat		sens;

	if (first_mouse)
	{
		lastX = x_pos;
		lastY = y_pos;
		first_mouse = false;
	}
	sens = 0.1f;

	yaw		+= (x_pos - lastX) * sens;
	pitch	-= (y_pos - lastY) * sens;

	lastX	= x_pos;
	lastY	= y_pos;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	target		= glm::normalize(direction);
}

void	scroll_callback(GLFWwindow *window, double x, double y)
{
	return ;
}

glm::mat4		perspective(float angle, float aspect, float near, float far)
{
	glm::mat4	projection;
	float		tangens;

	tangens = tan(angle / 2.0f);

	projection[0][0] = 1.0f / (tangens * aspect);
	projection[0][1] = 0.0f;
	projection[0][2] = 0.0f;
	projection[0][3] = 0.0f;
	projection[1][0] = 0.0f;
	projection[1][1] = 1.0f / tangens;
	projection[1][2] = 0.0f;
	projection[1][3] = 0.0f;
	projection[2][0] = 0.0f;
	projection[2][1] = 0.0f;
	projection[2][2] = far / (near - far);
	projection[2][3] = -1.0f;
	projection[3][0] = 0.0f;
	projection[3][1] = 0.0f;
	projection[3][2] = -(near * far) / (far - near);
	projection[3][3] = 0.0f;
	return (projection);
}

glm::mat4		lookAt(glm::vec3 eyePos, glm::vec3 target, glm::vec3 vectorUp = glm::vec3(0.0f, 1.0f, 0.0f))
{
	glm::mat4	view;
	glm::vec3	X;
	glm::vec3	Y;
	glm::vec3	Z;

	Z = glm::normalize(eyePos + -target);
	X = glm::normalize(glm::cross(vectorUp, Z));
	Y = glm::cross(Z, X);

	view[0][0] = X.x;
	view[1][0] = X.y;
	view[2][0] = X.z;
	view[3][0] = (-eyePos.x * X.x) + (-eyePos.y * X.y) + (-eyePos.z * X.z);
	view[0][1] = Y.x;
	view[1][1] = Y.y;
	view[2][1] = Y.z;
	view[3][1] = (-eyePos.x * Y.x) + (-eyePos.y * Y.y) + (-eyePos.z * Y.z);
	view[0][2] = Z.x;
	view[1][2] = Z.y;
	view[2][2] = Z.z;
	view[3][2] = (-eyePos.x * Z.x) + (-eyePos.y * Z.y) + (-eyePos.z * Z.z);
	view[0][3] = 0.0f;
	view[1][3] = 0.0f;
	view[2][3] = 0.0f;
	view[3][3] = 1.0f;
	return (view);
}

int				main(int argc, char **argv)
{
	Window		window;
	Buffer		vbo;
	Buffer		vao;
	Buffer		lightVao;
	Buffer		ebo;
	Shader		vertexShader;
	Shader		lightVertexShader;
	Shader		fragmentShader;
	Shader		lightFragmentShader;
	Program		shaderProgram;
	Program		lightProgram;
	glm::mat4	model;
	glm::mat4	view;
	glm::mat4	projection;
	glm::vec3	objectColor(1.0f, 1.0f, 1.0f);
	glm::vec3	lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3	objectPosition(0.0f, 0.0f, -4.0f);
	int			width;
	int			height;


	window.init();
	window.createWindow();
	window.engageKeys(keys_callback);
	window.engageMouse(mouse_callback);
	window.engageScroll(scroll_callback);
	window.lockMouse();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK && printf("An error occured(glew init)\n)"))
		return (-1);

	glfwGetFramebufferSize(window.m_ID, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	vbo.init(GL_VBO);
	vao.init(GL_VAO);
	lightVao.init(GL_VAO);
	ebo.init(GL_EBO);

	vbo.bind(GL_ARRAY_BUFFER, GL_VBO);
	vbo.copyData(GL_ARRAY_BUFFER, sizeof(Vertex::vertices), Vertex::vertices);
	vao.bind(GL_VAO, GL_VAO);
	vbo.layoutData(0, 3, 6, (GLvoid *)0);
	vbo.layoutData(1, 3, 6, (GLvoid *)(3 * sizeof(GLfloat)));
	lightVao.bind(GL_VAO, GL_VAO);
	vbo.bind(GL_ARRAY_BUFFER, GL_VBO);
	vbo.layoutData(0, 3, 6, (GLvoid *)0);

	vertexShader.init(GL_VERTEX_SHADER, 1, &Shaders::vertexShader);
	fragmentShader.init(GL_FRAGMENT_SHADER, 1, &Shaders::fragmentShader);
	lightVertexShader.init(GL_VERTEX_SHADER, 1, &Shaders::vertexLightShader);
	lightFragmentShader.init(GL_FRAGMENT_SHADER, 1, &Shaders::fragmentLightShader);

	vertexShader.compile();
	fragmentShader.compile();
	lightVertexShader.compile();
	lightFragmentShader.compile();

	shaderProgram.init();
	shaderProgram.attachShader(vertexShader.m_ID);
	shaderProgram.attachShader(fragmentShader.m_ID);
	shaderProgram.link();
	lightProgram.init();
	lightProgram.attachShader(lightVertexShader.m_ID);
	lightProgram.attachShader(lightFragmentShader.m_ID);
	lightProgram.link();

	while (!glfwWindowShouldClose(window.m_ID))
	{
		glfwPollEvents();
		keys_handler();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		view = lookAt(eyePos, target + eyePos, glm::vec3(0.0f, 1.0f, 0.0f));
		projection = perspective(45.0f, (float)window.m_width / (float)window.m_height, 0.1f, 500.0f);
		glm::mat4	model(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		glUseProgram(shaderProgram.m_ID);
		vao.bind(GL_VAO, GL_VAO);
		glUniform3f(glGetUniformLocation(shaderProgram.m_ID, "eyePos"), eyePos.x, eyePos.y, eyePos.z);
		glUniform3f(glGetUniformLocation(shaderProgram.m_ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(glGetUniformLocation(shaderProgram.m_ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram.m_ID, "objectColor"), objectColor.x, objectColor.y, objectColor.z);
		model = glm::translate(model, objectPosition);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.m_ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.m_ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.m_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUseProgram(lightProgram.m_ID);
		lightVao.bind(GL_VAO, GL_VAO);
		glUniform2f(glGetUniformLocation(lightProgram.m_ID, "test"), 1.0f, 0.3f);
		model = glm::translate(model, lightPosition);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lightProgram.m_ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(lightProgram.m_ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightProgram.m_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		vao.unbind(GL_VAO, GL_VAO);
		glfwSwapBuffers(window.m_ID);
	}
	glfwTerminate();
	return (0);
}