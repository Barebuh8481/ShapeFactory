#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include <windows.h>

// Интерфейс фигуры
class Shape {
public:

    virtual double getArea() const = 0; // чистая виртуальная функция
    virtual ~Shape() = default; // виртуальный деструктор
};

// треугольник
class Triangle : public Shape {
private:
    double a, b, c; // стороны треугольника

public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {
        //существования треугольника
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw std::invalid_argument("Несуществующий треугольник");
        }
    }

    double getArea() const override {
        // Формула Герона
        double s = (a + b + c) / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

// Класс пентагон
class Pentagon : public Shape {
private:
    double side; // длина стороны пятиугольника

public:
    Pentagon(double side) : side(side) {
        if (side <= 0) {
            throw std::invalid_argument("Сторона должна быть положительной");
        }
    }

    double getArea() const override {
        // Площадь правильного пятиугольника: (1/4) * sqrt(5*(5+2*sqrt(5))) * a^2
        const double coeff = 0.25 * std::sqrt(5.0 * (5.0 + 2.0 * std::sqrt(5.0)));
        return coeff * side * side;
    }
};

// Фабрика 
class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& type) {
        if (type == "Треугольник") {
            double a, b, c;
            std::cout << "Введите три стороны треугольника (a b c): ";
            std::cin >> a >> b >> c;
            return std::make_unique<Triangle>(a, b, c);
        }
        else if (type == "Пентагон") {
            double side;
            std::cout << "Введите длину стороны правильного пятиугольника: ";
            std::cin >> side;
            return std::make_unique<Pentagon>(side);
        }
        else {
            throw std::invalid_argument("Неизвестный тип фигуры: " + type);
        }
    }
};

// Основная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string choice;
    std::cout << "Введите тип фигуры (\"Треугольник\" или \"Пентагон\"): ";
    std::getline(std::cin, choice);

    try {
        auto shape = ShapeFactory::createShape(choice);
        std::cout << "Площадь фигуры: " << shape->getArea() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
