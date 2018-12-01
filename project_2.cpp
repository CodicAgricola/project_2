#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

int m, n, B;
int stepsum;
char map[1000][1000];
int step[1000][1000];
stringstream stepStream;

struct Point {
    int row;
    int col;
};

struct Node { 
    Point pt; 
    int dist;
}; 

vector<Node> pathNodes;

struct comp {
    inline bool operator() (const Node& n1, const Node& n2)
    {
        return (n1.dist > n2.dist);
    }
};

bool valid(int row, int col) 
{ 
    return (row >= 0) && (row < m) && 
           (col >= 0) && (col < n); 
} 

int rowNum[] = {-1, 0, 0, 1}; 
int colNum[] = {0, -1, 1, 0}; 

void BFS(Point R) {
    queue<Node> q;
    bool visited[m][n];

    memset(visited, false, sizeof visited);
    memset(step, -1, sizeof step);

    visited[R.row][R.col] = true;
    step[R.row][R.col] = 0;

    Node B = {R, 0};
    q.push(B);

    while(!q.empty()) {
        Node cur = q.front(); 
        Point pt = cur.pt; 
  
        q.pop(); 
  
        for (int i = 0; i < 4; i++) 
        { 
            int row = pt.row + rowNum[i]; 
            int col = pt.col + colNum[i]; 
              
            if (valid(row, col)) {
                if(map[row][col] == '0' &&  
               !visited[row][col]) {
                    step[row][col] = cur.dist + 1;
                    visited[row][col] = true; 
                    Node adj = { {row, col}, 
                                    step[row][col]};
                    q.push(adj);
                    pathNodes.push_back(adj); 
               }
            } 
        } 
    }
}

ostream& operator<<(ostream& os, const Node& r)  
{  
    os << r.pt.row << ' ' << r.pt.col << ' ' <<r.dist;  
    return os;  
}

void printPath() {
    stepsum = 0;
    memset(visited, false, sizeof visited);
    sort(pathNodes.begin(), pathNodes.end(), comp());
    cout<<pathNodes.size()<<endl;
    for (std::vector<Node>::const_iterator i = pathNodes.begin(); i != pathNodes.end(); ++i) {
        cout << *i << endl;
        if(!visited[(*i).row][(*i).col]) clean(*i);
    }
}

void clean(Node ep) {
    stack path;
    Node cur;
    while() {

    }
    for (int i = 0; i < 4; i++) { 
        int row = pt.row + rowNum[i]; 
        int col = pt.col + colNum[i]; 
            
        if (valid(row, col)) {
            if(map[row][col] == '0' && !visited[row][col]) {
                
            }
        } 
    } 
}

int main(int argc, char *argv[]) {
    Point R;

    ifstream inFile((string("./") + argv[1] + "/floor.data").c_str());

    inFile >> m >> n >> B;

    for(int i = 0; i<m; i++) {
        for(int j = 0; j<n; j++) {
            inFile >> map[i][j];
            if(map[i][j] == 'R') {
                R.row = i;
                R.col = j;
            }
        }
    }
    inFile.close();

    for(int i = 0 ; i<m; i++) {
        for(int j = 0; j<n; j++) {
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }

    BFS(R);

    printPath();

    for(int i = 0 ; i<m; i++) {
        for(int j = 0; j<n; j++) {
            if(step[i][j] < 10 && step[i][j] >= 0) cout<<"  "<<step[i][j];
            else cout<<" "<<step[i][j];
        }
        cout<<endl;
    }

    return 0;
}