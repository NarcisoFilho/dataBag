============== DataBag v 0.1:  Take your data wherever you go =================


 > BUILDING:
    Use the makefile to compile to server aplication(dataBag_server) and the client aplication(dataBag)
 
 > RUNNING:
    
 - Both server and one client in the same host:
	Open 7 terminals, 4 for the server and 3 to the client. You should to guarantee that the 4 server terminals are the terminal pts/1, pts/2, pts/3 e          pts/4 and the 3 client terminals are the terminals pts/5, pts/6, pts/7. Now run the server aplication in the terminal pts/1, and after this run the        client application in pts/4.
    
- Server and clients in diferent hosts:     
	Reserve terminals pts/1, pts/2, pts/3 and pts/4 for server aplication, adn run it in pts/1. In clients size reserve pts/1, pts/2 and pts/3 and run       the program with one parameter: The server ip adress. 
         
         
> TIPS:
- To discover the terminal code you can use 'tty' unix command. It will show a message like '/dev/pts/n', where n is the number code of the Pseudo Terminal Slave.

