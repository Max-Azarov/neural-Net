#include "logwrite.h"
#include "singleton.h"

#include <memory>

int main()
{
    std::unique_ptr<Synapse> synapse = Singleton::instance().createSynapse();
    LOGWRITE(synapse->getType());
    return 0;
}
