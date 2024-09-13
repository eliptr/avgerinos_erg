#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long flsum = 0;

int getdig(long nu) {   //βρισκει τον αριθμο ψηφιων
  int ret = 0;
  while (nu != 0) {
    ret++;
    nu /= 10;
  }
  return ret;
}

int getsum(long nu, int p) {  //βρισκει το αθροισμα των ψηφιων ανα p ψηφια(δηλαδη getsum(1234,2) = 12 + 34)
  int s = 0;
  int rem;
  while (nu != 0) {
    rem = nu % (long)pow(10, p);
    s = s + rem;
    nu /= pow(10, p);
  }
  return s;
}

int symtest(long nu, int dig, long i, long left) { //καλει την getsum σπαζοντας καθε φορα τον αριθμο ανα 1 μεχρι τα ψηφια του
  for (int j = 1; j <= dig; j++) {
    int tes = getsum(nu, j);
    if (tes + left == i) {    //ελεγχει αν ο τρεχων σθνδιασμος ειναι σωστος

      return 1;
    }
  }
  return 0;
}

int ch(long nu, int dig, long remleft, long i) {   //καθε for σπαει τον αριθμο και καλει την symtest για να ελεγξει αν το αθροισμα 
  for (int k = dig; k > 0; k--) {                  //των σπασμενων ισοθται με το i
    long left = nu / (long)pow(10, k - 1);  //edv to σπαει πρωτη φορα απο αριστερα αποθηκεθει το αριστερο κομματι και επεξαργεζεται αναλογως το δεξι
    long newnu = nu % (long)pow(10, k - 1);
    if (symtest(newnu, k, i, left + remleft)) {

      return 1;
    }
    for (int r = 0; r < k; r++) {
      long right = nu % (long)pow(10, r);  //το αντιστοιχο με την πανω for για το δεξι μερος αλλα σπαει απο δεξια
      long rnewnum = newnu / (long)pow(10, r);
      if (symtest(rnewnum, k - r, i, right + left + remleft)) {

        return 1;
      }
      for (int l2 = getdig(rnewnum); l2 > 1; l2--) {
        long left2 = rnewnum / (long)pow(10, l2 - 1);  //το αντιστοιχο με την πανω for για το αριστερο παλι 
        long lnewnum = rnewnum % (long)pow(10, l2 - 1);
        if (symtest(lnewnum, l2, i, right + left + remleft + left2)) {

          return 1;
        }
        for (int r2 = 0; r2 < getdig(lnewnum); r2++) {
          long right2 = lnewnum / (long)pow(10, r2);     //για το δεξι παλι
          long r2newnum = lnewnum % (long)pow(10, r2);  
          if (symtest(r2newnum, getdig(lnewnum) - r2, i,right + left + remleft + left2 + right2)) {

            return 1;
          }
        }
      }

    }

  }
  return 0;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    return 1;
  }

  long l = (atol(argv[1]));
  long h = (atol(argv[2]));
  if (l > h || l <= 0 || h > pow(10, 12)) return 1;
  long bot = ceill(sqrt(l));  //θετει τα ορια για να ελεγχθουν μονο τα τελεια τετραγωνα
  long lim = floorl(sqrt(h));

  for (long i = bot; i <= lim; i++) {
    if (getsum(i,1) % 9 == 0 ||getsum(i,1) % 9 == 1) {      //προθποθεση για να ειναι flawless
    
    long nu = i * i;
    int dig = getdig(nu);

    int loopc = dig;
    long remleft = 0;
    long numshift = nu;
    while (loopc != 0) {     //κανει την ιδια διαδικασια με πανω, για ενα ψηφιο καθε φορα και ελεγχει το αποτελσμα
      remleft += numshift / (long)pow(10, loopc);
      long remnewnu = numshift % (long)pow(10, loopc);
      if (ch(remnewnu, loopc, remleft, i)) {
        flsum += nu;
        break;
      }
      numshift = remnewnu;

      loopc--;
    }
    
    }

  }

  printf("%ld\n", flsum);
  return 0;
}
