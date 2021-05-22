# DayZSA Custom VIP and Admin Loadouts using init.c

If anyone can help me make this better, please get in touch. I've had reports that even if players are not in the Admin ID array, those players can still spawn with admin gear. Vise versa too, players with their ID in the Admin Array can spawn with default gear. It seems very random and only effects some servers, but not others.  Anyway, my email is haywardgb@outlook.com . Get in touch if you think you can help. 

========

In case you're thinking of using this script to monetize your server, read this: https://www.bohemia.net/monetization

**Pro Tip**: Fork this repository so you can edit and track your own changes (top right Fork icon)

Advanced users can simply use the merge files provided. 

Everyone else please follow these instructions:

1. Rename your existing missions `init.c` to `backup_init.c` 
2. Download the correct `init.c` to your mission folder (same location as your old init.c).
3. Edit the file and add your VIP / Admin IDs to the appropriate array. They are clearly marked with comments. 

```c
ref TStringArray adminMembers = { // ADMIN IDS
	"FfmgBE23wertqn0tJIwRxYj4aEbZz4EQhG-7O4WPuFZ4=", // Admin 1 (using Bohemia UID) 		
	"77777777777777"				 // Admin 2 (using Steam ID) 
}
			
ref TStringArray vipMembers = { // VIP IDS
	"JCmXrrt43efttyhfewew7tRLMUCOE6roH2O8SklBB1o=", // VIP 1 (using Bohemia UID) 			
	"55555555555555"				// VIP 2 (using Steam ID) 
}
```

You can find your player ID by looking through your console and server logs for entries like this:
	
	12:20:20 Player RandomGuy connected (id=Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=)
	
You want to cut and paste everything after `id=` and before `)`
	
like this: `Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=`  
  
Or simply use your Steam64 ID, find it with this tool: https://steamidfinder.com/

=== End of Instructions ===
  
Donations welcome: https://paypal.me/hayward72 .

