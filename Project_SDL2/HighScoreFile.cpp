#include "HighScoreFile.h"

int* getHighScore() {
    int* high_score = new int [NUM_OF_MODES];
    std::ifstream file ("HighScore.txt");
    if (file) {
        for (int i = 0; i < NUM_OF_MODES; i++) {
            file >> high_score[i];
        }
        file.close();
    }
    return high_score;
}

void setHighScore(const int* high_score) {
    std::ofstream file ("HighScore.txt");
    if (file) {
        for (int i = 0; i < NUM_OF_MODES; i++) {
            file << high_score[i] << endl;
        }
        file.close();
    }
}
