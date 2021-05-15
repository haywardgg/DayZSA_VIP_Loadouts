# DayZSA Custom VIP and Admin Loadouts using init.c

1. Rename your existing missions init.c to backup_init.c 
2. Download the correct (missionName).init.c to your mission folder (same location as your old init.c).
3. Rename (missionName).init.c to init.c
4. Edit the file and add your VIP / Admin IDs to the appropriate array. They are clearly marked with comments. 

You can find your player ID by looking through your console and server logs for entries like this:
	
	12:20:20 Player RandomGuy connected (id=Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=).
	
You want to cut and paste everything after id= and before )
	
	like this: Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=

