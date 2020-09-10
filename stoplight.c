
#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>
#include <machine/spl.h>

#define NCARS 20

struct lock *NW;
struct lock *NE;
struct lock *SW;
struct lock *SE;

struct lock *N;
struct lock *S;
struct lock *E;
struct lock *W;

int threadsLeft = 0; //How many threads have ended. We need 20, or NCARS

/*
Directional guide:
	North = 0
	|	|
	|	|
________|	|_______
	 NW | NE
West = 3 _______ East = 1
________ SW | SE________
	|	|
	|	|
	|	|
	South = 2
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */


static
void
gostraight(unsigned long cardirection,
           unsigned long carnumber)
{


	//Locks are acquired in priority order : NE before NW before SW before SE.(NE> NW > SW > SE)
	//Locks are released in the order the car leaves the intersection.
	if(cardirection == 0){
		//if the car comes from the North
		//Need locks NW and SW
		
		lock_acquire(NW);
		
		lock_acquire(SW);

		//Once a car has started getting the locks it needs, it can enter the intersection
		kprintf("Car %lu ENTERING going straight from the North, towards South \n", carnumber);

		//I was told having the prints like this was okay in Piazza post @183

		//Once the car has released all its locks, it can release them and leave
		//this LEAVING message must come before the locks are released so 
		//mesages don't appear out of order
		kprintf("Car %lu LEAVING going straight from the North, towards South\n", carnumber);
		
		lock_release(N);

		lock_release(NW);

		lock_release(SW);

	}
	else if(cardirection == 1){
		//if the car comes from the East
		//Need locks NW and NE

        	lock_acquire(NE);

        	lock_acquire(NW);

		kprintf("Car %lu ENTERING going straight from the East, towards West \n", carnumber);

		kprintf("Car %lu LEAVING going straight from the East, towards West \n", carnumber);
		
		lock_release(NE);

        	lock_release(NW);
		
		lock_release(E);

	}
	else if(cardirection == 2){
		//if the car comes from the South
		//Need locks SE and NE
    
        	lock_acquire(NE);

        	lock_acquire(SE);	

		kprintf("Car %lu ENTERING going straight from the South, towards North \n", carnumber);

		kprintf("Car %lu LEAVING going straight from the South, towards North \n", carnumber);
	
		lock_release(SE);

		lock_release(NE);
		
		lock_release(S);

	}
	else if(cardirection == 3){
		//if the car comes from the West
		//Need locks SW and SE
		
        	lock_acquire(SW);

        	lock_acquire(SE);

		kprintf("Car %lu ENTERING going straight from the West, towards East \n", carnumber);
		
		kprintf("Car %lu LEAVING going straight from the West, towards East \n", carnumber);
		
		lock_release(SE);

		lock_release(SW);

		lock_release(W);

	}
}


/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection,
         unsigned long carnumber)
{

	if(cardirection == 0){
		//if the car comes from the North
		//Need locks NW and SW and SE
		
		lock_acquire(NW);

		lock_acquire(SW);

		lock_acquire(SE);

		kprintf("Car %lu ENTERING turning left from the North, towards East \n", carnumber);

		kprintf("Car %lu LEAVING turning left from the North, towards East \n", carnumber);

		lock_release(NW);

		lock_release(SW);

		lock_release(SE);

		lock_release(N);

	}
	else if(cardirection == 1){
		//if the car comes from the East
		//Need locks NW and NE and SW

        	lock_acquire(NE);
	
        	lock_acquire(NW);

		lock_acquire(SW);

		kprintf("Car %lu ENTERING turning left from the East, towards South \n", carnumber);
		
		kprintf("Car %lu LEAVING turning left from the East, towards South \n", carnumber);

        	lock_release(NE);

		lock_release(NW);

		lock_release(SW);

		lock_release(E);

	}
	else if(cardirection == 2){
		//if the car comes from the South
		//Need locks SE and NE and NW
    
        	lock_acquire(NE);

        	lock_acquire(NW);

		lock_acquire(SE);

		kprintf("Car %lu ENTERING turning left from the South, towards West \n", carnumber);

		kprintf("Car %lu LEAVING turning left from the South, towards West \n", carnumber);

        	lock_release(SE);

		lock_release(NE);

        	lock_release(NW);

		lock_release(S);

	}
	else if(cardirection == 3){
		//if the car comes from the West
		//Need locks SW and SE and NE

       	 	lock_acquire(NE);
		
        	lock_acquire(SW);	
			
		lock_acquire(SE);

		kprintf("Car %lu ENTERING turning left from the West, towards North \n", carnumber);

		kprintf("Car %lu LEAVING turning left from the West, towards North \n", carnumber);

		lock_release(SW);

		lock_release(SE);

		lock_release(NE);

		lock_release(W);
	}
}


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long cardirection,
          unsigned long carnumber)
{

	if(cardirection == 0){
		//if the car comes from the North
		//Need locks NW
		
		lock_acquire(NW);

		kprintf("Car %lu ENTERING turning right from the North, towards West \n", carnumber);

		kprintf("Car %lu LEAVING turning right from the North, towards West \n", carnumber);

		lock_release(NW);
		
		lock_release(N);

	}
	else if(cardirection == 1){
		//if the car comes from the East
		//Need locks NE
		
		lock_acquire(NE);
		
		kprintf("Car %lu ENTERING turning right from the East, towards North \n", carnumber);

		kprintf("Car %lu LEAVING turning right from the East, towards North \n", carnumber);

		lock_release(NE);
		
		lock_release(E);

	}
	else if(cardirection == 2){
		//if the car comes from the South
		//Need locks SE
		
		lock_acquire(SE);
		
		kprintf("Car %lu ENTERING turning right from the South, towards East \n", carnumber);

		kprintf("Car %lu LEAVING turning right from the South, towards East \n", carnumber);

		lock_release(SE);

		lock_release(S);

	}
	else if(cardirection == 3){
		//if the car comes from the West
		//Need locks SW
		
		lock_acquire(SW);

		kprintf("Car %lu ENTERING turning right from the West, towards South \n", carnumber);

		kprintf("Car %lu LEAVING turning right from the West, towards South \n", carnumber);

		lock_release(SW);

		lock_release(W);

	}	
	
}

