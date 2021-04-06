
#define _USE_MATH_DEFINES
#include <string>
#include <map>
#include <iostream>
#include <memory>
#include <cmath>


typedef std::string string;


/*!
 * Liskov Substitution principle : 
 * we should be able to sustitute base class by derived without breaking application
 * incorrect inheritance leading to ambigous implementation (rectangle - square - area example)
 * -> use correct interface and classes hierarchy
 * -> use factory pattern with proper methods design
 */

 //-------------------------------------------------------------
 //-------------------------------------------------------------
/*!
* Wrong classes hierarchy
*/
class Rectangle 
{
    protected:
        int width, heigth;
    public:
        int Area() { return width * heigth; }
        virtual void setWidth(int iWidth) {   width = iWidth; }
        virtual void setHeigth(int iHeigth) { heigth = iHeigth; }
};

struct Square : public Rectangle
{
public:
    /*!
    * area = size*size;
    * Ambiguity: setting "width" should set "heigth"="width" and vice versa
    * - unexpected bechaviour of "Square" object used in context of "Rectangle"
    */
    void setWidth(int iWidth) override { width = heigth = iWidth; }
    void setHeigth(int iHeigth) override  { heigth = width = iHeigth; }
};

/*!
* correct classes hierarchy
*/
struct Shape {
    virtual int Area() = 0;
};
struct RectangleShape : Shape
{   
    int width, heigth;
    int Area() override
    {
        return width * heigth;
    }
};
struct SquareShape : Shape
{
    int size;
    int Area() override
    {
        return size * size;
    }
};

//-------------------------------------------------------------
//-------------------------------------------------------------

/*!
* Factory method
* Goal: 2D point should be initialized with Carthesian and Polar coordinates
* in clear manner
*/
class Point
{
    double m_x, m_y;
    Point(double x, double y) : m_x(x), m_y(y){}
 public:
     static Point NewCartesian(double x, double y) {
         return { x,y }; 
     }
     static Point NewPolar(double rho, double theta) {
         return { rho*cos(theta), rho*sin(theta) };
     }
};


/*!
* Abstract Factory 
* Goal: Factory class wraps complete construction 
* providing the requested object in polymorphical way
*/

/*!
* abstract class for hot drinks
*/
struct HotDrink
{
    virtual void drinkVolume(int volume) const = 0;
    virtual ~HotDrink() {}
};

struct Tea : HotDrink
{
    Tea(int volume) { std::cout << "make Tea: " << volume << "ml\n"; }
    void drinkVolume(int volume) const override { std::cout << "Drink Tea: " << volume << "ml\n"; }
};

struct Coffee : HotDrink
{
    Coffee(int volume) { std::cout << "make Koffee: " << volume << "ml\n"; }
    void drinkVolume(int volume) const override { std::cout << "Drink Koffee: " << volume << "ml\n"; }
};

/*!
* abstract class for hot drink factory
*/
struct HotDrinkFactory
{
    virtual std::unique_ptr<HotDrink> make(int volume) const = 0;
    virtual ~HotDrinkFactory() {}
};

/*!
* factories: wraps construction of objects
*/
struct TeaFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make(int volume) const override { 
        return std::make_unique<Tea>(Tea(volume)); 
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make(int volume) const override { 
        return std::make_unique<Coffee>(Coffee(volume)); 
    }
};


/*!
* DrinkFactory: stores different drinks factories
*               calls object construction depending on client request
*/
class DrinkFactory
{ 
    std::map<string, std::unique_ptr<HotDrinkFactory> > hotDrinkfactories;
public:
    DrinkFactory()
    {
        hotDrinkfactories["coffee"] = std::make_unique<CoffeeFactory>();
        hotDrinkfactories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(string type, int volume)
    {
        auto drinkFactoryIt = hotDrinkfactories.find(type);
        if (drinkFactoryIt!= hotDrinkfactories.end())
        {
            auto& [factoryName, teaOrCoffeeFactory] = *drinkFactoryIt;
            return teaOrCoffeeFactory->make(volume);
        }
        else
            return nullptr;
    }
};



int main()
{
    // factory method
    Point carthesian = Point::NewCartesian(2, 2),
          polarPoint = Point::NewPolar(5, M_PI_4);

    // abstract factory
    DrinkFactory drinkCreator;
    std::unique_ptr<HotDrink> cupOfTea = drinkCreator.make_drink("tea",100),
                              cupOfCoffee = drinkCreator.make_drink("coffee", 100);

    if (cupOfTea != nullptr && cupOfCoffee != nullptr)
    {
        cupOfTea->drinkVolume(100);
        cupOfCoffee->drinkVolume(100);
    }

    return 0;
}