// 329. Longest Increasing Path in a Matrix

/* Thinking:
    1. the path will always be opened
    2. be careful that new Array(x_len).fill({}) is pass by reference
    3. simply use dfs to search every options
    4. might use dijkstra for the non-recursion version
        - not implemented as js dont have min heap ...
*/

/**
 * @param {number[][]} matrix
 * @return {number}
 */
var longestIncreasingPath = function (matrix) {
    var x_len = matrix.length;
    var y_len = matrix[0].length;

    var dp = new Array(x_len);
    var dfs_dp = function (src, x, y) {
        // return 0 for invalid arg
        if (x < 0 || y < 0 || x >= x_len || y >= y_len
            // or failed to match the condition "increasing"
            || matrix[x][y] <= src) {
            return 0;
        }

        // create the 2D array, or dict X)
        if (dp[x] === undefined)
            dp[x] = {};

        if (dp[x][y] === undefined) {
            var _res = 0;
            var _val = matrix[x][y];

            // try all options
            _res = Math.max(_res, dfs_dp(_val, x - 1, y));
            _res = Math.max(_res, dfs_dp(_val, x + 1, y));
            _res = Math.max(_res, dfs_dp(_val, x, y - 1));
            _res = Math.max(_res, dfs_dp(_val, x, y + 1));

            dp[x][y] = 1 + _res;
        }
        return dp[x][y];
    };

    var longest = 0;
    for (var x = 0; x < x_len; x++) {
        for (var y = 0; y < y_len; y++) {
            longest = Math.max(longest, dfs_dp(-1, x, y));
        }
    }
    return longest;
};