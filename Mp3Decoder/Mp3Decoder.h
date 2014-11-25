#include<string>
using namespace std;
#include <cstdio>
#include <cstdint>

struct Frame_Header
{
	uint16_t sync;
	uint8_t version;
	uint8_t lay;
	uint8_t protection;
	uint8_t bitrate_index;
	uint8_t sampling_ferq;
	uint8_t padding;
	uint8_t extension;
	uint8_t mode;
	uint8_t mode_ext;
	uint8_t copyright;
	uint8_t original;
	uint8_t emphasis;
};

struct ID3_Header
{
	char indentify[4];
	char ver_major;
	char ver_minor;
	char flat;
	uint32_t size;
};

class Mp3Decoder{
public:
	Mp3Decoder(string filename) :
		mFileName(filename),mFileLen(0) {}

	~Mp3Decoder()
	{
		if (mPFile != NULL )
		{
			fclose(mPFile);
			mPFile = NULL;
		}
	}

	int Open();
	int SkipIDV3Header();
	int ReadFrame(Frame_Header *frameHeader);

	int getFIleLength(){ return this->mFileLen; }
private:
	string mFileName;
	FILE *mPFile;

	int mFileLen;
};



static const uint8_t RAW_ID3_HEADER_SIZE = 10;