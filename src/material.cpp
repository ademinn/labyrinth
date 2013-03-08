#include "material.h"

Material::Material(const GLfloat *amb, const GLfloat *diff, const GLfloat *spec, GLfloat shi, const GLfloat *emi)
	:shininess(shi)
{
	ambient = new GLfloat[4];
	diffuse = new GLfloat[4];
	specular = new GLfloat[4];
	emission = new GLfloat[4];
	if (amb != 0)
		for (int i = 0; i < 4; ++i)
			ambient[i] = amb[i];
	else
	{
		ambient[0] = 0.2f;
		ambient[1] = 0.2f;
		ambient[2] = 0.2f;
		ambient[3] = 1.0f;
	}
	if (diff != 0)
		for (int i = 0; i < 4; ++i)
			diffuse[i] = diff[i];
	else
	{
		diffuse[0] = 0.8f;
		diffuse[1] = 0.8f;
		diffuse[2] = 0.8f;
		diffuse[3] = 1.0f;
	}
	if (spec != 0)
		for (int i = 0; i < 4; ++i)
			specular[i] = spec[i];
	else
	{
		specular[0] = 0.0f;
		specular[1] = 0.0f;
		specular[2] = 0.0f;
		specular[3] = 1.0f;
	}
	if (emi != 0)
		for (int i = 0; i < 4; ++i)
			emission[i] = emi[i];
	else
	{
		emission[0] = 0.0f;
		emission[1] = 0.0f;
		emission[2] = 0.0f;
		emission[3] = 1.0f;
	}
}

Material::Material(Material const & m)
	:shininess(m.shininess)
{
	ambient = new GLfloat[4];
	diffuse = new GLfloat[4];
	specular = new GLfloat[4];
	emission = new GLfloat[4];
	for (int i = 0; i < 4; ++i)
	{
		ambient[i] = m.ambient[i];
		diffuse[i] = m.diffuse[i];
		specular[i] = m.specular[i];
		emission[i] = m.emission[i];
	}
}

Material &Material::operator =(Material const &m)
{
	for (int i = 0; i < 4; ++i)
	{
		ambient[i] = m.ambient[i];
		diffuse[i] = m.diffuse[i];
		specular[i] = m.specular[i];
		emission[i] = m.emission[i];
	}
	return *this;
}

void Material::setMaterial()const
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}

Material::~Material()
{
	delete[] ambient;
	delete[] diffuse;
	delete[] specular;
	delete[] emission;
}