
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

typedef std::string string;


/*!
 * Interface Segregation principle : 
 * client should not depend on method he does not use
 * ---------------------------------------------------------
 * Should keep in mind that interfaces limits the code reuse
 * by forcing every derived class implementing methods differently
 * To create more reusable code consider to use "Strategy Pattern"
 */

struct Document;

/*!
 * Wrong! Interface is too big.
 * some clients not able to implement all the methods
 */
struct IMachine {
    virtual void print(const Document& doc) const = 0;
    virtual void scan(Document& doc) const  = 0;
    virtual void fax(const Document& doc) const = 0;
};

/*!
 * Correct: Interface is too big.
 */
struct IPrinter {
    virtual void print(const Document& doc) const = 0;
};
struct IScanner {
    virtual void scan(Document& doc) const = 0;
};
struct IFax {
    virtual void fax(const Document& doc) const = 0;
};

struct Printer : IPrinter
{
    void print(const Document& doc) const override {/*prints*/}
};

struct OfficeMachine : IPrinter, IScanner, IFax
{
     void print(const Document& doc) const override {/*prints*/ }
     void scan(Document& doc) const override {/*scans*/ }
     void fax(const Document& doc) const override {/*faxes*/ }
};

int main()
{
    return 0;
}

