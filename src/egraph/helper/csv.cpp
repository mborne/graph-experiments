#include <egraph/helper/csv.h>

namespace egraph {
namespace helper {

///
///
///
std::string escapeCSV(const std::string & s)
{
    bool quoted = false;

    std::ostringstream os;
    for ( const char & c : s ){
        if ( c == '"' ){
            os << "\"\"" ;
            quoted = true;
        }else if ( c == ',' ){
            os << c ;
            quoted = true;
        }else{
            os << c ;
        }
    }
    if ( quoted ){
        return std::string("\"")+os.str()+std::string("\"");
    }else{
        return os.str();
    }
}

} // namespace csv
} // namespace egraph
