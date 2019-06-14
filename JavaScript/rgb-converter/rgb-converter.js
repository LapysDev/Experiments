Number.prototype.toFixed = (function() {
    var method = Number.prototype.toFixed;
    return function toFixed() {
        var fixed = LDKF.stringPrototypeTrimRight(method.apply(this, arguments), '0');
        if (fixed[fixed.length - 1] == '.') fixed = fixed.slice(0, -1);
        return fixed
    }
})();

// COLORS = ["red"];
COLORS = ["aliceblue", "antiquewhite", "aqua", "aquamarine", "azure", "beige", "bisque", "black", "blanchedalmond", "blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse", "chocolate", "coral", "cornflowerblue", "cornsilk", "crimson", "cyan", "darkblue", "darkcyan", "darkgoldenrod", "darkgray", "darkgrey", "darkkhaki", "darkmagenta", "darkolivegreen", "darkorange", "darkorchid", "darkred", "darksalmon", "darkseagreen", "darkslateblue", "darkslategray", "darkslategrey", "darkturquoise", "darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue", "firebrick", "floralwhite", "forestgreen", "fuchsia", "gainsboro", "ghostwhite", "gold", "goldenrod", "gray", "grey", "green", "greenyellow", "honeydew", "hotpink", "indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen", "lemonchiffon", "lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow", "lightgray", "lightgrey", "lightgreen", "lightpink", "lightsalmon", "lightseagreen", "lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow", "lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", "mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose", "moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange", "orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred", "papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "rebeccapurple", "red", "rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise", "violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen"];
source = "";

document.body.style.display = "none";

function isZeroed(number) { number = +number; return number > 0 && number < 1 }
function rgbToCmyk(r,g,b) {var computedC = 0;var computedM = 0;var computedY = 0;var computedK = 0;var r = parseInt( (''+r).replace(/\s/g,''),10 ); var g = parseInt( (''+g).replace(/\s/g,''),10 ); var b = parseInt( (''+b).replace(/\s/g,''),10 ); if ( r==null || g==null || b==null ||isNaN(r) || isNaN(g)|| isNaN(b) ){alert ('Please enter numeric RGB values!');return;}if (r<0 || g<0 || b<0 || r>255 || g>255 || b>255) {alert ('RGB values must be in the range 0 to 255.');return;}if (r==0 && g==0 && b==0) {computedK = 1;return [0,0,0,1];}computedC = 1 - (r/255);computedM = 1 - (g/255);computedY = 1 - (b/255);var minCMY = Math.min(computedC,Math.min(computedM,computedY));computedC = (computedC - minCMY) / (1 - minCMY) ;computedM = (computedM - minCMY) / (1 - minCMY) ; computedY = (computedY - minCMY) / (1 - minCMY) ; computedK = minCMY;computedC = +((computedC * 100).toFixed(6));computedM = +((computedM * 100).toFixed(6));computedY = +((computedY * 100).toFixed(6));computedK = +((computedK * 100).toFixed(6));return [computedC,computedM,computedY,computedK]}
function rgbToHexadecimal(r,g,b) { return [r.toString(16), g.toString(16), b.toString(16)] }
function rgbToHsl(rgbArr) {var r1 = rgbArr[0] / 255;var g1 = rgbArr[1] / 255;var b1 = rgbArr[2] / 255;var maxColor = Math.max(r1,g1,b1);var minColor = Math.min(r1,g1,b1);var L = (maxColor + minColor) / 2 ;var S = 0;var H = 0;if(maxColor != minColor){if(L < 0.5){S = (maxColor - minColor) / (maxColor + minColor);}else{S = (maxColor - minColor) / (2.0 - maxColor - minColor);}if(r1 == maxColor){H = (g1-b1) / (maxColor - minColor);}else if(g1 == maxColor){H = 2.0 + (b1 - r1) / (maxColor - minColor);}else{H = 4.0 + (r1 - g1) / (maxColor - minColor);}}L = L * 100;S = S * 100;H = H * 60;if(H<0){H += 360;}return [H, S, L]}
function rgbUnitToPercentage(unit) { return +(((+((+unit).toFixed(6)) * 100) / 255).toFixed(6)) }

for (var i = 0; i < COLORS.length; i++) {
    document.body.style.backgroundColor = COLORS[i];

    color = document.body.style.backgroundColor;

    RGB = getComputedStyle(document.body).backgroundColor;
    RGB1 = RGB.replace(/, /g, ' ');
    RGBA1 = RGB.replace("rgb", "rgba").replace(')', ", 1)");
    RGBA2 = RGB.replace("rgb", "rgba").replace(')', ", 100%)");
    RGBA3 = RGB1.replace("rgb", "rgba").replace(')', " / 1)");
    RGBA4 = RGB1.replace("rgb", "rgba").replace(')', " / 100%)");
    RGB$_R = rgbUnitToPercentage(RGB.replace(/rgb\([0-9]{1,3}/, x => x.replace(/[^0-9]/g, "") + '|').replace(/\|.*/g, ""));
    RGB$_G = rgbUnitToPercentage(RGB.replace(/rgb\([^,]{0,},/g, "").replace(/,[^,]{0,}\)/g, ""));
    RGB$_B = rgbUnitToPercentage(RGB.replace(/rgb\([^,]{0,},/g, "").replace(/[^,]{0,},/g, "").replace(')', ""));
    RGB$ = "rgb(" + RGB$_R + "%, " + RGB$_G + "%, " + RGB$_B + "%" + ')';
    RGB1$ = RGB$.replace(/, /g, ' ');
    RGBA$1 = RGB$.replace("rgb", "rgba").replace(')', ", 1)");
    RGBA$2 = RGB$.replace("rgb", "rgba").replace(')', ", 100%)");
    RGBA$3 = RGB1$.replace("rgb", "rgba").replace(')', " / 1)");
    RGBA$4 = RGB1$.replace("rgb", "rgba").replace(')', " / 100%)");

    CMYK$ = rgbToCmyk(
        +RGB.replace(/rgb\([0-9]{1,3}/, x => x.replace(/[^0-9]/g, "") + '|').replace(/\|.*/g, ""),
        +RGB.replace(/rgb\([^,]{0,},/g, "").replace(/,[^,]{0,}\)/g, ""),
        +RGB.replace(/rgb\([^,]{0,},/g, "").replace(/[^,]{0,},/g, "").replace(')', "")
    );
    CMYK = [...CMYK$]; CMYK[0] = ((CMYK[0] / 100) * 255) | 0; CMYK[1] = ((CMYK[1] / 100) * 255) | 0; CMYK[2] = ((CMYK[2] / 100) * 255) | 0; CMYK[3] = ((CMYK[3] / 100) * 255) | 0;
    CMYK = "cmyk(" + CMYK.join(", ") + ')';
    CMYK1 = CMYK.replace(/, /g, ' ');
    CMYK$_0 = CMYK$[0] = +((+CMYK$[0]).toFixed(6));
    CMYK$_1 = CMYK$[1] = +((+CMYK$[1]).toFixed(6));
    CMYK$_2 = CMYK$[2] = +((+CMYK$[2]).toFixed(6));
    CMYK$_3 = CMYK$[3] = +((+CMYK$[3]).toFixed(6));
    CMYK$ = "cmyk(" + [...CMYK$].map(x => x + '%').join(", ") + ')';
    CMYK$1 = CMYK$.replace(/, /g, ' ');

    HEX = rgbToHexadecimal(
        +RGB.replace(/rgb\([0-9]{1,3}/, x => x.replace(/[^0-9]/g, "") + '|').replace(/\|.*/g, ""),
        +RGB.replace(/rgb\([^,]{0,},/g, "").replace(/,[^,]{0,}\)/g, ""),
        +RGB.replace(/rgb\([^,]{0,},/g, "").replace(/[^,]{0,},/g, "").replace(')', "")
    );
    HEX[0][1] || (HEX[0] = '0' + HEX[0][0]); HEX[1][1] || (HEX[1] = '0' + HEX[1][0]); HEX[2][1] || (HEX[2] = '0' + HEX[2][0]);
    HEXs = HEX[0][0]  == HEX[0][1] && HEX[1][0]  == HEX[1][1] && HEX[2][0]  == HEX[2][1] ? '#' + HEX[0][0] + HEX[1][0] + HEX[2][0] : "";
    HEX = '#' + HEX.join("");
    HEXA = HEX + "ff";
    HEXsA = HEXs + 'f';

    HSL = rgbToHsl([
        +RGB.replace(/rgb\([0-9]{1,3}/, x => x.replace(/[^0-9]/g, "") + '|').replace(/\|.*/g, ""),
        +RGB.replace(/rgb\([^,]{0,},/g, "").replace(/,[^,]{0,}\)/g, ""),
        +RGB.replace(/rgb\([^,]{0,},/g, "").replace(/[^,]{0,},/g, "").replace(')', "")
    ]);
    HSL[0] = +(HSL[0].toFixed(6)); HSL[1] = +(HSL[1].toFixed(6)); HSL[2] = +(HSL[2].toFixed(6));
    HSL_H = HSL[0]; HSL_S = HSL[1]; HSL_L = HSL[2];
    HSL[1] += '%'; HSL[2] += '%';
    HSL_deg = [...HSL];
    HSL_deg_H = HSL_H;
    HSL_deg[0] += "deg"; HSL_deg = "hsl(" + HSL_deg.join(", ") + ')';
    HSL_rad = [...HSL]; HSL_rad[0] = (HSL_rad[0] * (Math.PI / 180)).toFixed(6);
    HSL_rad_H = HSL_rad[0];
    HSL_rad[0] += "rad"; HSL_rad = "hsl(" + HSL_rad.join(", ") + ')';
    HSL_turn = [...HSL];
    HSL_turn[0] = (HSL_turn[0] / 360).toFixed(6);
    HSL_turn_H = HSL_turn[0];
    HSL_turn[0] += "turn"; HSL_turn = "hsl(" + HSL_turn.join(", ") + ')';
    HSL = "hsl(" + HSL.join(", ") + ')';

    HSL1 = HSL.replace(/, /g, ' ');
    HSLA1 = HSL.replace("hsl", "hsla").replace(')', ", 1)");
    HSLA2 = HSL.replace("hsl", "hsla").replace(')', ", 100%)");
    HSLA3 = HSL1.replace("hsl", "hsla").replace(')', " / 1)");
    HSLA4 = HSL1.replace("hsl", "hsla").replace(')', " / 100%)");

    HSL_deg1 = HSL_deg.replace(/, /g, ' ');
    HSL_degA1 = HSL_deg.replace("hsl", "hsla").replace(')', ", 1)");
    HSL_degA2 = HSL_deg.replace("hsl", "hsla").replace(')', ", 100%)");
    HSL_degA3 = HSL_deg1.replace("hsl", "hsla").replace(')', " / 1)");
    HSL_degA4 = HSL_deg1.replace("hsl", "hsla").replace(')', " / 100%)");

    HSL_rad1 = HSL_rad.replace(/, /g, ' ');
    HSL_radA1 = HSL_rad.replace("hsl", "hsla").replace(')', ", 1)");
    HSL_radA2 = HSL_rad.replace("hsl", "hsla").replace(')', ", 100%)");
    HSL_radA3 = HSL_rad1.replace("hsl", "hsla").replace(')', " / 1)");
    HSL_radA4 = HSL_rad1.replace("hsl", "hsla").replace(')', " / 100%)");

    HSL_turn1 = HSL_turn.replace(/, /g, ' ');
    HSL_turnA1 = HSL_turn.replace("hsl", "hsla").replace(')', ", 1)");
    HSL_turnA2 = HSL_turn.replace("hsl", "hsla").replace(')', ", 100%)");
    HSL_turnA3 = HSL_turn1.replace("hsl", "hsla").replace(')', " / 1)");
    HSL_turnA4 = HSL_turn1.replace("hsl", "hsla").replace(')', " / 100%)");

    source += `(
    string == "${color}" || (TEST_FOR_COLOR_CODES ? (
        (string == "${CMYK}" || string == "${CMYK1}" || string == "${CMYK$}" || string == "${CMYK$1}"${isZeroed(CMYK$_0) || isZeroed(CMYK$_1) || isZeroed(CMYK$_2) || isZeroed(CMYK$_3) ? " || " + `string == "cmyk(${(CMYK$_0+"").replace("0.", '.')}%, ${(CMYK$_1+"").replace("0.", '.')}%, ${(CMYK$_2+"").replace("0.", '.')}%, ${(CMYK$_3+"").replace("0.", '.')}%)" || string == "cmyk(${(CMYK$_0+"").replace("0.", '.')}% ${(CMYK$_1+"").replace("0.", '.')}% ${(CMYK$_2+"").replace("0.", '.')}% ${(CMYK$_3+"").replace("0.", '.')}%)"` : ""}) ||
        (${HEXs ? (`string == "${HEXs.toLowerCase()}" || string == "${HEXsA.toLowerCase()}"`) + " || " : ""}${HEXs && (HEXs.match(/[a-zA-Z]/) || []).length ? (`string == "${HEXs.toUpperCase()}" || string == "${HEXsA.toUpperCase()}"`) + " || " : ""}string == "${HEX.toLowerCase()}" || string == "${HEXA.toLowerCase()}"${(HEX.match(/[a-zA-Z]/) || []).length ? " || " + (`string == "${HEX.toUpperCase()}" || string == "${HEXA.toUpperCase()}"`) : ""}) ||
        (string == "${HSL}" || string == "${HSL1}" || string == "${HSLA1}" || string == "${HSLA2}" || string == "${HSLA3}" || string == "${HSLA4}" || string == "${HSL_deg}" || string == "${HSL_deg1}" || string == "${HSL_degA1}" || string == "${HSL_degA2}" || string == "${HSL_degA3}" || string == "${HSL_degA4}" || string == "${HSL_rad}" || string == "${HSL_rad1}" || string == "${HSL_radA1}" || string == "${HSL_radA2}" || string == "${HSL_radA3}" || string == "${HSL_radA4}" || string == "${HSL_turn}" || string == "${HSL_turn1}" || string == "${HSL_turnA1}" || string == "${HSL_turnA2}" || string == "${HSL_turnA3}" || string == "${HSL_turnA4}"${isZeroed(HSL_H) || isZeroed(HSL_deg_H) || isZeroed(HSL_rad_H) || isZeroed(HSL_turn_H) || isZeroed(HSL_L) || isZeroed(HSL_S) ? " || " + `string == "hsl(${(HSL_H+"").replace("0.", '.')}, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%)" || string == "hsl(${(HSL_H+"").replace("0.", '.')} ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}%)" || string == "hsla(${(HSL_H+"").replace("0.", '.')}, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 1)" || string == "hsla(${(HSL_H+"").replace("0.", '.')}, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 100%)" || string == "hsla(${(HSL_H+"").replace("0.", '.')} ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 1)" || string == "hsla(${(HSL_H+"").replace("0.", '.')} ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 100%)" || string == "hsl(${(HSL_deg_H+"").replace("0.", '.')}deg, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%)" || string == "hsl(${(HSL_deg_H+"").replace("0.", '.')}deg ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}%)" || string == "hsla(${(HSL_deg_H+"").replace("0.", '.')}deg, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 1)" || string == "hsla(${(HSL_deg_H+"").replace("0.", '.')}deg, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 100%)" || string == "hsla(${(HSL_deg_H+"").replace("0.", '.')}deg ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 1)" || string == "hsla(${(HSL_deg_H+"").replace("0.", '.')}deg ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 100%)" || string == "hsl(${(HSL_rad_H+"").replace("0.", '.')}rad, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%)" || string == "hsl(${(HSL_rad_H+"").replace("0.", '.')}rad ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}%)" || string == "hsla(${(HSL_rad_H+"").replace("0.", '.')}rad, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 1)" || string == "hsla(${(HSL_rad_H+"").replace("0.", '.')}rad, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 100%)" || string == "hsla(${(HSL_rad_H+"").replace("0.", '.')}rad ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 1)" || string == "hsla(${(HSL_rad_H+"").replace("0.", '.')}rad ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 100%)" || string == "hsl(${(HSL_turn_H+"").replace("0.", '.')}turn, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%)" || string == "hsl(${(HSL_turn_H+"").replace("0.", '.')}turn ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}%)" || string == "hsla(${(HSL_turn_H+"").replace("0.", '.')}turn, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 1)" || string == "hsla(${(HSL_turn_H+"").replace("0.", '.')}turn, ${(HSL_L+"").replace("0.", '.')}%, ${(HSL_S+"").replace("0.", '.')}%, 100%)" || string == "hsla(${(HSL_turn_H+"").replace("0.", '.')}turn ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 1)" || string == "hsla(${(HSL_turn_H+"").replace("0.", '.')}turn ${(HSL_S+"").replace("0.", '.')}% ${(HSL_L+"").replace("0.", '.')}% / 100%)"` : ""}) ||
        (string == "${RGB}" || string == "${RGB1}" || string == "${RGBA1}" || string == "${RGBA2}" || string == "${RGBA3}" || string == "${RGBA4}" || string == "${RGB$}" || string == "${RGB1$}" || string == "${RGBA$1}" || string == "${RGBA$2}" || string == "${RGBA$3}" || string == "${RGBA$4}"${isZeroed(RGB$_R) || isZeroed(RGB$_G) || isZeroed(RGB$_B) ? " || " + `string == "rgb(${(RGB$_R+"").replace("0.", '.')}%, ${(RGB$_G+"").replace("0.", '.')}%, ${(RGB$_B+"").replace("0.", '.')}%)" || string == "rgb(${(RGB$_R+"").replace("0.", '.')}% ${(RGB$_G+"").replace("0.", '.')}% ${(RGB$_B+"").replace("0.", '.')}%)" || string == "rgba(${(RGB$_R+"").replace("0.", '.')}%, ${(RGB$_G+"").replace("0.", '.')}%, ${(RGB$_B+"").replace("0.", '.')}%, 1)" || string == "rgba(${(RGB$_R+"").replace("0.", '.')}%, ${(RGB$_G+"").replace("0.", '.')}%, ${(RGB$_B+"").replace("0.", '.')}%, 100%)" || string == "rgba(${(RGB$_R+"").replace("0.", '.')}% ${(RGB$_G+"").replace("0.", '.')}% ${(RGB$_B+"").replace("0.", '.')}% / 1)" || string == "rgba(${(RGB$_R+"").replace("0.", '.')}% ${(RGB$_G+"").replace("0.", '.')}% ${(RGB$_B+"").replace("0.", '.')}% / 100%)"` : ""})
    ) : false))`.replace(/\|\|\n/g, "|| ").replace(/(\n|    )/g, "") + (i == COLORS.length - 1 ? "" : " ||\n")
}

source
