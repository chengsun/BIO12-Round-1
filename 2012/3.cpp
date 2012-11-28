/* 
   We can model this problem as an undirected graph, where each node is a
   valid number, and each edge is a valid transformation between two numbers.
   Then, we can see that a number ladder is a path in the graph, and
   the problem statement is transformed into the standard task of finding
   the shortest path between two nodes.

   Notes:
   * When constructing the graph we don't need to generate any nodes
     representing numbers with 4 digits or more. This is because, although
     we might want to add a digit to a 3-digit number, we will need to remove
     a digit later (because the target is 3-digit or less), and it is never
     suboptimal if we do these two operations in reverse. So we can ignore any
     number ladders involving 4-digit numbers, and we will still get optimal
     ladder lengths.
   * Because the order of letters in a digit does not matter, that means that
     swapping two digits in a number can be done in "zero" steps. We need to
     take this into account in our graph construction.
   * I use the Floyd-Warshall shortest-path-finding algorithm, because it is
     far easier to code than Dijkstra. Although it is O(n^3) rather than
     O(n^2), because our graph is small this doesn't matter too much.
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int adj_matrix[1000][1000];

vector<char> number_to_letters(int number);
int count_changes(int i, int j);
void construct_graph();
void floyd_warshall();

int main() {
    /* input */
    int src_number[3], dst_number[3];
    for (int n = 0; n < 3; ++n)
        cin >> src_number[n] >> dst_number[n];

    /* first we fill in all edges representing valid one-step transformation */
    construct_graph();

    /* then we fill in every other edge with Floyd-Warshall shortest-path
     * algorithm */
    floyd_warshall();

    /* we simply look up the shortest path in our complete adjacency matrix */
    for (int n = 0; n < 3; ++n)
        cout << adj_matrix[src_number[n]][dst_number[n]]<< endl;

    return 0;
}

const char *spellings[] = {
    "ZERO", "ONE", "TWO", "THREE", "FOUR",
    "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"
};

/* returns a vector of sorted letters in that number */
vector<char> number_to_letters(int number) {
    vector<char> output;
    do {
        int digit = number % 10;
        output.insert(output.begin(),
                      spellings[digit],
                      spellings[digit] + strlen(spellings[digit]));
        number /= 10;
    } while (number);
    sort(output.begin(), output.end());
    return output;
}

/* returns the number of changes needed to go from one number to another */
int count_changes(int i, int j) {
    vector<char> i_letters = number_to_letters(i),
                 j_letters = number_to_letters(j);
    vector<char> difference(i_letters.size() + j_letters.size());
    vector<char>::iterator diff_end = set_symmetric_difference(
            i_letters.begin(), i_letters.end(),
            j_letters.begin(), j_letters.end(),
            difference.begin());
    int n_changes = diff_end - difference.begin();
    return n_changes;
}

void construct_graph() {
    for (int i = 0; i < 1000; ++i) {
        for (int j = i; j < 1000; ++j) {
            int n_changes = count_changes(i, j);
            if (n_changes == 0) {
                adj_matrix[i][j] = 0;
                adj_matrix[j][i] = 0;
            } else if (n_changes <= 5) {
                adj_matrix[i][j] = 1;
                adj_matrix[j][i] = 1;
            } else {
                // indicate that it is impossible to use this edge
                adj_matrix[i][j] = 99999;
                adj_matrix[j][i] = 99999;
            }
        }
    }
}
void floyd_warshall() {
    for (int k = 0; k < 1000; ++k) {
        for (int i = 0; i < 1000; ++i) {
            for (int j = i+1; j < 1000; ++j) {
                int new_path_length = adj_matrix[i][k] + adj_matrix[k][j];
                if (adj_matrix[i][j] > new_path_length) {
                    adj_matrix[i][j] = new_path_length;
                    adj_matrix[j][i] = new_path_length;
                }
            }
        }
    }
}