/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */
 
static
void
approachintersection(void * unusedpointer,
                     unsigned long carnumber)
{
        int cardirection;

	int spl;

        (void) unusedpointer;

        /*
         * cardirection is set randomly.
         */

        cardirection = random() % 4;

	/*Randomly select which direction the car is turnin
	0 = turn left
	1 = straight
	2 = turn right
	*/
	int carTurn = random() % 3;
	
	if(carTurn == 0){
		
		if(cardirection == 0){
			//if the car comes from the North
			kprintf("Car %lu APPROACHING from the North turning left, towards East\n", carnumber);
			
			lock_acquire(N);
		}
		else if(cardirection == 1){
			//if the car comes from the East
			kprintf("Car %lu APPROACHING from the East turning left, towards South\n", carnumber);
			
			lock_acquire(E);
		}
		else if(cardirection == 2){
			//if the car comes from the South
			kprintf("Car %lu APPROACHING from the South turning left, towards West\n", carnumber);
			
			lock_acquire(S);
		}
		else if(cardirection == 3){
			//if the car comes from the West
			kprintf("Car %lu APPROACHING from the West turning left, towards North\n", carnumber);
			
			lock_acquire(W);
		}

		turnleft(cardirection, carnumber);
	}
	else if(carTurn == 1){
		
		if(cardirection == 0){
			//if the car comes from the North
			kprintf("Car %lu APPROACHING from the North going straight, towards South\n", carnumber);

			lock_acquire(N);
		}
		else if(cardirection == 1){
			//if the car comes from the East
			kprintf("Car %lu APPROACHING from the East going straight, towards West\n", carnumber);
			
			lock_acquire(E);
		}
		else if(cardirection == 2){
			//if the car comes from the South
			kprintf("Car %lu APPROACHING from the South going straight, towards North\n", carnumber);
			
			lock_acquire(S);
		}
		else if(cardirection == 3){
			//if the car comes from the West
			kprintf("Car %lu APPROACHING from the West going straight, towards East\n", carnumber);
			
			lock_acquire(W);
		}
		
		gostraight(cardirection, carnumber);

	}
	else if(carTurn == 2){

		if(cardirection == 0){
			//if the car comes from the North
			kprintf("Car %lu APPROACHING from the North turning right, towards West\n", carnumber);
			
			lock_acquire(N);
		}
		else if(cardirection == 1){
			//if the car comes from the East
			kprintf("Car %lu APPROACHING from the East turning right, towards North\n", carnumber);
			
			lock_acquire(E);
		}
		else if(cardirection == 2){
			//if the car comes from the South
			kprintf("Car %lu APPROACHING from the South turning right East\n", carnumber);
			
			lock_acquire(S);
		}
		else if(cardirection == 3){
			//if the car comes from the West
			kprintf("Car %lu APPROACHING from the West turning right South\n", carnumber);
			
			lock_acquire(W);
		}

		turnright(cardirection, carnumber);
	}	

	threadsLeft++;
	spl = splhigh();
	//If 20 (NCARS) cars have left, we wakeup the main thread
	if(threadsLeft == NCARS){
		//thread_wakeup just requires a const void *. 
		//So we're using the threadsLeft counter
		thread_wakeup((void*)&threadsLeft);
			
	}
	splx(spl);

}
/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createcars(int nargs,
           char ** args)
{
        int index, error;

	int Spl;

	threadsLeft = 0;

        /*
         * Avoid unused variable warnings.
         */

        (void) nargs;
        (void) args;
	
	//initalize locks
	NW = lock_create("North West");
	NE = lock_create("North East");
	SE = lock_create("South West");
	SW = lock_create("South East");

	N = lock_create("North");
	S = lock_create("South");
	E = lock_create("East");
	W = lock_create("West");

        /*
         * Start NCARS approachintersection() threads.
         */

        for (index = 0; index < NCARS; index++) {

                error = thread_fork("approachintersection thread",
                                    NULL,
                                    index,
                                    approachintersection,
                                    NULL
                                    );

                /*
                 * panic() on error.
                 */

                if (error) {
                        
                        panic("approachintersection: thread_fork failed: %s\n",
                              strerror(error)
                              );
                }
        }

	
	//Wait for all threads to end so we can clean up and end
	Spl = splhigh();
	if(threadsLeft < NCARS){

		//Wait until threadsLeft == NCARS
		thread_sleep((void*)&threadsLeft);
	}

	splx(Spl);
	
	lock_destroy(NW);
	lock_destroy(NE);
	lock_destroy(SE);
	lock_destroy(SW);

	lock_destroy(N);
	lock_destroy(S);
	lock_destroy(E);
	lock_destroy(W);
	
        return 0;
}