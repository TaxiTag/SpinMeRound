#ifndef SANITIZE_H
#define SANITIZE_H

/*Kill the process associated with spin_me_round*/
int kill_process(void);

/*Destroys the payload hidden in afs*/
int del_payload(void);

/*Asks for user validation before doing the thing*/
int ask_confirmation(void);

/*Gets rid of spin_me_round confloose*/
int sanitize(void);

/*Removes the lock file*/
int remove_lock(void);

#endif