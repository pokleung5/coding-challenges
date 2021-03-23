// 966. Vowel Spellchecker

/* Thinking:
    1. need to identify the rule matched. (like # for vowel, @ for capitlization)
    2. be careful that rule match order: match > capitlization > vowel
*/

var translate = function (w) {
    return w.toLowerCase().replace(/a|e|i|o|u/g, '#');
};
/**
 * @param {string[]} wordlist
 * @param {string[]} queries
 * @return {string[]}
 */
var spellchecker = function (wordlist, queries) {
    var map = {};
    wordlist.forEach(function (w) {
        map[w] = w;
        var lower = '@' + w.toLowerCase();
        if (map.hasOwnProperty(lower) === false)
            map[lower] = w;
        var enc = translate(w);
        if (map.hasOwnProperty(enc) === false)
            map[enc] = w;
    });
    var res = [];
    queries.forEach(function (w) {
        res.push(map[w] || map['@' + w.toLowerCase()] || map[translate(w)] || "");
    });
    return res;
};