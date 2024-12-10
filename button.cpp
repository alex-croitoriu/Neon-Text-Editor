#include <SFML/Graphics.hpp>

class Button
{
    public:
    sf::IntRect Box; // This could easily be protected or private
   
    const bool IsClicked(const sf::Mouse Mouse, const float X, const float Y)
    {
        //We check if it's clicked first because a direct value comparison is less resource intensive than an area check
        if(!Mouse.isButtonPressed(sf::Mouse::Left)){return false;}
        //It's pressed! Let's check it's actually in the box:
        return Box.contains(X,Y);
    }
   
};