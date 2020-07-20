#include "Node.h"

namespace Sukhinsky {
    namespace Node {

        std::vector<Node*>::iterator Node::eraseChild(std::vector<Node*> :: iterator child) {
            delete *child;
            return children_.erase(child);
        }
        Node* Node::removeChild(std::vector<Node*> :: iterator child) {
            auto tempPtr = *child;
            children_.erase(child);
            return tempPtr;
        }

        std::vector<Node*>::iterator Node::childrenBegin() {
            return children_.begin();
        }

        std::vector<Node*>::iterator Node::childrenEnd() {
            return children_.end();
        }

    }
}