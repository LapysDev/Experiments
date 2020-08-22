/* RULES */
// Write a program that takes a passage of text on stdin,
// and swaps all English vowels (a, e, i, o, u) with their immediately preceding consonant,
// unless that consonant is a 'y', or there is no preceding letter. Case must be preserved.
// The transformed text should be displayed via stdout

/* EXAMPLE */
// Gorbit has yet more grand giveaway games. Why he has them? Nobody knows, but it is appreciated that he wishes to disperse his contraband with those deemed worthy enough. The metric of worthiness is deduced via the most ancient and purest form of cognitive combat - code golf.
// Ogribt ahs yet omer garnd igeavawy agems. Why eh ahs tehm? Onobdy konws, ubt it is apperiacetd taht eh iwsehs ot idsepres ihs ocntarabnd iwth tohes eedmde owrthy eoungh. Teh emtirc of owrtihenss is edudecd iav teh omst aniecnt nad uperst ofrm of ocginitev ocmabt - oced oglf.

/* NOTE */
// c|32 -> tolowercase
// 2016%((c&31)+27 -> consonant
// (35684898>>p)&1 -> vowel + y
// c^=d^=c^=d -> swap (and return c)
// c^=(d^=(c^=d&32)&32)&32 -> case swap (and return c)

main(p,c,d){while(p^1?putchar(strchr("aeiou",c=getchar())&&!strchr("aeiouy ",p)?c^=(p^=(c^=p&32)&32)&32:(d=p,p=c,d)),c^10:main(8)){}}
// main(c,p){if(10^c?putchar(c),main(getchar(),c):0){}}
// _(char*b){while(isalpha(*b)&&isalpha(*(b-1))&&(2016%(*b&31+27)||35684898>>*(b-1)&1||(*b^=*(b-1)^=*b^=*(b-1))&&(*b^=(*(b-1)^=(*b^=*(b-1)&32)&32)&32)),*++b){}}main(s){if(_(gets(s=malloc(512)+1)),puts(s)){}}
