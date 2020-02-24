/**
 * Test real-optimized version of kissfft.
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
    int slice = 30;
    int nfft = 256;
    kiss_fftr_cfg  kiss_fftr_state;
    kiss_fft_scalar rin[nfft+2];
    kiss_fft_cpx sout[nfft];

    int start_idx = slice * nfft;

    // Print first set of raw samples
    printf("Empty buffer:\r\n");
    for (int i = 0; i < nfft; i++) 
    {
        printf("%i", sout[i]);
        if (i < nfft - 1) 
        {
            printf(", ");
        }
    }
    printf("\r\n");

    // Print first set of raw samples
    printf("First %i samples\r\n", nfft);
    for (int i = 0; i < nfft; i++) 
    {
        printf("%i", waveform[start_idx + i]);
        if (i < nfft - 1) 
        {
            printf(", ");
        }
    }
    printf("\r\n");
    
    // Init buffer for kiss_fft
    kiss_fftr_state = kiss_fftr_alloc(nfft,0,0,0);

    // Fill input buffer with Hanning windowed raw values
    for (int i = 0; i < nfft; i++)
    {
        rin[i] = waveform[start_idx + i] * 
                    0.5 * (1 - cos(2 * M_PI * i / (nfft - 1)));
    }

    // Do real-optimized FFT
    kiss_fftr(kiss_fftr_state, rin, sout);

    // Print FFT Real results
    printf("FFT Real\r\n");
    for (int i = 0; i < (nfft / 2) + 1; i++) 
    {
        printf("%i", abs(sout[i].r));
        if (i < (nfft / 2)) 
        {
            printf(", ");
        }
    }
    printf("\r\n");

    // Free up buffers
    free(kiss_fftr_state);

    return 0;
}