#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    bool close = false;
    
    for(auto& place : places) {
        close = false;
        for (int i = 0 ; i < 5 ; i++) {
            for (int j = 0 ; j < 5 ; j++) {
                if (place[i][j] == 'P') {
                    if (j < 4 && place[i][j+1] == 'P') {
                        answer.push_back(0);
                        close = true;
                        break;
                    }
                    if (i < 4 && place[i+1][j] == 'P') {
                        answer.push_back(0);
                        close = true;
                        break;
                    }
                    if (j < 3 && place[i][j+2] == 'P') {
                        if (place[i][j+1] != 'X') {
                            answer.push_back(0);
                            close = true;
                            break;
                        }
                    }
                    if (i < 3 && place[i+2][j] == 'P') {
                        if (place[i+1][j] != 'X') {
                            answer.push_back(0);
                            close = true;
                            break;
                        }
                    }
                    if (i < 4 && j < 4 && place[i+1][j+1] == 'P') {
                        if (place[i][j+1] != 'X' || place[i+1][j] != 'X') {
                            answer.push_back(0);
                            close = true;
                            break;
                        }
                    }
                    if (i < 4 && j > 0 && place[i+1][j-1] == 'P') {
                        if (place[i][j-1] != 'X' || place[i+1][j] != 'X') {
                            answer.push_back(0);
                            close = true;
                            break;
                        }
                    }
                }
            }
            if (close) break;
        }
        if (!close) answer.push_back(1);
    }
    
    return answer;
}
