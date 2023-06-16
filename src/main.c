#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "Synth.h"

typedef struct s_Oscillator
{
	float phase;
	float phase_stride;
	float phase_stride2;
}	Oscillator;

void updateOsc(Oscillator *osc)
{
	osc->phase += osc->phase_stride;
	if (osc->phase >= 1.0f)
		osc->phase -= 1.0f;
}

#include <time.h>

void updateSignal(Oscillator *osc, float *signal)
{
	float x = ((float)rand()/(float)(RAND_MAX));
	float y = ((float)rand()/(float)(RAND_MAX));
	

	for (size_t t = 0; t < STREAM_BUFFER_SIZE; t++)
	{
		updateOsc(osc);	
		/*Sqr*/  // signal[t] = (PI * osc->phase) * (PI *  osc->phase);
		/*Sin*/ // signal[t] = sinf(2.0f * osc->phase * PI);
		/*RANDOM_1*/ // signal[t] = sinf(PI * osc->phase + cosf(276));
		/*RANDOM_2*/ // signal[t] = cosf(PI * osc->phase + sinf(PI * osc->phase) / 30);
		/*RANDOM_3*/  signal[t] = tanf(PI * osc->phase + 250 + sinf(PI * osc->phase));
		/*RANDOM_4*/ // signal[t] = cosf(2.0f * PI * osc->phase);
		// if (t % 2)
		// 	signal[t] = sinf(PI * osc->phase + (tanf(cosf(45))));
		// else
		 	//signal[t] = cosf(PI * osc->phase + 250 + sinf(PI * osc->phase));
	}
}

int main(void)
{
	InitWindow(1024, 700, "Synth");
	SetTargetFPS(60);
	InitAudioDevice();




	float signal[STREAM_BUFFER_SIZE];

	// float **signal = malloc(sizeof(float*) * 2);
	// for (int i = 0; i < 2; i++)
	// {
	// 	signal[i] = malloc(sizeof(float) * STREAM_BUFFER_SIZE);
	// 	for (int j = 0; j < STREAM_BUFFER_SIZE; j++)
	// 		signal[i][j] = 0.0f;
	// }	


	float frequency = 128.0f;
	unsigned int sample_rate = SAMPLE_RATE; // how many time in a secound it takes a sample
	float sample_duration = (1.0f / sample_rate);

	Oscillator osc;
	osc.phase = 0.0f;
	osc.phase_stride = frequency * sample_duration;

	// Low Frequency Oscillator
	Oscillator lfo;
	lfo.phase = 0.0f;
	lfo.phase_stride = 1000.0f * sample_duration;
	SetAudioStreamBufferSizeDefault(STREAM_BUFFER_SIZE);
	AudioStream as = LoadAudioStream(sample_rate, 32, 1);
	AudioStream as1 = LoadAudioStream(sample_rate, 32, 1);
	SetAudioStreamVolume(as, 0.9f);
	SetAudioStreamVolume(as1, 0.9f);
	PlayAudioStream(as);

	SynthKey keys[13];

	kInit(keys);

	float frequency2 = 252.0f;
	int m = 0;

	while (!WindowShouldClose())
	{
		if (IsAudioStreamProcessed(as))
		{
			// updateOsc(&lfo);
			
			// frequency = 320.0f + (sinf(2.0f * PI * lfo.phase) * 25.0f) / 2;

			osc.phase_stride = frequency * sample_duration;
			updateSignal(&osc, signal);
			UpdateAudioStream(as, signal, STREAM_BUFFER_SIZE);
		}
		kInputHandle(keys, &frequency);
		if (IsKeyPressed(KEY_Z))
			kPitchShiftDown(keys);
		if (IsKeyPressed(KEY_X))
			kPitchShiftUp(keys);

		BeginDrawing();
		ClearBackground(BLACK);
		Vector2 signal_points[STREAM_BUFFER_SIZE];
		Vector2 signal_points2[STREAM_BUFFER_SIZE];
		Vector2 signal_points3[STREAM_BUFFER_SIZE];
		for (size_t i = 0; i < STREAM_BUFFER_SIZE; i++)
		{
			signal_points[i].x = (float) i;
			signal_points[i].y = (float) (350) + (int )(signal[i] * 100);
			signal_points2[i].x = (float) i + 1;
			signal_points2[i].y = (float) (350) + (int )(signal[i] * 100) + 1;
			signal_points3[i].x = (float) i + 2;
			signal_points3[i].y = (float) (350) + (int )(signal[i] * 100) + 2;
		}
		DrawLineStrip(signal_points, STREAM_BUFFER_SIZE, BLUE);
		DrawLineStrip(signal_points2, STREAM_BUFFER_SIZE, BLUE);
		DrawLineStrip(signal_points3, STREAM_BUFFER_SIZE, BLUE);
		DrawText(TextFormat("FREQ: { %f }", frequency), 150, 100, 40, BLUE);
		EndDrawing();
	}
	CloseWindow();
	CloseAudioDevice();
}
