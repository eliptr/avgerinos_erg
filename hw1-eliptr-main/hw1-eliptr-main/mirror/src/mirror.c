#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long getkat (long nu) {    // συναρτηση που δεχεται εναν αριθμο και επιστρεφει το κατοπτρο του
    long ret = 0;
    long rem;
    while (nu!=0) {     
        rem = nu%10;         //αποθηκευει το ψηφιο των μοναδων
        ret = ret *10 + rem;   //προσθετει το τελεθταιο ψηφιο
        nu /= 10;  // καθε φορα ο αριθμος διαρειται ακεραιαμε το 10, ετσι θα γινουν τοσε επαναληψεις οσες και τα ψηφια
    }
    return ret;  
}

int ispal(long nu) {   // συναρτηση που δεχεται εναν αριθμο και επιστρεφει 0 ή 1 αναλογα αν ειναι παλινδρομικος ή οχι
    long new = getkat(nu);
    if (new == nu) return 1;      // αν ο αριθμος ειναι παλινδρομικος τοτε το κατοπτρο του θα ειναι ισο με αυτον
    return 0;
}

int main(int argc, char **argv) {

    if (argc != 3) {  // ελεγχει αν δωθηκε ακριβως το ονομα, το κατω οριο και το ανω οριο
        printf("again\n");
        return 1;
    }

    long l = atol(argv[1]);   // διαβαζει τα ορισματα
    long h = atol(argv[2]);
    if (h > pow(10,15) || l>h) return 1;   // ελεγχει αν ειναι εντος οριων
    if (l <= 0) return 1;

    long lim = floorl(sqrt(h));   // θετουμε το ανω οριο στη ριζα του ευρους ποθ δοθηκε για να βρουμε κατευθειαν τους πρωτους αριθμους και μετα να ελεγξοθμε το τετραγωνο τους
    l = ceill(sqrt(l));     //αντιστοιχα και για το κατω οριο

    int c = 1; // ελεγχουμε αν το κατω οριο ειναι ζυγος ωστε η for αργοτερα να αρχικοποειται σιφουρα σε μονο αριθμο
    if (l % 2 == 1) c = 0;
    l += c; 

    long sum = 0;
    int f = 0;     //αυξανεται αν παρατηρειται οτι η ριζα του αριθμου δεν ειναι πρωτος αριθμος ή το κατοπτρο του δεν ειναι τελειο τετραγωνο 

    for (long i = l; i <=lim; i+=2) {     // ελεγχει το ευρος που θα μπορουσε το τετραγωνο του i να ειναι κατοπτρικό πρώτο τετράγωνο με βημα δυο γιατι οι ζυγοι σιγουρα δεν ειναι
        long nu = i*i;  // το πιθανο κατοπτρικό πρώτο τετράγωνο

        if (floorl(sqrt(getkat(nu))) == sqrt(getkat(nu))) {   //ελεγχει αν το κατοπτρο του αριθμου ειναι τελειο τετραγωνο
            for (long j = 3;j<i/2 + 1;j+=2) { // ελεγχει αν το i ειναι πρωτοσ αριθμος
                if (i % j == 0) {                        
                    f++;      
                    break;
                }
            }
        } else {
            f++;
        }

        if (f == 0) {                
            long mir = getkat(nu);                
            long romir = sqrt(mir);
            int fm = 0;  // αυξανεται οταν παρατηρειται οτι η ριζα του κατοπτρου δεν ειανι πρωτος
            for (long k = 3;k<romir/2 + 1;k+=2) {  //ελεγχει αν η ριζα του κατοπτρου ειναι πρωτος
                if (romir % k == 0 || romir %2 == 0) {
                    fm++;
                    break;
                }    
            }
            if (fm == 0) {
                if (!ispal(nu)) {    // ελεγχει αν ο αριθμος ειναι παλινδρομικος
                    sum = sum + nu;  //ο αριθμος ειναι κατοπτρικο πρωτο τετραγωνο και προσθετεται στο τελικο αθροισμα
                }
            }
            fm = 0; //αρχικοποιει παλι τον ελεγχο
        }
        f = 0;  //αρχικοποιει παλι τον ελεγχο
    }
       

    printf("%ld\n", sum); //εκτυπωνει το αποτελεσμα
    return 0;
}


