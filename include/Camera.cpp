#include "Camera.h"
#include "Novice.h"

Camera::Camera()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	m_cameraWorldMatrix = Matrix33::MakeTranslation(m_position);
	m_viewMatrix = m_cameraWorldMatrix.Inverse();
	Vector2 halfSize = m_size / 2.0f;
	m_orthoMatrix = Matrix33::MakeOrthographic(-halfSize.x, halfSize.y, halfSize.x, -halfSize.y);
	m_viewportMatrix = Matrix33::MakeViewport(0, 0, m_size.x, m_size.y);
	m_vpVpMatrix = m_viewMatrix * m_orthoMatrix * m_viewportMatrix;
}

void Camera::DrawAxis()
{
	Vector2 scrWorldOrgin = m_vpVpMatrix.GetTranslation();
	Novice::DrawLine(0, static_cast<int>(scrWorldOrgin.y), m_size.x, static_cast<int>(scrWorldOrgin.y), RED);
	Novice::DrawLine(static_cast<int>(scrWorldOrgin.x), 0, static_cast<int>(scrWorldOrgin.x), m_size.y, BLUE);
}

Vector2 Camera::Transform(const Vector2& vec) const
{
	return vec * m_vpVpMatrix;
}

Vector2 Camera::Transform(const Vector2& vec, const Matrix33& world) const
{
	Matrix33 wvpVpMat = world * m_vpVpMatrix;
	return vec * wvpVpMat;
}

std::vector<Vector2> Camera::Transform(const std::vector<Vector2>& vec, const Matrix33& world) const
{
	Matrix33 wvpVpMat = world * m_vpVpMatrix;
	std::vector<Vector2> transVec;
	for (const auto& iter : vec) {
		transVec.emplace_back(iter * world);
	}
	return transVec;
}

float Camera::left() const
{
	return m_position.x - m_size.x / 2.0f;
}

float Camera::right() const
{
	return m_position.x + m_size.x / 2.0f;
}

float Camera::top() const
{
	return m_position.y + m_size.y / 2.0f;
}

float Camera::bottom() const
{
	return m_position.y - m_size.y / 2.0f;
}
