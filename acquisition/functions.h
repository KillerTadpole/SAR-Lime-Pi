
#include <complex.h>
struct SoapySDRDevice* connectToLime(void);
void DeviceInfo(struct SoapySDRDevice *sdr);
void Close(struct SoapySDRDevice *sdr2);


 void Read_1024_samples(struct SoapySDRDevice *sdr, double freq, std::complex<float> *buffer)
 {
 	// check freq is within range
 	if (freq <10e3)
 	{
 	freq = 10e3;
 	printf("Frequency out of range setting min: \n");
 	}
 	if (freq >3.8e9)
 	{
 	freq = 3.8e9;
 	printf("Frequency out of range setting max: \n");
 	}
 	//apply settings
 	if (SoapySDRDevice_setSampleRate(sdr, SOAPY_SDR_RX, 0, 1e6) != 0)
 	{
 	printf("setSampleRate fail: %s\n", SoapySDRDevice_lastError());
 	}
 	if (SoapySDRDevice_setAntenna(sdr, SOAPY_SDR_RX, 0, "LNAL") != 0)
 	{
 	printf("setAntenna fail: %s\n", SoapySDRDevice_lastError());
 	}
 	if (SoapySDRDevice_setGain(sdr, SOAPY_SDR_RX, 0, 20) != 0)
 	{
 	printf("setGain fail: %s\n", SoapySDRDevice_lastError());
 	}
 	if (SoapySDRDevice_setFrequency(sdr, SOAPY_SDR_RX, 0, freq, NULL) != 0)
 	{
 	printf("setFrequency fail: %s\n", SoapySDRDevice_lastError());
 	}
 	//setup a stream (std::complex floats)
 	SoapySDRStream *rxStream;
 	if (SoapySDRDevice_setupStream(sdr, &rxStream, SOAPY_SDR_RX, SOAPY_SDR_CF32, NULL, 0, NULL) != 0)
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



void Close(struct SoapySDRDevice *sdr)
{
	//cleanup device handle
	SoapySDRDevice_unmake(sdr);
	printf("Done\n\n\n");
	//return EXIT_SUCCESS;
	}

void DeviceInfo(struct SoapySDRDevice *sdr)
{
	size_t length;
	//query device info
 	char** names = SoapySDRDevice_listAntennas(sdr, SOAPY_SDR_RX, 0, &length);
 	printf("Rx antennas: ");
 	for (size_t i = 0; i < length; i++) printf("%s, ", names[i]);
 	printf("\n");
 	SoapySDRStrings_clear(&names,length);
 	names = SoapySDRDevice_listGains(sdr, SOAPY_SDR_RX, 0, &length);
 	printf("Rx gains: ");
 	for (size_t i = 0; i < length; i++) printf("%s, ", names[i]);
 	printf("\n");
 	SoapySDRStrings_clear(&names, length);
 	SoapySDRRange *ranges = SoapySDRDevice_getFrequencyRange(sdr, SOAPY_SDR_RX, 0, &length);
 	printf("Rx freq ranges: ");
 	for(size_t i = 0; i < length; i++) printf("[%g Hz -> %g Hz], ", ranges[i].minimum, ranges[i].maximum);
 	printf("\n");
 	free(ranges);
}

struct SoapySDRDevice* connectToLime(void)
{
	size_t length;
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
// 	SoapySDRKwargsList_clear(args, length);
 	//create device instance
	SoapySDRDevice *sdr = SoapySDRDevice_make(args);
	SoapySDRKwargs_clear(args);
	if (sdr == NULL)
	{
		printf("SoapySDRDevice_make fail: %s\n", SoapySDRDevice_lastError());
	}
	return sdr;
}



























