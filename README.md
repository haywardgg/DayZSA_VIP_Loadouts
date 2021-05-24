## ✨ DayZSA Custom VIP and Admin Loadouts using init.c

Originally scripted for UNIT487 DayZ server: Search community server list for "UNIT487"

In case you're thinking of using this script to monetize your server, read this: https://www.bohemia.net/monetization

**Pro Tip**: Fork this repository so you can edit and track your own changes (top right Fork icon)

Advanced users can simply use the merge files provided. 

Everyone else please follow these instructions:

1. Rename your existing missions `init.c` to `backup_init.c` 
2. Download this repository and unzip it to a temporary folder, or your desktop.
3. Copy the `init.c` from the appropriate *<Mission.Folder>* to your *<Mission.Folder>* (same location as your old init.c).
4. Edit the new `init.c` file and add your VIP / Admin IDs to the appropriate list. They are clearly marked with comments. 

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

---

### 💝 Donation and Discord Links 🗫

- Join my [**Discord**](https://discord.gg/dkRjW23XXj) if you've got any questions. 
  
- My scripts and mods will always be free, but donations are welcome via [**PayPal**](https://paypal.me/hayward72) (Thank you)  

### ✔️ ToDo List

- [x] Fix bug where loadouts are being assigned at random to the wrong playres.
- [x] Make it compatible with non-Expansion maps.
- [x] Make adding IDs easier for the end user (get rid of the complicated embedded array)
- [ ] Make it possible for server owners to add IDs on the fly without needing to restart the server.

### 🤝 Credits
**LieutenantMaster, Expansion developer** for his help with improving the script.   
**Blain, Playbox.Survival server** for helping me thoroughly test the script.   
**Chopper,** [**Better Loadouts**](https://steamcommunity.com/sharedfiles/filedetails/?id=1782718362) for the sample loadouts.
