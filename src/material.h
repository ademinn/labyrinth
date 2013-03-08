#pragma once
#include <GL/gl.h>

class Material
{
	GLfloat *ambient;
	GLfloat *diffuse;
	GLfloat *specular;
	GLfloat shininess;
	GLfloat *emission;

public:
	Material(GLfloat const *amb = 0, GLfloat const *diff = 0, GLfloat const *spec = 0, GLfloat shi = 0.0, GLfloat const *emi = 0);
	Material(Material const &);
	Material &operator =(Material const &);
	void setMaterial()const;
	~Material();
};

Material const NullMaterial;
