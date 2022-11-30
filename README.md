

# CVE-2022-0847-DirtyPipe-Exploits

# Backdoor
- On victim machine, once priviledge has been achieved, put the backdoor.service in /etc/systemd/system folder. And run $ sudo systemctl enable backdoor.service --now. Note that the IP of the attacker device/server needs to be changed.

- On attacker machine, execute whenever you want to connect: $ nc -nvlp 9001


## Credits
- https://github.com/febinrev/dirtypipez-exploit
- https://github.com/basharkey/CVE-2022-0847-dirty-pipe-checker
