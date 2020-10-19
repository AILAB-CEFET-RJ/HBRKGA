#include "FWChrono.h"

void FWChrono::start() {
	startTime = getMilliCount();
}

void FWChrono::stop() {
	stopTime = ((double) getMilliSpan() / 1000);
}

double FWChrono::span() {
	return ((double) getMilliSpan() / 1000);
}

double FWChrono::getMilliSpan() {
	int nSpan = getMilliCount() - startTime;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

int FWChrono::getMilliCount() {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}
