// if this is a stack array
char stack[16] = {0};

// would this be a heap array?
char (&heap)[16] = *reinterpret_cast<char (*)[16]>(new (std::malloc(16u * sizeof(char))) (char[16]) {0});
