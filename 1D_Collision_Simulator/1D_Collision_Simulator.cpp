#include <iostream>
#include "SFML/Graphics.hpp"

#define width 800
#define height 400

class Object {
    sf::Vector2f pos;
    sf::RectangleShape s;
    float vel_x;
    float len;
    float mass;

public:

    Object(float posx, float posy, float mass, float vel_x, float len, sf::Color c) {
        pos.x = posx;
        pos.y = posy-len;
        this->vel_x = vel_x;
        this->mass = mass;
        this->len = len;

        s.setSize({ len,len });
        s.setPosition(pos);
        s.setFillColor(c);
    }

    void render(sf::RenderWindow& wind) {
        wind.draw(s);
    }

    sf::Vector2f get_pos() {
        return pos;
    }

    float get_vel_x() {
        return vel_x;
    }

    void set_vel_x(float value) {
        vel_x = value;
    }

    float get_mass() {
        return mass;
    }

    void update() {
        if((vel_x > 0 && pos.x + len + vel_x > 800) || (pos.x + vel_x < 0 && vel_x < 0)){
            vel_x = -vel_x;
        }
        pos.x += vel_x;
        s.setPosition(pos);
    }

    void check_collision(Object& obj) {
        if (pos.x + len + vel_x > obj.get_pos().x + obj.get_vel_x()) {
            float ma = mass;
            float mb = obj.get_mass();
            float va1 = vel_x;
            float vb1 = obj.get_vel_x();

            float va2 = ((ma - mb) / (ma + mb)) * va1 + ((2 * mb) / (ma + mb)) * vb1;
            float vb2 = ((2 * ma) / (ma + mb)) * va1 + ((mb - ma) / (ma + mb)) * vb1;

            vel_x = va2;
            obj.set_vel_x(vb2);
         }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Test");
    window.setFramerateLimit(60);
    sf::Event e;

    Object o1(100, height, 5, 2,20, sf::Color::Blue);
    Object o2(400, height, 10, -3,30, sf::Color::Red);

    while (window.isOpen()) {
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        o1.check_collision(o2);
        o1.update(); o2.update();
        o1.render(window); o2.render(window);
        window.display();

        std::cout << "v1 = " << o1.get_vel_x() << std::endl;
        std::cout << "m1 = " << o1.get_mass() << std::endl;
        std::cout << std::endl;
        std::cout << "v2 = " << o2.get_vel_x() << std::endl;
        std::cout << "m2 = " << o2.get_mass() << std::endl;
    }

    return 0;
}
