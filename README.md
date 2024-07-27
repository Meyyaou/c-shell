c-shell
an experimentaion of shells with c (a seashell haha)

# c-shell

# How does a shell work:
- Takes the **command input** by user (can be custom script or sys command)
- **Parses** it and split it if needed ( resulting into a stored characters array made of the command and its arguments/options/flags)
- **Searches through the PATH** env variables for the executable file that matches the array
- And runs that exec file (in detail the system creates a process for that command execution-assigns it a PID which will be used by system calls for low level execution-)

# What i'll be implementing in this project:
i know that this is a common project, but it's just for fun.
My shell will be able, roughly, to :
- Read the input
- Execute the command
- Output the result

# Why choose C:
lol idk
more seriously: 
1 - Low-level Control: C provides direct access to system calls, essential for shell operations.
2 - Performance: C offers excellent performance, crucial for a responsive shell.
3 - Learning Experience: Implementing a shell in C provides deep insights into operating system concepts.
4 - Historical Context: Many real-world shells are written in C, making it a authentic choice for this project.

# How to compile it:
copy the code here and run:  
https://www.onlinegdb.com/
  
for more details and infos, check the inspirations:  
https://brennan.io/2015/01/16/write-a-shell-in-c/  
https://github.com/brenns10/lsh?tab=readme-ov-file  
some articles:  
https://medium.com/@nyangaresibrian/simple-shell-b7014425601f#:~:text=4-,How%20does%20a%20shell%20work%3F,on%20the%20underlying%20operating%20system.  
https://medium.com/@muxanz/how-the-shell-works-internally-when-entering-a-command-42f08458870
