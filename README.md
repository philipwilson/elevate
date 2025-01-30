# elevate - demonstrates running programs with root permissions

# Building
```
% gcc -o elevate elevate.c pathfinder.c
% sudo chown root elevate
% sudo chmod +s elevate
```

# Running
```
% ./elevate bash        
bash-5.2# 
```
