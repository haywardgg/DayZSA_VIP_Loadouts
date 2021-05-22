void main()
{
	/*
	  [Namalsk] CE init (offline)
	*/
	CreateHive();
	GetHive().InitOffline();

	/*
	  [Namalsk] Weather init
	   Warning: DO NOT ALTER following values as they are interconnected with other Namalsk-specific systems!
	   To ensure correct functionality, it is necessary to include weaher init AFTER the hive init.
	*/
	Weather weather = GetGame().GetWeather();
	weather.MissionWeather( true );
	weather.GetOvercast().SetLimits( 0.10, 0.30 );
	weather.GetRain().SetLimits( 0.0, 0.0 );
	weather.GetFog().SetLimits( 0.0, 0.0 );
	weather.GetOvercast().SetForecastChangeLimits( 0.1, 0.3 );
	weather.GetOvercast().SetForecastTimeLimits( 1600, 2100 );
	weather.GetOvercast().Set( Math.RandomFloatInclusive( 0.1, 0.2 ), 0, 0 );	// ignored if storage is present
	weather.GetRain().Set( 0, 0, 0 );											// ignored if storage is present
	weather.GetFog().Set( 0, 0, 0 );											// ignored if storage is present
	weather.SetWindMaximumSpeed( 30 );
	weather.SetWindFunctionParams( 0.1, 1.0, 42 );
	weather.SetStorm( 0, 1, 1 );
	weather.SetRainThresholds( 0.0, 1.0, 0 );

	/*
	  [Namalsk] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	   currently recommended time-frame is:
		12/1 -> 12/31
		keep in mind that gameplay features are tied to the mission date (stored in the storage) and that it SHOULD remain this period!
	   while using:
		day accelerated 6 times (serverTimeAcceleration=6), resulting in an average 78 min of day-time (RL)
		night accelerated 24 times (serverNightTimeAcceleration=4), resulting in an average of 26 min of night-time (RL)
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );

    if ( month < 12 )
    {
    	year = 2011;
        month = 12;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
};

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.85 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.4 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.4 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.6 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.35 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.3 );
		}
	}

	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat( 0.50, 0.85 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}


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
		EntityAI gun = player.GetInventory().CreateInInventory("AKM");                 
		gun.GetInventory().CreateAttachment("AK_RailHndgrd");										      
		ItemBase gunlight = gun.GetInventory().CreateAttachment("UniversalLight");			
		gunlight.GetInventory().CreateAttachment("Battery9V");										     
		addMags(player, "Mag_AKM_30Rnd", 4);														             
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());	
				
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
		EntityAI gun = player.GetInventory().CreateInInventory("AKS74U");							
		addMags(player, "Mag_AK74_30Rnd", 2);														              
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());	
		
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
		EntityAI gun = player.GetInventory().CreateInInventory("AKS74U");  							
		addMags(player, "Mag_AK74_30Rnd", 2); 														              						
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());	
		
		player.SetQuickBarEntityShortcut(gun, 0, true);
		player.SetQuickBarEntityShortcut(melee, 1, true);
		return gun;
	}

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
			player.RemoveAllItems();
			PlayerIdentity identity; 
		
			ref TStringArray adminMembers = { // ADMIN IDS
				"FfmgBE23wertqn0tJIwRxYj4aEbZz4EQhG-7O4WPuFZ4=", 		// Admin 1 (using Bohemia UID) 		
				"77777777777777"						// Admin 2 (using Steam ID) 
			}
			
			ref TStringArray vipMembers = { // VIP IDS
				"JCmXrrt43efttyhfewew7tRLMUCOE6roH2O8SklBB1o=", 		// VIP 1 (using Bohemia UID) 			
				"55555555555555"						// VIP 2 (using Steam ID) 
			}
		
		// Don't touch anything below this line - Unless you know what you're doing.				
			if ((adminMembers.Find(identity.GetPlainId()) != -1) || (adminMembers.Find(identity.GetId()) != -1)) { 			
				adminLoadOut(player);	// ADMIN LOADOUT			
			} else if ((vipMembers.Find(identity.GetPlainId()) != -1) || (vipMembers.Find(identity.GetId()) != -1)) { 		
				vipLoadOut(player);		// VIP LOADOUT
			} else {
				randomLoadOut(player);	// Default Non-VIP Non-Admin Loadout
			}
		// bump fresh spawn water and energy values (to compensate for the frozen food and harder-to-get wells)
		player.GetStatWater().Set( 900 );
		player.GetStatEnergy().Set( 1100 );
	}
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
};

