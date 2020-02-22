/**
 * Nano 33 BLE Audio Capture
 * Author: Shawn Hymel
 * Date: February 9, 2020
 * 
 * Capture 1 second of audio using PDM and spit raw values
 * out to Serial. Upload and open Serial monitor. Enter any
 * value to start recording.
 * 
 * License: Beerware
 */

#include <PDM.h>

// Pins
const int led_pin = LED_BUILTIN;

// Settings
const int sample_rate = 16000;
const int samples_to_read = 16000;

// Globals
short sample_buffer[samples_to_read + 1000];
int16_t throwaway_buffer[256];
volatile int samples_read;
volatile int idx;
byte is_recording;

void setup() {

  // Set up pins
  pinMode(led_pin, OUTPUT);

  // Pour a bowl of serial
  Serial.begin(115200);
  while(!Serial);
  delay(100);
  
  // configure the data receive callback
  PDM.onReceive(onPDMdata);

  // Initialize PDM with 1 channel and 16 kHz sampling
  if (!PDM.begin(1, sample_rate)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }

  is_recording = 0;
}

void loop() {

  char c;
  
  // Wait for button to be pressed
  Serial.println("Press Send button to record");
  while (!Serial.available());
  while (Serial.available()) {
    c = Serial.read();
  }
  Serial.println("Recording...");

  // Reset counter and recording flag
  idx = 0;
  is_recording = 1;
  
  // wait for samples to be read
  digitalWrite(led_pin, HIGH);
  while (idx < samples_to_read) {
    if (samples_read) {
  
      // print samples to the serial monitor
      /*for (int i = 0; i < samples_read; i++) {
        Serial.println(samples_read);
      }*/

      // Increment our counter
      //idx += samples_read;
  
      // clear the read count
      samples_read = 0;
    }
  }
  is_recording = 0;
  digitalWrite(led_pin, LOW);
  Serial.print("Samples read: ");
  Serial.println(idx);
  
  // Print samples
  for (int i = 0; i < samples_to_read; i++) {
    Serial.print(sample_buffer[i]);
    if (i < samples_to_read - 1) {
      Serial.print(", ");
    }
  }
  Serial.println();
  Serial.println();
  Serial.println("--------------------------");
}

void onPDMdata() {
  
  // Get number of bytes available to be read
  int bytes_available = PDM.available();

  // read into the sample buffer
  if (is_recording) {
    PDM.read(&sample_buffer[idx], bytes_available);
  } else {
    PDM.read(throwaway_buffer, bytes_available);
  }

  // 16-bit, 2 bytes per sample
  samples_read = bytes_available / 2;
  idx += samples_read;
}
