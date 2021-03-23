// 923. 3Sum With Multiplicity

/* Thinking:
    1. 3sum = loop + 2sum
    2. r in nCr at most is 3, so need factorial
*/

// var f = [];
// function factorial (n) {
//   if (n == 0 || n == 1)
//     return 1;
//   if (f[n] > 0)
//     return f[n];
//   return f[n] = factorial(n-1) * n;
// }

function combination(n, r) {
    if (n === r || r === 1)
        return 1;
    if (n > r) {
        var t1 = n;
        var t2 = 1;
        for (var i = 1; i < r; i++) {
            t1 = t1 * (n - i);
            t2 = t2 * (i + 1);
        }
        // console.log(`${t1};${t2}`);
        return t1 / t2;
    }
    return 0;
}


/**
 * @param {number[]} arr
 * @param {number} target
 * @return {number}
 */
var threeSumMulti = function (arr, target) {
    var result = 0;
    var highest = (target > 100 ? 100 : target) + 1;

    var nums = new Array(highest).fill(0);
    for (var i = 0; i < arr.length; i++) {
        nums[arr[i]] += 1;
    }
    for (var i = 0; i < highest; i++) {
        if (nums[i] > 0) {
            var r1 = target - i;
            for (var j = i; j < highest; j++) {
                var r2 = r1 - j;
                if (r2 >= j && r2 < highest && nums[j] > 0 && nums[r2] > 0) {
                    if (r2 === i) {
                        // r2 >= j >= i, so r2 == i then i == j 
                        result += combination(nums[i], 3);
                        // console.log(`${i};${j};${r2};${combination(nums[i], 3)}`);
                    } else if (r2 === j) {
                        result += nums[i] * combination(nums[j], 2);
                        // console.log(`${i};${j};${r2};${nums[i] * combination(nums[j], 2)}`);
                    } else if (i === j) {
                        result += combination(nums[i], 2) * nums[r2];
                        // console.log(`${i};${j};${r2};${combination(nums[i], 2) * nums[r2]}`);
                    } else if (r2 > j) {
                        result += nums[i] * nums[j] * nums[r2];
                        // console.log(`${i};${j};${r2};${nums[i] * nums[j] * nums[r2]}`);
                    }
                }
            }
        }
    }
    return result % 1000000007;
};

 