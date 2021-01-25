void parse_int(int number, char* str, int base) {
    if(base > 36)
        return;

    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    char remainder;
    while(number >= 0 && length >= 0) {
        length--;
        remainder = (number % base);
        if(remainder > 9) {
            remainder -= 10;
            str[length] = 'A' + remainder;    
        } else {
            str[length] = '0' + remainder;
        }
        number /= base;
    }
}