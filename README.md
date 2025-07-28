# Math Quiz Alarm ⏰🧮

A simple Arduino project that acts as an alarm clock, which can only be turned off by solving math multiplication questions using a keypad.

---

## Description
This project uses an Arduino, LCD display, keypad, and buzzer to create an alarm that forces you to solve **3 random multiplication questions** correctly to stop the alarm sound.

---

## Functions Breakdown
| Function            | What It Does                                              |
|---------------------|----------------------------------------------------------|
| `setup()`            | Initializes LCD, keypad, random seed.                    |
| `loop()`             | Runs the main program loop using a **State Machine**.    |
| `timerClock()`       | Handles countdown timer and triggers alarm when done.    |
| `generateQuestion()` | Randomizes two numbers and displays the multiplication question. |
| `getAnswer()`        | Reads keypad input, checks answer correctness.           |
| `waitForKey(char)`   | Pauses program until specific key is pressed.            |

---

## How It Works
1. **Timer counts down from 10 seconds**.
2. When timer hits zero:
   - Buzzer starts ringing.
   - LCD shows a random multiplication question.
3. User inputs the answer using the **keypad**.
4. If correct, score increases. After **3 correct answers**, the alarm turns off.
5. LCD displays a “Congrats” message.

The program uses a **State Machine** to switch between:
- Alarm Mode (countdown)
- Quiz Mode (answer questions)
- Congrats Mode (alarm off)

---

## How to Use
1. Upload the code to your Arduino.
2. Power the Arduino (USB or 6x AA Batteries).
3. When timer reaches 0, buzzer will ring.
4. Use the keypad to input the correct answer and press `#` to submit.
5. After 3 correct answers, alarm will stop.

---

## Components Required
- Arduino Uno / Nano (Any microcontroller)
- 16x2 LCD Display
- 4x4 Membrane Keypad
- Active Buzzer
- Jumper Wires, Breadboard
- Power Source (USB or 6x AA Batteries)

---

## Notes
- Press `*` to clear input if you typed wrong.
- You can adjust timer duration by changing the `seconds` variable.
