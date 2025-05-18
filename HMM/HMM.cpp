#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Vector;

// State and observation definitions
const vector<string> states = { "Rainy", "Sunny" };
const vector<string> observations = { "Walk", "Shop", "Clean" };
const vector<string> obs_sequence = { "Walk", "Shop", "Clean" };

Matrix transition = {
    {0.0, 0.0, 0.0},  // dummy row for 1-based indexing
    {0.0, 0.7, 0.3},
    {0.0, 0.4, 0.6}
};
Vector start_prob = { 0.0, 0.6, 0.4 };

Matrix emission = {
    {0.0, 0.0, 0.0, 0.0}, // dummy row for 1-based indexing
    {0.0, 0.1, 0.4, 0.5},
    {0.0, 0.6, 0.3, 0.1}
};

unordered_map<string, int> obs_map = {
    {"Walk", 1},
    {"Shop", 2},
    {"Clean", 3}
};

// Forward algorithm
double forward_algorithm(const vector<string>& obs_seq) {
    int N = states.size();
    int T = obs_seq.size();

    vector<vector<double>> forward(N + 1, vector<double>(T + 1, 0.0));

    // Initialization step
    for (int s = 1; s <= N; ++s) {
        int obs_index = obs_map[obs_seq[0]];
        forward[s][1] = start_prob[s] * emission[s][obs_index];
    }

    // Recursion step
    for (int t = 2; t <= T; ++t) {
        int obs_index = obs_map[obs_seq[t - 1]];
        for (int s = 1; s <= N; ++s) {
            double sum = 0.0;
            for (int i = 1; i <= N; ++i) {
                sum += forward[i][t - 1] * transition[i][s] * emission[s][obs_index];
            }
            forward[s][t] = sum;
        }
    }

    // Termination step
    double total_prob = 0.0;
    for (int s = 1; s <= N; ++s) {
        total_prob += forward[s][T];
    }

    return total_prob;
}

// Viterbi algorithm
pair<vector<string>, double> viterbi_algorithm(const vector<string>& obs_seq) {
    int N = states.size();
    int T = obs_seq.size();

    vector<vector<double>> viterbi(N + 1, vector<double>(T + 1, 0.0));
    vector<vector<int>> backpointer(N + 1, vector<int>(T + 1, 0));

    // Initialization step
    for (int s = 1; s <= N; ++s) {
        int obs_index = obs_map[obs_seq[0]];
        viterbi[s][1] = start_prob[s] * emission[s][obs_index];
        backpointer[s][1] = 0;
    }

    // Recursion step
    for (int t = 2; t <= T; ++t) {
        int obs_index = obs_map[obs_seq[t - 1]];
        for (int s = 1; s <= N; ++s) {
            double max_prob = 0.0;
            int best_prev_state = 1;
            for (int i = 1; i <= N; ++i) {
                double prob = viterbi[i][t - 1] * transition[i][s] * emission[s][obs_index];
                if (prob > max_prob) {
                    max_prob = prob;
                    best_prev_state = i;
                }
            }
            viterbi[s][t] = max_prob;
            backpointer[s][t] = best_prev_state;
        }
    }

    // Termination step
    double max_final_prob = 0.0;
    int last_state = 1;
    for (int s = 1; s <= N; ++s) {
        if (viterbi[s][T] > max_final_prob) {
            max_final_prob = viterbi[s][T];
            last_state = s;
        }
    }

    // Backtracking
    vector<int> state_sequence_indices(T + 1);
    state_sequence_indices[T] = last_state;
    for (int t = T; t >= 2; --t) {
        state_sequence_indices[t - 1] = backpointer[state_sequence_indices[t]][t];
    }

    // Convert to state names
    vector<string> best_path;
    for (int t = 1; t <= T; ++t) {
        best_path.push_back(states[state_sequence_indices[t] - 1]);
    }

    return { best_path, max_final_prob };
}

int main() {
    cout << "HMM Example: Weather Problem\n";
    cout << "Alice talks to Bob three days in a row and observes:\n";
    cout << "  - Day 1: Bob went for a walk\n";
    cout << "  - Day 2: Bob went shopping\n";
    cout << "  - Day 3: Bob cleaned his apartment\n";
    cout << "Observation sequence: [Walk, Shop, Clean]\n\n";

    cout << "Problems to solve:\n";
    cout << "1. Forward Algorithm: What is the total probability of this observation sequence occurring?\n";
    cout << "2. Viterbi Algorithm: What is the most likely sequence of weather states (Rainy/Sunny) that explains these observations?\n\n";

    cout << "Choose algorithm to run:\n1. Forward (total probability)\n2. Viterbi (most likely state sequence)\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        double prob = forward_algorithm(obs_sequence);
        cout << "\n[Forward Algorithm Result]\n";
        cout << "Total probability of the observation sequence: " << prob << endl;
    }
    else if (choice == 2) {
        auto [best_path, prob] = viterbi_algorithm(obs_sequence);
        cout << "\n[Viterbi Algorithm Result]\n";
        cout << "Most likely sequence of states: ";
        for (const string& s : best_path) {
            cout << s << " ";
        }
        cout << "\nProbability of this path: " << prob << endl;
    }
    else {
        cout << "Invalid option. Please enter 1 or 2.\n";
    }

    return 0;
}

