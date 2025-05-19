# Hidden Markov Model (HMM) Example in C++

This project contains a simple C++ implementation of two fundamental algorithms for Hidden Markov Models (HMMs): the **Forward** and **Viterbi** algorithms.

## Overview

Hidden Markov Models are widely used in natural language processing, speech recognition, and many other fields to model sequences of hidden states based on observed events.

This example focuses on the classic **Weather Problem**:

- Alice observes Bob over three days:
  - Day 1: Bob goes for a walk
  - Day 2: Bob goes shopping
  - Day 3: Bob cleans his apartment

Given these observations, the program answers:

1. **Forward Algorithm**: What is the total probability of this sequence of observations occurring under the model?

2. **Viterbi Algorithm**: What is the most likely sequence of hidden states (Rainy or Sunny) that explains the observed activities?

## Implementation Details

- Written in modern C++ (C++17 standard or higher recommended. If not the main function needs slight adjustment).
- Uses simple console input/output for interaction.
- The transition and emission probabilities, as well as the observation sequence, are hard-coded for clarity and simplicity.
- Modular functions separate the Forward and Viterbi algorithms for ease of understanding and potential extension.
- Libraries used are only for the usual standard functions (iostream) and for variables (string, vector, unordered_map).

## How to Use

1. Clone or download this repository.
2. Open the project in your preferred C++ IDE (Visual Studio recommended).
3. Build and run the program.
4. When prompted, choose either:
   - `1` to run the Forward algorithm (calculates the overall probability),
   - `2` to run the Viterbi algorithm (finds the most likely sequence of states).
5. View the results printed to the console.

## License

This project is provided for educational purposes and is licensed under the MIT License.

---

Feel free to customize or extend this project for your own natural language programming or HMM experiments!
