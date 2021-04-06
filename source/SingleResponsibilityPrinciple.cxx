
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

typedef std::string string;


/*!
 * Single responsibility principle : 
 * separation of concerns.
 * Class should have primary responsibility. 
 * should not take other responsibility.
 */

// responsible to keep the entries in journal
struct Journal
{
    
    string m_title;
    std::vector<string> m_entries;

    Journal(string const& iTitle) : m_title(iTitle) {}

    void add_entry(const string& entry)
    {
        static int count = 1;
        m_entries.push_back(std::to_string(count++) + ": " + entry);
    }

    /*!
    * WRONG! : persistance code 
    * in case if change persistance logic we will have to change it in numerous classes.
    * (ex. save in database instead of files)
    */
    //void save(string const& filename)
    //{
    //    std::ofstream ofs(filename);
    //    for (string entry : m_entries)
    //    {
    //        ofs << entry << std::endl;
    //    }
    //}//void save(string const& filename)
};

struct PersistenceManager
{
    static void save(Journal const& iJournal, string const& filename)
    {
        std::ofstream ofs(filename);
        for (string entry : iJournal.m_entries)
        {
            ofs << entry << std::endl;
        }
    }//void save(string const& filename)
};



int main()
{
    Journal journal("LogBook");
            journal.add_entry("wreck observation");
            journal.add_entry("rescue case");
            journal.add_entry("boat safari");

    PersistenceManager::save(journal, "LogBook.txt");

    return 0;
}

