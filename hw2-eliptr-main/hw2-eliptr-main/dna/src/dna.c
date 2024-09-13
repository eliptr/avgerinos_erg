#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Error: arguments missing. Usage: ./dna dnafile1 dnafile2\n");
        return 1;
    }
    char *na1 = argv[1];
    char *na2 = argv[2];   //αποθηκεθει τα ονοματα των φακελων


    FILE* fi1 = fopen(na1, "r");  //ανοιγει τους φακελους και ελεγχει αν υπαρχουν
    if (fi1 == NULL) {
        printf("Error: cannot open file %s\n", na1);
        return 1;
    }
    FILE* fi2 = fopen(na2, "r");
    if (fi2 == NULL) {
        printf("Error: cannot open file %s\n", na2);
        return 1;
    }

    char test = 42;   //μια προσωρινη μεταβλητη ωστε να αποθηκευεται η τιμη που διαβαζει το fread και μετα να μπορει η τιμη να ελεγχθει
    int size1 = 0;
    int used = 0;  //μια προσωρινη μεταβλητη ωστε να μπορει να μεταγλωτιστη το προγραμμα, αν το used γινει NULL τοτε κατι πηγε λαθος στο διαβασμα του αρχειου (δεν ελεγχεται για την ασκηση)
    while (feof(fi1) == 0) {
        used = fread(&test, sizeof(char), 1, fi1);
        if (test == 'C' || test == 'T' || test == 'A' || test == 'G')  //βρισκει το μεγεθος των ζητοθμενων χαρακτηρων για τους δθο πινακες ωστε να μπορει να αρχικοποιειθει αποδοτικα ο πινακας
           size1++;
    }

    int size2 = 0;
    while (feof(fi2) == 0) {
        used = fread(&test, sizeof(char), 1, fi2);
        if (test == 'C' || test == 'T' || test == 'A' || test == 'G') 
           size2++;
    }

    char *t1 = malloc(size1*sizeof(char));   //αρχικοποιει τους πινακες (μα malloc γιατι μπορει να μην χωρανε στη στοιβα χρνοθ εκτελεσης)
    for(int i = 0;i<size1;i++) t1[i] = i % 10;  //%10 ωστε να ειναι διαδοχικα διαφορετικες οποτε αν κατι παει στο διαβασμα να μην μπερδεψει τις αρχικες τιμες ως κοινη αλθσιδα
    char *t2 = malloc(size2*sizeof(char));
    for (int i = 0;i<size2;i++) t2[i] = i % 10;
    fseek(fi1, 0, SEEK_SET);
    fseek(fi2, 0, SEEK_SET);
    
    int c1 = 0;
    int c2 = 0;

    while (feof(fi1) == 0) {        // γεμιζει τους πινακες με τις καταλληλες τιμες
        used = fread(&test, sizeof(char), 1, fi1);
        if (test == 'C' || test == 'T' || test == 'A' || test == 'G') t1[c1++] = test;
    }

    while (feof(fi2) == 0) {
        used = fread(&test, sizeof(char), 1, fi2);
        if (test == 'C' || test == 'T' || test == 'A' || test == 'G') t2[c2++] = test;
    }

    if (size1 == size2 && strcmp(t1, t2) == 0) {
        printf("%s\n", t1);
        return 0;
    }
    used++; //για τη μεταγλωτιση

    int maxsize = size1;  //το μεγεθος της μεγαλθτερης δυνατης κοινης αλυσιδας
    if (size1>size2) {
       maxsize = size2;
    }
    char *maxs = malloc(maxsize*sizeof(char));
    char *tempmaxs = malloc(maxsize*sizeof(char));
    for (int i = 0;i<maxsize;i++) {
        maxs[i] = 0;
        tempmaxs[i] = 0;
    }
    int tempmaxc = 0;  //μετρητες για τους πινακες
    int maxc = 0;
    int flag = 0;
    
    int i = 0;
    while (i<size1) {  //περνα ενα ενα τα στοιχει του πρωτου φακελου

        int j = 0;
        while (j<size2 && i+tempmaxc<size1) {  //ο δευτερος ελεγχος για να μην βγει απο τα ορια του πινακα
            if (t1[i+tempmaxc] == t2[j]) {  // ελεγχει αν δθο στοιχεια ειναι ισα
                tempmaxs[tempmaxc] = t1[i+tempmaxc];  //αποθηκεθει τη τιμη στο προσωρινο πινακα και συνεχιζει μεχρι δυο στοιχεια δεν ειναι ισα
                tempmaxc++;
                j++;
                flag = 0;
            } else {
                if (tempmaxc>maxc) {  //αν το προσωρινο ειναι μεγαλθτερο απο το μαξ τοτε βρεθηκε μια ακομα μεγαλθτερη αλθσιδα

                    for (int k=0;k<tempmaxc;k++) {  //αποθηκευει τη νεα αλυσιδα ως την καινουρια μεγαλυτερη
                        maxs[k] = tempmaxs[k];
                    }
                    maxc = tempmaxc;

                }
                if (flag == 0) {  //αν το φλαγκ ειναι 0 τοτε ειναι στιγμη ποθ τελειωσε η κοινη αλυσιδα
                    flag = 1; //δεν αυξανεται το j για να μην χαθει ο ελεγχος για εκεινο το στοιχειο
                } else {
                    j++;
                }
                tempmaxc = 0; //επειδη τελειωσε η προηγοθμενη κοινη αλθσιδα, να ξεκινησει η επομενη
            }
            
        }
        i++;
        
    }
    // ξαναγινεται η παραπανω διαδικασια αλλα με αναποδα τοθς πινακες
    //αυτο επειδη η διαδιακασια δουλεθει σιγουρα αν ο δευτερος πινακας ειναι ο μικροτερος
    tempmaxc = 0;
    flag = 0;
    int j = 0;
    while (j<size2) {
        int i = 0;
        while (i<size1 && j+tempmaxc<size2) {
            if (t2[j+tempmaxc] == t1[i]) {
                tempmaxs[tempmaxc] = t2[j+tempmaxc];
                tempmaxc++;
                i++;
                flag = 0;
            } else {
                if (tempmaxc>maxc) {
                    for (int k=0;k<tempmaxc;k++) {
                        maxs[k] = tempmaxs[k];
                    }
                    maxc = tempmaxc;

                }
                if (flag == 0) {
                    flag = 1;
                } else {
                    i++;
                }
                tempmaxc = 0;
            }
            
        }
        j++;
        
    }
    printf("%s\n", maxs);


    fclose(fi1);
    fclose(fi2);
    free(t1);
    free(t2);
    free(tempmaxs);
    free(maxs);
    return 0;
}
