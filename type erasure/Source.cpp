#include <memory>
#include <string>
#include <iostream>
#include <vector>

class Square {
public:
	unsigned sizeLength;
	Square(unsigned sizeLength) : sizeLength(sizeLength) {}
	Square(const Square&) = default;
	Square(Square&&) = default;
};

class Circle {
public:
	unsigned radius;
	Circle(unsigned radius) : radius(radius) {}
	Circle(const Circle&) = default;
	Circle(Circle&&) = default;
};

class Screen {
public:
	void draw(const Square& sq) {
		std::cout << "square drawn on screen \n";
	}
	void draw(const Circle& shape) {
		std::cout << "circle drawn on screen \n";
	}
};

class Shape {
	struct TypeErasedShape;
	std::unique_ptr<TypeErasedShape> pImpl;

public:
	template <typename ConcreteShape>
	Shape(ConcreteShape&& shape) : pImpl{ std::make_unique<ExternallyPolymorphicShape<ConcreteShape>>(std::move(shape))} {}

	void draw(Screen& screen) const {
		pImpl->draw(screen);
	}

private:
	struct TypeErasedShape {
		virtual ~TypeErasedShape() {};
		virtual void draw(Screen&) const = 0;
	};

	template <typename ConcreteShape>
	struct ExternallyPolymorphicShape : TypeErasedShape {
		ExternallyPolymorphicShape(ConcreteShape&& t) : shape{ std::forward<ConcreteShape>(t) } {}
		void draw(Screen& s) const override {
			s.draw(shape);
		}
		ConcreteShape shape;
	};
};

int main() {
	Screen screen;
	std::vector<Shape> shapes;

	shapes.emplace_back(Square(1));
	shapes.emplace_back(Circle(2));
	shapes.emplace_back(Square(3));

	for (const auto& shape : shapes)
		shape.draw(screen);

	return 0;
}
