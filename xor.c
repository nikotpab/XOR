#include <stdio.h>

int str_length(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

void encrypt(void);
void decrypt(void);
void print(char);

const char *ascii[128] = {
    "00000000", "00000001", "00000010", "00000011", "00000100", "00000101", "00000110", "00000111",
    "00001000", "00001001", "00001010", "00001011", "00001100", "00001101", "00001110", "00001111",
    "00010000", "00010001", "00010010", "00010011", "00010100", "00010101", "00010110", "00010111",
    "00011000", "00011001", "00011010", "00011011", "00011100", "00011101", "00011110", "00011111",
    "00100000", "00100001", "00100010", "00100011", "00100100", "00100101", "00100110", "00100111",
    "00101000", "00101001", "00101010", "00101011", "00101100", "00101101", "00101110", "00101111",
    "00110000", "00110001", "00110010", "00110011", "00110100", "00110101", "00110110", "00110111",
    "00111000", "00111001", "00111010", "00111011", "00111100", "00111101", "00111110", "00111111",
    "01000000", "01000001", "01000010", "01000011", "01000100", "01000101", "01000110", "01000111",
    "01001000", "01001001", "01001010", "01001011", "01001100", "01001101", "01001110", "01001111",
    "01010000", "01010001", "01010010", "01010011", "01010100", "01010101", "01010110", "01010111",
    "01011000", "01011001", "01011010", "01011011", "01011100", "01011101", "01011110", "01011111",
    "01100000", "01100001", "01100010", "01100011", "01100100", "01100101", "01100110", "01100111",
    "01101000", "01101001", "01101010", "01101011", "01101100", "01101101", "01101110", "01101111",
    "01110000", "01110001", "01110010", "01110011", "01110100", "01110101", "01110110", "01110111",
    "01111000", "01111001", "01111010", "01111011", "01111100", "01111101", "01111110", "01111111"
};

const char *ascci_ch[128] = {
    "NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL",
    "BS","TAB","LF","VT","FF","CR","SO","SI",
    "DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
    "CAN","EM","SUB","ESC","FS","GS","RS","US",
    " ","!","\"","#","$","%","&","'","(",")",
    "*","+",",","-",".","/","0","1","2","3",
    "4","5","6","7","8","9",":",";","<","=",
    ">","?","@","A","B","C","D","E","F","G",
    "H","I","J","K","L","M","N","O","P","Q",
    "R","S","T","U","V","W","X","Y","Z","[",
    "\\","]","^","_","`","a","b","c","d","e",
    "f","g","h","i","j","k","l","m","n","o",
    "p","q","r","s","t","u","v","w","x","y",
    "z","{","|","}","~","DEL"
};

int main(void) {
    while (1) {
        printf("Bienvenidx al encriptador XOR, ingrese la opción que desea realizar\n");
        printf("1. Encriptar\n2. Desencriptar\n3. Salir\n");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 1:
                encrypt();
                break;
            case 2:
                decrypt();
                break;
            case 3:
                return 0;
            default:
                printf("Entrada no válida\n");
        }
        printf("\n");
    }
}

void encrypt(void) {
    printf("Ingrese el texto que desea encriptar (máximo 100 caracteres)\n" );
    char input[101];
    scanf(" %100[^\n]", input);
    if (str_length(input) > 100) {
        printf("El mensaje no puede tener más de 100 caracteres\n");
        return;
    }

    printf("Ingrese la llave (máximo 99 caracteres)\n" );
    char key[100];
    scanf(" %99[^\n]", key);
    if (str_length(key) >= str_length(input)) {
        printf("La llave no puede ser más ni igual de larga que el mensaje\n");
        return;
    }
    printf("------------------------------------------------------------------------------------------\n" );
    if (str_length(key) == 0&&key[0]=='\0') {
        printf("La llave no puede estar vacía.\n");
        return;
    }

    char c[str_length(input)*8 + 1];
    int cIndex = 0;
    for (int i = 0; i < str_length(input); i++) {
        unsigned char bin = (unsigned char)input[i];
        const char *bits = ascii[bin];
        for (int j = 0; bits[j] != '\0'; j++) {
            c[cIndex] = bits[j];
            cIndex++;
        }
        printf("%s ", ascii[bin]);
    }
    c[cIndex] = '\0';
    printf("\n");

    int keyLen = (int)str_length(key);

    char k[str_length(input)*8 + 1];
    int kIn = 0;
    for (int i = 0; i < str_length(input); i++) {
        unsigned char binK = (unsigned char)key[i % keyLen];
        const char *bitsK = ascii[binK];
        for (int j = 0; bitsK[j] != '\0'; j++) {
            k[kIn++] = bitsK[j];
        }
        printf("%s ", bitsK);
    }
    k[kIn] = '\0';

    printf("\n");
    printf("------------------------------------------------------------------------------------------\n" );

    char res[ str_length(input)*8 + 1];
    for (int i = 0; i < str_length(input)*8 + 1; i++) {
        if (c[i] == k[i]) {
            res[i] = '0';
        }else {
            res[i] = '1';
        }
    }

    int tBits = (int)str_length(c);
    int tBytse = tBits / 8;
    char resInd[tBytse][9];

    int byteIdx = 0;
    int bitIdx = 0;
    for (int i = 0; i < tBits; i++) {
        resInd[byteIdx][bitIdx++] = res[i];
        if (bitIdx == 8) {
            resInd[byteIdx][8] = '\0';
            byteIdx++;
            bitIdx = 0;
        }
    }

    for (int b = 0; b < tBytse; b++) {
        printf("%s", resInd[b]);
        if (b + 1 < tBytse) printf(" ");
    }
    printf("\n");
    printf("------------------------------------------------------------------------------------------\n" );

    char final[tBytse + 1];
    for (int b = 0; b < tBytse; b++) {
        int val = 0;
        for (int j = 0; j < 8; j++) {
            val = (val << 1) | (resInd[b][j] == '1');
        }
        final[b] = (char)val;
    }
    final[tBytse] = '\0';

    printf("\n");
    printf("Resultado:\n");
    for (int i = 0; i < tBytse; i++) {
        unsigned char ch = (unsigned char)final[i];
        if (ch >= 32 && ch <= 126) {
            putchar(ch);
        } else {
            putchar('.');
        }
    }
    printf("\n");
    printf("Resultado en hexadecimal:\n");
    for (int i = 0; i < tBytse; i++) {
        printf("%02X", (unsigned char)final[i]);
        if (i + 1 < tBytse) printf(" ");
    }

}

