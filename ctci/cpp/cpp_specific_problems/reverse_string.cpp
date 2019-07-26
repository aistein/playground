#include <iostream>
#include <string> 

using namespace std;

void reverseString( char* str )
{
    int n = strlen(str);
    char tmp;
    for (int i = 0; i < n / 2; i++) {
        tmp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = tmp;
    }
    return;
}


int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "usage: ./reverse_string \"<your-string>\"" << endl;
        exit(-1);
    }

    char *str = argv[1];
    printf("input:  \"%s\"\n", str);
    
    reverseString( str );
    printf("output: \"%s\"\n", str);

    return 0;
}