#ifndef TREESERIALIZETESTTASK_ICLONEABLE_H
#define TREESERIALIZETESTTASK_ICLONEABLE_H

#include <iostream>
#include <string>

namespace Sukhinsky {
    namespace ICloneable {

        class ICloneable {
        public:
            virtual ~ICloneable() {}

            virtual ICloneable*   clone()              const = 0;
            virtual std::ostream& show(std::ostream &) const = 0;
            virtual std::string   name()               const = 0;
        };

    }
}

#endif //TREESERIALIZETESTTASK_ICLONEABLE_H
