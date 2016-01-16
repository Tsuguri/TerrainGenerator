#include "Renderable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


Renderable::Renderable(Mesh* mesh)
{
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1);
	this->mesh = mesh;
}

void Renderable::Render(GLint modelLocation)
{
	glm::mat4 mat = glm::translate(position);// *glm::rotate(glm::mat4(1.0f), 90.0f, rotation)*glm::scale(scale);

	//glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER,mesh->vbo[2]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(mat));
	glDrawElements(GL_TRIANGLES, mesh->count, GL_UNSIGNED_INT, NULL);
}

void Renderable::SetAnimation(Animation* anim)
{
	if (animation)
		delete animation;
	animation = anim;
}

void Renderable::Animate(float time)
{
	if (animation)
		animation->Animate(this,time);
}

void Renderable::SetAnimationStart(bool val) const
{
	if (!animation)
		return;
	if (val)
		animation->StartAnimation();
	else
		animation->StopAnimation();

}
