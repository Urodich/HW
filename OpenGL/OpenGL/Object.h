#pragma once
#include "Header.h"
#include "Material.h"

class Object
{
private:
	GLint mvp_location, projection_location, texture_indx_location, view_location, vpos_location, vcol_location;
public:
	float* model;
	vec3 position;
	Material material;

public:
	Object(Material material, vec3 position, float* model) {
		this->material = material;
		vec3_scale(this->position, position, 1);
		this->model = model;
	}

	void UseShader(mat4x4 projection, mat4x4 view) {
		GLuint program = material.CompileShaders();

		mvp_location = glGetUniformLocation(program, "MVP");
		view_location = glGetUniformLocation(program, "view");
		projection_location = glGetUniformLocation(program, "projection");

		vpos_location = glGetAttribLocation(program, "vPos");
		vcol_location = glGetUniformLocation(program, "texCoord");

		GLuint vertex_buffer;
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(model), model, GL_STATIC_DRAW);

		glUseProgram(program);

		glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(vpos_location);
		/*glVertexAttribPointer(vcol_location, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(vcol_location);*/

		glUniformMatrix4fv(view_location, 1, GL_FALSE, (const GLfloat*)material.color);
		//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)m);
		glUniformMatrix4fv(view_location, 1, GL_FALSE, (const GLfloat*)view);
		glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat*)projection);
	}
};

