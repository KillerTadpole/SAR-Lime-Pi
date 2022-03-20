
#include <armadillo>
#include <iostream>
#include <fstream>


int main(void)
{
	std::ofstream outfile;
	outfile.open("data.dat", std::ios::binary);

	int buff_size = 10;
	std::complex<short> buffer[buff_size];

	for (int i = 0; i < 10; i++)
	{
		buffer[i] = {3, 6};
//		outfile.write(reinterpret_cast<const char*>(&buffer[i]), sizeof(std::complex<short>));
	}
outfile.write(reinterpret_cast<const char*>(&buffer), sizeof(std::complex<short>)*buff_size);
	outfile.close();
}








