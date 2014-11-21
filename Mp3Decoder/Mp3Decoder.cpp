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
	if (this->mPFile == NULL )
	{
		return -1;
	}
	char buf[RAW_ID3_HEADER_SIZE];
	ID3_Header header;

	size_t size = fread_s(buf, RAW_ID3_HEADER_SIZE, RAW_ID3_HEADER_SIZE, 1, this->mPFile);
	if (buf == NULL && size != RAW_ID3_HEADER_SIZE)
	{
		cerr << "Read ID3 Header failed " << endl;
		return -1;
	}

	for (int i = 0; i < 3; i++){
		header.indentify[i] = buf[i];
	}
	header.indentify[3] = 0;

	header.ver_major = buf[3];
	header.ver_minor = buf[4];
	header.flat = buf[5];

	uint32_t s = 0 ;
	for (int i = 0; i < 4; i++)
	{
		s = s << 7;
		s |= buf[6 + i];
	}
	header.size = s;
	//cout << "The ID3 header size is " << header.size <<endl;
	fseek(this->mPFile, header.size, SEEK_CUR);
	return header.size;
}