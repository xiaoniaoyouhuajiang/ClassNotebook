#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <memory>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Graphics/Shape.hpp"

#include "ObjectID.hpp"
#include "MyShape.hpp"
#include "MySquare.hpp"
#include "MyRhombus.hpp"
#include "MyTrapeze.hpp"

class ShapesOnTheScreen {
private:
    std::vector <std::shared_ptr<MyShape> > shapes;
    MyShape *activeShape;
    sf::Color activeColor;
public:
    ShapesOnTheScreen(sf::RenderWindow* win) {
        srand(time(NULL));
        shapes.reserve(30);
        shapes.push_back(std::shared_ptr<MyShape>(new MySquare(win, 80, 80)));
        shapes.back().get()->ChangeScale(0.5);
        shapes.push_back(std::shared_ptr<MyShape>(new MyTrapeze(win, 210, 80)));
        shapes.back().get()->ChangeScale(0.5);
        shapes.push_back(std::shared_ptr<MyShape>(new MyRhombus(win, 340, 80)));
        shapes.back().get()->ChangeScale(0.5);
        activeColor = sf::Color::Black;
        for (auto &cur_shape : shapes){
            cur_shape->ChangeOutLineColor(activeColor.r, activeColor.g, activeColor.b);    
            cur_shape->ChangeOutLineThickness(1);
        }
        activeShape = shapes[0].get();
        activeShape->ChangeOutLineThickness(4);        
    }

    void addShape(MyShape* shp){
        shapes.push_back(std::shared_ptr<MyShape>(shp));
        std::cout << "Now size is: " << shapes.size() << std::endl;
    }

    void sortBySquare(){
        std::sort(shapes.begin(), shapes.end(), 
                [&](std::shared_ptr<MyShape> const &lhs, std::shared_ptr<MyShape> const &rhs)
                {
                    return lhs.get()->getArea() > rhs.get()->getArea();
                }
        );
        ChangePositionAfterSort();
    }

    void sortByColor(){
        std::sort(shapes.begin(), shapes.end(), 
                [&](std::shared_ptr<MyShape> const &lhs, std::shared_ptr<MyShape> const &rhs)
                {
                    return cmpColors(lhs.get()->getColor(), rhs.get()->getColor());                                                                  
                }
        );
        ChangePositionAfterSort();
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
                activeShape = cur_shape.get();
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

    void ChangePositionAfterSort(){
        float x = 0;
        float y = 80;
        for (auto &shape : shapes){
            x += 130;
            if (x == 910){
                x = 130;
                y += 140;
            }
            shape.get()->setPos(x-50,y);
        }
    }

    bool cmpColors(sf::Color left, sf::Color right){
        if (left == sf::Color::Red)
            return true;
        if (right == sf::Color::Red)
            return false;
        if (left == sf::Color::Green)
            return true;
        if (right == sf::Color::Green)
            return false;
        if (left == sf::Color::Blue)
            return true;
        if (right == sf::Color::Blue)
            return false;

        if (left == sf::Color::Cyan)
            return true;
        if (right == sf::Color::Cyan)
            return false;
        if (left == sf::Color::Magenta)
            return true;
        if (right == sf::Color::Magenta)
            return false;
        if (left == sf::Color::Yellow)
            return true;
        if (right == sf::Color::Yellow)
            return false;
        return true;
    }

    MyShape* getObjectById(int requested_id){
        for (const auto &cur_shape : shapes){
            if (cur_shape->getObjectID().getNumberID() == requested_id)
                return cur_shape.get();
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
        tmp.setPosition(20, 465);
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Green);
        tmp.setPosition(130, 465);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Blue);
        tmp.setPosition(240, 465);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Cyan);
        tmp.setPosition(350, 465);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Magenta);
        tmp.setPosition(460, 465);    
        colorizeRects.push_back(tmp);

        tmp.setFillColor(sf::Color::Yellow);
        tmp.setPosition(570, 465);    
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
    sf::Text sortHintText;
    sf::Text sortTypes;
