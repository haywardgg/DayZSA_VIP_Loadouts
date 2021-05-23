# DayZSA Custom VIP and Admin Loadouts using init.c

Originally scripted for UNIT487 DayZ server: Search community server list for "UNIT487"

In case you're thinking of using this script to monetize your server, read this: https://www.bohemia.net/monetization

**Pro Tip**: Fork this repository so you can edit and track your own changes (top right Fork icon)

Advanced users can simply use the merge files provided. 

Everyone else please follow these instructions:

1. Rename your existing missions `init.c` to `backup_init.c` 
2. Download the correct `init.c` to your mission folder (same location as your old init.c).
3. Edit the file and add your VIP / Admin IDs to the appropriate array. They are clearly marked with comments. 

```c
	// Example with Steam64 ID: 	adminMembers.Insert( "76561198040948171" );
		
	// ADMIN MEMBERS: Can be Steam64 ID or Bohemia UID
	adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
        adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
		
	// VIP MEMBERS: Can be Steam64 ID or Bohemia UID
	vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
        vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
```

You can find your player ID by looking through your console and server logs for entries like this:
	
	12:20:20 Player RandomGuy connected (id=Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=)
	
You want to cut and paste everything after `id=` and before `)`
	
like this: `Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=`  
  
Get your Steam64 ID from this website: https://steamidfinder.com/

=== Good luck and join my Discord if you've got any questions: https://discord.gg/dkRjW23XXj ===
  
Donations welcome: https://paypal.me/hayward72 .

TODO: Make it possible for server owners to add IDs on the fly without needing to restart the server.
