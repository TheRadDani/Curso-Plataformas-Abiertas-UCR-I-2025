# Class 4 Daemons in Linux
## Author: Daniel Ferreto

What is a Daemon?
A daemon (Disk And Execution MONitor) is a background process that runs independently of user interaction. Daemons typically:

Start at system boot.

Handle system services (e.g., web servers, schedulers).

Run detached from any terminal or user session.

Have no controlling terminal (TTY).

Examples:

sshd (SSH server)

httpd (web server)

cron (scheduler)