#include <string>
#include <fstream>

#include "sieve_driver.hh"
#include "sieve_parser.tab.hh"

sieve_driver::sieve_driver()
    : trace_scanning( false ), trace_parsing( false ) {}

sieve_driver::~sieve_driver() {}

int sieve_driver::parse( const std::string &f ) {
    file = f;
    scan_begin();
    yy::sieve_parser parser( *this );
    parser.set_debug_level( trace_parsing );
    result = parser.parse();
    scan_end();
    return result;
}

void sieve_driver::error( const yy::location &l, const std::string &message, const std::string &suggestion ) {
    error( l, message );
    
    std::cerr << std::endl << suggestion << std::endl;
}

void sieve_driver::error( const yy::location &l, const std::string &message ) {
    std::ifstream fin( file );
    std::string line;
    
    for (int i = 1; !fin.eof(); i++) {
        getline(fin, line);
        
        if (i == l.begin.line)
            break;
    }
    
    std::cerr << file << ": " << message << std::endl;
    std::cerr << "On line " << l.begin.line << ":" << std::endl;
    std::cerr << line << std::endl;
    std::cerr << std::string(l.begin.column - 1, ' ') << std::string(l.end.column - l.begin.column, '^') << std::endl;
}

void sieve_driver::error( const std::string &m ) {
    std::cerr << m << std::endl;
}