#include <GAME/serialize/FileSigner.hpp>

void FileSigner::makeSign(std::fstream& fs) {
	fs.seekp(0, std::ios::end);

	int needBytes = sizeof(int) - ((int)fs.tellp() % sizeof(int));

	while (needBytes > 0) {
		fs.put((char)0);
		needBytes--;
	}

	fs.seekg(0, std::ios::beg);
	int sum = 0;

	while (true) {
		int cur;
		fs.read((char*)&cur, sizeof(int));

		if (fs.eof())
			break;

		sum += cur;
	}

	fs.clear();
	fs.seekp(0, std::ios::end);
	fs.write((char*)&sum, sizeof(int));

	fs.seekg(0, std::ios::beg);
	fs.seekp(0, std::ios::beg);
}

bool FileSigner::checkSign(std::fstream& fs) {
	fs.seekg(0, std::ios::end);

	int test = fs.tellg();

	if ((int)fs.tellg() % sizeof(int) != 0)
		return false;

	int signPosition = (int)fs.tellg() - 4;

	fs.seekg(0, std::ios::beg);
	int sum = 0;
	
	while (fs.tellg() < signPosition) {
		int cur;
		fs.read((char*)&cur, sizeof(int));
		sum += cur;
	}

	int checkSum;
	fs.read((char*)&checkSum, sizeof(int));

	fs.seekg(0, std::ios::beg);

	return sum == checkSum && !fs.rdstate();
}