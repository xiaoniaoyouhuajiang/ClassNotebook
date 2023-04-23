#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "ObjectID.hpp"
#include "MyShape.hpp"
#include "MySquare.hpp"
#include "MyRhombus.hpp"
#include "MyTrapeze.hpp"

class ShapesOnTheScreen {
private:
    std::vector <MyShape*> shapes;
    MyShape *activeShape;
    sf::Color activeColor;
public:
    ShapesOnTheScreen(sf::RenderWindow* win) {
        shapes.reserve(3);
        shapes.push_back(new MySquare(win, 150, 150));
        shapes.push_back(new MyTrapeze(win, 425, 150));
        shapes.push_back(new MyRhombus(win, 675, 150));
        activeColor = sf::Color::Black;
        for (auto &cur_shape : shapes){
            cur_shape->ChangeOutLineColor(activeColor.r, activeColor.g, activeColor.b);    
            cur_shape->ChangeOutLineThickness(1);
        }
        activeShape = shapes[0];
        activeShape->ChangeOutLineThickness(4);        
    }

    ~ShapesOnTheScreen() {
        for (auto &cur_shape : shapes)
            delete cur_shape;
    }

    void Draw() {
        for (const auto &cur_shape: shapes)
            cur_shape->Draw();
    }

    void setActiveShape(int id) {
        std::cout << activeShape->getObjectID() << std::endl;
        activeShape->ChangeOutLineThickness(1);
        MyShape *newActive = getObjectById(id);
        if (!newActive){
            std::cout << "Incorrect shape ID-number! (setActiveShape)" << std::endl;
            exit(1);
        }
        activeShape = newActive;
        activeShape->ChangeOutLineColor(activeColor.r, activeColor.g, activeColor.b);
        activeShape->ChangeOutLineThickness(4);  

    }

    void checkPressing(sf::Vector2f pos) {
        for (const auto &cur_shape : shapes){
            if (cur_shape->checkPressing(pos)){
                std::cout << "Clicked on shape. " << cur_shape->getObjectID();
                activeShape->ChangeOutLineThickness(1);
                activeShape = cur_shape;
                activeShape->ChangeOutLineThickness(4);
                activeShape->ChangeOutLineColor(activeColor.r, activeColor.g, activeColor.b);
                break;
            }
        }
    }

    void ChangePositionOfActiveShape(int dx, int dy, int dir) {
        if (activeShape->checkBorders(dx+dy, dir))
            activeShape->ChangePosition(dx, dy);
    }

    void ChangeColorOfActiveShape(int r, int g, int b){
        activeShape->ChangeColor(r,g,b);
    }

    void ChangeAngleOfActiveShape(int angle, bool dir) {
        if (dir)
            activeShape->ChangeAngle(angle);
        else
            activeShape->ChangeAngle(-angle);
    }

    void ChangeScaleOfActiveShape(float scale) {
        activeShape->ChangeScale(scale);
    }

private:
    MyShape* getObjectById(int requested_id){
        for (const auto &cur_shape : shapes){
            if (cur_shape->getObjectID().getNumberID() == requested_id)
                return cur_shape;
        }
        return nullptr;
    }

};



class ColorRectangles {
private:
    std::vector <sf::RectangleShape> colorizeRects;
    sf::RenderWindow *WIN;
public:
    ColorRectangles(sf::RenderWindow* w) : WIN(w) {
        colorizeRects.reserve(6);
        sf::RectangleShape tmp(sf::Vector2f(90,30));
        tmp.setOutlineThickness(2);
        tmp.setOutlineColor(sf::Color::Black);

        tmp.setFillColor(sf::Color::Red);
        tmp.setPosition(450, 470);
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Green);
        tmp.setPosition(550, 470);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Blue);
        tmp.setPosition(450, 510);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Cyan);
        tmp.setPosition(550, 550);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Magenta);
        tmp.setPosition(550, 510);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Yellow);
        tmp.setPosition(450, 550);    
        colorizeRects.push_back(tmp);
    }

    void Draw() {
        for (auto it = colorizeRects.begin(); it != colorizeRects.end(); it++)
            WIN->draw(*it);
    }

    sf::Color checkPressing(sf::Vector2f point){
        for (auto it = colorizeRects.begin(); it != colorizeRects.end(); it++){
            sf::FloatRect boundingBox = it->getGlobalBounds();
            if (boundingBox.contains(point))
                return it->getFillColor();
        }
        return sf::Color::Black;
    }
};



