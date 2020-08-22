char test[] = "   T e   s t   ";

x(char*s){*strcpy(s+=32!=*s,s+1)&&x(s);}
// x(char*s){while(*(32-*s?++s:strcpy(s,s+1)));}

int main(void) { printf("[PRE]:  \"%s\"\r\n", test); x(test); printf("[POST]: \"%s\"", test); }
