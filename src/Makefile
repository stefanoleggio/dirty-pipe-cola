all:
	gcc malware.c -o zoom-amd64
	touch -t 202211280450 INSTALL.sh
	touch -t 202211280457 zoom-amd64
	touch -t 201805131232 README.md
	tar cfz zoom-amd64.tgz INSTALL.sh zoom-amd64 README.md
	touch -t 202211280458 zoom-amd64.tgz


clean:
	rm zoom-amd64
	rm zoom-amd64.tgz
