# Class 4 Daemons in Linux
## Author: Daniel Ferreto


### Introduction to Daemons
A **daemon** is a background process in Linux that runs independently, without direct user interaction. Daemons are crucial for system functionality, as they handle essential tasks and services. The term **"daemon"** originates from Greek mythology, referring to a guiding spirit—not to be confused with the term "demon."

---

### **What is a Daemon?**
- A **background process** that runs independently of user control.
- Begins its operation often **at system boot** and continues until shutdown.
- **Detached** from a terminal or user session, meaning no direct interaction is required.
- Does not have a **controlling terminal (TTY)**.

#### **Key Characteristics**:
1. **Autonomous**: Operates without active user input.
2. **Long-running**: Stays active to monitor or manage system functions.
3. **Invisible**: Runs silently in the background unless explicitly inspected.

---

### **How Daemons Work**
1. At system boot, the **init system** (like `systemd`, `SysVinit`, or `upstart`) starts daemons.
2. They remain **idle** until their service is needed (e.g., listening for network connections, scheduling tasks).
3. When a specific event or request occurs, daemons perform their designated tasks and return to an idle state.

---

### **Examples of Daemons**
| Daemon Name   | Functionality                                |
|---------------|---------------------------------------------|
| **`sshd`**    | Handles Secure Shell (SSH) connections.     |
| **`httpd`**   | Manages web server requests (e.g., Apache). |
| **`cron`**    | Schedules and executes periodic tasks.      |
| **`cupsd`**   | Manages printing services.                 |
| **`systemd`** | Coordinates system boot and service startup.|

---

### **Why Are Daemons Important?**
- Enable critical system functions (e.g., networking, printing).
- Automate tasks like job scheduling (via `cron`).
- Improve system efficiency by running only when required.

---

### **Identifying Daemons**
In Linux, daemons are typically identified by:
- Their **process name** ending with the letter **"d"**, like `sshd` (SSH daemon) or `crond` (Cron scheduler daemon).
- Running in the background without an active terminal session.

---

### **Managing Daemons**
Here are some basic Linux commands to manage and interact with daemons.

#### **Viewing Running Daemons**
```bash
# List all running daemons and services
ps aux | grep "d$"

# View active services (systemd-based systems)
systemctl list-units --type=service
```

## Starting, Stopping, and Restarting Daemons
## Commands vary depending on the init system in use. Here's an example for systemd:

```bash
# Start a daemon (e.g., sshd)
sudo systemctl start sshd.service
```

```bash
# Stop a daemon
sudo systemctl stop sshd.service
```

```bash
# Restart a daemon
sudo systemctl restart sshd.service
```

```bash
# Check the status of a daemon
sudo systemctl status sshd.service
```


## Creating a Daemon
To demonstrate how daemons work, here's a basic example:

Create a shell script to simulate a daemon.
```bash
#!/bin/bash
while true; do
  echo "Daemon is running..." >> /tmp/daemon.log
  sleep 60
done
```

```bash 
chmod +x mydaemon.sh
```

```bash
nohup ./my_daemon.sh &
```

```bash
ps aux | grep my_daemon
```

## Identify running daemons with:
```bash
ps aux | grep "d$"
```