void print(char txt) {
    printf("%s ", ascii[txt]);
}
void decrypt() {
        printf("Ingrese el texto que desea desencriptar (máximo 100 caracteres)\n" );
    char input[101];
    scanf(" %100[^\n]", input);
    if (str_length(input) > 100) {
        printf("El mensaje no puede tener más de 100 caracteres\n");
        return;
    }

    printf("Ingrese la llave (máximo 99 caracteres)\n" );
    char key[99];
    scanf(" %99[^\n]", key);
    if (str_length(key) >= str_length(input)) {
        printf("La llave no puede ser más ni igual de larga que el mensaje\n");
        return;
    }
    printf("------------------------------------------------------------------------------------------\n" );
    if (str_length(key) == 0&&key[0]=='\0') {
        printf("La llave no puede estar vacía\n");
        return;
    }



    char c[str_length(input)*8 + 1];
    int cIndex = 0;
    for (int i = 0; i < str_length(input); i++) {
        unsigned char bin = (unsigned char)input[i];
        const char *bits = ascii[bin];
        for (int j = 0; bits[j] != '\0'; j++) {
            c[cIndex] = bits[j];
            cIndex++;
        }
        printf("%s ", ascii[bin]);
    }
    c[cIndex] = '\0';
    printf("\n");

    int keyLen = (int)str_length(key);

    char k[str_length(input)*8 + 1];
    int kIn = 0;
    for (int i = 0; i < str_length(input); i++) {
        unsigned char binK = (unsigned char)key[i % keyLen];
        const char *bitsK = ascii[binK];
        for (int j = 0; bitsK[j] != '\0'; j++) {
            k[kIn++] = bitsK[j];
        }
        printf("%s ", bitsK);
    }
    k[kIn] = '\0';

    printf("\n");
    printf("------------------------------------------------------------------------------------------\n" );

    char res[ str_length(input)*8 + 1];
    for (int i = 0; i < str_length(input)*8 + 1; i++) {
        if (c[i] == k[i]) {
            res[i] = '0';
        }else {
            res[i] = '1';
        }
    }

    int tBits = (int)str_length(c);
    int tBytse = tBits / 8;
    char resInd[tBytse][9];

    int byteIdx = 0;
    int bitIdx = 0;
    for (int i = 0; i < tBits; i++) {
        resInd[byteIdx][bitIdx++] = res[i];
        if (bitIdx == 8) {
            resInd[byteIdx][8] = '\0';
            byteIdx++;
            bitIdx = 0;
        }
    }

    for (int b = 0; b < tBytse; b++) {
        printf("%s", resInd[b]);
        if (b + 1 < tBytse) printf(" ");
    }
    printf("\n");
    printf("------------------------------------------------------------------------------------------\n" );

    char final[tBytse + 1];
    for (int b = 0; b < tBytse; b++) {
        int val = 0;
        for (int j = 0; j < 8; j++) {
            val = (val << 1) | (resInd[b][j] == '1');
        }
        final[b] = (char)val;
    }
    final[tBytse] = '\0';

    printf("\n");
    printf("Resultado:\n");
    for (int i = 0; i < tBytse; i++) {
        unsigned char ch = (unsigned char)final[i];
        if (ch >= 32 && ch <= 126) {
            putchar(ch);
        } else {
            putchar('.');
        }
    }
    printf("\n");

    printf("Resultado en hexadecimal:\n");
    for (int i = 0; i < tBytse; i++) {
        printf("%02X", (unsigned char)final[i]);
        if (i + 1 < tBytse) printf(" ");
    }
}
