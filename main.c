#include <stdio.h>

int main() {

    int b, g, r;
    char name[30];

//    printf("\nHi, in this program you can change the color/shade"
//           " of your image in .bmp format.\n"
//           "All you have to do is enter the next 3 numbers of color intensities (0-255; blue, green, red),"
//           "if you would like to leave the color unchanged, write \"-1\"."
//           " Then enter the name of your photo file (e.g. \"picture1.bmp\"). The program will"
//           " create a new version of photo according to your color requirements (\"new.bmp\"). \n\n ");

    printf("BLUE (0-255): ");
    scanf("%d", &b);
    printf("GREEN (0-255): ");
    scanf("%d", &g);
    printf("RED (0-255): ");
    scanf("%d", &r);

    printf("\nOK, now enter the exact file name of the photo: \n");
    scanf("%s", name);

    FILE* in = fopen(name,"rb");
    FILE* out = fopen("new.bmp","wb");

    unsigned char info[54];

    fread(info, 1, 54, in);
    fwrite(info, 1, 54, out);

    int width = *(int *)&info[18];
    int height = *(int *)&info[22];

    unsigned int padding = width%4;

    for(int i = 0;i < height;i++){
        for(int j = 0;j < width;j++){

            unsigned char px[3];
            fread(px,1,3,in);

            if(b!=-1)
                px[0] = b;

            if(g!=-1)
                px[1] = g;

            if(r!=-1)
                px[2] = r;

            fwrite(px,1,3,out);
        }

        unsigned char pom2[4];
        fread(pom2,1,padding,in);
        fwrite(pom2,1,padding,out);
    }

    fclose(in);
    fclose(out);

    printf("\nDONE!\n");

    return 0;
}