/* Import */
#include <fstream> // File Stream

/* Function > (Length, String) */
const unsigned char len(const char* string) { unsigned char length = 0; while (*(string + length)) length += 1; return length; }
const char* str(unsigned short stop) { switch (stop) { case 255: return "255"; case 254: return "254"; case 253: return "253"; case 252: return "252"; case 251: return "251"; case 250: return "250"; case 249: return "249"; case 248: return "248"; case 247: return "247"; case 246: return "246"; case 245: return "245"; case 244: return "244"; case 243: return "243"; case 242: return "242"; case 241: return "241"; case 240: return "240"; case 239: return "239"; case 238: return "238"; case 237: return "237"; case 236: return "236"; case 235: return "235"; case 234: return "234"; case 233: return "233"; case 232: return "232"; case 231: return "231"; case 230: return "230"; case 229: return "229"; case 228: return "228"; case 227: return "227"; case 226: return "226"; case 225: return "225"; case 224: return "224"; case 223: return "223"; case 222: return "222"; case 221: return "221"; case 220: return "220"; case 219: return "219"; case 218: return "218"; case 217: return "217"; case 216: return "216"; case 215: return "215"; case 214: return "214"; case 213: return "213"; case 212: return "212"; case 211: return "211"; case 210: return "210"; case 209: return "209"; case 208: return "208"; case 207: return "207"; case 206: return "206"; case 205: return "205"; case 204: return "204"; case 203: return "203"; case 202: return "202"; case 201: return "201"; case 200: return "200"; case 199: return "199"; case 198: return "198"; case 197: return "197"; case 196: return "196"; case 195: return "195"; case 194: return "194"; case 193: return "193"; case 192: return "192"; case 191: return "191"; case 190: return "190"; case 189: return "189"; case 188: return "188"; case 187: return "187"; case 186: return "186"; case 185: return "185"; case 184: return "184"; case 183: return "183"; case 182: return "182"; case 181: return "181"; case 180: return "180"; case 179: return "179"; case 178: return "178"; case 177: return "177"; case 176: return "176"; case 175: return "175"; case 174: return "174"; case 173: return "173"; case 172: return "172"; case 171: return "171"; case 170: return "170"; case 169: return "169"; case 168: return "168"; case 167: return "167"; case 166: return "166"; case 165: return "165"; case 164: return "164"; case 163: return "163"; case 162: return "162"; case 161: return "161"; case 160: return "160"; case 159: return "159"; case 158: return "158"; case 157: return "157"; case 156: return "156"; case 155: return "155"; case 154: return "154"; case 153: return "153"; case 152: return "152"; case 151: return "151"; case 150: return "150"; case 149: return "149"; case 148: return "148"; case 147: return "147"; case 146: return "146"; case 145: return "145"; case 144: return "144"; case 143: return "143"; case 142: return "142"; case 141: return "141"; case 140: return "140"; case 139: return "139"; case 138: return "138"; case 137: return "137"; case 136: return "136"; case 135: return "135"; case 134: return "134"; case 133: return "133"; case 132: return "132"; case 131: return "131"; case 130: return "130"; case 129: return "129"; case 128: return "128"; case 127: return "127"; case 126: return "126"; case 125: return "125"; case 124: return "124"; case 123: return "123"; case 122: return "122"; case 121: return "121"; case 120: return "120"; case 119: return "119"; case 118: return "118"; case 117: return "117"; case 116: return "116"; case 115: return "115"; case 114: return "114"; case 113: return "113"; case 112: return "112"; case 111: return "111"; case 110: return "110"; case 109: return "109"; case 108: return "108"; case 107: return "107"; case 106: return "106"; case 105: return "105"; case 104: return "104"; case 103: return "103"; case 102: return "102"; case 101: return "101"; case 100: return "100"; case 99: return "99"; case 98: return "98"; case 97: return "97"; case 96: return "96"; case 95: return "95"; case 94: return "94"; case 93: return "93"; case 92: return "92"; case 91: return "91"; case 90: return "90"; case 89: return "89"; case 88: return "88"; case 87: return "87"; case 86: return "86"; case 85: return "85"; case 84: return "84"; case 83: return "83"; case 82: return "82"; case 81: return "81"; case 80: return "80"; case 79: return "79"; case 78: return "78"; case 77: return "77"; case 76: return "76"; case 75: return "75"; case 74: return "74"; case 73: return "73"; case 72: return "72"; case 71: return "71"; case 70: return "70"; case 69: return "69"; case 68: return "68"; case 67: return "67"; case 66: return "66"; case 65: return "65"; case 64: return "64"; case 63: return "63"; case 62: return "62"; case 61: return "61"; case 60: return "60"; case 59: return "59"; case 58: return "58"; case 57: return "57"; case 56: return "56"; case 55: return "55"; case 54: return "54"; case 53: return "53"; case 52: return "52"; case 51: return "51"; case 50: return "50"; case 49: return "49"; case 48: return "48"; case 47: return "47"; case 46: return "46"; case 45: return "45"; case 44: return "44"; case 43: return "43"; case 42: return "42"; case 41: return "41"; case 40: return "40"; case 39: return "39"; case 38: return "38"; case 37: return "37"; case 36: return "36"; case 35: return "35"; case 34: return "34"; case 33: return "33"; case 32: return "32"; case 31: return "31"; case 30: return "30"; case 29: return "29"; case 28: return "28"; case 27: return "27"; case 26: return "26"; case 25: return "25"; case 24: return "24"; case 23: return "23"; case 22: return "22"; case 21: return "21"; case 20: return "20"; case 19: return "19"; case 18: return "18"; case 17: return "17"; case 16: return "16"; case 15: return "15"; case 14: return "14"; case 13: return "13"; case 12: return "12"; case 11: return "11"; case 10: return "10"; case 9: return "9"; case 8: return "8"; case 7: return "7"; case 6: return "6"; case 5: return "5"; case 4: return "4"; case 3: return "3"; case 2: return "2"; case 1: return "1"; case 0: return "0"; } }

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > FIle
    std::ofstream file;

    // File > Open
    file.open("rgb-color-printer.txt");

    // Loop
    for (unsigned short RED_ITERATOR = 0; RED_ITERATOR ^ 256; RED_ITERATOR += 1)
    for (unsigned short GREEN_ITERATOR = 0; GREEN_ITERATOR ^ 256; GREEN_ITERATOR += 1)
    for (unsigned short BLUE_ITERATOR = 0; BLUE_ITERATOR ^ 256; BLUE_ITERATOR += 1) {
        // Constant > (Red, Green, Blue) (Length)
        const char *RED = ::str(RED_ITERATOR), *GREEN = ::str(GREEN_ITERATOR), *BLUE = ::str(BLUE_ITERATOR);
        const unsigned char RED_LENGTH = ::len(RED), GREEN_LENGTH = ::len(GREEN), BLUE_LENGTH = ::len(BLUE);

        // Initialization > Color (Length)
        char COLOR[20]; unsigned char COLOR_LENGTH = 0;

        // Update > Color
        *COLOR = 'r'; *(COLOR + (COLOR_LENGTH += 1)) = 'g'; *(COLOR + (COLOR_LENGTH += 1)) = 'b'; *(COLOR + (COLOR_LENGTH += 1)) = '(';

        // Logic > Update > Color
        switch (RED_LENGTH) {
            case 1: *(COLOR + (COLOR_LENGTH += 1)) = *RED; *(COLOR + (COLOR_LENGTH += 1)) = ','; *(COLOR + (COLOR_LENGTH += 1)) = ' '; break;
            case 2: *(COLOR + (COLOR_LENGTH += 1)) = *RED; *(COLOR + (COLOR_LENGTH += 1)) = *(RED + 1); *(COLOR + (COLOR_LENGTH += 1)) = ','; *(COLOR + (COLOR_LENGTH += 1)) = ' '; break;
            case 3: *(COLOR + (COLOR_LENGTH += 1)) = *RED; *(COLOR + (COLOR_LENGTH += 1)) = *(RED + 1); *(COLOR + (COLOR_LENGTH += 1)) = *(RED + 2); *(COLOR + (COLOR_LENGTH += 1)) = ','; *(COLOR + (COLOR_LENGTH += 1)) = ' ';
        }

        switch (GREEN_LENGTH) {
            case 1: *(COLOR + (COLOR_LENGTH += 1)) = *GREEN; *(COLOR + (COLOR_LENGTH += 1)) = ','; *(COLOR + (COLOR_LENGTH += 1)) = ' '; break;
            case 2: *(COLOR + (COLOR_LENGTH += 1)) = *GREEN; *(COLOR + (COLOR_LENGTH += 1)) = *(GREEN + 1); *(COLOR + (COLOR_LENGTH += 1)) = ','; *(COLOR + (COLOR_LENGTH += 1)) = ' '; break;
            case 3: *(COLOR + (COLOR_LENGTH += 1)) = *GREEN; *(COLOR + (COLOR_LENGTH += 1)) = *(GREEN + 1); *(COLOR + (COLOR_LENGTH += 1)) = *(GREEN + 2); *(COLOR + (COLOR_LENGTH += 1)) = ','; *(COLOR + (COLOR_LENGTH += 1)) = ' ';
        }

        switch (BLUE_LENGTH) {
            case 1: *(COLOR + (COLOR_LENGTH += 1)) = *BLUE; break;
            case 2: *(COLOR + (COLOR_LENGTH += 1)) = *BLUE; *(COLOR + (COLOR_LENGTH += 1)) = *(BLUE + 1); break;
            case 3: *(COLOR + (COLOR_LENGTH += 1)) = *BLUE; *(COLOR + (COLOR_LENGTH += 1)) = *(BLUE + 1); *(COLOR + (COLOR_LENGTH += 1)) = *(BLUE + 2);
        }

        // Update > Color
        *(COLOR + (COLOR_LENGTH += 1)) = ')'; *(COLOR + (COLOR_LENGTH += 1)) = '\n'; *(COLOR + (COLOR_LENGTH += 1)) = '\0';

        // Update > File
        file << COLOR;
    }

    // File > Close
    file.close();

    // Return
    return 0;
}
