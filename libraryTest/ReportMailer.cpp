#include "gmock/gmock.h"
#include "ReportMailer.h"
#include "MailDestination.h"
#include "Report.h"

#include <vector>

using namespace testing;
using namespace std;

TEST(AReportMailer, CanConstructMailMessage)
{
	auto toAddress{ "jeff@example.com" };
	Report report;
	ReportMailer::ConstructMailMessageStatic(toAddress, report);
}