
#include "Lime.h"
#include <fstream>
#include <signal.h>
#include <cmath>
//#include <armadillo>

std::ofstream outfile;
std::ofstream logg;
Lime lime;

void my_handler(int signum)
{
	outfile.close();
	logg.close();
	lime.closeStreamRx();
	printf("\nCaught signal %d\n",signum);
	exit(signum); 
}

int main(void)
{
	signal (SIGINT,my_handler); // define a handler for stoping the program

	std::cout << "RX Sample rate " << lime.getSampleRateRx(0) << "\n";
	std::cout << "TX Sample rate " << lime.getSampleRateTx(0) << "\n";
	std::cout << "RX Antenna " << lime.getAntennaRx(0) << "\n";
	std::cout << "TX Antenna " << lime.getAntennaTx(0) << "\n";
	std::cout << "RX Gain " << lime.getGainRx(0) << "\n";
	std::cout << "TX Gain " << lime.getGainTx(0) << "\n";
	size_t freq = 2.45e9;
	lime.setSampleRateRx(0, 6e7);
//	lime.setSampleRateTx(0, 6e7);
	lime.listStreamFormatsRx(0);
	lime.setFrequencyRx(0, freq);
	lime.setAntennaRx(0, "LNAH");
	lime.setGainRx(0, 20);
	
	outfile.open("../sar_processing/data/data.dat", std::ios::binary);
	logg.open("acq_log.txt");

	size_t buff_size = std::pow(2, 16);
	std::complex<short> buffer[buff_size];
	lime.setupStreamRx(buffer, buff_size);
	int ret;
	int cnt = 0;
	int max_cnt = 10;
	std::cout << "capturing!!!\n";
	while(1)
	{
		ret = lime.readStreamRx();
		logg << ret << "\n";
//		if (cnt >= 10)
//		{
//			outfile.write(reinterpret_cast<const char*>(&buffer), sizeof(std::complex<short>)*ret);
//			cnt = 0;
//			logg << ret << "\n";
//		}
//		else
//		{
//			cnt++;
//		}
	}
}
























