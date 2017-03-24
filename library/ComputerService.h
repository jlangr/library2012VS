#pragma once

class ComputerService
{
public:
	virtual bool IsAvailable() const = 0;
	virtual int Reserve(int patronId) = 0;
};
