enum Animal {Cat, Dog};
void makeCatSound();
void makeDogSound();
using MakeSoundFunc = void(*)();
MakeSoundFunc makeSoundTable[] = {&makeCatSound, &makeDogSound};
//usage
makeSoundTable[Cat]();
