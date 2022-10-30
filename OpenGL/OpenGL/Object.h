#pragma once
#include "Header.h"
#include "Material.h"

struct Vertices {
	float x, y, z;
	float Nx, Ny, Nz;
};

class Object
{
private:
	GLint mvp_location, projection_location, texture_indx_location, view_location, vpos_location, vcol_location;
public:
	Vertices* model;
	vec3 position;
	Material* material;

public:
	Object(Material* material, vec3 position, Vertices* model) {
		this->material = material;
		vec3_scale(this->position, position, 1);
		this->model = model;
	}

	void UseShader(mat4x4 projection, mat4x4 view, vec3 gloabal_light_color, float gloabal_light_power) {
		GLuint program = material->CompileShaders();

		GLuint vertex_buffer;
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(model), model, GL_STATIC_DRAW);

		glUseProgram(program);

		vpos_location = glGetAttribLocation(program, "vPos");
		glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)0);
		glEnableVertexAttribArray(vpos_location);


		glUniform1fv(glGetUniformLocation(program, "color"), sizeof(material->color), material->color);
		glUniform1fv(glGetUniformLocation(program, "gloabalLightColor"), sizeof(gloabal_light_color), gloabal_light_color);
		glUniform1f(glGetUniformLocation(program, "globalLightPower"), gloabal_light_power);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, (const GLfloat*)view);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, (const GLfloat*)projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);// floor(sizeof(model) / sizeof(Vertices)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(vpos_location);
	}
};

