// 869. Reordered Power of 2

/* Thinking:
    1. pow^2 value might be reused
    2. order of the value is not matters
    3. lenght must match as "leader zero is not valid"
*/

var sort_str = function (n) {
    // 10: 0 - 9 
    var counter = new Array(10).fill(0);
    var n_str = "" + n;

    var len = n_str.length;
    // count number
    while (len--) {
        var d = n_str.charAt(len);
        counter[d] += 1;
    }

    var res_str = "";
    for (var i = 0; i < 10; i++) {
        // this fail when n > 10^9, as count will be more than one digit
        res_str += counter[i];
    }
    return res_str;
};

var pow2 = {};

pow2[sort_str(1)] = 1;
for (var n = 2; n < Math.pow(10, 9); n *= 2) {
    pow2[sort_str(n)] = 1;
}

/**
 * @param {number} N
 * @return {boolean}
 */
var reorderedPowerOf2 = function (N) {
    return pow2.hasOwnProperty(sort_str(N));
};