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