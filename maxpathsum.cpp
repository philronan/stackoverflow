#include <iostream>
#include <vector>
using namespace std;

/**************************************************************************************

https://stackoverflow.com/q/64258707/1679849

Given two integer arrays a and b of lengths n and m, generate an n×m matrix where the
value in row i and column j is equal to a[i] × 10^9 + b[j]. Find the path from square
1,1 to n,m with the maximum sum, moving either to the right or down at each step.

Input parameters:
- The first line contains n and m (1 <= n, m <= 100000)
- The second line contains the values of array a (0 <= a[i] <= 9, 1 <= i <= n)
- The third line contains the values of array b (0 <= b[j] <= 9, 1 <= j <= m)

**************************************************************************************/

int main() {
    int n, m;
    cin >> n >> m;

    vector<int64_t> a(n), b(m);
    int tmp, astart, aend, bmax, i, j;
    
    // Read in arrays a[] and b[]. At the same time,
    // find the first and last indices of the maximum
    // value in a[] (astart and aend) and any index
    // corresponding to the maximum value of b[] (bmax)
    
    for (tmp = -1, i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] >= tmp) {
            aend = i;
            if (a[i] > tmp) {
                astart = i;
                tmp = a[i];
            }
        }
        a[i] *= 1000000000LL;
    }
    for (tmp = -1, j = 0; j < m; j++) {
        cin >> b[j];
        if (b[j] > tmp) {
            tmp = b[j];
            bmax = j;
        }
    }
    
    // Trace through the matrix. First work down as far as
    // astart, then right until column bmax. Then work down
    // as far as row aend, add the remaining elements in this
    // row, and finally add the last element of each remaining
    // rows until we reach the bottom right corner.
    
    i = j = 0;
    int64_t tot = a[i] + b[j];
    while (i < astart) tot += a[++i] + b[j];
    while (j < bmax) tot += a[i] + b[++j];
    while (i < aend) tot += a[++i] + b[j];
    while (j < m-1) tot += a[i] + b[++j];
    while (i < n-1) tot += a[++i] + b[j];
        
    cout << tot << endl;
    return 0;
}
