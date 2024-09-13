#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char mn[2];
    int used; //για τη μεταγλωτηση, αν το used ειναι null τοτε κατι πηγε στραβα στο διαβασμα (δεν ελεγχεται για την ασκηση)
    int temp; //"αχρηστη" μεταβλητη χρησιμοποιειται για το paddding
    used = fread(&mn, sizeof(mn), 1, stdin); //μαγικοι αριθμοι, ελεγχεται οτι το αρχειο ειναι οντως BMP
    if (strcmp(mn, "BM") != 0) {
        printf("Error: not a BMP file\n");
        return 1;
    }
    //αρχικοποιοθνται τιμες με βασικα στοιχεια της εικονας
    int fil_siz;
    used = fread(&fil_siz, sizeof(int), 1, stdin);
    fseek(stdin, 10, SEEK_SET); //αλλαζει το ποιο byte διαβαζεται
    int head;
    used = fread(&head, sizeof(int), 1, stdin);
    if (head < 54) return 1;
    fseek(stdin, 22, SEEK_SET);
    int height_p;
    used = fread(&height_p, sizeof(int), 1, stdin);
    fseek(stdin, 18, SEEK_SET);
    int width_p;
    used = fread(&width_p, sizeof(int), 1, stdin);
    fseek(stdin, 34, SEEK_SET);
    int imsi_wp;
    used = fread(&imsi_wp, sizeof(int), 1, stdin);

    if (imsi_wp != fil_siz - head) return 1; //ελεγχος οτι η εικονα εχει σωστα στοιχεια

    int pad_b = width_p % 4;  // το παντινγκ αυτης της εικονας


    int pad_a = height_p % 4;  // το παντινγκ που θα χρειαζεται η γυρισμενη εικονα

    if (height_p*width_p*3 + pad_b*height_p != imsi_wp) return 1;  //ελεγχος οτι η εικονα εχει σωστα στοιχεια
    if (height_p*width_p*3 + pad_b*height_p + head != fil_siz) return 1;




    int **p = malloc(width_p * sizeof(int*));  //αρχικοποιειται πινακας των πιξελς της γυρισμενης εικονας
    for (int i = 0; i < width_p; i++)
        p[i] = malloc(height_p*3 * sizeof(int));

    fseek(stdin, head, SEEK_SET);

    for(int j = 0;j<height_p*3;j= j+3) {  //τα στοιχεια του πινακα αρχικοποιοθνται καθετα για να ειναι γθρισμενα τα πιξελς αφοθ το fread τα διαβαζει οριζοντια

        for(int i = 0;i<width_p;i++){
            used = fread(&p[i][j], 1, 1, stdin);  // ανα τρια αφοθ ενα πιξελ χρειαζεται τρεις τιμες RGB
            used = fread(&p[i][j + 1], 1, 1, stdin);
            used = fread(&p[i][j + 2], 1, 1, stdin);
            if (pad_b != 0 && i+1>=width_p) { //διαβαζει το παντινγκ αν υπαρχει ωστε να μην αποθηκευτει στον πινακα μας
                used = fread(&temp, pad_b, 1, stdin);
            }
        }
    }

    fseek(stdin, 0, SEEK_SET);
    int *h = malloc(head*sizeof(int));  //ωστε να αντιγραφθοθν τα στοιχεια της κεφαλιδας
    for (int i =0; i<head;i++) {
        used = fread(&h[i], 1, 1, stdin);
    }

    int new_size = width_p*height_p*3 + pad_a*width_p + head;  //τα νεα βασικα στοιχεια της εικονας
    int new_im = new_size - head;
    used = used;
    
    //ορισμος της κεφαλιδας της νεας εικονας
    fwrite(&mn, sizeof(mn), 1, stdout);
    fwrite(&new_size, sizeof(int), 1, stdout);
 
    for (int i =6; i<head;i++) {
        if (i == 22) {  //μεταβαλλονται οι διαφορες στο μεγεθος της νεας εικονας
            fwrite(&width_p, sizeof(int), 1, stdout);
        } else if (i == 18) {
            fwrite(&height_p, sizeof(int), 1, stdout);
        } else  if ((i>1 && i<18) || (i>25 && i<34) || (i>37)){
            fwrite(&h[i], 1, 1, stdout);
        } else if (i == 34) {
            fwrite(&new_im, sizeof(int), 1, stdout);
        }
    }

    temp = 0;
    for(int i = width_p -1;i>=0;i--) {

        for(int j =0;j<height_p*3;j=j+3){
            fwrite(&p[i][j], 1, 1, stdout);  //γραφονται τα πιξελσ στη καταλληλη σειρα της γυρισμενης εικονας
            fwrite(&p[i][j + 1], 1, 1, stdout);
            fwrite(&p[i][j +2], 1, 1, stdout);
            if (pad_a != 0 && j+3>=height_p*3) { // ελεγχει αν χρεαιζεται παντινγκ στο τελος καθε σειρας και το θετει αναλογως
                fwrite(&temp,pad_a,1,stdout);
            }
        }
    }




    for (int i = 0; i < width_p; i++)
        free(p[i]);

    free(p);
    free(h);
    return 0;
}
