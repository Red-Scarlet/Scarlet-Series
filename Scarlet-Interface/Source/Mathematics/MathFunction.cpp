#include "MathFunction.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ScarletInterface { namespace Mathematics {

	Matrix4 Mathematics::MathFunction::Orthographic(const float32& _Left, const float32& _Right, const float32& _Bottom, const float32& _Top, const float32& _Near, const float32& _Far)
	{
		glm::mat4 matrix = glm::ortho(_Left, _Right, _Bottom, _Top, _Near, _Far);

		Matrix4 result = {};
		result.Elements[0] = matrix[0][0];
		result.Elements[1] = matrix[0][1];
		result.Elements[2] = matrix[0][2];
		result.Elements[3] = matrix[0][3];
		result.Elements[4] = matrix[1][0];
		result.Elements[5] = matrix[1][1];
		result.Elements[6] = matrix[1][2];
		result.Elements[7] = matrix[1][3];
		result.Elements[8] = matrix[2][0];
		result.Elements[9] = matrix[2][1];
		result.Elements[10] = matrix[2][2];
		result.Elements[11] = matrix[2][3];
		result.Elements[12] = matrix[3][0];
		result.Elements[13] = matrix[3][1];
		result.Elements[14] = matrix[3][2];
		result.Elements[15] = matrix[3][3];

		return result;
	}

	Matrix4 Mathematics::MathFunction::Perspective(const float32& _FOV, const float32& _AspectRatio, const float32& _Near, const float32& _Far)
	{
		glm::mat4 matrix = glm::perspective(_FOV, _AspectRatio, _Near, _Far);

		Matrix4 result = {};
		result.Elements[0] = matrix[0][0];
		result.Elements[1] = matrix[0][1];
		result.Elements[2] = matrix[0][2];
		result.Elements[3] = matrix[0][3];
		result.Elements[4] = matrix[1][0];
		result.Elements[5] = matrix[1][1];
		result.Elements[6] = matrix[1][2];
		result.Elements[7] = matrix[1][3];
		result.Elements[8] = matrix[2][0];
		result.Elements[9] = matrix[2][1];
		result.Elements[10] = matrix[2][2];
		result.Elements[11] = matrix[2][3];
		result.Elements[12] = matrix[3][0];
		result.Elements[13] = matrix[3][1];
		result.Elements[14] = matrix[3][2];
		result.Elements[15] = matrix[3][3];

		return result;
	}

	Matrix4 Mathematics::MathFunction::LookAt(const Vector3& _Camera, const Vector3& _Object, const Vector3& _Up)
	{
		glm::vec3 camera = { _Camera.x, _Camera.y, _Camera.z };
		glm::vec3 object = { _Object.x, _Object.y, _Object.z };
		glm::vec3 up = { _Up.x, _Up.y, _Up.z };
		glm::mat4 matrix = glm::lookAt(camera, object, up);

		Matrix4 result = {};
		result.Elements[0] = matrix[0][0];
		result.Elements[1] = matrix[0][1];
		result.Elements[2] = matrix[0][2];
		result.Elements[3] = matrix[0][3];
		result.Elements[4] = matrix[1][0];
		result.Elements[5] = matrix[1][1];
		result.Elements[6] = matrix[1][2];
		result.Elements[7] = matrix[1][3];
		result.Elements[8] = matrix[2][0];
		result.Elements[9] = matrix[2][1];
		result.Elements[10] = matrix[2][2];
		result.Elements[11] = matrix[2][3];
		result.Elements[12] = matrix[3][0];
		result.Elements[13] = matrix[3][1];
		result.Elements[14] = matrix[3][2];
		result.Elements[15] = matrix[3][3];

		return result;
	}

	Matrix4 Mathematics::MathFunction::Translate(const Vector3& _Translation)
	{
		glm::vec3 translation = { _Translation.x, _Translation.y, _Translation.z };
		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), translation);

		Matrix4 result = {};
		result.Elements[0] = matrix[0][0];
		result.Elements[1] = matrix[0][1];
		result.Elements[2] = matrix[0][2];
		result.Elements[3] = matrix[0][3];
		result.Elements[4] = matrix[1][0];
		result.Elements[5] = matrix[1][1];
		result.Elements[6] = matrix[1][2];
		result.Elements[7] = matrix[1][3];
		result.Elements[8] = matrix[2][0];
		result.Elements[9] = matrix[2][1];
		result.Elements[10] = matrix[2][2];
		result.Elements[11] = matrix[2][3];
		result.Elements[12] = matrix[3][0];
		result.Elements[13] = matrix[3][1];
		result.Elements[14] = matrix[3][2];
		result.Elements[15] = matrix[3][3];

		return result;
	}

	Matrix4 Mathematics::MathFunction::Rotation(const Vector3& _Rotate)
	{
		glm::vec3 rotate = { _Rotate.x, _Rotate.y, _Rotate.z };
		glm::mat4 matrix = glm::mat4(glm::quat(rotate));

		Matrix4 result = {};
		result.Elements[0] = matrix[0][0];
		result.Elements[1] = matrix[0][1];
		result.Elements[2] = matrix[0][2];
		result.Elements[3] = matrix[0][3];
		result.Elements[4] = matrix[1][0];
		result.Elements[5] = matrix[1][1];
		result.Elements[6] = matrix[1][2];
		result.Elements[7] = matrix[1][3];
		result.Elements[8] = matrix[2][0];
		result.Elements[9] = matrix[2][1];
		result.Elements[10] = matrix[2][2];
		result.Elements[11] = matrix[2][3];
		result.Elements[12] = matrix[3][0];
		result.Elements[13] = matrix[3][1];
		result.Elements[14] = matrix[3][2];
		result.Elements[15] = matrix[3][3];

		return result;
	}

	Matrix4 Mathematics::MathFunction::Scale(const Vector3& _Scale)
	{
		glm::vec3 scale = { _Scale.x, _Scale.y, _Scale.z };
		glm::mat4 matrix = glm::scale(glm::mat4(1.0f), scale);

		Matrix4 result = {};
		result.Elements[0] = matrix[0][0];
		result.Elements[1] = matrix[0][1];
		result.Elements[2] = matrix[0][2];
		result.Elements[3] = matrix[0][3];
		result.Elements[4] = matrix[1][0];
		result.Elements[5] = matrix[1][1];
		result.Elements[6] = matrix[1][2];
		result.Elements[7] = matrix[1][3];
		result.Elements[8] = matrix[2][0];
		result.Elements[9] = matrix[2][1];
		result.Elements[10] = matrix[2][2];
		result.Elements[11] = matrix[2][3];
		result.Elements[12] = matrix[3][0];
		result.Elements[13] = matrix[3][1];
		result.Elements[14] = matrix[3][2];
		result.Elements[15] = matrix[3][3];

		return result;
	}

	Matrix4 Mathematics::MathFunction::Inverse(const Matrix4& _Matrix)
	{
		glm::mat4 matrix = {};
		matrix[0][0] = _Matrix.Elements[0];
		matrix[0][1] = _Matrix.Elements[1];
		matrix[0][2] = _Matrix.Elements[2];
		matrix[0][3] = _Matrix.Elements[3];
		matrix[1][0] = _Matrix.Elements[4];
		matrix[1][1] = _Matrix.Elements[5];
		matrix[1][2] = _Matrix.Elements[6];
		matrix[1][3] = _Matrix.Elements[7];
		matrix[2][0] = _Matrix.Elements[8];
		matrix[2][1] = _Matrix.Elements[9];
		matrix[2][2] = _Matrix.Elements[10];
		matrix[2][3] = _Matrix.Elements[11];
		matrix[3][0] = _Matrix.Elements[12];
		matrix[3][1] = _Matrix.Elements[13];
		matrix[3][2] = _Matrix.Elements[14];
		matrix[3][3] = _Matrix.Elements[15];
		matrix = glm::inverse(matrix);

		Matrix4 result = {};
		result.Elements[0] = matrix[0][0];
		result.Elements[1] = matrix[0][1];
		result.Elements[2] = matrix[0][2];
		result.Elements[3] = matrix[0][3];
		result.Elements[4] = matrix[1][0];
		result.Elements[5] = matrix[1][1];
		result.Elements[6] = matrix[1][2];
		result.Elements[7] = matrix[1][3];
		result.Elements[8] = matrix[2][0];
		result.Elements[9] = matrix[2][1];
		result.Elements[10] = matrix[2][2];
		result.Elements[11] = matrix[2][3];
		result.Elements[12] = matrix[3][0];
		result.Elements[13] = matrix[3][1];
		result.Elements[14] = matrix[3][2];
		result.Elements[15] = matrix[3][3];

		return result;
	}

	float32* MathFunction::ValuePtr(const Matrix4& _Matrix)
	{
		glm::mat4 matrix = {};

		matrix[0][0] = _Matrix.Elements[0];
		matrix[0][1] = _Matrix.Elements[1];
		matrix[0][2] = _Matrix.Elements[2];
		matrix[0][3] = _Matrix.Elements[3];
		matrix[1][0] = _Matrix.Elements[4];
		matrix[1][1] = _Matrix.Elements[5];
		matrix[1][2] = _Matrix.Elements[6];
		matrix[1][3] = _Matrix.Elements[7];
		matrix[2][0] = _Matrix.Elements[8];
		matrix[2][1] = _Matrix.Elements[9];
		matrix[2][2] = _Matrix.Elements[10];
		matrix[2][3] = _Matrix.Elements[11];
		matrix[3][0] = _Matrix.Elements[12];
		matrix[3][1] = _Matrix.Elements[13];
		matrix[3][2] = _Matrix.Elements[14];
		matrix[3][3] = _Matrix.Elements[15];

		return glm::value_ptr(matrix);
	}

}}