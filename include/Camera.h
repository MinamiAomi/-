#pragma once
#include "MyMath.h"
#include <vector>

class Camera
{
private:
	Vector2 m_position = { 640.0f,360.0f };
	Vector2 m_size = { 1280.0f,720.0f };
	Matrix33 m_cameraWorldMatrix;
	Matrix33 m_viewMatrix;
	Matrix33 m_orthoMatrix;
	Matrix33 m_viewportMatrix;
	Matrix33 m_vpVpMatrix;

public:
	Camera();
	void UpdateMatrix();
	void DrawAxis();
	Vector2 Transform(const Vector2& vec) const;
	Vector2 Transform(const Vector2& vec, const Matrix33& world) const;
	std::vector<Vector2> Transform(const std::vector<Vector2>& vec, const Matrix33& world) const;

	const Vector2& position() const { return m_position; }
	void position(const Vector2& v) { m_position = v; }
	const Vector2& size() const { return m_size; }
	void size(const Vector2& v) { m_size = v; }
	const Matrix33& vpVpMatrix() const { return m_vpVpMatrix; }

	float left() const;
	float right() const;
	float top() const;
	float bottom() const;
};