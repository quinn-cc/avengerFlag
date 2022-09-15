/*
 Custom flag: AVenger (+AV)
 If you get killed with someone why they are holding a flag, they die too. If
 the killer is holding geno, then their team dies instead of yours.

 Special notes:
 - Works in parallel with the teamFlagGeno, gruesomeKiller, and fiftyPoint plugin.
   Those plugins are not needed for this plugin to work.
 - Assumes that player world weapon shots have the metadata "owner" associated
   with them.
 - SteamRoller (+SR) is immune to Avenger

 Copyright 2022 Quinn Carmack
 May be redistributed under either the LGPL or MIT licenses.
 
 ./configure --enable-custom-plugins=avengerFlag
*/

#include "bzfsAPI.h"

using namespace std;

class AvengerFlag : public bz_Plugin {

    virtual const char* Name()
    {
        return "Avenger Flag";
    }

    virtual void Init(const char*);
    virtual void Event(bz_EventData*);
    ~AvengerFlag();

    virtual void Cleanup(void)
    {
        Flush();
    }
};

BZ_PLUGIN(AvengerFlag)

void AvengerFlag::Init(const char*)
{
    bz_RegisterCustomFlag("AV", "Avenger", "If your killer is holding a flag, they die too. In the case of geno, their team dies instead of yours!", 0, eGoodFlag);
    Register(bz_ePlayerDieEvent);
}

AvengerFlag::~AvengerFlag() {}

void AvengerFlag::Event(bz_EventData *eventData)
{
    if (eventData->eventType == bz_ePlayerDieEvent)
    {
        bz_PlayerDieEventData_V2 *data = (bz_PlayerDieEventData_V2*) eventData;

        // Don't cover the case of non-shots and don't cover case of shooting yourself.
        if (data->shotID == -1 || data->playerID == data->killerID)
        	return;
        
        bz_ApiString flagHeldWhenKilled = bz_getFlagName(data->flagHeldWhenKilled);
			
		// If the victim was holding Avenger when they died...
	    if (flagHeldWhenKilled == "AV")
	    {
	    	uint32_t shotGUID = bz_getShotGUID(data->killerID, data->shotID);
	    	
	    	// This clever if statement ensures that the killer held a flag.
	    	// Either they officially have a flagKilledWith that is not
	    	// just an empty string, or the world weapon shot has an owner,
	    	// in which the world weapon shot belonged to a player with a
	    	// flag.
	    		
	    	if (data->flagKilledWith != "" || bz_shotHasMetaData(shotGUID, "owner"))
	    	{
	    		bz_BasePlayerRecord* playerRecord = bz_getPlayerByIndex(data->killerID);
	    		
	    		if (playerRecord && playerRecord->spawned == true)		// Make sure the player exists and is alive
	    		{
					bz_killPlayer(data->killerID, false, data->playerID, "AV");
					bz_sendTextMessage(BZ_SERVER, data->killerID, "You killed my father, prepare to die.");
	    		}
	    		
	    		bz_freePlayerRecord(playerRecord);
	    	}
	    }
    }
}

