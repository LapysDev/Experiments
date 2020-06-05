/* Namespace > Test */
var Test = {
    currentTimestamp: typeof performance == "undefined" ?
        function currentTimestamp() { return (new Date).valueOf() } :
        function currentTimestamp() { return performance.now() }
    ,
    getminpositive: null
};

/* Modification > Test > Get Minimum Positive [Integer from Integer Array]
        --- WARN ---
            #Lapys: The array gets corrupted.
*/
Test.getminpositive = function getminpositive(array) {
    var length = array.length, iterator = length;
    var minimum = 1;

    // Loop --- NOTE (Lapys) -> Filter out signed and "zero" integers.
    while (iterator) {
        // Update > ... NOTE (Lapys) -> Assert if the element is greater than 0 within it`s specified range of `2 ** 20` (i.e.: about 1 million).
        array[iterator] = --array[iterator] >> 20 ? array[--length] : ++array[iterator];
        iterator--
    }

    while (iterator ^ length)
    if (minimum == array[iterator++]) {
        array[--iterator] = array[--length];
        iterator = 0;
        minimum++
    }

    return minimum || 1
};

/* Main */
void function Main() {
    /* Global > Test ... --- NOTE (Lapys) -> Configuration for testing. */
    var TEST_TYPES = {"ACCURACY": 0, "PERFORMANCE": 1};
    var TEST_TYPE;

    // Logic
    switch (TEST_TYPE = TEST_TYPES["ACCURACY"]) {
        // [Accuracy]
        case TEST_TYPES["ACCURACY"]: {
            // : Initialization > (Array, Duration)
            // : Evaluation > Minimum
            var array; var duration;
            var minimum;

            // Print
            console.info("TESTING ACCURACY...\n");

            // : Update > ...
            // : Print
            array = new Array(Number.parseInt(Math.random() * 20) + 10).fill().map(function() { return (Math.random() * 10 > 5 ? 1 : -1) * Number.parseInt(Math.random() * 10) });
            console.log("ARRAY", array);

            // : Update > ...
            // : Print
            duration = Test.currentTimestamp();
            minimum = Test.getminpositive(array);
            duration = Test.currentTimestamp() - duration;

            console.log("MINIMUM", minimum);
            console.log("TIME", duration, "milliseconds")
        } break;

        // [Performance]
        case TEST_TYPES["PERFORMANCE"]: {
            // Global > Performance Test ...
            var PERFORMANCE_TEST_TYPES = {"TEST 1": 0, "TEST 2": 1, "TEST 3": 2, "TEST 4": 3};
            var PERFORMANCE_TEST_TYPE;

            // Initialization > ...
            var averageDuration = 0; // NOTE (Lapys) -> Average duration overall for each iteration.
            var sampleSize = 3e3; // NOTE (Lapys) -> Number of samples to test.
            var totalDuration = 0; // NOTE (Lapys) -> Total time spent to complete the sample.

            // Constant > ...
            var REGENERATE_SAMPLE = true;

            var SHOW_PROGRESSION = true;
            var PROGRESSION_REFRESH_RATE = sampleSize * ((Number.parseInt(Math.random() * 1) + 1) / 100);

            // Modification > Test > ...
            Test.getsample = function getsample() {
                // Logic > Return
                switch (PERFORMANCE_TEST_TYPE = PERFORMANCE_TEST_TYPES["TEST 2"]) {
                    case PERFORMANCE_TEST_TYPES["TEST 1"]: return new Array(1e5 + 5).fill().map(function() { return (Math.random() * 10 > 5 ? 1 : -1) * ((Math.random() * 1e6) | 0) });
                    case PERFORMANCE_TEST_TYPES["TEST 2"]: return new Array(4e5).fill().map(function() { return (Math.random() * 1e6) | 0 });
                    case PERFORMANCE_TEST_TYPES["TEST 3"]: return new Array(1e7).fill().map(function() { return (Math.random() * 1e6) | 0 });
                    case PERFORMANCE_TEST_TYPES["TEST 4"]: return new Array(1e8).fill().map(function() { return (Math.random() * 10 > 5 ? 1 : -1) * ((Math.random() * 1e6) | 0) })
                }
            };

            // Print
            console.info("TESTING PERFORMANCE...");

            // Loop
            for (var array = Test.getsample(), iterator = 0; iterator ^ sampleSize; iterator++) {
                // Logic
                if (SHOW_PROGRESSION && !(iterator % PROGRESSION_REFRESH_RATE)) {
                    // Print
                    console.clear();
                    console.info("TESTING @ " + ((iterator * 100) / sampleSize) + "% (" + iterator + " / " + sampleSize + ')')
                }

                // Logic > Update > Array --- NOTE (Lapys) -> Regenerate a new randomized array each sample.
                if (REGENERATE_SAMPLE) array = Test.getsample();

                // ...
                var duration = Test.currentTimestamp();
                Test.getminpositive(array);

                // Update > Total Duration
                duration = Test.currentTimestamp() - duration;
                totalDuration += duration
            }

            // Update > Average Duration
            averageDuration = totalDuration / sampleSize;

            // Print
            console.clear();
            console.info("TESTING PERFORMANCE...\n");

            console.log("SAMPLE SIZE", sampleSize);
            console.log("AVERAGE TIME", averageDuration, "milliseconds");
            console.log("TOTAL TIME", totalDuration / 1e3, " seconds")
        } break;
    }
}()
