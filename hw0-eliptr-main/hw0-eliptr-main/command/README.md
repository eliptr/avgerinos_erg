bandit0: μπηκα με την εντολη ssh bandit0@bandit.labs.overthewire.org -p2220 οπως και στα υπολοιπα 

bandit1: με την εντολη cat readme εμφανισα τον κωδικο

bandit2: με την εντολη cat ./- εμφανισα τα περιεχομενα του -

bandit3: με την εντολη cat "spaces in this filename" εμφανισα τα περιεχομενα του spaces in this filename

bandit4: εκανα cd inhere για να μπω στο φακελο και ls -a για να δω τα ονοματα των hidden files και μετα cat 

bandit5: εκανα cd inhere για να μπω στο φακελο και cat σε ολα τα αρχεια για να δω ποιο ειναι human readable

bandit6: με την εντολη find -size 1033c -perm 640 μου εμφανισε εναν φακελα ποθ πληρει τις προυποθεσεις, ο οποιος ηταν και κρυφος. μετα εκανα cd στο path του και εμφανισα τα περιεχομενα με cat και ειδα οτι ειναι human readabel

bandit7: εκανα 2 φορες cd .. για να παω στο κυριο directory και με την εντολη find -group bandit6 -user bandit7 μου εμφανισε διαφορα αρχεια. Ενα απο αυτα λεγοταν 
badit7.password και εκανα cd στο φακελο που βρισκοταν, ειδα οτι ειναι το καταλληλο μεγεθος και με cat εμφανισε τον κωδικο

bandit8: με την εντολη grep millionth data.txt εμφανισα την καταλληλη γραμμη με τον κωδικο

bandit9: με την εντολη sort data.txt εμφανισα ολες της γραμμες σε αλφαβητικη σειρα. επειδη ολες επαναλαμβανοντοθσαν πολλες φορες ηταν ευκολο να διακρινω ποια ηταν μοναδικη οπου αυτη ηταν και ο κωδικος

bandit10: με την εντολη strings data.txt εμφανισε μονο τους printable χαρακτηρες ξεχωριζοντας ετσι της γραμμες με το ====== που αποκαλυπτουν τον κωδικο

bandit11: με την εντολη base64 -d data.txt εκανε decode το encoded data.txt και εμφανισε το μηνυμα με τον κωδικο