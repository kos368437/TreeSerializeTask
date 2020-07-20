#include "AnyData.h"
#include <algorithm>
#include <sstream>

namespace Sukhinsky {
    namespace AnyData {

        AnyData::AnyData(const AnyData & other) {
            dataHolder_ = nullptr;
            if ( (&other) != nullptr )  {
                if (other.dataHolder_ != nullptr) dataHolder_ = (other.dataHolder_)->clone();
            }
        }

        void AnyData::swap(AnyData &other) {
            std::swap(dataHolder_, other.dataHolder_);
        }

        AnyData& AnyData::operator=(const AnyData & other) {
            if (this != &other) AnyData(other).swap(*this);
            return *this;
        }

        std::ostream& operator<<(std::ostream & out, const AnyData & data)  {
            return data.dataHolder_->show(out);
        }

        std::string AnyData::showData() const {
            std::stringstream ss;
            dataHolder_->show(ss);
            return ss.str();
        }


        template <typename T>
        T * AnyData::cast() {
            auto * tempPtr = dynamic_cast<DataHolder::DataHolder <T> *>(this->dataHolder_);
            if (tempPtr != nullptr)
                return &tempPtr->data_;
            return nullptr;
        }

    }
}