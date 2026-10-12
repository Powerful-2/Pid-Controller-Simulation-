# Engineering Board (C++)

A menu-driven C++ console program that solves three engineering problems, plus a standalone PID simulation. Built for IME 307 (Computer Programming) at Yaba College of Technology.

## Contents

- [What it does](#what-it-does)
- [Files](#files)
- [What you need](#what-you-need)
- [Set up (Windows)](#set-up-windows)
- [Set up (Linux or macOS)](#set-up-linux-or-macos)
- [Get the code](#get-the-code)
- [Compile and run](#compile-and-run)
- [How to use each module](#how-to-use-each-module)
- [Input rules](#input-rules)
- [Standalone PID program](#standalone-pid-program)
- [Troubleshooting](#troubleshooting)
- [What I learned](#what-i-learned)

## What it does

| Menu option | Module                    | You enter                                   | You get                                                                                  |
| ----------- | ------------------------- | ------------------------------------------- | ---------------------------------------------------------------------------------------- |
| 1           | PID controller simulation | setpoint, starting value, number of steps   | a table with error, P, I, D terms, and control output for each step                      |
| 2           | RLC circuit AC impedance  | R, L, C, frequency                          | step-by-step working for angular frequency, reactances, impedance, and phase angle       |
| 3           | Pipe friction loss        | length, diameter, velocity, friction factor | step-by-step head loss using the Darcy-Weisbach equation: `h_f = f * (L/D) * (v^2 / 2g)` |
| 4           | Exit                      | none                                        | closes the program                                                                       |

The PID module uses Kp = 1.5, Ki = 0.5, Kd = 0.1, and a time step of 0.1 s.

## Files

| File                    | Purpose                                                   |
| ----------------------- | --------------------------------------------------------- |
| `engineering_board.cpp` | Main program with the menu and all three modules          |
| `pid_robot.cpp`         | Standalone PID simulation with fixed settings (150 steps) |
| `README.md`             | This guide                                                |
| `.gitignore`            | Stops compiled `.exe` files from being uploaded           |

## What you need

- A C++ compiler (g++). Instructions below.
- Git, only if you want to download the code with `git clone`. You can also download the ZIP from GitHub (green **Code** button, then **Download ZIP**).
- About 600 MB of free disk space on Windows for the compiler.

Tested on Windows with MSYS2 UCRT64 and g++ 15.2.0.
Not tested on macOS.

## Set up (Windows)

1. Download and install MSYS2 from https://www.msys2.org/ using the default settings.
2. Open **MSYS2 UCRT64** from the Start menu. It is a black terminal window. Use the **UCRT64** one, not MSYS or MINGW64.
3. Install the compiler (type `Y` and press Enter when asked):
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```
   The download is about 70 MB and can take several minutes on a slow connection.
   Messages such as "failed retrieving file ... too slow" can appear. If the install then continues and finishes, it is fine.
4. Check that it worked:
   ```bash
   g++ --version
   ```
   You should see a version number. If you see "command not found", close the window and open a new **MSYS2 UCRT64** window.

## Set up (Linux or macOS)

- **Ubuntu or Debian:** `sudo apt install g++`
- **macOS:** run `xcode-select --install` (this installs a C++ compiler)

Check with `g++ --version`.

## Get the code

**Option A: Git**

```bash
git clone https://github.com/Powerful-2/Pid-Controller-Simulation-.git
```

**Option B: ZIP.** On the GitHub page, click **Code**, then **Download ZIP**, and unzip it.

## Compile and run

Run these one line at a time. Press Enter after each line.

**Windows (MSYS2 UCRT64 window):**

```bash
cd /c/path/to/Pid-Controller-Simulation-
ls
g++ engineering_board.cpp -o engineering_board.exe
./engineering_board.exe
```

Replace `/c/path/to/` with where you saved the folder. A folder at `C:\cpp_project\Pid-Controller-Simulation-` becomes `/c/cpp_project/Pid-Controller-Simulation-`. Use `/` slashes, not `\`.

`ls` should list `engineering_board.cpp`. If it does not, you are in the wrong folder.

**Linux or macOS:**

```bash
cd Pid-Controller-Simulation-
g++ engineering_board.cpp -o engineering_board
./engineering_board
```

When compiling, nothing is printed if it succeeds. The `-o` in the command is the lowercase letter **o**, not the number zero.

## How to use each module

Start the program and type a number from 1 to 4, then press Enter.

### Option 1: PID simulation

Enter `100`, then `0`, then `10`. You should see this:

```
Step | Error     | P-Term    | I-Term    | D-Term    | Control Output
---------------------------------------------------------------------
   1 |       100 |       150 |         5 |       100 |            255
   2 |        -2 |        -3 |       4.9 |      -102 |         -100.1
   3 |     38.04 |     57.06 |     6.802 |     40.04 |        103.902
   4 |   -3.5208 |   -5.2812 |   6.62596 |  -41.5608 |        -40.216
   5 |   12.5656 |   18.8484 |   7.25424 |   16.0864 |        42.1891
   6 |  -4.31002 |  -6.46502 |   7.03874 |  -16.8756 |       -16.3019
   7 |   2.21075 |   3.31613 |   7.14928 |   6.52077 |        16.9862
   8 |  -4.58372 |  -6.87558 |   6.92009 |  -6.79447 |       -6.74995
   9 |  -1.88374 |   -2.8256 |    6.8259 |   2.69998 |        6.70028
  10 |  -4.56385 |  -6.84577 |   6.59771 |  -2.68011 |       -2.92817
```

The simulated position overshoots the target and then swings above and below it. The error is still about 4.6 after 10 steps. Use more steps (for example 30) to see it settle.

### Option 2: RLC impedance

Enter `10`, `0.1`, `0.0001`, `50` (R in ohms, L in henries, C in farads, frequency in Hz). Expected results:

```
X_L = 31.4159 Ohms
X_C = 31.831 Ohms
X_total = -0.415062 Ohms
|Z| = 10.0086 Ohms
theta = -2.37677 degrees
```

Check by hand: X_C = 1 / (314.159 x 0.0001) = 31.83 ohm. This circuit is close to resonance at 50 Hz, so |Z| is almost equal to R.

### Option 3: Pipe friction loss

Enter `100`, `0.1`, `2`, `0.02` (length in m, diameter in m, velocity in m/s, friction factor). Expected result:

```
h_f = 0.02 * 1000 * (4 / 19.62) = 4.07747 meters of fluid
```

### Option 4: Exit

Type `4` to close the program.

## Input rules

| Where                         | Rule                                                         | What happens if broken                                                    |
| ----------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------------------- |
| Menu                          | Enter 1, 2, 3, or 4                                          | Letters or other numbers show "Invalid choice" and the menu appears again |
| PID steps                     | A whole number, at least 1                                   | Message "Invalid input" and back to the menu                              |
| RLC capacitance and frequency | Greater than 0                                               | Message "Invalid input" and back to the menu                              |
| Pipe diameter                 | Greater than 0                                               | Message "Invalid input" and back to the menu                              |
| All numbers                   | Digits only, using a dot for decimals (for example `0.0001`) | Message "Invalid input" and back to the menu                              |

Units are not converted. Enter all values in the units shown in the prompts.

## Standalone PID program

`pid_robot.cpp` runs one fixed PID simulation with no input: setpoint 100 cm, 150 steps of 0.1 s, Kp 1.60, Ki 0.40, Kd 0.12. It prints every 10th step, then the final position, the overshoot, and a status line calculated from the result.

```bash
g++ pid_robot.cpp -o pid_robot.exe
./pid_robot.exe
```

Expected last lines:

```
Final position: 100.36 cm | Final error: -0.36 cm
Peak position: 112.34 cm | Overshoot: 12.34 cm
STATUS: Settled within 1 cm of the target.
```

## Troubleshooting

| Message or problem                            | Cause                                                       | Fix                                                                                                                                                                                |
| --------------------------------------------- | ----------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `g++: command not found`                      | Compiler is not installed, or you are in the wrong terminal | Follow the setup steps. On Windows, use the **MSYS2 UCRT64** window. The VS Code PowerShell terminal does not find g++ unless `C:\msys64\ucrt64\bin` is added to the Windows PATH. |
| `unrecognized command-line option '-0'`       | Typed a zero instead of the letter o                        | Use `-o` (lowercase letter o)                                                                                                                                                      |
| `No such file or directory` for the .cpp file | You are in the wrong folder, or the file name is different  | Run `ls` and check that the file is listed. Rename files like `engineering_board (1).cpp` to `engineering_board.cpp`.                                                              |
| `cd: too many arguments`                      | Several commands were pasted on one line                    | Enter each command separately. Folder names with spaces need quotes: `cd "/c/my folder"`                                                                                           |
| `Move-Item: command not found`                | A PowerShell command was typed in the MSYS2 window          | In MSYS2, use `mv` instead                                                                                                                                                         |
| `./engineering_board.exe: No such file`       | The compile step failed or was skipped                      | Run the `g++` line again and read any error it prints                                                                                                                              |
| `pacman` cannot find or download the package  | Slow or blocked connection                                  | Run `pacman -Syu`, reopen the window if it asks, then try again                                                                                                                    |
| Program appears to freeze                     | It is waiting for your input                                | Read the last prompt and type a value                                                                                                                                              |
| Press `Ctrl + C` to stop                      |                                                             | Stops any running program                                                                                                                                                          |

## What I learned

- In the PID module, the arm overshoots the target on step 2 and then swings above and below it. The response is a simple model (`position += output * 0.4`), not a real robot.
- The large D-term on step 1 happens because there is no previous error yet, so the first change in error looks very large.
- Reading input with `cin` can fail on letters or zero values, so each module checks its input before calculating.

## Possible next steps

- Tune the PID gains to reduce overshoot
- Save results to a file and plot them
- Add more modules
