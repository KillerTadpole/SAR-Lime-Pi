
#include "Lime.h"

Lime::Lime(void)
{
	SoapySDRKwargs *args = SoapySDRDevice_enumerate(NULL, &length);
	for (size_t i = 0; i < length; i++)
	{
		printf("Found device #%d: ", (int)i);
		for (size_t j = 0; j < args[i].size; j++)
		{
			printf("%s=%s, ", args[i].keys[j], args[i].vals[j]);
		}
	printf("\n");
	}
 	//create device instance
	sdr = SoapySDRDevice_make(args);
 	SoapySDRKwargsList_clear(args, length);
	if (sdr == NULL)
	{
		printf("SoapySDRDevice_make fail: %s\n", SoapySDRDevice_lastError());
	}
}

Lime::~Lime(void)
{
	SoapySDRDevice_unmake(sdr);
}

void Lime::setSampleRateRx(size_t chan, double rate)
{
 	int rtn = SoapySDRDevice_setSampleRate(sdr, SOAPY_SDR_RX, chan, rate);
	Lime::validateCommand(rtn, "setSampleRateRX fail: ");
}

//----------------------- Setters and Getters ---------------------------

double Lime::getSampleRateRx(size_t chan)
{
 	return SoapySDRDevice_getSampleRate(sdr, SOAPY_SDR_RX, chan);
}

void Lime::setSampleRateTx(size_t chan, double rate)
{
 	int rtn = SoapySDRDevice_setSampleRate(sdr, SOAPY_SDR_TX, chan, rate);
	Lime::validateCommand(rtn, "setSampleRateTX fail: ");
}

double Lime::getSampleRateTx(size_t chan)
{
 	return SoapySDRDevice_getSampleRate(sdr, SOAPY_SDR_TX, chan);
}

void Lime::setFrequencyRx(size_t chan, double freq)
{
 	int rtn = SoapySDRDevice_setFrequency(sdr, SOAPY_SDR_RX, chan, freq, NULL);
	Lime::validateCommand(rtn, "setFrequencyRX fail: ");
}

double Lime::getFrequencyRx(size_t chan)
{
 	return SoapySDRDevice_getSampleRate(sdr, SOAPY_SDR_RX, chan);
}

void Lime::setFrequencyTx(size_t chan, double freq)
{
 	int rtn = SoapySDRDevice_setFrequency(sdr, SOAPY_SDR_TX, chan, freq, NULL);
	Lime::validateCommand(rtn, "setFrequencyTx fail: ");
}

double Lime::getFrequencyTx(size_t chan)
{
 	return SoapySDRDevice_getSampleRate(sdr, SOAPY_SDR_TX, chan);
}

void Lime::setAntennaRx(size_t chan, const char* ant)
{
 	int rtn = SoapySDRDevice_setAntenna(sdr, SOAPY_SDR_RX, chan, ant);
	Lime::validateCommand(rtn, "setAntennaRX fial: ");
}

std::string Lime::getAntennaRx(size_t chan)
{
	return SoapySDRDevice_getAntenna(sdr, SOAPY_SDR_RX, chan);
}

void Lime::setAntennaTx(size_t chan, const char* ant)
{
 	int rtn = SoapySDRDevice_setAntenna(sdr, SOAPY_SDR_TX, chan, ant);
	Lime::validateCommand(rtn, "setAntennaTX fail: ");
}

std::string Lime::getAntennaTx(size_t chan)
{
	return SoapySDRDevice_getAntenna(sdr, SOAPY_SDR_TX, chan);
}

void Lime::setGainRx(size_t chan, double gain)
{
	int rtn = SoapySDRDevice_setGain(sdr, SOAPY_SDR_RX, chan, gain);
	Lime::validateCommand(rtn, "setGainRX fail: ");
}

double Lime::getGainRx(size_t chan)
{
	return SoapySDRDevice_getGain(sdr, SOAPY_SDR_RX, chan);
}

void Lime::setGainTx(size_t chan, double gain)
{
	int rtn = SoapySDRDevice_setGain(sdr, SOAPY_SDR_TX, chan, gain);
	Lime::validateCommand(rtn, "setGainTX fail: ");
}

double Lime::getGainTx(size_t chan)
{
	return SoapySDRDevice_getGain(sdr, SOAPY_SDR_TX, chan);
}

void Lime::listStreamFormatsRx(size_t chan)
{
 	char** names = SoapySDRDevice_getStreamFormats(sdr, SOAPY_SDR_RX, chan, &length);
 	printf("Rx stream formats: ");
 	for (size_t i = 0; i < length; i++) printf("%s, ", names[i]);
 	printf("\n");
 	SoapySDRStrings_clear(&names,length);
}


//----------------------- Setters and Getters ---------------------------

