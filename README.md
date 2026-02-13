# Quiz Program in C

This is a **console-based quiz** written in **C**. The quiz adapts its difficulty based on your answers and keeps track of high scores with a leaderboard.

---

## Features

- **Adaptive Difficulty:**  
  The quiz increases the difficulty for correct answers and decreases it for wrong answers (Easy → Medium → Hard).  

- **Randomized Questions:**  
  Each quiz round selects **10 random questions** from the pool of Easy, Medium, and Hard questions.  

- **Limited Attempts:**  
  Each participant can attempt the quiz a maximum of **5 times**.  

- **Leaderboard:**  
  Scores and attempts are saved in `leaderboard.txt` and displayed after each quiz.  

---

## File Structure

- `main.c` – The main quiz program.  
- `leaderboards.c` / `leaderboards.h` – Functions to handle the leaderboard.  
- `getanswer.c` / `getanswer.h` – Handles user input validation.  
- `easy.txt`, `medium.txt`, `hard.txt` – Question banks for different difficulty levels.  
- `README.md` – This file.

---

## How to Compile and Run

If you are using **GCC**:

```bash
gcc *.c -o quiz.exe

.\quiz.exe

