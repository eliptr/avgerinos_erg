#include <stdio.h>
#include <string.h>

int main() {
    int com = 68;  //η επιλογη του προγραμματος
    int ans = 67;  //η επιλογη του παικτη
    int round = 0;  //οι γυροι
    int fr = 0;  //μετραει σε ενα βαθμο το ποσο εκδικητικος η σθνεργατικος ειναι ο παικτης

    while (ans != EOF) {
        round++;
        putchar(com);
        printf("\n");
        fflush(stdout);
        do {
            ans = getchar();
            if (ans == EOF) break;
        } while(ans != 68 && ans != 67);  //διαβαζει μεχρι να βρει τον χαρακτηρα C ή D
        if (ans == EOF) break;
        while ( getchar() != '\n' );  //το getchar διαβαζει το υπολοιπο του buffer ωστε να μην ξαναεκτελεστει στην επομενη getchar

        com = 67 + (ans+1)%2;  //στον επομενο γυρο το προγραμμα θα παιξει οτι επαιξε ο παικτης πριν
        (ans == 67) ? fr++: fr--;      
        if (fr<(-6)|| fr>6) com = 68;  //εκτος αν ο παικτης ειναι πολυ εκδικητικος ή πολυ σθνεργατικος
        if (round > 1000000) return 1;
        if (round%1000 == 1) {    //ωστε το προγραμμα σιγουρα καθε 1000 γυρους να παιζει τουλαχιστον μια φορα C και D
            com = 67;
        } else if (round % 1000 == 2) {
            com = 68;
        }


    }

    return 0;
}
