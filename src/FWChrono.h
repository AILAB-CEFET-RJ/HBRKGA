#ifndef FWOPT_MODULE_MEASUREMENT_FWCHRONO_H_
#define FWOPT_MODULE_MEASUREMENT_FWCHRONO_H_

// SYSTEM LIBRARY
// For chronometer
#include <sys/timeb.h>

class FWChrono {
public:
	// Default constructor
	FWChrono() :
			startTime(0), stopTime(-1) {
	}
	// Destructor
	virtual ~FWChrono() {
	}

	///// OPERATION
	// Start time measurement
	void start();
	// Get final running time
	void stop();
	// Get actual time
	double span();

	///// GETTER
	// Get stop time
	double getStopTime() const {
		return stopTime;
	}

private:
	// Initial time
	double startTime;
	// End time
	double stopTime;

	///// GETTER
	// Get millispan
	double getMilliSpan();
	// Actual time in milliseconds
	int getMilliCount();
};

#endif /* FWOPT_MODULE_MEASUREMENT_FWCHRONO_H_ */
