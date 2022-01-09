#pragma once
#include <android/log.h>
#include <GLES3/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#undef LOG_TAG
#define LOG_TAG "SHADER"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// See: https://arm-software.github.io/opengl-es-sdk-for-android/jni_2_astc_textures_8h_source.html
#define GL_CHECK(x)																				\
	x;																							\
	{                                                                                           \
        GLenum glError = glGetError();                                                          \
        if(glError != GL_NO_ERROR)                                                              \
        {                                                                                       \
            LOGE("glGetError() = %i (%#.8x) at %s:%i\n", glError, glError, __FILE__, __LINE__); \
            exit(EXIT_FAILURE);                                                                 \
        }                                                                                       \
    }


enum ShaderType
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

class Shader
{
public:
	// ID of the program
	unsigned int shaderProgramID = -1;

	Shader() = default;

	~Shader()
	{
		glDeleteShader(shaderProgramID);
	}

	void AddShader(const char* shaderCode, ShaderType type)
	{
		int success;
		char infoLog[512];

		// Create shader Object
		unsigned int shader;
		shader = glCreateShader(type);
		if (shaderProgramID == -1)
			shaderProgramID = glCreateProgram();

		// Attach shader source to shader object
		glShaderSource(shader, 1, &shaderCode, nullptr);
		// Compile shader (at run-time)
		glCompileShader(shader);
		// Check compilation
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			LOGE("COMPILATION FAILED: %s", infoLog);
		}

		// Shader program
		glAttachShader(shaderProgramID, shader);

		// Delete Shaders after linking, not needed anymore
		glDeleteShader(shader);

	}

	void Activate() const
	{
		glUseProgram(shaderProgramID);
	}

	void linkProgram() const
	{
		int success;
		char infoLog[512];

		glLinkProgram(shaderProgramID);

		// Check compilation
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
			LOGE("LINKING ERROR: %s", infoLog);
		}
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(getUniformLocation(name), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(getUniformLocation(name), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(getUniformLocation(name), value);
	}
	void setVec3(const std::string& name, glm::vec3 value) const
	{
		glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
	}
	void setVec4(const std::string& name, glm::vec4 value) const
	{
		glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
	}
	void setMat4(const std::string& name, glm::mat4 value) const
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

private:
	GLint getUniformLocation(const std::string& name) const
	{
		GLint location = glGetUniformLocation(shaderProgramID, name.c_str());
		if (location == -1)
		{
			LOGE("Invalid uniform location: %s", name.c_str());
		}
		return location;
	}
};
