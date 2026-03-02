ppcfetch: ppcfetch.c
	@gcc -o ppcfetch ppcfetch.c
	
clean: ppcfetch
	@rm ppcfetch

install: ppcfetch 
	@sudo cp ppcfetch /usr/sbin
	@sudo chmod 755 /usr/sbin/ppcfetch
	@echo "ppcfetch installed on /usr/sbin/"

uninstall: ppcfetch
	@sudo rm /usr/sbin/ppcfetch
	@echo "ppcfetch uninstalled successfully"