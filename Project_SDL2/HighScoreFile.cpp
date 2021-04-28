#include "HighScoreFile.h"

int getHighScore() {
    int high_score;
    std::ifstream file ("HighScore.txt");
    if (file) {
        file >> high_score;
        file.close();
    }
    return high_score;
}

void setHighScore(const int &score) {
    std::ofstream file ("HighScore.txt");
    if (file) {
        file << score;
        file.close();
    }
}
