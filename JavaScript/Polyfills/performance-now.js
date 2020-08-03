if (!Date.now) { Date.now = function() { return new Date().getTime(); } }
(function()
{
    if (window.performance && window.performance.now) { return; }

    window.performance = window.performance || {};

    if
    (
        window.performance.timing && window.performance.timing.navigationStart &&
        window.performance.mark &&
        window.performance.clearMarks &&
        window.performance.getEntriesByName
    )
    {
        window.performance.now = function()
        {
            window.performance.clearMarks('__PERFORMANCE_NOW__');
            window.performance.mark('__PERFORMANCE_NOW__');
            return window.performance.getEntriesByName('__PERFORMANCE_NOW__')[0].startTime;
        };
    }
    else if ("now" in window.performance === false)
    {
        var nowOffset = Date.now();

        if (window.performance.timing && window.performance.timing.navigationStart)
        {
            nowOffset = window.performance.timing.navigationStart
        }

        window.performance.now = function now()
        {
            return Date.now() - nowOffset;
        }
    }
})();
