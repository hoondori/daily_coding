
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

# 16->17
```
$> nc -zvnw 1 127.0.0.1 31000-32000  
listen ports: 31960 31790 31691 31518 31046
$> openssl s_client -connect 127.0.0.1:31790
내용을 키파일로 만들고 
$> ssh -i ./키파일 bandit17@bandit.labs.overthewire.org -p 2220
$> cat  /etc/bandit_pass/bandit17
VwOSWtCA7lRKkTfbr2IDh6awj9RNZM5e
```

# 17->18
```
$> diff passwords.old passwords.new
42c42
< glZreTEH1V3cGKL6g4conYqZqaEj0mte
---
> hga5tuuCLF6fFzUpnagiMN8ssu9LFrdg  <--   이것
```

# 18->19
```
How to start a shell without any user configuration?
bash --noprofile --norc
Login without running bash_profile or bashrc
ssh -t user@host bash --norc --noprofile

bash-5.1$ cat /etc/shells  # 다른  shell 사용해도 가능
# /etc/shells: valid login shells
/bin/sh
/bin/bash
/usr/bin/bash
/bin/rbash
/usr/bin/rbash
/usr/bin/sh
/bin/dash
/usr/bin/dash
/usr/bin/tmux
/usr/bin/screen
/usr/bin/showtext

$> ssh -p 2220 -t bandit18@bandit.labs.overthewire.org /bin/bash --noprofile --norc
$> bash-5.1$ cat readme 
awhqfNnAbc1naukrpqDYcF95h7HoMTrC
```


# 19->20
```
Meaning of the access permissions "rws"

The s in rws stands for setuid meaning set user ID. This is a special permission bit that allows the program, when run by any user, to be run with the effective UID of the owner.


$> ls -al
-rwsr-x---  1 bandit20 bandit19 14876 Apr 23 18:04 bandit20-do

$> file ./bandit20-do 
./bandit20-do: setuid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, BuildID[sha1]=c148b21f7eb7e816998f07490c8007567e51953f, for GNU/Linux 3.2.0, not stripped

$> ./bandit20-do id
uid=11019(bandit19) gid=11019(bandit19) euid=11020(bandit20) groups=11019(bandit19)

$> ./bandit20-do cat /etc/bandit_pass/bandit20 
VxCazJaVykI6W36BkBU0mJTCM8rR95XT
```


# 20->21
```
How to Run Linux Commands in the Background
https://www.makeuseof.com/run-linux-commands-in-background/


$> ls -al ./suconnect 
-rwsr-x--- 1 bandit21 bandit20 15600 Apr 23 18:04 ./suconnect

$> ./suconnect
Usage: ./suconnect <portnumber>
This program will connect to the given port on localhost using TCP. If it receives the correct password from the other side, the next password is transmitted back.

$> nc -l -p 35001 < /etc/bandit_pass/bandit20 &
[1] 2026460

$> jobs
[1]+  Running    nc -l -p 35001 < /etc/bandit_pass/bandit20 &

$> ./suconnect 35001
Read: VxCazJaVykI6W36BkBU0mJTCM8rR95XT
Password matches, sending next password
NvEJF7oVjkddltPSrdKEFOllh9V1IBcq

```

# 21->22
```

$> ls -al /etc/cron.d/3
$> cat /etc/cron.d/cronjob_bandit22
@reboot bandit22 /usr/bin/cronjob_bandit22.sh &> /dev/null

$> cat /usr/bin/cronjob_bandit22.sh
#!/bin/bash
chmod 644 /tmp/t7O6lds9S0RqQh9aMcz6ShpAoZKF7fgv
cat /etc/bandit_pass/bandit22 > /tmp/t7O6lds9S0RqQh9aMcz6ShpAoZKF7fgv

$> cat /tmp/t7O6lds9S0RqQh9aMcz6ShpAoZKF7fgv
WdDozAdTM2z9DiFEQ2mGlwngMfj4EZff

```

# 22->23
```

$> cat /usr/bin/cronjob_bandit23.sh
#!/bin/bash

myname=$(whoami)
mytarget=$(echo I am user $myname | md5sum | cut -d ' ' -f 1)

echo "Copying passwordfile /etc/bandit_pass/$myname to /tmp/$mytarget"

cat /etc/bandit_pass/$myname > /tmp/$mytarget
$> myname=bandit23
$> bandit22@bandit:~$ mytarget=$(echo I am user $myname | md5sum | cut -d ' ' -f 1)
$> echo $mytarget
8ca319486bfbbc3663ea0fbe81326349
$> cat /tmp/8ca319486bfbbc3663ea0fbe81326349
QYw0Y2aiA672PsMmh9puTQuhoz8SyR2G


```

# 23->24 
```
$> cat /usr/bin/cronjob_bandit24.sh
#!/bin/bash

myname=$(whoami)

cd /var/spool/$myname/foo || exit 1
echo "Executing and deleting all scripts in /var/spool/$myname/foo:"
for i in * .*;
do
    if [ "$i" != "." -a "$i" != ".." ];
    then
        echo "Handling $i"
        owner="$(stat --format "%U" ./$i)"
        if [ "${owner}" = "bandit23" ]; then
            timeout -s 9 60 ./$i
        fi
        rm -rf ./$i
    fi
done


$> ls -al /var/spool/bandit24
drwxrwx-wx 7 root     bandit24 4096 May 19 20:12 foo

$> cat /tmp/my_folder/my.sh
#/bin/bash
cat /etc/bandit_pass/bandit24 > /tmp/my_folder/pass.txt

$> chmod 777 /tmp/my_folder/my.sh
$> chmod o+w /tmp/my_folder
$> cp /tmp/my_folder/my.sh /var/spool/bandit24/foo/
wait....
$> ls -al /tmp/my_folder/
-rwxrwxrwx    1 bandit23 bandit23      68 May 19 20:17 my.sh
-rw-rw-r--    1 bandit24 bandit24      33 May 19 20:22 pass.txt
$> cat /tmp/my_folder/pass.txt 
VAfGXJ1PBSsPSnvsjI8p759leLZ9GGar


```

