# Akeed Restaurant Simulation Model

This project simulates customer data processing for an Akeed Restaurant system, reading and writing data to CSV files.

## Features

- Simulates customer data processing (e.g., `cid_lnum_vid`).
- Reads and writes data to CSV files.
- Implements linked list for storing and manipulating customer data.
- Includes soft error handling for string splitting.

## Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Akeed-Restaurant.git
   ```
2. Compile the project:
   ```bash
   gcc -o simulateModel AkeedRestaurant.c
   ```
3. Run the simulation:
   ```bash
   ./AkeedRestaurant
   ```

In that case, the README should reflect the correct file name. Here's the updated part for your README:

---

## Code Overview

- **`AkeedRestaurant.c`:** Simulates customer data and writes it to `cidxlnoxvid_v2target.csv`.
- **`strsplit`:** Splits strings into customer data fields.
- **`insertFirst`:** Inserts customer data into a linked list.
- **`stringToInt`:** Converts string to integer, validating numeric characters.

## Output

CSV file `cidxlnoxvid_v2target.csv` with columns:
- `cid_X_lnum_X_vid`
- `target`