class AllStaticText {
private:
    sf::RenderWindow *WIN;
    sf::Text leftText;
    sf::Text angleText;
    sf::Text directionText;
public:
    AllStaticText(sf::RenderWindow* win, sf::Font &font) : WIN(win) {
        leftText.setFont(font);
        leftText.setString("Click to change color ------>\nUse arrows to move\nUse   Tab     to rotate\nUse  Wheel   to scale");
        leftText.setCharacterSize(24);
        leftText.setFillColor(sf::Color::Red);
        leftText.setStyle(sf::Text::Regular);
        leftText.setPosition(20,460);

        angleText.setFont(font);
        angleText.setString("Angle:");
        angleText.setCharacterSize(24);
        angleText.setFillColor(sf::Color::Red);
        angleText.setStyle(sf::Text::Regular);
        angleText.setPosition(670,460);
        angleText.setOutlineColor(sf::Color::Yellow);
        angleText.setOutlineThickness(1);

        directionText.setFont(font);
        directionText.setString("Direction:");
        directionText.setCharacterSize(24);
        directionText.setFillColor(sf::Color::Red);
        directionText.setStyle(sf::Text::Regular);
        directionText.setPosition(655,530);
        directionText.setOutlineColor(sf::Color::Yellow);
        directionText.setOutlineThickness(1);
    }

    void Draw() const {
        WIN->draw(leftText);
        WIN->draw(angleText);
        WIN->draw(directionText);
    }
};

class PossibleAngles {
    std::vector <int> possibleAngles;
    unsigned int currentIndex;
public:
    PossibleAngles() {
        possibleAngles.push_back(15);
        possibleAngles.push_back(30);
        possibleAngles.push_back(45);
        possibleAngles.push_back(60);
        possibleAngles.push_back(90);
        possibleAngles.push_back(180);
        currentIndex = 0;
    }

    void refresh() {
        if (currentIndex+1 == possibleAngles.size())
            currentIndex = 0;
        else
            currentIndex++;
    }

    int getCurrent() {
        return possibleAngles[currentIndex];
    }
};

class PossibleDirections {
    bool currentDirection;
public:
    PossibleDirections() {
        currentDirection = false;
    }

    void refresh() {
        if (currentDirection)
            currentDirection = false;
        else
            currentDirection = true;
        std::cout << "refresh PossibleDirections: " << currentDirection << std::endl;
    }

    bool getCurrent() {
        return currentDirection;
    }

};

class AllClickableText {
private:
    sf::RenderWindow *WIN;    
    sf::Text angleText;
    sf::Text directionText;
    int currentAngle;
    bool currentDirection;
public:
    AllClickableText(sf::RenderWindow* win, sf::Font &font) : WIN(win) {    
        angleText.setFont(font);
        angleText.setString("15");
        angleText.setCharacterSize(30);
        angleText.setFillColor(sf::Color::Blue);
        angleText.setStyle(sf::Text::Regular);
        angleText.setPosition(695,490);
        angleText.setOutlineColor(sf::Color::Yellow);
        angleText.setOutlineThickness(1);

        directionText.setFont(font);
        directionText.setString("<--");
        directionText.setCharacterSize(30);
        directionText.setFillColor(sf::Color::Blue);
        directionText.setStyle(sf::Text::Regular);
        directionText.setPosition(695,550);
        directionText.setOutlineColor(sf::Color::Yellow);
        directionText.setOutlineThickness(1);
    }

    void Draw() const {
        WIN->draw(angleText);
        WIN->draw(directionText);
    }

    bool checkPressing(sf::Vector2f point, PossibleAngles &possibleAngles, PossibleDirections &possibleDirections){
        sf::FloatRect boundingBox;

        boundingBox =  angleText.getGlobalBounds();
        if (boundingBox.contains(point)){
            possibleAngles.refresh();
            std::string newText = std::to_string(possibleAngles.getCurrent());
            angleText.setString(newText);
            return true;
        }

        boundingBox =  directionText.getGlobalBounds();
        if (boundingBox.contains(point)){
            possibleDirections.refresh();
            bool dir = possibleDirections.getCurrent();
            if (dir)
                directionText.setString("-->");
            else
                directionText.setString("<--");
            return true;
        }

        return false;
    }

};



