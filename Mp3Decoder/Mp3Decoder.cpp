#include "Mp3Decoder.h"
#include <iostream>
#include <assert.h>

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

int Mp3Decoder::ReadFrame(Frame_Header *frameHeader)
{
	assert(frameHeader != NULL);
	
	char buf[4];

	size_t size = fread_s(buf, 4, 4, 1, this->mPFile);
	if (buf == NULL && size != 4)
	{
		cerr << "Read ID3 Header failed " << endl;
		return -1;
	}
	frameHeader->sync = (buf[1] & 0x07) << 8 | (0xff & buf[0]);
	frameHeader->version = (buf[1] & 0x18) >> 3;
	frameHeader->lay = (buf[1] & 0x06) >> 1;
	frameHeader->protection = buf[1] & 0x01;

	frameHeader->bitrate_index = (buf[2] & 0xf0) >> 4;
	frameHeader->sampling_ferq = (buf[2] & 0x0C) >> 2;
	frameHeader->padding = (buf[2] & 0x02) & 0x01;
	frameHeader->extension = buf[2] & 0x01;

	frameHeader->mode = (buf[3] & 0xC0) >> 6;
	frameHeader->mode_ext = (buf[3] & 0x30) >> 4;
	frameHeader->copyright = (buf[3] & 0x08) >> 3;
	frameHeader->original = (buf[3] & 0x04) >> 2;
	frameHeader->emphasis = buf[3] & 0x03;
	return 0;
}