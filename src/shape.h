#pragma once

#include "raylib.h"

class Shape {
public:
	enum class Type {
		CIRCLE,
		SQUARE,
		NUMSHAPES
	};

public:
	Shape() = default;

	Shape(Vector2& position, float size = 20, const Color& color = WHITE) :
		_postition{ position },
		_size{ size },
		_color{ color }
	{}

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual Type GetType() = 0;

	const Vector2& GetPosition() const { return _postition; }
	void SetPosition(const Vector2& position) { _postition = position; }

	float GetSize() const { return _size; }
	void SetSize(float size) { _size = size; }

	const Color& GetColor() const { return _color; }
	void SetColor(const Color& color) { _color = color; }

protected:
	Color _color = WHITE;
	Vector2 _postition{0, 0};
	float _size = 20;
};