//------------------------- Streaming ------------------------------

void Lime::streamRx(size_t chan, std::complex<short>* buffer)
{
       	SoapySDRDevice_setupStream(sdr, &rxStream, SOAPY_SDR_RX, SOAPY_SDR_CS16, NULL, 0, NULL);
 	if (rxStream == NULL)
 	{
		printf("setupStream fail: %s\n", SoapySDRDevice_lastError());
 	}
 	SoapySDRDevice_activateStream(sdr, rxStream, 0, 0, 0); //start streaming
 	void *buffs[] = {buffer}; //array of buffers
 	int flags; //flags set by receive operation
 	long long timeNs; //timestamp for receive buffer
 	int ret = SoapySDRDevice_readStream(sdr, rxStream, buffs, 1024, &flags, &timeNs, 100000);
 	//shutdown the stream
 	SoapySDRDevice_deactivateStream(sdr, rxStream, 0, 0); //stop streaming
 	SoapySDRDevice_closeStream(sdr, rxStream);
}

void Lime::setupStreamRx(std::complex<short>* buffer, size_t buffer_len)
{
	Rx_buff_len = buffer_len;
 	Rx_buff = buffer;
       	SoapySDRDevice_setupStream(sdr, &rxStream, SOAPY_SDR_RX, SOAPY_SDR_CS16, NULL, 0, NULL);
 	if (rxStream == NULL)
 	{
		printf("setupStream fail: %s\n", SoapySDRDevice_lastError());
 	}
 	SoapySDRDevice_activateStream(sdr, rxStream, 0, 0, 0); //start streaming
}

void Lime::closeStreamRx(void)
{
 	//shutdown the stream
 	SoapySDRDevice_deactivateStream(sdr, rxStream, 0, 0); //stop streaming
 	SoapySDRDevice_closeStream(sdr, rxStream);
}

int Lime::readStreamRx()
{
	void *buffs[50] = {Rx_buff}; //array of buffers
 	int ret = SoapySDRDevice_readStream(sdr, rxStream, buffs, Rx_buff_len, &flags, &timeNs, 100000);
	return ret;
}

//------------------------- Streaming ------------------------------

void Lime::validateCommand(int rtn, std::string error_msg)
{
	if (rtn != 0)
	{
		std::cout << error_msg << SoapySDRDevice_lastError() << "\n";
	}
}

// void Read_1024_samples(struct SoapySDRDevice *sdr, double freq, complex float *buffer)
// {
// 	// check freq is within range
// 	if (freq <10e3)
// 	{
// 	freq = 10e3;
// 	printf("Frequency out of range setting min: \n");
// 	}
// 	if (freq >3.8e9)
// 	{
// 	freq = 3.8e9;
// 	printf("Frequency out of range setting max: \n");
// 	}
// 	//apply settings
// 	if (SoapySDRDevice_setSampleRate(sdr, SOAPY_SDR_RX, 0, 1e6) != 0)
// 	{
// 	printf("setSampleRate fail: %s\n", SoapySDRDevice_lastError());
// 	}
// 	if (SoapySDRDevice_setAntenna(sdr, SOAPY_SDR_RX, 0, "LNAL") != 0)
// 	{
// 	printf("setAntenna fail: %s\n", SoapySDRDevice_lastError());
// 	}
// 	if (SoapySDRDevice_setGain(sdr, SOAPY_SDR_RX, 0, 20) != 0)
// 	{
// 	printf("setGain fail: %s\n", SoapySDRDevice_lastError());
// 	}
// 	if (SoapySDRDevice_setFrequency(sdr, SOAPY_SDR_RX, 0, freq, NULL) != 0)
// 	{
// 	printf("setFrequency fail: %s\n", SoapySDRDevice_lastError());
// 	}
// 	//setup a stream (complex floats)
// 	SoapySDRStream *rxStream;
// 	if (SoapySDRDevice_setupStream(sdr, &rxStream, SOAPY_SDR_RX, SOAPY_SDR_CF32, NULL, 0, NULL) != 0)
// 	{
// 	printf("setupStream fail: %s\n", SoapySDRDevice_lastError());
// 	}
// 	SoapySDRDevice_activateStream(sdr, rxStream, 0, 0, 0); //start streaming
// 	void *buffs[] = {buffer}; //array of buffers
// 	int flags; //flags set by receive operation
// 	long long timeNs; //timestamp for receive buffer
// 	int ret = SoapySDRDevice_readStream(sdr, rxStream, buffs, 1024, &flags, &timeNs, 100000);
// 	//shutdown the stream
// 	SoapySDRDevice_deactivateStream(sdr, rxStream, 0, 0); //stop streaming
// 	SoapySDRDevice_closeStream(sdr, rxStream);
// 	}






