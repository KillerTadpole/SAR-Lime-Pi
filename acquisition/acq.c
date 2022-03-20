
#include "Lime.h"
#include <fstream>
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
	size_t freq = 2.4e9;
	lime.setSampleRateRx(0, 6e7);
	lime.setSampleRateTx(0, 6e7);
	lime.listStreamFormatsRx(0);
	lime.setFrequencyRx(0, freq);
	lime.setAntennaRx(0, "LNAL");
	lime.setGainRx(0, 20);
	
	std::ofstream outfile;
	outfile.open("data.dat");

	int buff_size = 1024;
	std::complex<short> buffer[buff_size];
	lime.streamRx(0, buffer);
	for (int i = 0; i < 10; i++)
	{
	outfile << buffer[i];
	}
	outfile.close();
}
























