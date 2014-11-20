#include "Mp3Decoder.h"
#include <iostream>

int Mp3Decoder::Open()
{
	errno_t ret =  fopen_s(&this->mPFile, this->mFileName.c_str(), "rb");
	if ( ret != 0 )
	{
		std::cerr << "Open " << this->mFileName << " failed (" << ret << ")" << std::endl;
		return -1;
	}

	fseek(this->mPFile, 0, SEEK_END);
	this->mFileLen = ftell(this->mPFile);
	fseek(this->mPFile, 0, SEEK_SET);

	return 0;		
}

int Mp3Decoder::SkipIDV3Header()
{
	return 0;
}