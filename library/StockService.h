#pragma once

#include <string>

class StockService
{
public:
    virtual unsigned int CurrentPrice(const std::string& symbol)=0;
};