// 870. Advantage Shuffle

/* Thinking:
    1. if A1, A2 > B1, B2 then
        (A1 - B1) + (A2 - B2) = (A2 - B1) + (A1 - B2)
    2. use small A against big B
*/


// revised version
/**
 * @param {number[]} A
 * @param {number[]} B
 * @return {number[]}
 */
var advantageCount = function (A, B) {

    var sortedA = A.sort(function (a, b) {
        return a - b;
    });
    var sortedB = B.map(function (o, i) {
        return { idx: i, value: o };
    }).sort(function (a, b) {
        return a.value - b.value;
    });

    var idxA = 0, idxB = 0;
    var result = new Array(B.length);
    while (idxA < result.length) {
        if (sortedA[idxA] <= sortedB[idxB].value) {
            var lastB = sortedB.pop();
            result[lastB.idx] = sortedA[idxA];
        } else {
            var firstB = sortedB[idxB];
            result[firstB.idx] = sortedA[idxA];
            idxB += 1;
        }
        idxA += 1;
    }
    return result;
};

// stupid version
/**
 * @param {number[]} A
 * @param {number[]} B
 * @return {number[]}
 */
var advantageCount = function (A, B) {
    var nA = {}, nB = {};
    var result = new Array(A.length);

    for (var i = 0; i < A.length; i++) {

        if (nA.hasOwnProperty(A[i]))
            nA[A[i]] += 1;
        else
            nA[A[i]] = 1;

        // need B index for result
        if (nB.hasOwnProperty(B[i]))
            nB[B[i]].push(i);
        else
            nB[B[i]] = [i];
    }

    // assumed it is stable sort
    var sortedA = Object.keys(nA).map(x => Number(x));
    var sortedB = Object.keys(nB).map(x => Number(x));

    var idxA = 0, idxB = 0;
    while (idxA < sortedA.length) {
        var rIdx;
        if (sortedA[idxA] <= sortedB[idxB]) {
            var lastB = sortedB.pop();
            rIdx = nB[lastB].pop();
            if (nB[lastB].length > 0) sortedB.push(lastB);
        } else {
            rIdx = nB[sortedB[idxB]].pop();
            if (nB[sortedB[idxB]].length === 0) idxB += 1;
        }
        result[rIdx] = sortedA[idxA];
        nA[sortedA[idxA]] -= 1;
        if (nA[sortedA[idxA]] === 0) idxA += 1;
    }

    return result;
};

