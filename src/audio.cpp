#include "raylib.h"
#include "audio.h"

Music bg_wind;
void load_sounds()
{
    bg_wind = LoadMusicStream("resources/audio/wind2.wav");
}
//Music bg_wind = LoadMusicStream("resources/audio/wind2.ogg");

void play_bg_music()
{
    PlayMusicStream(bg_wind);
    //if (!IsMusicStreamPlaying(bg_wind)) PlayMusicStream(bg_wind);
    //PlayMusicStream(bg_wind);
}