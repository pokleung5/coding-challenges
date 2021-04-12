// 667. Beautiful Arrangement II

/* Thinking:
    1. 1 .. x has x distinct value
    2. n must >> k, having that case as first if-block can run faster
    3. repeat add value then substract value can make sure value < n
        - 1 + x - ( x - 1) = 2
        - 1 + x - ( x - 1) + ( x - 2 ) = x
        - 1 + x - ( x - 1) + ( x - 2 ) - ( x - 3 ) = 2 + 1
        - 1 + x - ( x - 1) + ( x - 2 ) - ( x - 3 ) + ( x - 4 ) = x + 1, and so on
    4. "If there are multiple answers, print any of them." is fake
        - this is the hardest part !
*/

/**
 * @param {number} n
 * @param {number} k
 * @return {number[]}
 */
var constructArray = function (n, k) {

    var result = [1];

    var val = 1;
    var should_add = true;

    for (var i = 1; i < n; i++) {

        if (k < 0) {
            val = val + 1;
        }
        else if (k > 0) {
            if (should_add) {
                val = val + k;
            } else {
                val = val - k;
            }
            k = k - 1;
            should_add = !should_add;
        } else if (k === 0) {
            val = result[1] + 1;
            k = k - 1;
        }

        result.push(val);
    }
    return result;
};