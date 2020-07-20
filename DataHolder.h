#ifndef TREESERIALIZETESTTASK_DATAHOLDER_H
#define TREESERIALIZETESTTASK_DATAHOLDER_H

#include "ICloneable.h"



namespace Sukhinsky {
    namespace DataHolder  {
        //using Sukhinsky::STANDART_STRING_DELIMETER;
        template <typename T>
        class DataHolder : ICloneable::ICloneable { // Template class DataHolder used for saving data of any type           *
        public:                                     // with defined default constructor, operator= and operator <<(ostream&)*
            DataHolder(const T & data = T()) : data_(data) {}
            DataHolder(const DataHolder & other) : data_(other.data_) {}

            ICloneable*   clone()                  const { return new DataHolder(*this); }
            std::ostream& show(std::ostream & out) const { out << data_; return out; }
            std::string   name()                   const { return typeid(data_).name(); } // Unsafe. Implementation depends on the compiler version
        private:
            T data_;
        };

        template <>
        class DataHolder<std::string> : ICloneable::ICloneable {  // String template specialization ( just for "show" method )
        public:
            DataHolder(const std::string & data = std::string()) : data_(data) {}
            DataHolder(const DataHolder & other) : data_(other.data_) {}

            ICloneable*   clone()                  const { return new DataHolder(*this); }
            std::ostream& show(std::ostream & out) const { out << '\"' << data_ << '\"'; return out; }
            std::string   name()                   const { return typeid(data_).name(); } // Unsafe. Implementation depends on the compiler version
        private:
            std::string data_;
        };

    }
}

#endif //TREESERIALIZETESTTASK_DATAHOLDER_H