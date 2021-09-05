#ifndef NETCOACH_H
#define NETCOACH_H

#include <vector>


#include "types.h"


namespace Neural {

class INetHolder;



//==============================================
class INetCoacher
//==============================================
{
public:
    virtual void training() = 0;

public:
    virtual ~INetCoacher() {}
};



//==============================================
class NetCoacherRefSet : public INetCoacher
//==============================================
{
public:
    void training() override;

public:
    NetCoacherRefSet( INetHolder* netHolder,
                    const coachContainer_t&  trainingSet,
                    const coachContainer_t&  idealOut)
        : p_netHolder( netHolder)
        , c_trainingSet( trainingSet)
        , c_idealOut( idealOut)
    {}

private:
    INetHolder* p_netHolder;
    const coachContainer_t&  c_trainingSet;
    const coachContainer_t&  c_idealOut;
};


} // namespace Neural

#endif // NETCOACH_H
