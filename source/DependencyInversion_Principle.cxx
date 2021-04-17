
#include <string>
#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

/*!
 * Dependency inversion principle : 
 * - High-level modules should not depend on Low-level modules
 *   both should depend on abstractions
 * - Abstrations should not depend on details.
 *   details should depend on abstrations.
 */


enum class Relationship { parent, child };

struct Person {
    string name;
};

struct RelationshipBrowser {
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};


/*!
* Low level module
*/
struct Relationships : RelationshipBrowser
{
    vector<tuple<Person, Relationship, Person> > relations;

    void add_parent_and_child(const Person& parent, const Person& child)
    {
        relations.push_back({ parent, Relationship::parent, child });
    }

    vector<Person> find_all_children_of(const string& name)
    {
        vector<Person> result;
        for (auto& [first, rel, second] : relations)
        {
            if (first.name == "John" && rel == Relationship::parent)
                result.push_back(second);
        }
        return result;
    }
};


/*!
* High level module
*/
struct Research
{
    /*!
    * Wrong way to access Low-level module "Relationships"
   
        Research(Relationships& iRelationships)
        {
            /* Tight coupling
            * Problem:  if Low-level modified = High Level is broken
            * Exxample: if access to "iRelationships.relations" restricted == High level code is broken
            *\/
            auto& relations = iRelationships.relations;
            
            for ( auto&[first, rel, second] : relations)
            {
                if (first.name=="John" && rel== Relationship::parent)
                    cout << "John child:"<< second.name << "\n";
            }
        }
    */

    /*!
    * Correct way to access "Relationships" module
    */
    Research(RelationshipBrowser& iRelationships)
    {
        for (auto& child : iRelationships.find_all_children_of({ "John" }))
        {
           cout << "John child:" << child.name << "\n";
        }
    }
};

int main()
{
    Relationships   relationships;
                    relationships.add_parent_and_child( { "John" }, {"John's baby1"} );
                    relationships.add_parent_and_child( { "John" }, {"John's baby2"} );
                    relationships.add_parent_and_child( { "Tom" },  {"Tom's baby1"}  );

    // find "John" children in constructor
    Research research(relationships);

    return 0;
}

