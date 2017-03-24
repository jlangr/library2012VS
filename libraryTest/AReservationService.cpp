#include "gmock/gmock.h"

#include "ReservationService.h"
#include "ComputerService.h"
#include "PrinterService.h"

using namespace testing;

class MockPrinterService : public PrinterService
{
public:
	MOCK_METHOD2(PrintReservationSlip, void(int, int));
};

class MockComputerService : public ComputerService
{
public:
	MOCK_CONST_METHOD0(IsAvailable, bool());
	MOCK_METHOD1(Reserve, int(int));
};

class AReservationService : public Test
{
public:
	ReservationService reservationService;
	MockComputerService mockComputerService;
	MockPrinterService mockPrinterService;

	static const int PatronId{ 1 };

	void SetUp() {
		reservationService.SetComputerService(&mockComputerService);
		reservationService.SetPrinterService(&mockPrinterService);
	}
};

TEST_F(AReservationService, ReservesComputerForPatronWhenAvailable)
{
	EXPECT_CALL(mockComputerService, IsAvailable()).WillOnce(Return(true));
	EXPECT_CALL(mockComputerService, Reserve(PatronId)); 

	reservationService.ReserveComputer(PatronId);
}

TEST_F(AReservationService, PrintsReservationSlipOnReserve)
{
	auto computerId{ 10 };
	EXPECT_CALL(mockComputerService, IsAvailable()).WillOnce(Return(true));
	EXPECT_CALL(mockComputerService, Reserve(PatronId)).WillOnce(Return(computerId));
	EXPECT_CALL(mockPrinterService, PrintReservationSlip(PatronId, computerId)); 

	reservationService.ReserveComputer(PatronId);
}

TEST_F(AReservationService, DoesNotReserveComputerForPatronWhenNoneAvailable)
{
	EXPECT_CALL(mockComputerService, IsAvailable()).WillOnce(Return(false));
	EXPECT_CALL(mockComputerService, Reserve(PatronId)).Times(0);

	reservationService.ReserveComputer(PatronId);
}