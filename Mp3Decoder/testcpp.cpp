#include "Mp3Decoder.h"
#include <iostream>

#include <boost/scoped_ptr.hpp>
using namespace std
;

int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		cerr << "Please input the mp3 file to decode " << endl;
		exit(EXIT_FAILURE);
	}

	boost::scoped_ptr<Mp3Decoder> decoder(new Mp3Decoder(argv[1]));
	if ( decoder->Open())
	{
		exit(EXIT_FAILURE);
	}

	cout << "Open " << argv[1] << " success , length (" << decoder->getFIleLength() << ")" << endl;
}