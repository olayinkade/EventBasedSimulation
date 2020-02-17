CC = clang++
CFLAGS = -g -Wall -DNDEBUG

PROG = main
HDRS = Event.h Node.h Obj.h Simulation.h Queue.h PriorityQueue.h Process.h
SRCS = main.cpp Event.cpp Node.cpp Obj.cpp Simulation.cpp Queue.cpp PriorityQueue.cpp Process.cpp

OBJDIR = object
OBJS = $(OBJDIR)/main.o $(OBJDIR)/Node.o $(OBJDIR)/Event.o $(OBJDIR)/Obj.o $(OBJDIR)/Simulation.o $(OBJDIR)/Queue.o $(OBJDIR)/PriorityQueue.o $(OBJDIR)/Process.o

# compiling rules

# WARNING: *must* have a tab before each definition
$(PROG): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

$(OBJDIR)/Event.o: Event.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c Event.cpp -o $(OBJDIR)/Event.o

$(OBJDIR)/main.o: main.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/Node.o: Node.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c Node.cpp -o $(OBJDIR)/Node.o
 
 $(OBJDIR)/Obj.o: Obj.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c Obj.cpp -o $(OBJDIR)/Obj.o
 
 $(OBJDIR)/Simulation.o: Simulation.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c Simulation.cpp -o $(OBJDIR)/Simulation.o
 
 $(OBJDIR)/Queue.o: Queue.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c Queue.cpp -o $(OBJDIR)/Queue.o
 
 $(OBJDIR)/PriorityQueue.o: PriorityQueue.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c PriorityQueue.cpp -o $(OBJDIR)/PriorityQueue.o
 
 $(OBJDIR)/Process.o: Process.cpp $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c Process.cpp -o $(OBJDIR)/Process.o

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(PROG) $(OBJS)