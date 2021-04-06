
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

typedef std::string string;


/*!
 * open-closed principle
 * code: open to extension closed to modification
 * avoid to modify already written code.
 * create extensions instead. (inherit interface )
 */

 /*!
 * given qualities
 */
enum class Color {red,   green,  blue};
enum class Size  {small, medium, large};

/*!
* given product
*/
struct Product
{
    string name;
    Color  color;
    Size   size;
};

/*!
* Task: filter products by qualities
* Wrong implementation: 
* "ProductFilter" modified each time when new option needed
*/
struct ProductFilter
{
    std::vector<Product*> by_color(std::vector<Product*> items, Color iColor)
    {
        std::vector<Product*> result;

        for (Product* item : items)
            if (item->color == iColor)
                result.push_back(item);

        return result;
    }//by_color(...)

    std::vector<Product*> by_size(std::vector<Product*> items, Size iSize)
    {
        std::vector<Product*> result;

        for (Product* item : items)
            if (item->size == iSize)
                result.push_back(item);

        return result;
    }//by_size(...)
};

/*!
* Correct implementation:
*   Specification pattern : 
*   - generic specification for every Quality
*   - generic filter for different products
*/
template <typename T> struct Specification
{
    virtual bool is_satisfied(T* item) = 0;
};
template <typename T> struct Filter 
{
    virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
};


struct GenericFilter : Filter<Product>
{
    std::vector<Product*> filter( std::vector<Product*> items,
                                  Specification<Product>& spec) override
    {
        std::vector<Product*> result;
        for (Product* item : items)
            if (spec.is_satisfied(item))
                result.push_back(item);

        return result;
    }
};

struct ColorSpec : Specification<Product>
{
    ColorSpec(Color iColor) : color(iColor) {}

    bool is_satisfied(Product* item) override
    {
        return item->color == color ;
    }

    Color color;
};

struct SizeSpec : Specification<Product>
{
    SizeSpec(Size iSize) :size(iSize) {}

    bool is_satisfied(Product* item)
    {
        return item->size == size;
    }

    Size size;
};

int main()
{
    // create products
    Product
        apple{ "green small",Color::green,Size::small },
        tree{  "green large",Color::green,Size::large },
        house{ "blue, large ",Color::blue,Size::large };
    // store in vector
    std::vector<Product*> items{ &apple ,&tree ,&house };

    // filter products by qualities
    ProductFilter pf;
    std::vector<Product*> greenItems(pf.by_color(items, Color::green));
    std::vector<Product*> largeItems(pf.by_size(items, Size::large));

    GenericFilter gf;
    std::vector<Product*> greenGItems(gf.filter(items, ColorSpec(Color::green)));
    std::vector<Product*> largeGItems(gf.filter(items, SizeSpec(Size::large)));

    std::for_each(greenItems.begin(), greenItems.end(), [](Product* pr) {std::cout << pr->name << " "; });
    std::cout << "\n";
    std::for_each(greenGItems.begin(), greenGItems.end(), [](Product* pr) {std::cout << pr->name << " "; });
    return 0;
}

