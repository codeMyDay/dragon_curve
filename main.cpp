#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <unistd.h>
#include <time.h>

#define sqrt_2 sqrt(2)

void lineTo(float x, float y, float len, float angle)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x+len*cos(angle), y+len*sin(angle));
    glEnd();
}

void dragon_curve(float x, float y, float len, float angle, int depth)
{
    if(depth == 0)
    {
        lineTo(x, y, len, angle);
        return;
    }

    dragon_curve(x, y, len/sqrt_2, angle-M_PI/4.0, depth-1);
    dragon_curve(x+len*cos(angle), y+len*sin(angle), len/sqrt_2, M_PI + angle + M_PI/4.0, depth-1);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Dragon curve", sf::Style::Fullscreen);
    window.setFramerateLimit(30);
	window.setMouseCursorVisible(false);
    glOrtho(0.0, window.getSize().x, window.getSize().y, 0.0, 1.0, -1.0);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        
        dragon_curve(300.0, window.getSize().y/8*5, window.getSize().x-600.0, 0.0, 15);

        window.display();
        usleep(100000);
    }
    return 0;
}
