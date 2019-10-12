/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classes.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:28:03 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/12 13:07:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSES_H
# define CLASSES_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <cstring>
#include "../include/ilu.h"
#include "../shader_source/shaders.h"
#include "../VertexData/vertex.h"
#include "../include/glfw3.h"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtc/type_ptr.hpp"
#include "../libs/glm/glm/glm.hpp"

#define GL_VBO			0
#define GL_VAO			1
#define GL_EBO			2

#define GL_UNBIND_VAO	3

class	Buffer
{
	private:
		GLuint m_ID;

	public:
		Buffer(void) : m_ID(0) { }

		void	init(int type)
		{
			if (type == GL_VBO || type == GL_EBO)
				glGenBuffers(1, &m_ID);
			else if (type == GL_VAO)
				glGenVertexArrays(1, &m_ID);
		}

		void	bind(GLenum target, int type)
		{
			if (type == GL_VBO || type == GL_EBO)
				glBindBuffer(target, m_ID);
			else if (type == GL_VAO)
				glBindVertexArray(m_ID);
		}

		void	unbind(GLenum target, int type)
		{
			if (type == GL_VBO || type == GL_EBO)
				glBindBuffer(target, 0);
			else if (type == GL_VAO)
				glBindVertexArray(0);
		}

		void	copyData(GLenum target, GLsizeiptr size, GLvoid *data = NULL, GLenum usage = GL_STATIC_DRAW)
		{
			if (!data)
			{
				std::cout << "Error copying data in VBO or argument wasn't provided\n";
				exit(-1);
			}
			glBufferData(target, size, data, usage);
		}

		void	layoutData(GLuint layout, GLint size, int stride, const void *pointer, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE)
		{
			glVertexAttribPointer(layout, size, type, normalized, stride * sizeof(type), pointer);
			glEnableVertexAttribArray(layout);
		}
};

class	Window
{
	public:
		GLFWwindow	*m_ID;
		int			m_width;
		int			m_height;

		Window() :m_width(3840), m_height(2160), m_ID(NULL) { }

		void	change_resolution(int width = 3840, int height = 2160)
		{
			m_width = width;
			m_height = height;
		}

		void	init(void)
		{
			glfwInit();
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}

		void	createWindow(void)
		{
			if (!(m_ID = glfwCreateWindow(m_width, m_height, "LearnOpenGL", NULL, NULL)))
			{
				std::cout << "Failed to create GLFW window\n";
				glfwTerminate();
				exit(-1);
			}
			glfwMakeContextCurrent(m_ID);
		}

		void	lockMouse(void)
		{
			glfwSetInputMode(m_ID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		void	engageKeys(GLFWkeyfun cbfun)
		{
			glfwSetKeyCallback(m_ID, cbfun);
		}

		void	engageMouse(GLFWcursorposfun cbfun)
		{
			glfwSetCursorPosCallback(m_ID, cbfun);
		}

		void	engageScroll(GLFWscrollfun cbfun)
		{
			glfwSetScrollCallback(m_ID, cbfun);
		}
};

class	Shader
{
	private:
		GLint		m_status;
		std::string	m_name;
		GLchar		m_infoLog[512];

	public:
		GLuint		m_ID;

		Shader() : m_ID(0), m_name("None"), m_status(1) { }

		void	init(GLenum type, GLsizei count, const GLchar **source, const GLint *length = NULL)
		{
			if (type == GL_VERTEX_SHADER)
				m_name = "Vertex";
			else if (type == GL_FRAGMENT_SHADER)
				m_name = "Fragment";
			m_ID = glCreateShader(type);
			glShaderSource(m_ID, count, source, length);
		}

		void	compile(void)
		{
			glCompileShader(m_ID);
			glGetShaderiv(m_ID, GL_COMPILE_STATUS, &m_status);
			if (!m_status)
			{
				glGetShaderInfoLog(m_ID, 512, NULL, m_infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED - " << m_name << " shader" << std::endl;
				std::cout << m_infoLog << std::endl;
				exit(-1);
			}
		}

		void	changeName(std::string new_name = "None")
		{
			m_name = new_name;
		}

		void	del(void)
		{
			glDeleteShader(m_ID);
		}
};

class	Program
{
	private:
		GLint		m_status;
		std::string	m_name;

	public:
		GLuint		m_ID;

		Program() : m_ID(0), m_status(1), m_name("None") { }

		void	init(void)
		{
			m_ID = glCreateProgram();
		}

		void	attachShader(GLuint shader)
		{
			glAttachShader(m_ID, shader);
		}

		void	link(void)
		{
			glLinkProgram(m_ID);
			glGetProgramiv(m_ID, GL_LINK_STATUS, &m_status);
			if (!m_status)
			{
				std::cout << "Linking program error - " << m_name << " program\n";
				exit(-1);
			}
		}
};

typedef struct	vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vec4;

typedef	struct	mat4
{
	t_vec4	x;
	t_vec4	y;
	t_vec4	z;
	t_vec4	w;
}				t_mat4;

#endif