static string ReduceVehicleDamageDIR = "$profile:ReduceVehicleDamage";
static string ReduceVehicleDamagePATH = ReduceVehicleDamageDIR + "\\config.json";

class ReduceVehicleDamageSettings
{
    private static bool initialized = false;
    private static ref ReduceVehicleDamageSettings settings;

	//Default Values
	string configVersion = "4";
    float dmgModifier = 0.8;
	float mindmg = 1350;
	bool subtractmindmg = true;
	bool nodmgifoff = false;
	bool perventCarRuined = false;
	
	float heliDmgModifier = 0.7;
	float heliMinDmg = 900;
	bool noExplodeIfOff = false;
	bool dmgBeforeExplode = true;
	bool autoHeliStablization = false;
	
	bool ResetLifeTimeOnStart = true;
		
	bool debugLogs = false;

	
    static ref ReduceVehicleDamageSettings Get()
    {
        if (initialized)
        {
            return settings;
        }

        ref ReduceVehicleDamageSettings data = new ref ReduceVehicleDamageSettings;
		
        if (FileExist(ReduceVehicleDamagePATH)) //If config file exsit load the file
        {
            JsonFileLoader<ReduceVehicleDamageSettings>.JsonLoadFile(ReduceVehicleDamagePATH, data);
            initialized = true;
			if (!data.heliDmgModifier){ //Update settings file with new settings
				data.perventCarRuined = false;
				data.heliDmgModifier = data.dmgModifier;
				data.heliMinDmg = data.mindmg;
				data.noExplodeIfOff = false;
				data.dmgBeforeExplode = false;
				data.debugLogs = false;
				JsonFileLoader<ReduceVehicleDamageSettings>.JsonSaveFile(ReduceVehicleDamagePATH, data);
			}
			if (!data.configVersion){
				data.configVersion = "3";
				data.autoHeliStablization = false;
				JsonFileLoader<ReduceVehicleDamageSettings>.JsonSaveFile(ReduceVehicleDamagePATH, data);
			}
			if (data.configVersion == "3"){
				data.configVersion = "4";
				data.ResetLifeTimeOnStart = true;
				JsonFileLoader<ReduceVehicleDamageSettings>.JsonSaveFile(ReduceVehicleDamagePATH, data);
			}
        }
        else //If config file doesn't exsit create the file
        {
			
            if (GetGame().IsServer() || !GetGame().IsMultiplayer())
            {
                MakeDirectory(ReduceVehicleDamageDIR);
                JsonFileLoader<ReduceVehicleDamageSettings>.JsonSaveFile(ReduceVehicleDamagePATH, data);
            }
        }

        settings = data;

        return settings;
    }
}
