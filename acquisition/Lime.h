
# ifndef LIME_H
# define LIME_H

#include <SoapySDR/Device.h>
#include <SoapySDR/Formats.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <complex.h>
#include <string>

class Lime
{
	size_t length;
	void validateCommand(int, std::string);
 	SoapySDRStream *rxStream;
	std::complex<short>* Rx_buff;
	size_t Rx_buff_len;
 	int flags; //flags set by receive operation
 	long long timeNs; //timestamp for receive buffer

	public:
	SoapySDRDevice *sdr;
	Lime(void);
	~Lime(void);
	void setSampleRateRx(size_t, double);
	double getSampleRateRx(size_t);
	void setSampleRateTx(size_t, double);
	double getSampleRateTx(size_t);
	void setFrequencyRx(size_t, double);
	double getFrequencyRx(size_t);
	void setFrequencyTx(size_t, double);
	double getFrequencyTx(size_t);
	void setAntennaRx(size_t, const char*);
	std::string getAntennaRx(size_t);
	void setAntennaTx(size_t, const char*);
	std::string getAntennaTx(size_t);
	void setGainRx(size_t, double);
	double getGainRx(size_t);
	void setGainTx(size_t, double);
	double getGainTx(size_t);
	void listStreamFormatsRx(size_t);

	void streamRx(size_t, std::complex<short>*);
	void setupStreamRx(std::complex<short>*, size_t);
	void closeStreamRx(void);
	int readStreamRx(void);

};

# endif

