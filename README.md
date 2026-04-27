# Spin me round

## Confloose

Spin me round is a simple confloose made by a student in ordre to pull pranks on people who didn't lock their computer.
It just turns the screen of the computer in a random direction once in a while.

It works in 3 phases :
- Setup

    You have to run the confloose in the "/home/user/ " directory. Otherwise, the confloose will have uninted effects, I am NOT responsible for any of these.
    When the confloose is executed, it will look for a lock file in tmp that it usually creates, if it doesn't exist, the confloose will enter it's hiding phase.

- Hiding

    Since this confloose is made for a specific config, it will create a .local file in /home/user/afs.
    Then it adds a line in the .bashrc in order to autostart.

- Executing payload

    Once everything is done, the program creates a user daemon named spin_me_round, this daemon waits a random time and then
    flips the screen. It repeats this process until killed.

## Sanitizer

If you consider that the person did not deserve this, you can compile the sanitizer using the makefile.
It will kill the daemon and remove the folder where it is hidden.
