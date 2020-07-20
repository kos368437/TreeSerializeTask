#ifndef TREESERIALIZETESTTASK_ISERIALIZABLE_H
#define TREESERIALIZETESTTASK_ISERIALIZABLE_H

#include <string>

namespace Sukhinsky {
    namespace Serialize {

        class ISerializable {
        public:
            virtual void serialize(std::ostream&) = 0;
        };

    }
}
#endif //TREESERIALIZETESTTASK_ISERIALIZABLE_H
