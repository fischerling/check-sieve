#pragma once

#include <string>

#include "ASTNode.hh"

namespace sieve
{

class ASTVisitor;

class ASTString : public ASTNode {
public:
    ASTString() : ASTNode() {}    
    ASTString(yy::location location);
    ASTString(std::string str);
    ASTString(yy::location location, std::string str);
    
    void accept(ASTVisitor &visitor);
    
    std::string value() const { return this->_str; }

    template<class T>
    std::vector<ASTNode *>::const_iterator find(const T& value) const {
        for (std::vector<ASTNode *>::const_iterator it = this->children().begin(); it != this->children().end(); ++it) {
            const T* child = dynamic_cast<T*>(*it);

            if (child == NULL)
                continue;

            if (child->value() == value.value())
                return it;
        }

        return this->children().end();
    }
    
private:
    std::string _str;
};

} // namespace sieve
