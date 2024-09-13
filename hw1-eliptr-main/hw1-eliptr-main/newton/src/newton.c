#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	double a1,a2,a3,a4,a5,a0,x0;

	if (argc != 8) {    // ελεγχει αν δωθηκε το ονομα, οι 6 συντελεστες και το αρχικο χ0
	    printf("again\n");
	    return 1;
	}

    char *test;   //το χρειαζεται η strtod() και αποθηκευει τη διευθηνση μεσα στο string μετα το double

    a0 = strtod(argv[1], &test);      //αποθηκευει τους συντελεστες και το χ0 στις μεταβλητες
    a1 = strtod(argv[2], &test);
    a2 = strtod(argv[3], &test);
    a3 = strtod(argv[4], &test);
    a4 = strtod(argv[5], &test);
    a5 = strtod(argv[6], &test);
    x0 = strtod(argv[7], &test);

    double sol;
    int te = 0;
    double f,fd;

    for (int i = 0;i<1000;i++) {
        f = a0 + a1*x0 + a2*x0*x0 + a3*x0*x0*x0 + a4*x0*x0*x0*x0 + a5*x0*x0*x0*x0*x0;     //υπολογιζει τη τιμη της συναρτησης που εδωσε ο χρηστης
        fd = a1 + 2*a2*x0+ 3*a3*x0*x0 + 4*a4*x0*x0*x0 + 5*a5*x0*x0*x0*x0;                 //υπολογιζει τη τιμη της παραγωγου της συναρτησης που εδωσε ο χρηστης

        if (fd == 0  || isnan(f + fd)) {       //ελεγχει αν μπορει να γινει διαιρεση με το μηδεν ή αν καποια τιμη ειναι nan
            printf("nan\n");
            return 0;          //τερματιζει το προγραμμα
        }

        sol = x0 - f/fd;        //υπολογιζει την προσεγγιση της λυσης
        if (fabs(sol - x0)< 0.000001) {     //ελεγχει αν η νεα προσεγγιση ειναι αρκετα κοντα στο 0 οσο ζηταει η ασκηση
            break;
        }

        x0 = sol;     //αν δεν ειναι, θετει το επομενο χ0 ωστε η for να υπολογισει την επομενη προσεγγιση
        te = i;       //αποθηκεθει το ποσες επαναληψεις εχουν γινει

    }

    if (te == 999) {       //ελεγχει αν ο αλγοριθμος δεν κατεφερε σε 1000 επαναληψεις να βρει αρκετα καλη λυση
        printf("incomplete\n");
    } else if (fd != 0) {        //αφου βρηκε τυπωνει το αποτελεσμα
        printf("%.2f\n", sol);
    }

	return 0;
}
