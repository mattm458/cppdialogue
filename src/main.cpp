#include <SDL3/SDL.h>

#include <PipelineCore/Processor.h>
#include <PipelineExample/StringConsumer.h>
#include <PipelineExample/TextFileProducer.h>

#include <iostream>
#include <string>
#include <thread>

int main() {
    TextFileProducer p("frankenstein.txt");
    StringConsumer c(p);

    p.start();
    c.start();

    while (p.is_running()) {
        std::this_thread::yield();
    }
}

// int main()
// {
//     // Init the SDL audio system
//     if (!SDL_Init(SDL_INIT_AUDIO))
//     {
//         SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
//         return SDL_APP_FAILURE;
//     }

//     Uint8 *wav_data = NULL;
//     Uint32 wav_data_len = 0;

//     // Load a test WAV file
//     SDL_AudioSpec spec;
//     char *wav_path = NULL;
//     SDL_asprintf(&wav_path, "%swav/LJ025-0076.wav", SDL_GetBasePath());
//     if (!SDL_LoadWAV(wav_path, &spec, &wav_data, &wav_data_len))
//     {
//         SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
//         return SDL_APP_FAILURE;
//     }
//     SDL_free(wav_path);

//     // Open the default playback device
//     SDL_AudioStream *stream = NULL;
//     stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
//     &spec, NULL, NULL); if (!stream)
//     {
//         SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
//         return SDL_APP_FAILURE;
//     }

//     // Start the stream
//     SDL_ResumeAudioStreamDevice(stream);

//     // Main loop
//     bool loop = true;
//     int offset = 0;
//     int chunk_size = 4096;
//     while (loop)
//     {
//         // Feed the WAV file into the stream in chunks
//         if (offset < wav_data_len)
//         {
//             int to_copy = std::min(chunk_size, (int)wav_data_len - offset);
//             SDL_PutAudioStreamData(stream, wav_data + offset, to_copy);
//             offset += to_copy;
//         }

//         // Play the stream
//         SDL_GetAudioStreamQueued(stream);

//         // Listen for quit events
//         SDL_Event e;
//         while (SDL_PollEvent(&e))
//         {
//             if (e.type == SDL_EVENT_QUIT)
//             {
//                 loop = false;
//             }
//         }
//     }

//     SDL_DestroyAudioStream(stream);
//     SDL_free(wav_data);
//     SDL_Quit();
// }