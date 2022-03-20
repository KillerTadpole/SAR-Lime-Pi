
#include <armadillo>
#include <iostream>
#include <fstream>
#include <signal.h>

std::ofstream outfile;

void my_handler(int signum)
{
	outfile.close();
	printf("Caught signal %d\n",signum);
	exit(1); 
}

int main(void)
{
	signal (SIGINT,my_handler);
	outfile.open("data.dat", std::ios::binary);

	int buff_size = 10;
	std::complex<short> buffer[buff_size];

	for (int i = 0; i < 10; i++)
	{
		buffer[i] = {1, 6};
	}
outfile.write(reinterpret_cast<const char*>(&buffer), sizeof(std::complex<short>)*buff_size);
	while(1);
}