# 24->25

```
from pwn import *

HOST='127.0.0.1'
PORT=30002
r = remote(HOST, PORT)
bandit24pw = 'VAfGXJ1PBSsPSnvsjI8p759leLZ9GGar '

for i in range(0, 10000):
  subStr = bandit24pw + str(i).zfill(4)
  r.sendline(susStr)
  print("[Sended]" + susStr)
  rData = r.recvuntil("\n")
  print("[Received]" + str(rData))
r.close()


$> cat /tmp/my_folder/submit.sh
#/bin/bash

for i in {0000..9999}
do
	echo VAfGXJ1PBSsPSnvsjI8p759leLZ9GGar $i >> /tmp/my_folder/try.txt  
done

$> cat /tmp/my_folder/try.txt | nc localhost 30002 > /tmp/my_folder/result.txt


p7TaowMYrmu23Ol8hiZh9UvD0O9hpx8d

```

# 25->26

```
# default shell 확인
$>  cat /etc/passwd | grep bandit26
bandit26:x:11026:11026:bandit level 26:/home/bandit26:/usr/bin/showtext

$> cat /usr/bin/showtext 
#!/bin/sh

export TERM=linux

exec more ~/text.txt
exit 0


$> ls -al
-r--------  1 bandit25 bandit25 1679 Apr 23 18:04 bandit26.sshkey
$> ssh -i bandit26.sshkey -t -p 2220 bandit26@bandit.labs.overthewire.org -p 2220


화면 작게 하고 more 작동, v누르고 편집기 모드 

:e /etc/bandit_pass/bandi26

c7GvcKlw9mC7aUQaPx7nwFstuAIBw1o1


```

# 26->27

```

more v 진입후...
:set shell=/bin/bash
:!ls -al
-rwsr-x---  1 bandit27 bandit26 14876 Apr 23 18:04 bandit27-do

:!./bandit27-do cat /etc/bandit_pass/bandit27
YnQpBuifNMas1hcUFk70ZmqkhUU2EuaS

```

# 27->28

```
The following syntaxes may be used with them:
- ssh://[user@]host.xz[:port]/path/to/repo.git/

$> git clone ssh://bandit27-git@localhost:2220/home/bandit27-git/repo /tmp/my_clone/

bandit27@bandit:/tmp/my_clone$ cat README 
The password to the next level is: AVanL161y9rsbcJIsFHuw35rjaOM19nR

```


# 28->29

```

$> git clone ssh://bandit28-git@localhost:2220/home/bandit28-git/repo temp폴더
$> catt README.md 
# Bandit Notes
Some notes for level29 of bandit.

## credentials

- username: bandit29
- password: xxxxxxxxxx


$> git log 
Author: Morla Porla <morla@overthewire.org>
Date:   Sun Apr 23 18:04:39 2023 +0000

    fix info leak

commit abcff758fa6343a0d002a1c0add1ad8c71b88534
Author: Morla Porla <morla@overthewire.org>
Date:   Sun Apr 23 18:04:39 2023 +0000

    add missing data

$> git checkout abcff758fa6343a0d002a1c0add1ad8c71b88534
$> cat README.md 
# Bandit Notes
Some notes for level29 of bandit.

## credentials

- username: bandit29
- password: tQKvmcwNYcFS6vmPHIUSI3ShmsrQZK8S

```


# 29->30
```
$> git clone ssh://bandit29-git@localhost:2220/home/bandit29-git/repo temp폴더

$> git branch -r
  origin/HEAD -> origin/master
  origin/dev
  

$> git checkout -t origin/dev
$> git log
commit 13e735685c73e5e396252074f2dca2e415fbcc98 (HEAD -> dev, origin/dev)
Author: Morla Porla <morla@overthewire.org>
Date:   Sun Apr 23 18:04:40 2023 +0000

    add data needed for development

$> git show 13e735685c73e5e396252074f2dca2e415fbcc98
 
 - username: bandit30
-- password: <no passwords in production!>
+- password: xbhV3HpNGlTIdnjUrdAlPzc2L6y9EOnS

```


# 30->31

```

bandit30@bandit:/tmp/c$ git tag
secret

$> git show-ref
831aac2e2341f009e40e46392a4f5dd318483019 refs/tags/secret

$> git show 831aac2e2341f009e40e46392a4f5dd318483019
OoffzGDlzhAlerFJ2cAiz1D41JW1Mhmt



```

# 31->32

```

$> cat README.md 
This time your task is to push a file to the remote repository.

Details:
    File name: key.txt
    Content: 'May I come in?'
    Branch: master


$> echo 'May I come in?' > key.txt
$> git add -f key.txt 
$> git push
remote: Well done! Here is the password for the next level:
remote: rmCBvG56y58BXzv98yZGdO7ATVL5dW8y 

```

# 32->33

```
>> $0  
$ cat /etc/bandit_pass/bandit33
odHo63fHiFqcWWJG9rLiLDtPm45KzUKy

```

ssh -p 2220 bandit18@bandit.labs.overthewire.org
