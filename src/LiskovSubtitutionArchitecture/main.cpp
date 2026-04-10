//
// Created by moinshaikh on 4/10/26.
//

#include "../../include/LiskovSubtitutionArchitecture/shapes.hpp"
#include "../../include/LiskovSubtitutionArchitecture/Rectangle.hpp"
#include "../../include/LiskovSubtitutionArchitecture/Circle.hpp"
#include <iostream>
#include <vector>

/*
        How should we implement the members of the Square class? If we want to follow the LSP and save
        the users of such classes from unexpected behavior, we can’t: our square stops being a square if we set
        different values in setWidth and setHeight because the dimensions of a square are always equal. We
        can either stop having a square (not expressible using the preceding code) or modify the height as well,
        thus making the square look different than a rectangle. Therefore, the Square class has problematic
        setWidth and setHeight functions as a workaround. If the width changes, the height changes too,
        and vice versa, but we have the Rectangle base class and expect the sides to change independently.
        If your code violates the LSP, it’s likely that you’re using an incorrect abstraction. In our case, Square
        shouldn’t inherit from Rectangle after all. A better approach could be to make the two implement a
        Shape interface:
        class Shape {
        public:
        virtual double area() = 0;
        virtual ~Shape() = default;
        };
        class Rectangle : public Shape {
        public:
        Rectangle(double width, double height) : width_(width), height_(height) {}
        ~Rectangle() override = default;
        double area() override { return width_ * height_; }
        virtual void setWidth(double width) { width_ = width; }
        virtual void setHeight(double height) { height_ = height; }
        private:Importance of Software Architecture and Principles of Great Design
        20
        double width_;
        double height_;
        };
        class Square : public Shape {
        public:
        Square(double side) : side_(side) {}
        ~Square() override = default;
        double area() override { return side_ * side_; }
        void setSide(double side) { side_ = side; }
        private:
        double side_;
        };
        The conceptual error is resolved without loss of functionality since the Shape class is the base class
        of both classes:
        Shape* s1 = new Rectangle(2, 3);
        Square* s = new Square(4);
        s->setSide(5);
        Shape* s2 = s;
        std::cout << s1->area() << std::endl;// 2*3=6 (expected)
        std::cout << s2->area() << std::endl;// 5*5=25 (expected)
        Since we are on the topic of interfaces, let’s move on to the next item, which is also related to them.
 */
// Function that demonstrates LSP - works with any Shape subclass
void renderShape(Shape* shape, cv::Mat& canvas) {
    shape->draw(canvas);
    std::cout << "Shape drawn successfully!" << std::endl;
}

// Function that demonstrates perfect substitution
void displayShape(Shape* shape, const cv::Mat& image, const std::string& windowName) {
    shape->show(image, windowName);
}

int main()
{
    // Create a canvas
    cv::Mat canvas(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
    
    // Create shapes - both can be treated as Shape*
    std::vector<Shape*> shapes;
    
    Rectangle rectangle(cv::Point(50, 50), cv::Point(200, 150), cv::Scalar(255, 0, 0), 2);
    Circle circle(cv::Point(300, 250), 50, cv::Scalar(0, 255, 0));
    
    shapes.push_back(&rectangle);
    shapes.push_back(&circle);
    
    std::cout << "=== Liskov Substitution Principle Demo ===" << std::endl;
    std::cout << "Both Rectangle and Circle can be substituted for Shape" << std::endl;
    std::cout << "without breaking the program's correctness." << std::endl;
    std::cout << std::endl;
    
    // Demonstrate LSP - both shapes work identically through Shape interface
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "Rendering shape " << (i + 1) << "..." << std::endl;
        renderShape(shapes[i], canvas);
    }
    
    // Display the result
    displayShape(shapes[0], canvas, "LSP Demonstration");
    
    std::cout << std::endl;
    std::cout << "LSP Compliance Check:" << std::endl;
    std::cout << "✓ Same interface (draw, show)" << std::endl;
    std::cout << "✓ No strengthened preconditions" << std::endl;
    std::cout << "✓ No weakened postconditions" << std::endl;
    std::cout << "✓ Perfect substitutability" << std::endl;
    
    return 0;
}
