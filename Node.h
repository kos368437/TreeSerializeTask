#ifndef TREESERIALIZETESTTASK_NODE_H
#define TREESERIALIZETESTTASK_NODE_H

#include <vector>
#include "AnyData.h"

namespace Sukhinsky {
    namespace Node {

        class Node { // Class Node -- basic element of Tree structure
        public:
                     Node()             = default;
            explicit Node(AnyData::AnyData const & data) : data_(data) {}
                     Node(Node const &) = delete;
                    ~Node()             = default; // Unsafe. Destructor doesn't delete children of the node.

            Node*             getParent()                 { return parent_; }
            void              setParent(Node * newParent) { parent_ = newParent; }

            AnyData::AnyData& getData()                        { return data_; }
            void              setData(AnyData::AnyData & data) { data_ = data; }

            // children_ methods can easily invalidate children's iterators
            void                         addChild(Node * newChild) { newChild->parent_ = this; children_.push_back(newChild);  }
            std::vector<Node*>::iterator eraseChild(std::vector<Node*> :: iterator child);      // Deletes(!!!) child, returns iterator, which points to the next child(or to childrenEnd)
            Node*                        removeChild(std::vector<Node*> :: iterator child);     // Removes child from children_, returns pointer to a child ("You are NOT my child anymore. Go away!")
            std::vector<Node*>::iterator childrenBegin();
            std::vector<Node*>::iterator childrenEnd();
            bool                         hasChildren() { return (children_.empty()); }
        private:
            Node *             parent_ = nullptr;
            std::vector<Node*> children_ = std::vector<Node*>();
            AnyData::AnyData   data_ = AnyData::AnyData();
        };

    }
}

#endif //TREESERIALIZETESTTASK_NODE_H
