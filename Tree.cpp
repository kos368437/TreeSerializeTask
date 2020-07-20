#include "Tree.h"
#include <sstream>
namespace Sukhinsky {
    namespace Tree {

        Tree::~Tree() {
            Tree::TreePostOrderIterator iter = Tree::TreePostOrderIterator(*this);
            Tree::TreePostOrderIterator end = Tree::TreePostOrderIterator(*this);
            end.end();
            while (iter != end) {
                delete iter.current();
                iter++;
            }
        }

        void Tree::ASCIIVisualisation(std::ostream& out) {
            std::vector<std::string> outBuffer;
            std::stringstream ss;
            auto iter = TreePreOrderIterator(*this);
            auto end = TreePreOrderIterator(*this);
            auto next = TreePreOrderIterator(*this);
            next++;
            end.end();
            while (iter != end) {
                for (auto i : outBuffer) {
                    out << i;
                }
                out << "--" << iter.textValue() << std::endl;


                if(next == end) {
                    next.begin();
                }

                if(iter.isLastChild()) {
                    outBuffer.pop_back();
                    outBuffer.push_back("   ");
                }

                if (iter.hasChildren()) {
                    if(next.isLastChild()) {
                        outBuffer.push_back("  L");
                    }
                    else {
                        outBuffer.push_back("  |");
                    }
                }


                if (next.notAChild(iter.current())) {
                    for(size_t i = iter.TreePreOrderIterator::degreeOfRelation(next); i > 0; i--) {
                        outBuffer.pop_back();
                    }
                }
                if(next.isLastChild()) {
                    outBuffer.pop_back();
                    outBuffer.push_back("  L");
                }

                iter++;
                next++;
            }
        }

        void Tree::serialize(std::ostream& out)  {
            auto iter = TreePreOrderIterator(*this);
            auto end = TreePreOrderIterator(*this);
            auto next = iter;
            next++;
            end.end();
            while (iter != end) {
                out << iter.typeName() << std::endl;
                out << iter.textValue() << std::endl;
                out << '(' << std::endl;
                if (!iter.hasChildren()) {
                    out << ')' << std::endl;
                }

                if(next == end) {
                    next.begin();
                }
                if (next.notAChild(iter.current())) {
                    for(size_t i = iter.TreePreOrderIterator::degreeOfRelation(next); i > 0; i--) {
                        out << ')' << std::endl;
                    }
                }
                iter++;
                next++;
            }
        }

        /////////////////////////////////PreOrder///////////////////////////////////////

        Node::Node * Tree::TreePreOrderIterator::current() const {
            if (nextStepStack_.empty()) return nullptr;
            return nextStepStack_.top();
        }

        void Tree::TreePreOrderIterator::begin() {
            while (!nextStepStack_.empty()) {
                nextStepStack_.pop();
            }
            nextStepStack_.push(head_);
        }
        void Tree::TreePreOrderIterator::end() {
            while (!nextStepStack_.empty()) {
                nextStepStack_.pop();
            }
        }

        Tree::TreePreOrderIterator& Tree::TreePreOrderIterator::operator++ () {
            auto begin = current()->childrenBegin();
            auto end = current()->childrenEnd();
            nextStepStack_.pop();

            while (end != begin) {
                end--;
                nextStepStack_.push(*end);
            }
            return *this;
        }

        Tree::TreePreOrderIterator  Tree::TreePreOrderIterator::operator++ (int) {
            auto temp(*this);
            ++(*this);
            return temp;
        }

        bool Tree::TreePreOrderIterator::operator!= (const TreePreOrderIterator& it) const {
            return (it.current() != this->current());
        }
        bool Tree::TreePreOrderIterator::operator== (const TreePreOrderIterator& it) const {
            return !(it != *this);
        }
        AnyData::AnyData& Tree::TreePreOrderIterator::operator*() const {
            return current()->getData();
        }
        AnyData::AnyData* Tree::TreePreOrderIterator::operator->() const {
            return &(current()->getData());
        }

        void Tree::TreePreOrderIterator::insertChild(AnyData::AnyData data) {
            current()->addChild(new Node::Node(data));
        }

        bool Tree::TreePreOrderIterator::hasChildren() const {
            auto begin = current()->childrenBegin();
            auto end = current()->childrenEnd();
            return  (begin != end);
        }
        bool Tree::TreePreOrderIterator::notAChild(Node::Node * parentCandidate) const {
            auto parent  = current()->getParent();
            return (parent != parentCandidate);
        }
        std::string Tree::TreePreOrderIterator::typeName() const {
            return (*this)->dataTypeName();
        }
        std::string  Tree::TreePreOrderIterator::textValue() const {
            std::stringstream temp;
            temp << *(*this);
            return temp.str();
        }

        bool Tree::TreePreOrderIterator::isLastChild() {
            if (current() == head_) return false;
            Node::Node * child = *(--this->current()->getParent()->childrenEnd());
            return (child == current());
        }

        size_t Tree::TreePreOrderIterator::degreeOfRelation(TreePreOrderIterator const & other) const {
            auto parent = this->current()->getParent();
            auto newParent = other.current()->getParent();
            size_t count = 0;
            if (other.notAChild(this->current())) {
                while (newParent != parent) {
                    count++;
                    parent = parent->getParent();
                }
            }
            return count;
        }

        //////////////////////////////PostOrder////////////////////////////////////////////

        void Tree::TreePostOrderIterator::goToLeaf() {
            auto begin = nextStepStack_.top()->childrenBegin();
            auto end = nextStepStack_.top()->childrenEnd();
            while (nextStepStack_.top()->hasChildren()) {
                while (end != begin) {
                    end--;
                    nextStepStack_.push(*end);
                }
                begin = nextStepStack_.top()->childrenBegin();
                end = nextStepStack_.top()->childrenEnd();
            }
        }

        void Tree::TreePostOrderIterator::begin() {
            while (!nextStepStack_.empty()) {
                nextStepStack_.pop();
            }
            nextStepStack_.push(head_);
            this->goToLeaf();
        }

        void Tree::TreePostOrderIterator::end() {
            while (!nextStepStack_.empty()) {
                nextStepStack_.pop();
            }
        }

        Tree::TreePostOrderIterator& Tree::TreePostOrderIterator::operator++ () {
            auto temp(current());
            nextStepStack_.pop();
            if (!nextStepStack_.empty()) {
                if (nextStepStack_.top() != temp->getParent()) {
                    this->goToLeaf();
                }
            }
            return *this;
        }

        Tree::TreePostOrderIterator  Tree::TreePostOrderIterator::operator++ (int) { //postfix
            auto temp(*this);
            ++(*this);
            return temp;
        }

        bool Tree::TreePostOrderIterator::operator!= (const TreePostOrderIterator& it) const {
            return (it.current() != this->current());
        }

        bool Tree::TreePostOrderIterator::operator== (const TreePostOrderIterator& it) const {
            return !(it != *this);
        }

        AnyData::AnyData& Tree::TreePostOrderIterator::operator*() const {
            return current()->getData();
        }
        AnyData::AnyData* Tree::TreePostOrderIterator::operator->() const {
            return &(current()->getData());
        }

        Node::Node * Tree::TreePostOrderIterator::current() const {
            if (nextStepStack_.empty()) return nullptr;
            return nextStepStack_.top();
        }

        void Tree::TreePostOrderIterator::insertChild(AnyData::AnyData data) {
            auto child = new Node::Node(data);
            current()->addChild(child);
            nextStepStack_.push(child);
            goToLeaf();
        }

    }
}