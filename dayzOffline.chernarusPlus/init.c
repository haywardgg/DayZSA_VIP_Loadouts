void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false);    // false = use weather controller from Weather.c

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set( 0, 0, 1);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer
{

    ref array< string > adminMembers = new array< string >;
    ref array< string > vipMembers = new array< string >;

    void CustomMission()
    {
        adminMembers = new array< string >;
        vipMembers = new array< string >;
      
        InitPlayerWhitelist();
	}	
	
	// ------------------------------------------------------------
	// Override CreateCharacter
	// ------------------------------------------------------------
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{

		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );
		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}
	
	// ------------------------------------------------------------
	// SetRandomHealth
	// ------------------------------------------------------------
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.25, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}
	
	// ------------------------------------------------------------
	// Override StartingEquipSetup
	// ------------------------------------------------------------
	void addMags(PlayerBase player, string mag_type, int count)
	{
		if (count < 1)
			return;

		EntityAI mag;

		for (int i = 0; i < count; i++) {
			mag = player.GetInventory().CreateInInventory(mag_type);
		}

		player.SetQuickBarEntityShortcut(mag, 2, true);
	}


// Admin Loadout
	EntityAI adminLoadOut(PlayerBase player)
	{
		ref TStringArray hatArray = {"BallisticHelmet_Black"};
		ref TStringArray topArray = {"M65Jacket_Black"};
		ref TStringArray pantsArray = {"CargoPants_Black"};	
		ref TStringArray vestArray  = {"HighCapacityVest_Black"};	
		ref TStringArray glassesArray = {""};
		ref TStringArray shoesArray = {"MilitaryBoots_Black"};	
		ref TStringArray maskArray = {"BalaclavaMask_Blackskull"};	
		ref TStringArray glovesArray = {"TacticalGloves_Black"};		
		ref TStringArray foodArray = {"BakedBeansCan"};
		ref TStringArray drinkArray = {"SodaCan_Cola"};
		ref TStringArray backpackArray = {""};
		ref TStringArray knifeArray  = {"HuntingKnife"};
		ref TStringArray meleeArray = {"FirefighterAxe"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(knifeArray.GetRandomElement());
		player.GetInventory().CreateInInventory("Lockpick");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		EntityAI gun = player.GetInventory().CreateInInventory("AKM");					// Weapon
		gun.GetInventory().CreateAttachment("AK_RailHndgrd");						// Weapon Attachment (Handguard)
		ItemBase gunlight = gun.GetInventory().CreateAttachment("UniversalLight");			// Weapon Attachment (Universal Light)
		gunlight.GetInventory().CreateAttachment("Battery9V");						//     Add battery to Universal Light
		addMags(player, "Mag_AKM_30Rnd", 4);								// Magazines
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());	// Melee
				
		player.SetQuickBarEntityShortcut(gun, 0, true);
		player.SetQuickBarEntityShortcut(melee, 1, true);
		return gun;
	}

