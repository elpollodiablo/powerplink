#include "Arduino.h"
#include <EEPROM.h>

/* MQ Sensors */
#define NAME_A0 "C1"
#define SAMPLES_A0 5
#define LOW_A0 3500
#define HIGH_A0 3900
#define TICKS_PER_COUNT_A0 6
#define WH_PER_COUNT_A0 10

/*#define NAME_A1 "C2"
#define SAMPLES_A1 10
#define NAME_A2 "C3"
#define SAMPLES_A2 10
#define NAME_A3 "C4"
#define SAMPLES_A3 10
#define NAME_A4 "C5"
#define SAMPLES_A4 10
//#define NAME_A5 "C6"
//#define SAMPLES_A0 10
//#define NAME_A6 "MQ138"
//#define SAMPLES_A0 10
*/

int led_state = LOW;
float wph;

#ifdef NAME_A0
  int last_val_a0;
  int val_a0 = 0;
  int ticks_a0 = 0;
  unsigned long last_count_a0 = 0;
  unsigned long count_duration_a0;
#endif
#ifdef NAME_A1
  int val_a1 = 0;
#endif
#ifdef NAME_A2
  int val_a2 = 0;
#endif
#ifdef NAME_A3
  int val_a3 = 0;
#endif
#ifdef NAME_A4
  int val_a4 = 0;
#endif
#ifdef NAME_A5
  int val_a5 = 0;
#endif
#ifdef NAME_A6
  int val_a6 = 0;
#endif

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(115200);

#ifdef NAME_A0
  pinMode(A0, INPUT);
#endif
#ifdef NAME_A1
  pinMode(A1, INPUT);
#endif
#ifdef NAME_A2
  pinMode(A2, INPUT);
#endif
#ifdef NAME_A3
  pinMode(A3, INPUT);
#endif
#ifdef NAME_A4
  pinMode(A4, INPUT);
#endif
#ifdef NAME_A5
  pinMode(A5, INPUT);
#endif
#ifdef NAME_A6
  pinMode(A6, INPUT);
#endif
  digitalWrite(13, LOW);
  delay(1000);
}

void send_result_int(const char pin_name[], int val) {
  Serial.print(pin_name);
  Serial.print(":");
  Serial.println(val);
}

int get_analog_val(int pin_analog, int sample_no) {
  double analog_val = 0;

  // create an average from 100 samples
  for(int i = 0; i < sample_no; i++) { 
    analog_val = analog_val + (float) analogRead(pin_analog);
  }

  analog_val = analog_val / sample_no;

  // convert to millivolts
  analog_val = (ceil)(analog_val / 1025 * 5000.0);

  return ceil(analog_val);
}

void loop()
{
#ifdef NAME_A0
  val_a0 = get_analog_val(A0, SAMPLES_A0);
  if ((val_a0 > HIGH_A0) && (last_val_a0 < LOW_A0)) {
    ticks_a0 ++;
    if (ticks_a0 == TICKS_PER_COUNT_A0) {
      send_result_int(NAME_A0, WH_PER_COUNT_A0);
      ticks_a0 = 0;
      if (last_count_a0 != 0) {
        count_duration_a0 = millis() - last_count_a0;
        wph = (WH_PER_COUNT_A0 * 3600000) / count_duration_a0;
        send_result_int("C1_Wph", round(wph));
      }
      last_count_a0 = millis();

    }
    led_state = led_state ? LOW : HIGH;
    digitalWrite(13, led_state);
  }
  // we're not interested in the values in between
  if (!((val_a0 > LOW_A0) && (val_a0 < HIGH_A0))) {
    last_val_a0 = val_a0;
  }
  //send_result_int("deb", val_a0);

#endif
#ifdef NAME_A1
  digitalWrite(13, HIGH);
  val_a1 = get_analog_val(A1, SAMPLES_A1);
  send_result_int(NAME_A1, val_a1);
#endif
#ifdef NAME_A2
  digitalWrite(13, LOW);
  val_a2 = get_analog_val(A2, SAMPLES_A2);
  send_result_int(NAME_A2, val_a2);
#endif
#ifdef NAME_A3
  digitalWrite(13, HIGH);
  val_a3 = get_analog_val(A3, SAMPLES_A3);
  send_result_int(NAME_A3, val_a3);
#endif
#ifdef NAME_A4
  digitalWrite(13, LOW);
  val_a4 = get_analog_val(A4, SAMPLES_A4);
  send_result_int(NAME_A4, val_a4);
#endif
#ifdef NAME_A5
  digitalWrite(13, HIGH);
  val_a5 = get_analog_val(A5, SAMPLES_A5);
  send_result_int(NAME_A5, val_a5);
#endif
#ifdef NAME_A6
  digitalWrite(13, LOW);
  val_a6 = get_analog_val(A6, SAMPLES_A6);
  send_result_int(NAME_A6, val_a6);
#endif
}

