#pragma once

#include "shape.h"

class Circle : public Shape {
public:
	Circle() = default;

	Circle(Vector2& position, float size = 20, const Color& color = WHITE) :
		Shape(position, size, color)
	{ }

	Type GetType() override {
		return Type::CIRCLE;
	}

	// Inherited via Shape
	void Update() override;
	void Draw() override;
};