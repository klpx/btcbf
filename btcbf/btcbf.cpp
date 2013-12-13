// btcbf.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

std::vector<std::string> wantedKeys;
bool isWantedKey(std::string s);
double timeCheckpoint(void);

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Reading input file: ";
	std::ifstream wantedKeysFile("targets-500.txt");
	if (!wantedKeysFile.good()) {
		std::cout << "no such file\n";
		return -1;
	}
	else {
		std::cout << "Ok\n";
	}
	std::string line;
	while (wantedKeysFile >> line) {
		wantedKeys.push_back(line);
	}
	std::cout << wantedKeys.size() << " keys got.\n";

	unsigned int keysToGenerate;
	std::cout << "Keys to test: ";
	std::cin >> keysToGenerate;


	for (int threads = 1; threads < 8; threads++) {
		unsigned long int keysGenerated = 0;
		double timeDiff;

		omp_set_num_threads(threads);
		timeCheckpoint();
		#pragma omp parallel
		{
			while (true) {
				CKey key;
				key.MakeNewKey(false);
				CPubKey pubkey = key.GetPubKey();
				CPrivKey privkey = key.GetPrivKey();

				#pragma omp atomic
				keysGenerated++;

				if (keysGenerated > keysToGenerate) break;
			}
			//std::cout << "Address: " << pubkey.GetID().ToString() << "\n";
			//std::cout << "Private key: (" << privkey.size() << ") ";
			//std::cout << std::hex;
			//for (int i = 0; i != privkey.size(); i++) {
			//	 std::cout << std::hex << (int) privkey[i];
			//}
			//std::cout << CBitcoinAddress(pubkey.GetID()).ToString() << "\n";
		}
		std::cout << threads << " thread(s): " << (double)keysGenerated / timeCheckpoint() << " kps\n";
	}

	//std::string test("1FfmbHfnpaZjKFvyi1okTjJJusN455paPH");
	//std::cout << test << " is " << (isWantedKey(test) ? "" : "not ") << "present.\n";

	/*
	std::cout << "Start working\n";
	omp_set_num_threads(8);
	#pragma omp parallel nowait
	{

	}
	*/
	return 0;
}

bool isWantedKey(std::string key) {
	for (std::vector<int>::size_type i = 0; i != wantedKeys.size(); i++) {
		if (wantedKeys[i] == key) {
			return true;
		}
	}
	return false;
}

double timeCheckpoint() {
	static clock_t prev_clock= 0;
	clock_t curr_clock = clock();
	double diff = curr_clock - prev_clock;
	prev_clock = curr_clock;
	return diff/CLOCKS_PER_SEC;
}