public:
    AllStaticText(sf::RenderWindow* win, sf::Font &font) : WIN(win) {
        leftText.setFont(font);
        leftText.setString("\nUse arrows to move\nUse   Tab     to rotate\nUse  Wheel  to scale");
        leftText.setCharacterSize(24);
        leftText.setFillColor(sf::Color::Red);
        leftText.setStyle(sf::Text::Regular);
        leftText.setPosition(20,470);

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

        sortHintText.setFont(font);
        sortHintText.setString("Sort by:\nSquare -\nColor   -");
        sortHintText.setCharacterSize(28);
        sortHintText.setFillColor(sf::Color::Blue);
        sortHintText.setStyle(sf::Text::Regular);
        sortHintText.setPosition(380, 495);
        sortHintText.setOutlineColor(sf::Color::Yellow);
        sortHintText.setOutlineThickness(2);

        sortTypes.setFont(font);
        sortTypes.setString("S\nC");
        sortTypes.setCharacterSize(30);
        sortTypes.setFillColor(sf::Color::Black);
        sortTypes.setStyle(sf::Text::Regular);
        sortTypes.setPosition(530, 527);
        sortTypes.setOutlineColor(sf::Color::Yellow);
        sortTypes.setOutlineThickness(2);
    }

    void blinkAnimatonTick(){
        static bool state = false;
        if (state){
            sortHintText.setOutlineThickness(0);
            sortTypes.setOutlineThickness(0);
        }
        else {
            sortHintText.setOutlineThickness(2);
            sortTypes.setOutlineThickness(2);            
        }

        state = !state;
    }

    void Draw() const {
        WIN->draw(leftText);
        WIN->draw(angleText);
        WIN->draw(directionText);
        WIN->draw(sortHintText);
        WIN->draw(sortTypes);
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
        if (elapsed.asMilliseconds() > 300){
            StaticText.blinkAnimatonTick();
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ 
                sf::Time timeElapsed_FromLastClick = clock_for_shapes.getElapsedTime();
                    if (timeElapsed_FromLastClick.asMilliseconds() > 100) {
                        auto activeColor = sf::Color::Black;
                        static int index = 0;
                        static int index_sq = 2;
                        static int index_tr = 2;
                        static int index_rh = 2;
                        static float x = 390;
                        static float y = 80;
                        x += 130;
                        if (x == 910){
                            x = 130;
                            y += 140;
                        }
                        MyShape* ptr = nullptr;
                        switch (index % 3){
                            case 0:
                                if (index_sq > 5){ std::cout << "Enough squares!\n"; break; }
                                ptr = new MySquare(&window1, x-50, y);
                                index_sq++;
                                break;
                            case 1:
                                if (index_tr > 5){ std::cout << "Enough trapeze!\n"; break; }
                                ptr = new MyTrapeze(&window1, x-50, y);                              
                                index_tr++;
                                break;
                            case 2:
                                if (index_rh > 5){ std::cout << "Enough rhombus!\n"; break; }
                                ptr = new MyRhombus(&window1, x-50, y);
                                index_rh++;
                                break;
                            default:
                                exit(100);
                        }
                        if (ptr){
                            double kf = ((double)(rand() % 40 + 10)) / 100;
                            std::cout << kf << std::endl;
                            ptr->ChangeScale(kf);
                            ptr->ChangeOutLineColor(activeColor.r, activeColor.g, activeColor.b);    
                            ptr->ChangeOutLineThickness(1);   
                            shapesOnTheScreen.addShape(ptr);
                        }
                        clock_for_shapes.restart();
                        index++;
                    }
                // shapesOnTheScreen.sortBySquare();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ 
                shapesOnTheScreen.sortBySquare();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){ 
                shapesOnTheScreen.sortByColor();
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