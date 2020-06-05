/* NOTE (Lapys) -> Provides information on
        The altitude, coordinates, latitude, longitude and speed of the device with additional context,
*/
if ("geolocation" in navigator typeof navigator.geolocation == "object")
    const WATCH_POSITION_ID = navigator.geolocation.watchPosition(
        function GeolocationSuccess(GeolocationPosition) {
            console.group("GEOLOCATION", GeolocationPosition);
                console.log("LATITUDE:", GeolocationPosition.coords.latitude);
                console.log("LONGITUDE:", GeolocationPosition.coords.longitude);
            console.groupEnd()
        },
        function GeolocationError(PositionError) { throw PositionError },
        GEOLOCATION_OPTIONS = {
            enableHighAccuracy: true,
            maximumAge: 3e4,
            timeout: 27e3
        }
    )
