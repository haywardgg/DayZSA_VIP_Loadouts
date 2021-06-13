## ✨ DayZSA Custom VIP and Admin Loadouts using init.c

In case you're thinking of using this script to monetize your server, [read this first](https://www.bohemia.net/monetization).

**Pro Tip**: Fork this repository so you can edit and track your own changes (top right Fork icon)

Advanced users can simply use the merge files provided. 

Everyone else please follow these instructions:

1. Rename your existing missions `init.c` to `backup_init.c` 
2. [Download](https://github.com/haywardgb/DayZSA_VIP_Loadouts/archive/refs/heads/main.zip) this repository and unzip it to a temporary folder, or your desktop.
3. Copy the `init.c` from the appropriate *<Mission.Folder>* to your *<Mission.Folder>* (same location as your old init.c).
4. Edit the new `init.c` file and add your VIP / Admin IDs to the appropriate list. They are clearly marked with comments. 

```c
	// Example with Steam64 ID: 	adminMembers.Insert( "76561198040948171" );
		
	// ADMIN MEMBERS: Can be Steam64 ID or Bohemia UID
	adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
        adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
		
	// Silver VIP MEMBERS: Can be Steam64 ID or Bohemia UID
	vipMembersSilver.Insert( "ReplaceWithUniqueID" ); // Players Name
        vipMembersSilver.Insert( "ReplaceWithUniqueID" ); // Players Name
```
Careful to add your ID's to the correct lists.

You can find your player ID by looking through your console and server logs for entries like this:
	
	12:20:20 Player RandomGuy connected (id=Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=)
	
You want to cut and paste everything after `id=` and before `)`
	
like this: `Iju6RjrohthfN7ITmRaf8eerbS4hjSfyzGs1vhHvm8g=`  
  
Get your Steam64 ID from this website: https://steamidfinder.com/

5. Now you can edit the loadouts.

```c
	EntityAI adminLoadOut(PlayerBase player) 
	{
		ref TStringArray hatArray = {"BallisticHelmet_Black"};
		ref TStringArray topArray = {"M65Jacket_Black","M65Jacket_Green"};
		ref TStringArray pantsArray = {"CargoPants_Black"};	
		ref TStringArray vestArray  = {""};
```
Each Array can be either empty, contain a single item or contain multiple items. If an array contains multiple items then one of those items will be selected at random. You can list multiple items like this `"item1","item2","item3","etc"`. There is no comma or full stop after the last item in an Array. If you don't want any items listed in an Array just add `""` (see above for examples). 

Lines like this `player.GetInventory().CreateInInventory(hatArray.GetRandomElement());` don't need to be edited. But you can however replace `hatArray.GetRandomElement()` with `"BallisticHelmet_Blue"` for example, which would override any hat array from the previous code example above. You can see an example in the `init.c` file with the Admin loadout, where I've given the admin a LockPick. Remember these are mostly just examples, you can either keep them, edit them or remove them. 

**NOTE:** Do not delete any lines, just delete the `"item_classname"` and leave the quotes empty like this `""`. 
You can do this for the ammo, weapon, rags, etc.. too! **Always backup your files before editing**

**DISCLAIMER:** Use these configs at your own risk. I'm under no obligations to fix your configs or to teach you how to code. I've done my best to answer the most frequently asked questions [Here](https://github.com/haywardgb/DayZSA_VIP_Loadouts/wiki/FAQ) on my FAQ Wiki page.

### 🥰 Donation and Discord Links 💬

Join my [**Discord**](https://discord.gg/dkRjW23XXj) if you've got any questions.   
Donations are welcome via [**PayPal**](https://paypal.me/hayward72) (Thank you)  

### 🤝 Credits
**LieutenantMaster, Expansion developer** for his help with improving the script.   
**Blain, Playbox.Survival server** for helping me thoroughly test the script.   
**Chopper,** [**Better Loadouts**](https://steamcommunity.com/sharedfiles/filedetails/?id=1782718362) for the sample loadouts.
