## Class 3: Process Management**

## Process Control

| Command | Description | Example |
|---------|-------------|---------|
| `ps`    | Current processes | `ps aux` |
| `top`   | Live system monitor | `top` |
| `kill`  | Terminate process | `kill -9 4482` |
| `jobs`  | Background tasks | `jobs -l` |

## Priority Management
```bash
nice -n 10 long_task.sh  # Start low priority
renice 15 -p 2291        # Change priority
```

```
python script.py &  # Start in background
fg %1               # Bring job 1 to foreground
```