all:
  gcc log.c init.c mission.c server.c  -o server
  
clean:
  rm -rf *.o
  rm -rf server
