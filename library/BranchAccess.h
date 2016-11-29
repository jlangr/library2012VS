#pragma once

#include "boost/shared_ptr.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Persistence.h"

class Branch;

class BranchAccess
{
public:
    BranchAccess();
    explicit BranchAccess(boost::shared_ptr<Persistence<Branch>> persister);
    virtual ~BranchAccess();

    static std::string DataFileName();

    bool Find(Branch&) const;
    int Size() const;
    bool ExistsWithName(const std::string& name) const;
    void Save(Branch&);
    void DeleteAll();

private:
    boost::shared_ptr<Persistence<Branch>> mPersister;
};
