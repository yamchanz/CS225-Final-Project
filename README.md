# ndarand2-cgordon5-nylogan2
Final Project

The Executable of our project is named <pathFinder>.  To get information on all the
command line calls, you can read below, or run [./pathFinder] through the terminal.

LIST AIRPORT CODE CALL:
./pathFinder list [number < 5997]
    This will give a list of approximately 100 airport 3-letter codes.  The codes
    you recieve are determined by the number (up to 5997) argument that follows "list".


PRIMARY COMMANDLINE CALL:
./pathFinder [Type of operation (DISTANCE or STOPS)] [3-letter airport code source] [3-letter airport code destination]

            ARGUMENT                                VALID INPUTS
    -------------------------------------------------------------------------
    [Type of operation (DISTANCE or STOPS)]     = DISTANCE/STOPS/BOTH
    [3-letter airport code source]              = Any airport's 3 letter code
    [3-letter airport code destination]         = Any airport's 3 letter code

    This call will effectively run all of our important code, finding the
    shortest path (whether it is by DISTANCE, STOPS, or BOTH) and plot the path
    on our map "Out.png".  Both DISTANCE and STOPS arguments will plot one
    route, whereas BOTH will plot both of the routes on the same output map.



BASIC HELP AND COMMENTS:
    Our airport data is full, holding over 6000 visitable airports, that said,
    many of them are extremely small, having only one route in/out.  This is 
    made more noticable, as we are using 1/4 of the total airplane routes to
    speed up the CS225 graders/testers experience using our DISTANCE shortest
    path finder.  As a result, many airports will not be able to find a route
    to another.  To mitigate this annoyance, we recommend using major airports
    as one of the arguments, either the source airport or the destination one.
    
    Below are the codes of the 20 LARGEST AIRPORTS:
        ATL, LAX, ORD, DFW, DEN, JFK, SFO, SEA, LAS, MCO, EWR,
            CLT, PHX, IAH, MIA, BOS, MSP, FLL, DTW, PHL

    