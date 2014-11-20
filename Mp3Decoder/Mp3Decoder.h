#include<string>
using namespace std;
#include <cstdio>

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