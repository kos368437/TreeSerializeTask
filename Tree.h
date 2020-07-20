#ifndef TREESERIALIZETESTTASK_TREE_H
#define TREESERIALIZETESTTASK_TREE_H

#include <ostream>
#include "Node.h"
#include <stack>
#include "ISerializable.h"

namespace Sukhinsky {
    namespace Tree {
        class Tree : Serialize::ISerializable {
        public:
            class TreePostOrderIterator;
            class TreePreOrderIterator;

            Tree() = default;
            Tree(AnyData::AnyData const & data) : root_(new Node::Node(data)) {}
            ~Tree();

            //void deserialize(std::istream&);           I don't know how to do it well
            void ASCIIVisualisation(std::ostream& out);
            void serialize(std::ostream&); // structure: typename\n data\n (\n ...children...\n )\n

            TreePreOrderIterator beginPreOrder() { return TreePreOrderIterator(*this); }
            TreePostOrderIterator beginPostOrder() { return TreePostOrderIterator(*this); }

            void createRoot(AnyData::AnyData & data) { root_= new Node::Node(data); }

            class TreePreOrderIterator :
                    std::iterator<std::forward_iterator_tag, AnyData::AnyData> {
                friend class Tree;
            public:
                TreePreOrderIterator()                                     = default;
                TreePreOrderIterator(TreePreOrderIterator const &)         = default;
                explicit TreePreOrderIterator(Tree & tree) { head_ = tree.root_; begin(); }
                ~TreePreOrderIterator()                                     = default;

                TreePreOrderIterator & operator=(TreePreOrderIterator &&)       = default;
                TreePreOrderIterator & operator=(TreePreOrderIterator const &)  = default;

                void begin();
                void end();

                TreePreOrderIterator  operator++ (int);
                TreePreOrderIterator& operator++ ();
                bool                  operator!= (const TreePreOrderIterator& it) const;
                bool                  operator== (const TreePreOrderIterator& it) const;
                AnyData::AnyData&     operator*()                                 const;
                AnyData::AnyData*     operator->()                                const;

                std::string typeName()       const;
                std::string textValue()      const;

                void insertChild(AnyData::AnyData data); // After that method you will stay at the same position as before

            private:
                std::stack<Node::Node *> nextStepStack_ = std::stack<Node::Node *>(); // The top element is pointer to current node for this iterator
                Node::Node*              head_ = nullptr;

                bool hasChildren()           const;
                bool isLastChild();
                bool notAChild(Node::Node *) const;
                Node::Node * current() const;
                size_t degreeOfRelation(TreePreOrderIterator const &) const;
            };

            class TreePostOrderIterator
                    : std::iterator<std::forward_iterator_tag, AnyData::AnyData> {
                friend class Tree;
            public:
                TreePostOrderIterator()                                    = default;
                explicit TreePostOrderIterator(Tree & tree) { head_ = tree.root_; nextStepStack_.push(head_); };
                TreePostOrderIterator(TreePostOrderIterator const &)       = default;
                ~TreePostOrderIterator()                                    = default;

                TreePostOrderIterator & operator=(TreePostOrderIterator &&)         = default;
                TreePostOrderIterator & operator=(TreePostOrderIterator const &)    = default;

                void begin();
                void end();

                TreePostOrderIterator  operator++ (int);
                TreePostOrderIterator& operator++ ();
                bool                   operator!= (const TreePostOrderIterator& it) const;
                bool                   operator== (const TreePostOrderIterator& it) const;
                AnyData::AnyData&            operator*()                                  const;
                AnyData::AnyData*            operator->()                                 const;

                void insertChild(AnyData::AnyData data);
            private:
                std::stack<Node::Node *> nextStepStack_ = std::stack<Node::Node *>(); // The top element is pointer to current node for this iterator
                Node::Node*              head_ = nullptr;

                Node::Node * current() const;
                void goToLeaf();
            };

        private:
            Node::Node * root_ = nullptr;

        };
    }
}

#endif //TREESERIALIZETESTTASK_TREE_H
