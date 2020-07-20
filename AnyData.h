#ifndef TREESERIALIZETESTTASK_ANYDATA_H
#define TREESERIALIZETESTTASK_ANYDATA_H

#include "DataHolder.h"

namespace Sukhinsky {
    namespace AnyData {

        class AnyData { // Class AnyData used for saving any ICloneable data holder
        public:
             AnyData() {}
             AnyData(const AnyData &);
             template <typename T>  AnyData(const T & data) : dataHolder_( DataHolder::DataHolder<T>(data).clone() ) {}
            ~AnyData() { delete dataHolder_; }

            void     swap(AnyData &other);

            AnyData&      operator=(const AnyData &);
            friend std::ostream& operator<<(std::ostream &, AnyData const &);

            std::string dataTypeName() const { return dataHolder_->name(); }
            std::string showData()     const;
            template <typename T>
            T * cast(); //This method returns pointer to saved data or nullptr, if T isn't an original type of data

        private:
            ICloneable::ICloneable * dataHolder_ = nullptr;
        };

    }
}

#endif //TREESERIALIZETESTTASK_ANYDATA_H
