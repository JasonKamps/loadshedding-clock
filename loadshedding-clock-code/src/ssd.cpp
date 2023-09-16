#include "ssd.h"

// common annode seven-segment display and BCD driver pins
const int BCD_A = 23;
const int BCD_B = 5;
const int BCD_C = 17;
const int BCD_D = 15;
const int LT = 16;      // lamp test
const int BI_RBO = 4;   // blanking input, ripple blanking output
const int RBI = 2;      // ripple blanking input
const int DIGIT_0 = 18; // leftmost digit
const int DIGIT_1 = 19;
const int DIGIT_2 = 3;
const int DIGIT_3 = 1; // rightmost digit

int currentDigit = 0;

void setupSSD()
{
    // set pin modes
    pinMode(BCD_A, OUTPUT);
    pinMode(BCD_B, OUTPUT);
    pinMode(BCD_C, OUTPUT);
    pinMode(BCD_D, OUTPUT);
    pinMode(LT, OUTPUT);
    pinMode(BI_RBO, OUTPUT);
    pinMode(RBI, OUTPUT);
    pinMode(DIGIT_0, OUTPUT);
    pinMode(DIGIT_1, OUTPUT);
    pinMode(DIGIT_2, OUTPUT);
    pinMode(DIGIT_3, OUTPUT);

    // activate all digits
    digitalWrite(DIGIT_0, HIGH);
    digitalWrite(DIGIT_1, HIGH);
    digitalWrite(DIGIT_2, HIGH);
    digitalWrite(DIGIT_3, HIGH);

    // lamp test
    digitalWrite(LT, LOW);
    digitalWrite(BI_RBO, HIGH);
    delay(1000);

    // stop lamp test
    digitalWrite(LT, HIGH);
    digitalWrite(DIGIT_0, LOW);
    digitalWrite(DIGIT_1, LOW);
    digitalWrite(DIGIT_2, LOW);
    digitalWrite(DIGIT_3, LOW);
}

/**
 * Display a number on the seven segment display.
 *
 * @param number The number to display (0-9).
 * @param digit The digit to display the number on (0-3). 0 is the leftmost digit.
 */
void displayNumber(int number, int digit)
{
    if (number < 0 || number > 9)
    {
        // invalid number
        digitalWrite(DIGIT_0, LOW);
        digitalWrite(DIGIT_1, LOW);
        digitalWrite(DIGIT_2, LOW);
        digitalWrite(DIGIT_3, LOW);
        return;
    }

    // convert number to binary coded decimal
    boolean bcd[4];
    for (int i = 0; i < 4; i++)
    {
        bcd[i] = (number >> i) & 0x01;
    }

    // activate the digit
    boolean digits[4] = {LOW, LOW, LOW, LOW};
    digits[digit] = HIGH;
    digitalWrite(DIGIT_0, digits[0]);
    digitalWrite(DIGIT_1, digits[1]);
    digitalWrite(DIGIT_2, digits[2]);
    digitalWrite(DIGIT_3, digits[3]);

    // set the digit value
    digitalWrite(BCD_A, bcd[0]);
    digitalWrite(BCD_B, bcd[1]);
    digitalWrite(BCD_C, bcd[2]);
    digitalWrite(BCD_D, bcd[3]);
}

//**
// * Display countdown on the seven segment display.
// *
// * Only a single digit is displayed at a time. This function should be called repeatedly to display all digits.
// * Digits are automatically cycled. 250 Hz is the recommended calling frequency.
// *
// * @param secondsUntilNextTransition The number of seconds until the next transition.
// */
void displayCountdown(int secondsUntilNextTransition)
{
    if (secondsUntilNextTransition > 0)
    {
        // convert seconds to hour value and minute value
        int hoursUntilNextEvent = secondsUntilNextTransition / 3600;
        int minutesUntilNextEvent = (secondsUntilNextTransition % 3600) / 60;

        // extract digits
        int firstDigitOfHourValue = hoursUntilNextEvent / 10;
        int secondDigitOfHourValue = hoursUntilNextEvent % 10;
        int firstDigitOfMinuteValue = minutesUntilNextEvent / 10;
        int secondDigitOfMinuteValue = minutesUntilNextEvent % 10;

        // remove leading zeros
        if (firstDigitOfHourValue == 0)
        {
            firstDigitOfHourValue = -1;
        }
        if (firstDigitOfMinuteValue == 0)
        {
            firstDigitOfMinuteValue = -1;
        }

        // display digits
        int digitValues[4] = {firstDigitOfHourValue, secondDigitOfHourValue, firstDigitOfMinuteValue, secondDigitOfMinuteValue};

        displayNumber(digitValues[currentDigit], currentDigit);
        currentDigit = (currentDigit + 1) % 4;
    }
    else
    {
        // no loadshedding expected today
        digitalWrite(DIGIT_0, LOW);
        digitalWrite(DIGIT_1, LOW);
        digitalWrite(DIGIT_2, LOW);
        digitalWrite(DIGIT_3, LOW);
    }
}