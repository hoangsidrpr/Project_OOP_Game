#include "Sound.h"

void Sound::InGame() 
{
	PlaySound(TEXT("Music/InGame.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

void Sound::CharacterStep() 
{
	PlaySound(TEXT("Music/Step.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::Crash() 
{
	PlaySound(TEXT("Music/CarCrashed.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::Lose() 
{
	PlaySound(TEXT("Music/Lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void Sound::Victory()
{
	PlaySound(TEXT("Music/Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
}