#include "Synth.h"
#include "raylib.h"

#include <stdio.h>

void	kPitchShiftDown(SynthKey *keys)
{
	if ((keys[0].kFreq / 2) < 16.35)
		return ;
	for (int i = 0; i < kSYNTH_COUNT; i++)
		keys[i].kFreq /= 2;
}

void	kPitchShiftUp(SynthKey *keys)
{
	if ((keys[0].kFreq * 2) > 4186.01)
		return ;
	for (int i = 0; i < kSYNTH_COUNT; i++)
		keys[i].kFreq *= 2;
}

void	kInputHandle(SynthKey *keys, float *freq)
{
	for (int i = 0; i < kSYNTH_COUNT; i++)
	{
		if (IsKeyPressed(keys[i].kID) || IsKeyDown(keys[i].kID))
		{
			printf("%f\n", keys[i].kFreq);
			(*freq) = keys[i].kFreq;
		}
		// else
		// 	(*freq) = 0.0f;
	}
}

int	kInit(SynthKey *keys)
{
		/* C */
	keys[0].kFreq = 16.35;
	keys[0].kID = KEY_A;
	keys[0].kWavelength = 2109.89;

		/* c# / d^B */
	keys[1].kFreq = 17.32;
	keys[1].kID = KEY_W;
	keys[1].kWavelength = 1991.47;

		/* D */
	keys[2].kFreq = 18.35;
	keys[2].kID = KEY_S;
	keys[2].kWavelength = 1879.69;

		/* d# / e^B*/
	keys[3].kFreq = 19.45;
	keys[3].kID = KEY_E;
	keys[3].kWavelength = 1774.20;

		/**/
	keys[4].kFreq = 20.60;
	keys[4].kID = KEY_D;
	keys[4].kWavelength = 1674.62;

		/**/
	keys[5].kFreq = 21.83;
	keys[5].kID = KEY_F;
	keys[5].kWavelength = 1580.63;

		/**/
	keys[6].kFreq = 23.12;
	keys[6].kID = KEY_T;
	keys[6].kWavelength = 1491.91;

		/**/
	keys[7].kFreq = 24.50;
	keys[7].kID = KEY_G;
	keys[7].kWavelength = 1408.18;

		/**/
	keys[8].kFreq = 25.96;
	keys[8].kID = KEY_Y;
	keys[8].kWavelength = 1329.24;

		/**/
	keys[9].kFreq = 27.50;
	keys[9].kID = KEY_H;
	keys[9].kWavelength = 1254.55;

		/**/
	keys[10].kFreq = 29.14;
	keys[10].kID = KEY_U;
	keys[10].kWavelength = 1184.13;

		/**/
	keys[11].kFreq = 30.87;
	keys[11].kID = KEY_J;
	keys[11].kWavelength = 1117.76;

	keys[11].kFreq = 30.87;
	keys[11].kID = KEY_J;
	keys[11].kWavelength = 1117.76;

	keys[12].kFreq = 32.70;
	keys[12].kID = KEY_K;
	keys[12].kWavelength = 1054.94;
	return (0);
}
