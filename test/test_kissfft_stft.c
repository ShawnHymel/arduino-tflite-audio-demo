/**
 * Test real-optimized version of kissfft by computing STFT.
 * 
 * Author: Shawn Hymel
 * Data: February 22, 2020
 * License: Beerware
 */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "kiss_fftr.h"

// Example waveform with raw 16-bit audio samples
#include "stop_mono_16k.h"

int main(void) 
{
    // STFT parameters
    int nfft = 256;
    int hop = 128;

    // Buffers for kissfft
    kiss_fftr_cfg  kiss_fftr_state;
    kiss_fft_scalar rin[nfft+2];
    kiss_fft_cpx sout[nfft];

    // Init buffer for kiss_fft
    kiss_fftr_state = kiss_fftr_alloc(nfft,0,0,0);

    // Do STFT
    for (int slice = 0; (slice * hop) + nfft < waveform_len; slice++)
    {
        // Fill input buffer with Hanning-windowed raw values
        for (int i = 0; i < nfft; i++)
        {
            rin[i] = (float)waveform[(slice * hop) + i] * 
                        0.5 * (1 - cos(2 * M_PI * i / (nfft - 1)));
        }

        // Do real-optimized FFT
        kiss_fftr(kiss_fftr_state, rin, sout);

        // Print FFT Real results
        for (int i = 0; i < (nfft / 2) + 1; i++) 
        {
            printf("%.2f", fabs((float)sout[i].r));
            if (i < (nfft / 2)) 
            {
                printf(", ");
            }
        }
        printf("\n");
    }

    // Free up buffers
    free(kiss_fftr_state);

    return 0;
}