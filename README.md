c-shell
an experimentaion of shells with c (a seashell haha)

# c-shell

# How does a shell work:
- Takes the **command input** by user (can be custom script or sys command)
- **Parses** it and split it if needed ( resulting into a stored characters array made of the command and its arguments/options/flags)
- Searches through the PATH env variables for the executable file that matches the array
- And runs that exec file (in detail the system creates a process for that command execution-gives it a PID which will be used by system calls for low level execution-)

# What i'll be implementing in this project:
i know that this is a common project, but it's just for fun.
My shell will be able, roughly, to :
- Read the input
- Execute the command
- Output the result

# Why choose C:
lol idk
