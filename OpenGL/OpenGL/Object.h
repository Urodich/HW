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
	GLint vpos_location, vcol_location;
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

	void UseShader(mat4x4 projection, mat4x4 view, vec3 cameraPos, vec3 gloabal_light_color, float gloabal_light_power) {
		GLuint program = material->CompileShaders();
		GLuint vertex_buffer;
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertices), model, GL_STATIC_DRAW);

		glUseProgram(program);

		vpos_location = glGetAttribLocation(program, "vPos");
		vcol_location = glGetAttribLocation(program, "vNorm");

		glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(model[0]), (void*)0);
		glEnableVertexAttribArray(vpos_location);
		glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(model[0]), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(vcol_location);

		glUniform3f(glGetUniformLocation(program, "color"), 0.3f, 1.f, 0.7f);
		glUniform1f(glGetUniformLocation(program, "globalLightPower"), 0.1f);
		glUniform3f(glGetUniformLocation(program, "globalLightColor"), 1.f, 0.6f, 1.f);

		glUniform3f(glGetUniformLocation(program, "lightPos"), 1.f, 4.f, 4.f);
		glUniform1f(glGetUniformLocation(program, "lightPower"), 0.5f);
		glUniform3f(glGetUniformLocation(program, "viewPos"), cameraPos[0], cameraPos[1], cameraPos[2]);

		mat4x4 m;
		mat4x4_ortho(m, -1, 1, -1.f, 1.f, 1.f, -1.f);
		glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, GL_FALSE, (const GLfloat*)m);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, (const GLfloat*)view);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, (const GLfloat*)projection);
		/*glUniform3f(glGetUniformLocation(program, "color"), material->color[0], material->color[0], material->color[0]);
		glUniform3f(glGetUniformLocation(program, "gloabalLightColor"), material->color[0], material->color[0], material->color[0]);
		glUniform1f(glGetUniformLocation(program, "globalLightPower"), gloabal_light_power);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, (const GLfloat*)view);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, (const GLfloat*)projection);*/

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};

