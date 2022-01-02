///
/// @file:   example_program.cpp
/// @author: GrandChris
/// @date:   2022-02-01
/// @brief:  Tests reading a pei file
///

#include <cstdint>
#include <iostream>

enum class Color : uint8_t {
    red = 0,
    green = 1,
    blue = 2
};

class ColorPrinter final 
{
public:
    [[nodiscard]] constexpr auto
    set_color(Color const color) noexcept
    {
        color_ = color;
    }

    [[nodiscard]] constexpr auto
    print() const noexcept {
        switch (color_)
        {
        case Color::red:
            std::cout << "red" << std::endl;
            break;
        case Color::green:
            std::cout << "green" << std::endl;
            break;
        case Color::blue:
            std::cout << "blue" << std::endl;
            break;
        
        default:
            break;
        }
    }

private:
    Color color_ = {};
};

ColorPrinter color_printer;


[[nodiscard]] auto
main() noexcept -> int
{    
    color_printer.set_color(Color::green);
    color_printer.print();

    return 0;
}

