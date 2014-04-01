There are 11 files in the RPC folder.
• vote.x Interface file which creates server and client stubs
• vote_server.c Server file
• vote.h Header file that needs to be included in server and client codes
• vote_svc.c Server stub file which is to be linked with the server file
• vote_clnt.c Client stub file which is to be linked with all the client files
• rzeroize.c Client file which exercises zeroize function in server
• raddvoter.c Client file which exercises addvoter function in server
• rvotefor.c Client file which exercises votefor function in server
• rlistcandidates.c Client file which exercises listcandidates function in server
• rvotecount.c Client file which exercises votecount function in server
• mymake Bash script which compiles and links the necessary files and gives executables.
chmod 755 mymake needs to be executed on the kernel before using this file.

mymake needs to be executed to get the executables. 
The executables take the following command line arguments. 
SERVERIP can be mentioned as either localhost or 127.0.0.1

• mymake
• vote server
• rzeroize SERVERIP
• raddvoter SERVERIP VOTERID
• rvotefor SERVERIP NAME VOTERID
• rlistcandidates SERVERIP
• rvotecount SERVERIP NAME

There are 7 files in the UDP folder.
• serv.c Server file
• zeroize.c Client file which exercises zeroize function in server
• addvoter.c Client file which exercises addvoter function in server
• votefor.c Client file which exercises votefor function in server
• listcandidates.c Client file which exercises listcandidates function in server
• votecount.c Client file which exercises votecount function in server
• udpmake Bash script which compiles all the above files and gives executables.
chmod 755 udpmake needs to be executed on the kernel before using this file.

udpmake needs to be executed to get the executables. 
The executables take the following command line arguments. 
SERVERIP can be mentioned as either localhost or 127.0.0.1 and the PORTNUMBER is 7654

• udpmake
• serv
• zeroize SERVERIP PORTNUMBER
• addvoter SERVERIP PORTNUMBER VOTERID
• votefor SERVERIP PORTNUMBER NAME VOTERID
• listcandidates SERVERIP PORTNUMBER
• votecount SERVERIP PORTNUMBER NAME