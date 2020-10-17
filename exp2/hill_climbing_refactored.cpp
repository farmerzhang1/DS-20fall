#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;
class NQueens {
private:
    vector<int> board;
    int size;
public:
    NQueens(int _size) : size(_size) {
        for (int i = 0; i < size; i++) board.push_back(i);
    }
/**该函数的时间性能是否能提高？（提示：利用前一个解的value，调整邻居的value, len*len => 2*len）
 * yeah, I think you only need to take the two changed rows into consideration
 **/
    int numberofConflicts() const {
        int n, i, j;
        n = 0;
        for (i = 0; i < size - 1; i++) {
            for (j = i + 1; j < size; j++) {
                if (board[j] - board[i] == j - i || board[j] - board[i] == i - j)
                    n++;
            }
        }
        return n;
    }

    void restart() {
        default_random_engine randomEngine{random_device{}()};
        shuffle(board.begin(), board.end(), randomEngine);      //shuffle machine, read in a cpp book
        cout << "board shuffled. restart" << endl;
        printeasyboard();
    }

    int bestResult() {
        int i, j, count;
        int rowi, rowj, besti, bestj;
        int bestfound{numberofConflicts()}, bestIndex{-1}, temp;
        for (i = count = 0; i < size - 1; i++) {
            for (j = i + 1; j < size; j++, count++) {           //這裡可以封裝
                rowi = board.at(i);
                rowj = board.at(j);                             //record data
                board[i] = rowj;
                board[j] = rowi;                                //swap, temporarily
                if ((temp = numberofConflicts()) < bestfound) { // if there is a better result(did not consider multiple best results)
                    bestIndex = count;
                    bestfound = temp;
                    besti = i;
                    bestj = j;
                }
                board[i] = rowi;
                board[j] = rowj;                                //recover it.
            }
        }
        if (bestIndex == -1) { restart(); return -1; }
        temp = board[besti];
        board[besti] = board[bestj];
        board[bestj] = temp;
        return bestfound;
    }
    void printboard() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (j == board[i]) cout << 'o';
                else cout << '*';
            }
            cout << endl;
        }
        cout << endl;
    }
    void printeasyboard() {
        for (int i = 0; i < size; i++) cout << board[i] << ' ';
        cout << endl;
    }
    void climb() {
        int aaa;
        while ((aaa = bestResult()) != 0);
        printboard();
    }
};
int main(void) {
    NQueens aaa(8);
    aaa.climb();
    return 0;
}