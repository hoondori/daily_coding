
https://overthewire.org/wargames/bandit/

# connect
ssh -p 2220 banditX@bandit.labs.overthewire.org

# 0->1
NH2SXQwcBdpmTEzi3bvBHMM9H66vVXjL


# 1->2
How to open a "-" dashed filename using terminal?
```
you can use redirection
cat < -file_name
```
rRGizSaX8Mk1RTb1CNQoXTcYZWU6lgzi

# 2->3
```
$> cat ./spaces\ in\ this\ filename
$> cat < 'spaces in this filename'
$> cat ./*
```
aBZ0W5EmUfAf7kHTQeOwd8bauFJ2lAiG

# 3->4
```
bandit3@bandit:~$ cat ./inhere/.hidden
2EW7BBsr6aMMoJ2HjW067dm8EgX26xNe
```

# 4->5
```
bandit4@bandit:~/inhere$ file ./*
./-file00: data
./-file01: data
./-file02: data
./-file03: data
./-file04: data
./-file05: data
./-file06: data
./-file07: ASCII text
./-file08: data
./-file09: Non-ISO extended-ASCII text, with no line terminators
bandit4@bandit:~/inhere$ cat ./-file07
lrIWWI6bB37kxfiCQZqUdOIYfr6eEeqR

```

# 5->6
```
bandit5@bandit:~/inhere$ find . -size 1033c
./maybehere07/.file2
bandit5@bandit:~/inhere$ cat ./maybehere07/.file2
P4L4vucdmLnm8I7Vl7jG1ApGSfjYKqJU

```

# 6->7
```
bandit6@bandit:~$ find / -user bandit7 -group bandit6 -size 33c 2>/dev/null
/var/lib/dpkg/info/bandit7.password
bandit6@bandit:~$ cat /var/lib/dpkg/info/bandit7.password
z7WtoNQU2XfjmMtWA8u5rN4vzqu4v99S

```

# 7->8
```
bandit7@bandit:~$ cat --number data.txt | grep -w "millionth"
  8994	millionth	TESKZC0XvTetK0S9xNwm25STk5iWrBvP
```

# 8->9
```
$> sort data.txt | uniq -c
     10 dMNfFW0t7tDLsN6jM4t15q7sGdXIJlDO
      1 EN632PlfYiZbn3PhVK3XOGSlNInNE00t
     10 EoxGdakqWSJE03uzpJBLKabYEb5J458U
```

# 9->10
```
$> strings data.txt | grep ^===
========== password
========== is
========== G7w8LIi6J3kTb8A7j9LgrywtEUlyyp6s
```

# 10->11
```
$> base64 -d data.txt 
The password is 6zPeziLdR2RKNdNYFNb6nVCKzphlXHBM

```

# 11->12
* https://www.geeksforgeeks.org/tr-command-in-unix-linux-with-examples/
* https://stackoverflow.com/questions/5442436/using-rot13-and-tr-command-for-having-an-encrypted-email-address
```
$> cat data.txt | tr '[A-Za-z]' '[N-ZA-Mn-za-m]'
The password is JVNBBFSmZwKKOP0XbFXOoW8chDz5yVRv
```

# 12->13
The password is wbWdlBxEir4CaE8LaPhauuOo6pwRmrDw


# 13->14

https://mayadevbe.me/posts/overthewire/bandit/level14/
```
$> nc -zvnw 1 127.0.0.1 2220  # 22번 open 확인 
$>  ssh -i ./키파일 bandit14@bandit.labs.overthewire.org -p 2220
$> cat /etc/bandit_pass/bandit14 
fGrHPx402xGC7U7rXKDaxiWFTOiF0ENq
```

# 14->15

```
$> nc -zvnw 1 127.0.0.1 30000
Connection to 127.0.0.1 30000 port [tcp/*] succeeded!
$> nc 127.0.0.1 30000
fGrHPx402xGC7U7rXKDaxiWFTOiF0ENq
Correct!
jN2kgmIXJ6fShzhT2avhotn4Zcka6tnt
```

# 15->16
```
$> nc -znvw 1 127.0.0.1 30001
Connection to 127.0.0.1 30001 port [tcp/*] succeeded!
$> openssl s_client -connect 127.0.0.1:30001
jN2kgmIXJ6fShzhT2avhotn4Zcka6tnt
Correct!
JQttfApK4SeyHwDlI9SXGR50qclOAil1
```