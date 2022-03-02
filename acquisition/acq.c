
#include "Lime.h"
//#include <armadillo>



int main(void)
{
	std::cout << "\ntest\n\n";
	Lime lime;
	std::cout << "RX Sample rate " << lime.getSampleRateRx(0) << "\n";
	std::cout << "TX Sample rate " << lime.getSampleRateTx(0) << "\n";
	std::cout << "RX Antenna " << lime.getAntennaRx(0) << "\n";
	std::cout << "TX Antenna " << lime.getAntennaTx(0) << "\n";
	std::cout << "RX Gain " << lime.getGainRx(0) << "\n";
	std::cout << "TX Gain " << lime.getGainTx(0) << "\n";
//	lime.listStreamFormatsRx(0);
	lime.setFrequencyRx(0, 2.4e9);
	lime.setAntennaRx(0, "LNAL");
	lime.setGainRx(0, 20);
	int buff_size = 1024;
	std::complex<float> buffer[buff_size];
	lime.streamRx(0, buffer);
	for (int i = 0; i < 20; i++)
	{
	std::cout << buffer[i] << "\n";
	}
}
























