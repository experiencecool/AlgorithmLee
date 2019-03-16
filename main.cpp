#include <fstream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

class pattern {
    static const int WALL = 1;
    static const int BLANK = 0;
    static const int START = 2;
    static const int FINISH = 3;
    static const int WAWE_START = 4;
    static const int M = 7;
    int arr[M][M]; // work field
    int len;
    int px[M * M], py[M * M]; // path coordinates
public:
    int start[2];
    int finish[2];

public:
    pattern();
    void out();
    void in();
    void find_start_end();
    bool lee(int ax, int ay, int bx, int by);
    bool lee();
};

//main --------------------
int main(){
    pattern pat;
    pat.in();
    pat.find_start_end();
    pat.out();
	if(pat.lee())
		cout << "Done\n";
	else
		cout << "something goes wrong";
    pat.out();
	system("pause");

    return 0;
}
//main ---------------------

pattern::pattern() {
    memset(&arr, 0, sizeof(arr));
    memset(&px, 0, sizeof(px));
    memset(&py, 0, sizeof(py));
    len = 0;
    start[0] = 0;
    start[1] = 0;
    finish[0] = 0;
    finish[1] = 0;
}

void pattern::out() {
    for(int y = 0; y < M; y++) {
        for(int x = 0; x < M; x++) {
            if ( arr[y][x] == -1 ) fout << setw(2) << '*';
            else fout << setw(2) << arr[y][x];
        }
        fout << endl;
    }
    fout << endl;
    fout << "path lenght: ";

    if ( len != 0 ) fout << len - WAWE_START << endl;
    else fout << "path has not found yet\n" << endl;
    //cout << start[0] << " " << start[1] << endl;
    //cout << finish[0] << " " << finish[1] << endl;
}

void pattern::in() {
    for(int y = 0; y < M; y++) {
        for(int x = 0; x < M; x++) {
            fin >> arr[y][x];
        }
    }
}

void pattern::find_start_end() {
    for(int y = 0; y < M; y++) {
        for(int x = 0; x < M; x++) {
            if ( arr[y][x] == START ) {
                start[0] = y;
                start[1] = x;
                arr[y][x] = BLANK;
            }else if ( arr[y][x] == FINISH ) {
                finish[0] = y;
                finish[1] = x;
                arr[y][x] = BLANK;
            }
        }
    }
}

bool pattern::lee(int ax, int ay, int bx, int by) {
    int dx[4] = {1, 0, -1, 0};  // right   0    left   0;
    int dy[4] = {0, 1, 0, -1};  //    0   up     0    down
    int d, x, y, k;
    bool stop;

    if (arr[ay][ax] == WALL || arr[by][bx] == WALL) cout << "error: wrong input";

    d = WAWE_START;
    arr[ay][ax] = WAWE_START;
    do {
        stop = true; //pretend that all free cells was marked
        for ( y = 0; y < M; y++)
        {
            for ( x = 0; x < M; x++)
            {
                if ( arr[y][x] == d )
                { // cell (x, y) already marked as "d"
                    for ( k = 0; k < 4; k++)
                    {// check "neighbours"
                        int iy = y + dy[k], ix = x + dx[k];
                        if ( iy >= 0 && iy < M && ix >= 0 && ix < M &&
                             arr[iy][ix] == BLANK )
                        {
                            stop = false;
                            arr[iy][ix] = d + 1;  // found not marked
                        }
                    }
                }
            }
        }
        d++;

    for(int y = 0; y < M; y++) {
        for(int x = 0; x < M; x++) {
            if ( arr[y][x] == -1 ) fout << setw(2) << '*';
            else fout << setw(3) << arr[y][x];
        }
        fout << endl;
    }
    fout << endl;
    } while ( !stop && by == finish[0] && bx == finish[1] );

    for(int y = 0; y < M; y++) {
        for(int x = 0; x < M; x++) {
            fout << setw(3) << arr[y][x];
        }
        fout << endl;
    }

    if (arr[finish[0]][finish[1]] == BLANK) return false; // path have not found

    //rebuilding path
    len = arr[finish[0]][finish[1]];
    x = finish[1];
    y = finish[0];
    d = len;
    while ( d > WAWE_START )
    {
        px[d] = x;
        py[d] = y;
        d--;
        for (k = 0; k < 4; k++)
        {
            int iy=y + dy[k], ix = x + dx[k];
            if ( iy >= 0 && iy < M && ix >= 0 && ix < M &&
                 arr[iy][ix] == d)
            {
                x = x + dx[k];
                y = y + dy[k]; // move to the start point
                break;
            }
        }
    }
    px[0+d] = ax;
    py[0+d] = ay;

    //drawing the path
    fout << endl;
    for(int i = WAWE_START; i <= len; i++) {
        arr[py[i]][px[i]] =  -1;
    }
    arr[start[0]][start[1]] = START;
    arr[finish[0]][finish[1]] = FINISH;

    //restructing pattern
    for(int y = 0; y < M; y++) {
        for(int x = 0; x < M; x++) {
            if(arr[y][x] >= WAWE_START) arr[y][x] = 0;

        }
    }

    return true;
}

bool pattern::lee()
{
    return lee(start[1], start[0], finish[1], finish[0]);
}



