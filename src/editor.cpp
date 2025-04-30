#include "editor.h"
#include "square.h"
#include "circle.h"

Editor::Editor()
{
	_shape = Create(_type);
}

Editor::~Editor()
{
	ClearAll();
	delete _shape;
}

void Editor::Update()
{
	if (IsKeyDown(KEY_UP)) {
		_size += 0.5f;
		_size = std::min(_size, 100.0f);
	}

	if (IsKeyDown(KEY_DOWN)) {
		_size -= 0.5f;
		_size = std::max(_size, 0.5f);
	}

	_shape->SetSize(_size);

	// SHAPE COLOR
	if (IsKeyPressed(KEY_RIGHT)) {
		_colorIndex = ++_colorIndex % _colors.size();
		_shape->SetColor(_colors[_colorIndex]);
	}

	// SHAPE SELECT
	if (IsKeyPressed(KEY_LEFT)) {
		_type = static_cast<Shape::Type>((static_cast<int>(_type) + 1) % static_cast<int>(Shape::Type::NUMSHAPES));
		delete _shape;
		_shape = Create(_type);
	}

	//Clear Screen
	if (IsKeyPressed(KEY_DELETE)) {
		ClearAll();
	}

	if (IsMouseButtonPressed(0) || (IsMouseButtonDown(0) && IsKeyDown(KEY_LEFT_CONTROL))) {
		_shapes.push_back(_shape);

		//shape = new Circle(Vector2{ 400, 400 });
		_shape = Create(_type);
	}

	_shape->SetPosition(GetMousePosition());

	for (auto shape : _shapes) {
		shape->Update();
	}

	_shape->Update();
}

void Editor::Draw()
{
	//Draw editor shapes
	for (auto shape : _shapes) {
		shape->Draw();
	}

	//Draw current shape
	_shape->Draw();
}

Shape* Editor::Create(Shape::Type type)
{
	Shape* shape = nullptr;

	switch (type) {

	case Shape::Type::CIRCLE:
		shape = new Circle(GetMousePosition(), _size, _colors[_colorIndex]);
		break;

	case Shape::Type::SQUARE:
		shape = new Square(GetMousePosition(), _size, _colors[_colorIndex]);
		break;

	default:
		break;
	}

	return shape;
}

void Editor::ClearAll()
{
	for (auto shape : _shapes) {
		delete shape;
	}
	_shapes.clear();
}
