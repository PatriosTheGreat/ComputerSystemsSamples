gcc -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.c -ldl
gcc -o intr int.c

# (setenv LD_PRELOAD "./mymalloc.so"; ./intr; unsetenv LD_PRELOAD)