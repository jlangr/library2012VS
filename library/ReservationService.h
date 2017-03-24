#pragma once

#include "ComputerService.h"
#include "PrinterService.h"

class ReservationService {
public:
	void SetComputerService(ComputerService* computerService)
	{
		_computerService = computerService;
	}

	void SetPrinterService(PrinterService* printerService)
	{
		_printerService = printerService;
	}

	void ReserveComputer(int patronId)
	{
		if (_computerService->IsAvailable()) {
			int computerId = _computerService->Reserve(patronId);
			_printerService->PrintReservationSlip(patronId, computerId);
		}
	}

private:
	ComputerService* _computerService;
	PrinterService* _printerService;
};