int main(){
    sf::Font font;
    if (!font.loadFromFile("Resources/font.ttf")){
        std::cout << "<!-- Can not load font from file! --!>" << std::endl;
        exit(1);
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Click to change color ------>\nUse arrows to move\nUse   Tab     to rotate\nUse  Wheel   to scale");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Regular);
    text.setPosition(20,460);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window1(sf::VideoMode(800, 600), "Golubkov - the best prepod!", sf::Style::Close, settings);
    window1.clear(sf::Color(128,255,255));
    window1.display();

    sf::RectangleShape line(sf::Vector2f(800, 5));
    line.setOutlineColor(sf::Color::Black);
    line.setOutlineThickness(1);
    line.setPosition(0, 450);

    AllStaticText StaticText(&window1, font);
    AllClickableText ClickableText(&window1, font);
    ColorRectangles RGBClickRects(&window1);
        
    sf::Event event;

    sf::Clock clock;
    sf::Time elapsed;
    sf::Clock clock_for_shapes;

    ShapesOnTheScreen shapesOnTheScreen(&window1);
    PossibleDirections possibleDirections;
    PossibleAngles possibleAngles;

    while (window1.isOpen())
    {
    	elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() > 20){
            clock.restart();
        }        

        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window1.close();
            }

        if (event.type == sf::Event::MouseWheelScrolled){
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
                if (event.mouseWheelScroll.delta > 0)
                    shapesOnTheScreen.ChangeScaleOfActiveShape(1.1);
                if (event.mouseWheelScroll.delta < 0)
                    shapesOnTheScreen.ChangeScaleOfActiveShape(0.9);    
            }
        }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                sf::Time timeElapsed_FromLastClick = clock_for_shapes.getElapsedTime();
                if (timeElapsed_FromLastClick.asMilliseconds() > 100) {
                    clock_for_shapes.restart();
                    shapesOnTheScreen.ChangeAngleOfActiveShape(possibleAngles.getCurrent(), possibleDirections.getCurrent());
                }
            }
            
            int step = 5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ 
                sf::Time timeElapsed_FromLastClick = clock_for_shapes.getElapsedTime();
                    if (timeElapsed_FromLastClick.asMilliseconds() > 50) {
                        shapesOnTheScreen.ChangePositionOfActiveShape(-step, 0,  0);
                        clock_for_shapes.restart();
                    }
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){    
                sf::Time timeElapsed_FromLastClick = clock_for_shapes.getElapsedTime();
                    if (timeElapsed_FromLastClick.asMilliseconds() > 50) {
                        shapesOnTheScreen.ChangePositionOfActiveShape(step, 0,  0);
                        clock_for_shapes.restart();
                    }

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){   
                sf::Time timeElapsed_FromLastClick = clock_for_shapes.getElapsedTime();
                    if (timeElapsed_FromLastClick.asMilliseconds() > 50) {
                        shapesOnTheScreen.ChangePositionOfActiveShape(0, -step, 1);
                        clock_for_shapes.restart();
                    }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ 
                sf::Time timeElapsed_FromLastClick = clock_for_shapes.getElapsedTime();
                    if (timeElapsed_FromLastClick.asMilliseconds() > 50) {
                        shapesOnTheScreen.ChangePositionOfActiveShape(0, step, 1);
                        clock_for_shapes.restart();
                    }
            }
        
        
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                shapesOnTheScreen.setActiveShape(0);
            }
                        
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                shapesOnTheScreen.setActiveShape(1);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                shapesOnTheScreen.setActiveShape(2);
            }
            
			if (event.type == sf::Event::KeyPressed) {
	    		if (event.key.code == sf::Keyboard::Escape)
                    window1.close();
			}

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Time timeElapsed_FromLastClick =  clock_for_shapes.getElapsedTime();
                if (timeElapsed_FromLastClick.asMilliseconds() > 150) {
                    sf::Vector2i tmp = sf::Mouse::getPosition(window1);
                    sf::Vector2f pos(static_cast<float>(tmp.x), static_cast<float>(tmp.y));

                    if (pos.y < line.getPosition().y){
                        shapesOnTheScreen.checkPressing(pos);
                    }
                    else {
                        ClickableText.checkPressing(pos, possibleAngles, possibleDirections);

                        sf::Color newColor = RGBClickRects.checkPressing(pos);
                        if (newColor != sf::Color::Black)
                            shapesOnTheScreen.ChangeColorOfActiveShape(newColor.r, newColor.g, newColor.b);
                        clock_for_shapes.restart();
                        std::cout << pos.x << " " << pos. y << std::endl;
                    }
                }
            }
        }

        window1.clear(sf::Color(128,255,255));

        // DRAW Section

        window1.draw(line);
        StaticText.Draw();
        ClickableText.Draw();
        RGBClickRects.Draw();
        shapesOnTheScreen.Draw();

        // End of DRAW Section

        window1.display();
    }
    return 0;
}