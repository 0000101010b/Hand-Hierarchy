#include "maths_funcs.h"


// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma once

glm::mat4 qRotate(glm::vec3 angles);
glm::mat4 qMatrix(glm::quat q)
{
	float w = q.w;
	float x = q.x;
	float y = q.y;
	float z = q.z;

	float quat[16]
	{
		1.0f - 2.0f * y * y - 2.0f * z * z,
		2.0f * x * y - 2.0f * w * z,
		2.0f * x * z + 2.0f * w * y,
		0.0f,

		2.0f * x * y + 2.0f * w * z,
		1.0f - 2.0f * x * x - 2.0f * z * z,
		2.0f * y * z - 2.0f * w * x,
		0.0f,

		2.0f * x * z - 2.0f * w * y,
		2.0f * y * z + 2.0f * w * x,
		1.0f - 2.0f * x * x - 2.0f * y * y,
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	};

	glm::mat4 qMatrix = glm::make_mat4(quat);
	return qMatrix;
}


glm::mat4 qRotate(glm::vec3 angles)
{
	versor qX = quat_from_axis_rad(angles.x, 0.0f, 1.0f, 0.0f);
	versor qY = quat_from_axis_rad(angles.y, 1.0f, 0.0f, 0.0f);
	versor qZ = quat_from_axis_rad(angles.z, 0.0f, 0.0f, 1.0f);


	versor q = qX*qY*qZ;

	float w = q.q[0];
	float x = q.q[1];
	float y = q.q[2];
	float z = q.q[3];

	float quat[16]
	{
		1.0f - 2.0f * y * y - 2.0f * z * z,
		2.0f * x * y - 2.0f * w * z,
		2.0f * x * z + 2.0f * w * y,
		0.0f,

		2.0f * x * y + 2.0f * w * z,
		1.0f - 2.0f * x * x - 2.0f * z * z,
		2.0f * y * z - 2.0f * w * x,
		0.0f,

		2.0f * x * z - 2.0f * w * y,
		2.0f * y * z + 2.0f * w * x,
		1.0f - 2.0f * x * x - 2.0f * y * y,
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	};

	glm::mat4 qMatrix = glm::make_mat4(quat);
	return qMatrix;
}

