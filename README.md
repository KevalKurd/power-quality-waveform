# power-quality-waveform
Project for analysing 3-phase power quality waveform data
This project is a C99 command-line program that analyses 3-phase power quality waveform data from a CSV file.

## Files

- `main.c` - program entry point
- `waveform.c` / `waveform.h` - waveform analysis functions
- `io.c` / `io.h` - CSV loading and results file writing
- `CMakeLists.txt` - CLion/CMake build configuration

## How to run in CLion

1. Open the project folder in CLion.
2. Make sure `power_quality_log.csv` is in the project folder.
3. Go to Run > Edit Configurations.
4. Add this program argument:

```text
power_quality_log.csv

## GitHub Repository
https://github.com/KevalKurd/power-quality-waveform
