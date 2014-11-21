#include<string>
using namespace std;
#include <cstdio>
#include <cstdint>

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

	int getFIleLength(){ return this->mFileLen; }
private:
	string mFileName;
	FILE *mPFile;

	int mFileLen;
};

struct ID3_Header
{
	char indentify[4];
	char ver_major;
	char ver_minor;
	char flat;
	uint32_t size;
};

static const uint8_t RAW_ID3_HEADER_SIZE = 10;