// VIP Loadout
	EntityAI vipLoadOut(PlayerBase player) 
	{
		ref TStringArray hatArray = {"BaseballCap_CMMG_Pink","BaseballCap_Pink","BaseballCap_Red","BaseballCap_Blue"};
		ref TStringArray topArray = {"Sweater_Red","Sweater_Blue","Sweater_Gray","Sweater_Green"};
		ref TStringArray pantsArray = {"Jeans_Blue","Jeans_BlueDark","Jeans_Grey","Jeans_Brown","Jeans_Black","Jeans_Green"};	
		ref TStringArray vestArray  = {""};	
		ref TStringArray glassesArray = {""};
		ref TStringArray shoesArray = {"CombatBoots_Grey","CombatBoots_Beige","CombatBoots_Brown","CombatBoots_Black","CombatBoots_Green"};	
		ref TStringArray maskArray = {""};	
		ref TStringArray glovesArray = {"WorkingGloves_Brown"};		
		ref TStringArray foodArray = {"BakedBeansCan"};
		ref TStringArray drinkArray = {"SodaCan_Cola"};
		ref TStringArray backpackArray = {"DryBag_Yellow","DryBag_Orange","DryBag_Red","DryBag_Blue","DryBag_Black","DryBag_Green"};
		ref TStringArray knifeArray  = {"HuntingKnife"};
		ref TStringArray meleeArray = {"FirefighterAxe"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(knifeArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		EntityAI gun = player.GetInventory().CreateInInventory("AKS74U");				// Weapon
		addMags(player, "Mag_AK74_30Rnd", 2);								// Magazines
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());	// Melee
		
		player.SetQuickBarEntityShortcut(gun, 0, true);
		player.SetQuickBarEntityShortcut(melee, 1, true);
		return gun;
	}
	
// Non-VIP Loadout (Default Loadout)
	EntityAI randomLoadOut(PlayerBase player) 
	{
		ref TStringArray hatArray = {"BaseballCap_CMMG_Pink","BaseballCap_Pink","BaseballCap_Red"};
		ref TStringArray topArray = {"Sweater_Red","Sweater_Blue","Sweater_Gray","Sweater_Green"};
		ref TStringArray pantsArray = {"Jeans_Blue","Jeans_BlueDark","Jeans_Grey","Jeans_Brown","Jeans_Black","Jeans_Green"};	
		ref TStringArray vestArray  = {""};	
		ref TStringArray glassesArray = {""};
		ref TStringArray shoesArray = {"CombatBoots_Grey","CombatBoots_Beige","CombatBoots_Brown","CombatBoots_Black","CombatBoots_Green"};	
		ref TStringArray maskArray = {""};	
		ref TStringArray glovesArray = {"WorkingGloves_Brown"};		
		ref TStringArray foodArray = {"BakedBeansCan"};
		ref TStringArray drinkArray = {"SodaCan_Cola"};
		ref TStringArray backpackArray = {"DryBag_Yellow","DryBag_Orange","DryBag_Red","DryBag_Blue","DryBag_Black","DryBag_Green"};
		ref TStringArray knifeArray  = {"HuntingKnife"};
		ref TStringArray meleeArray = {"FirefighterAxe"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(knifeArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		EntityAI gun = player.GetInventory().CreateInInventory("AKS74U");  				// Weapon
		addMags(player, "Mag_AK74_30Rnd", 2); 								// Magazines								
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());	// Melee
		
		player.SetQuickBarEntityShortcut(gun, 0, true);
		player.SetQuickBarEntityShortcut(melee, 1, true);
		return gun;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		player.RemoveAllItems();
					
		if (adminMembers.Find(GetUserID(player)) != -1 || adminMembers.Find(GetUserSteamID(player)) != -1 ) {		
			adminLoadOut(player);			
		} else if (vipMembers.Find(GetUserID(player)) != -1 || vipMembers.Find(GetUserSteamID(player)) != -1 ) { 		
			vipLoadOut(player);	
		} else {
			randomLoadOut(player);	
		}
	}
	
		string GetUserID(PlayerBase player)
    {
        if ( player.GetIdentity() )
            return player.GetIdentity().GetPlainId();
        
        return "OFFLINE";
    }

    string GetUserSteamID(PlayerBase player)
    {
        if ( player.GetIdentity() )
            return player.GetIdentity().GetId();
        
        return "OFFLINE";
    }
	
	void InitPlayerWhitelist()
    {
		// Example with Bohemia UID: 	adminMembers.Insert( "JCmXrrt43efttyhfewew7tRLMUCOE6roH2O8SklBB1o=" );
		// Example with Steam64 ID: 	adminMembers.Insert( "76561198040948171" );
				
		// ADMIN MEMBERS: Can be Steam64 ID or Bohemia UID
		adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
		adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
		adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
		adminMembers.Insert( "ReplaceWithUniqueID" ); // Admins Name
				
		// VIP MEMBERS: Can be Steam64 ID or Bohemia UID
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
		vipMembers.Insert( "ReplaceWithUniqueID" ); // Players Name
    }
	
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
