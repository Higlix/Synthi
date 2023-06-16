#ifndef SSYNTH_H
# define SSYNTH_H

# define STREAM_BUFFER_SIZE 2048
# define SAMPLE_RATE 44100

# define kSYNTH_COUNT 13

typedef struct s_SynthKey
{
	int		kID;
	float	kFreq;
	float	kWavelength;
}	SynthKey;

/* MAIN.C */

/* KEY.C */
int		kInit(SynthKey *keys);

void	kPitchShiftUp(SynthKey *keys);
void	kPitchShiftDown(SynthKey *keys);
void	kInputHandle(SynthKey *keys, float *freq);



#endif