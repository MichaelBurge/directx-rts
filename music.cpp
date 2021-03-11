// music.cpp: implementation of the music class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

music::music()
{
	current=0;
	::CoInitialize(NULL);
	::CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC, IID_IDirectMusicPerformance8, (void **)&directmusic);
	directmusic->InitAudio(NULL, NULL, NULL, DMUS_APATH_SHARED_STEREOPLUSREVERB, 64, DMUS_AUDIOF_ALL, NULL);
	::CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, IID_IDirectMusicLoader8,(void **)&loader);
}

music::~music()
{
	if (directmusic)
	{
		directmusic->CloseDown();
		directmusic->Release();
		directmusic = NULL;
	}
	if (loader)
	{
		loader->Release();
		loader = NULL;
	}
}
int music::LoadMusic(unsigned short *file,int repeat,_GUID type) {
	IDirectMusicSegment8 *segment = NULL;
	HRESULT h;
	if (SUCCEEDED(h=loader->LoadObjectFromFile(CLSID_DirectMusicSegment, IID_IDirectMusicSegment8, file, (void **) &segment)))


    if (SUCCEEDED(h=segment->SetParam(type, 0xFFFFFFFF, DMUS_SEG_ALLTRACKS, 0, NULL)))
	if (SUCCEEDED(h=segment->SetRepeats(repeat)))
	if (FAILED(segment->Download(directmusic)))
		MessageBox(NULL,"Couldn't download music to sound card",NULL,NULL);else;else
		MessageBox(NULL,"Couldn't set music repeat",NULL,NULL);else
		MessageBox(NULL,"Couldn't set music parameters",NULL,NULL);else
		MessageBox(NULL,"Couldn't load music",NULL,NULL);
	themusic.push_back(segment);
	return current++;
}

void music::PlayMusic(int music) {
	directmusic->PlaySegment(themusic[music], DMUS_SEGF_AFTERPREPARETIME, 0, NULL);
}
void music::StopMusic() {
	directmusic->Stop(NULL,NULL,0,0);
}