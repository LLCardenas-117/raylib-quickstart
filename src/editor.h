#pragma once

#include "shape.h"
#include <vector>
#include <array>

class Editor {
public:
	Editor();

	~Editor();

	void Update();

	void Draw();

private:
	Shape* Create(Shape::Type type);

	void ClearAll();

private:
	float _size = 20;
	Shape::Type _type = Shape::Type::CIRCLE;
	const std::array<Color, 7> _colors = { WHITE, GREEN, RED, BLUE, PURPLE, SKYBLUE, MAGENTA };
	int _colorIndex = 0;

	Shape* _shape = nullptr;
	std::vector<Shape*> _shapes;
};