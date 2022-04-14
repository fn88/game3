#include "raylib.h"
#include "audio.h"

Music music[1];
Sound sounds[6];

void load_sounds()
{
    music[0] = LoadMusicStream("resources/audio/windogg.ogg");;

    sounds[0] = LoadSound("resources/audio/stick_swing1.ogg");
    sounds[1] = LoadSound("resources/audio/stick_swing2.ogg");
    sounds[2] = LoadSound("resources/audio/stick_swing3.ogg");
    sounds[3] = LoadSound("resources/audio/stick_swing4.ogg");
    sounds[4] = LoadSound("resources/audio/stick_hit1.ogg");
    sounds[5] = LoadSound("resources/audio/stick_hit2.ogg");
}

void play_bg_music()
{
    PlayMusicStream(music[0]);
    UpdateMusicStream(music[0]);
}

void update_audio()
{
    play_bg_music();
}
