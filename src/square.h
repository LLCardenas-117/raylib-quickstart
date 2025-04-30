#pragma once

#include "shape.h"

class Square : public Shape {
public:
	Square() = default;

	Square(Vector2& position, float size = 20, const Color& color = WHITE) :
		Shape(position, size, color)
	{ }

	Type GetType() override {
		return Type::SQUARE;
	}

	// Inherited via Shape
	void Update() override;
	void Draw() override;
};
