ppcfetch: ppcfetch.c
	@gcc -o ppcfetch ppcfetch.c
	
clean: ppcfetch
	@rm ppcfetch

install: ppcfetch 
	@echo "ppcfetch installing in /usr/sbin/ ..."
	@cp ppcfetch /usr/sbin
	@chmod 755 /usr/sbin/ppcfetch

uninstall: ppcfetch
	@echo "uninstalling ppcfetch..."
	@rm /usr/sbin/ppcfetch
