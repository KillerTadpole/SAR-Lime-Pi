
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
	SoapySDRDevice *sdr;
	void validateCommand(int, std::string);

	public:
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

		void streamRx(size_t, std::complex<float>*);
};

# endif

