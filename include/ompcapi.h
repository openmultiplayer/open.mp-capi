#ifndef OMPCAPI_H
#define OMPCAPI_H

#include <stdint.h>
#include <stdbool.h>

#ifndef CAPI_COMPONENT_BUILD
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#define LIBRARY_OPEN(path) LoadLibrary(path)
#define LIBRARY_GET_ADDR(lib, symbol) GetProcAddress((HMODULE)lib, symbol)
#else
#include <dlfcn.h>
#define LIBRARY_OPEN(path) dlopen(path, RTLD_LAZY | RTLD_LOCAL)
#define LIBRARY_GET_ADDR dlsym
#endif
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define OMP_API_EXPORT __declspec(dllexport)
#else
#define OMP_API_EXPORT __attribute__((visibility("default")))
#endif

// Events

enum EventPriorityType
{
	EventPriorityType_Highest,
	EventPriorityType_FairlyHigh,
	EventPriorityType_Default,
	EventPriorityType_FairlyLow,
	EventPriorityType_Lowest,
};

struct EventArgs_Common
{
	int size;
	void** list;
};

typedef bool (*EventCallback_Common)(struct EventArgs_Common* args);

// Components

struct ComponentVersion
{
	uint8_t major; ///< MAJOR version when you make incompatible API changes
	uint8_t minor; ///< MINOR version when you add functionality in a backwards compatible manner
	uint8_t patch; ///< PATCH version when you make backwards compatible bug fixes
	uint16_t prerel; ///< PRE-RELEASE version
};

typedef void (*ComponentOnReadyCallback)();
typedef void (*ComponentOnResetCallback)();
typedef void (*ComponentOnFreeCallback)();

struct CAPIStringView
{
	unsigned int len;
	char* data;
};

#ifndef CAPI_COMPONENT_BUILD

typedef void* Player;
typedef void* Vehicle;
typedef void* Menu;
typedef void* TextDraw;
typedef void* TextLabel;
typedef void* Object;
typedef void* PlayerObject;
typedef void* PlayerTextLabel3D;
typedef void* PlayerTextDraw;
typedef void* Class;
typedef void* GangZone;
typedef void* Pickup;


// Actor function type definitions
typedef void* (*Actor_Create_t)(int model, float x, float y, float z, float rot, int* id);
typedef bool (*Actor_Destroy_t)(void* actor);
typedef void* (*Actor_FromID_t)(int actorid);
typedef int (*Actor_GetID_t)(void* actor);
typedef bool (*Actor_IsStreamedInFor_t)(void* actor, void* player);
typedef bool (*Actor_SetVirtualWorld_t)(void* actor, int vw);
typedef int (*Actor_GetVirtualWorld_t)(void* actor);
typedef bool (*Actor_ApplyAnimation_t)(void* actor, const char* name, const char* library, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time);
typedef bool (*Actor_ClearAnimations_t)(void* actor);
typedef bool (*Actor_SetPos_t)(void* actor, float x, float y, float z);
typedef bool (*Actor_GetPos_t)(void* actor, float* x, float* y, float* z);
typedef bool (*Actor_SetFacingAngle_t)(void* actor, float angle);
typedef float (*Actor_GetFacingAngle_t)(void* actor);
typedef bool (*Actor_SetHealth_t)(void* actor, float hp);
typedef float (*Actor_GetHealth_t)(void* actor);
typedef bool (*Actor_SetInvulnerable_t)(void* actor, bool toggle);
typedef bool (*Actor_IsInvulnerable_t)(void* actor);
typedef bool (*Actor_IsValid_t)(void* actor);
typedef bool (*Actor_SetSkin_t)(void* actor, int skin);
typedef int (*Actor_GetSkin_t)(void* actor);
typedef bool (*Actor_GetAnimation_t)(void* actor, struct CAPIStringView* library, struct CAPIStringView* name, float* delta, bool* loop, bool* lockX, bool* lockY, bool* freeze, int* time);
typedef bool (*Actor_GetSpawnInfo_t)(void* actor, float* x, float* y, float* z, float* angle, int* skin);


// Checkpoint function type definitions
typedef bool (*Checkpoint_Set_t)(void* player, float x, float y, float z, float radius);
typedef bool (*Checkpoint_Disable_t)(void* player);
typedef bool (*Checkpoint_IsPlayerIn_t)(void* player);
typedef bool (*Checkpoint_IsActive_t)(void* player);
typedef bool (*Checkpoint_Get_t)(void* player, float* x, float* y, float* z, float* radius);


// RaceCheckpoint function type definitions
typedef bool (*RaceCheckpoint_Set_t)(void* player, int type, float x, float y, float z, float nextX, float nextY, float nextZ, float radius);
typedef bool (*RaceCheckpoint_Disable_t)(void* player);
typedef bool (*RaceCheckpoint_IsPlayerIn_t)(void* player);
typedef bool (*RaceCheckpoint_IsActive_t)(void* player);
typedef bool (*RaceCheckpoint_Get_t)(void* player, float* x, float* y, float* z, float* nextX, float* nextY, float* nextZ, float* radius);


// Class function type definitions
typedef void* (*Class_Add_t)(uint8_t team, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3, int* id);
typedef void* (*Class_FromID_t)(int classid);
typedef int (*Class_GetID_t)(void* cls);
typedef int (*Class_Count_t)();
typedef bool (*Class_GetData_t)(void* classptr, uint8_t* teamid, int* skin, float* x, float* y, float* z, float* angle, uint8_t* weapon1, uint32_t* weapon1_ammo, uint8_t* weapon2, uint32_t* weapon2_ammo, uint8_t* weapon3, uint32_t* weapon3_ammo);
typedef bool (*Class_Edit_t)(void* classptr, uint8_t teamid, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3);


// Player function type definitions
typedef bool (*Player_SetSpawnInfo_t)(void* player, uint8_t team, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3);
typedef bool (*Player_GetSpawnInfo_t)(void* player, uint8_t* team, int* skin, float* x, float* y, float* z, float* angle, uint8_t* weapon1, uint32_t* ammo1, uint8_t* weapon2, uint32_t* ammo2, uint8_t* weapon3, uint32_t* ammo3);
typedef int (*Player_GetNetworkStats_t)(void* player, struct CAPIStringView* output);
typedef int (*Player_NetStatsBytesReceived_t)(void* player);
typedef int (*Player_NetStatsBytesSent_t)(void* player);
typedef int (*Player_NetStatsConnectionStatus_t)(void* player);
typedef int (*Player_NetStatsGetConnectedTime_t)(void* player);
typedef bool (*Player_NetStatsGetIpPort_t)(void* player, struct CAPIStringView* output);
typedef int (*Player_NetStatsMessagesReceived_t)(void* player);
typedef int (*Player_NetStatsMessagesRecvPerSecond_t)(void* player);
typedef int (*Player_NetStatsMessagesSent_t)(void* player);
typedef float (*Player_NetStatsPacketLossPercent_t)(void* player);
typedef int (*Player_GetCustomSkin_t)(void* player);
typedef int (*Player_GetDialog_t)(void* player);
typedef bool (*Player_GetDialogData_t)(void* player, int* dialogid, int* style, struct CAPIStringView* title, struct CAPIStringView* body, struct CAPIStringView* button1, struct CAPIStringView* button2);
typedef void* (*Player_GetMenu_t)(void* player);
typedef void* (*Player_GetSurfingPlayerObject_t)(void* player);
typedef void* (*Player_GetCameraTargetPlayerObject_t)(void* player);
typedef void* (*Player_FromID_t)(int playerid);
typedef int (*Player_GetID_t)(void* player);
typedef bool (*Player_SendClientMessage_t)(void* player, uint32_t color, const char* text);
typedef bool (*Player_SetCameraPos_t)(void* player, float x, float y, float z);
typedef bool (*Player_SetDrunkLevel_t)(void* player, int level);
typedef bool (*Player_SetInterior_t)(void* player, int interior);
typedef bool (*Player_SetWantedLevel_t)(void* player, int level);
typedef bool (*Player_SetWeather_t)(void* player, int weather);
typedef int (*Player_GetWeather_t)(void* player);
typedef bool (*Player_SetSkin_t)(void* player, int skin);
typedef bool (*Player_SetShopName_t)(void* player, const char* name);
typedef bool (*Player_GiveMoney_t)(void* player, int amount);
typedef bool (*Player_SetCameraLookAt_t)(void* player, float x, float y, float z, int cutType);
typedef bool (*Player_SetCameraBehind_t)(void* player);
typedef bool (*Player_CreateExplosion_t)(void* player, float x, float y, float z, int type, float radius);
typedef bool (*Player_PlayAudioStream_t)(void* player, const char* url, float x, float y, float z, float distance, bool usePos);
typedef bool (*Player_StopAudioStream_t)(void* player);
typedef bool (*Player_ToggleWidescreen_t)(void* player, bool enable);
typedef bool (*Player_IsWidescreenToggled_t)(void* player);
typedef bool (*Player_SetHealth_t)(void* player, float health);
typedef float (*Player_GetHealth_t)(void* player);
typedef bool (*Player_SetArmor_t)(void* player, float armor);
typedef float (*Player_GetArmor_t)(void* player);
typedef bool (*Player_SetTeam_t)(void* player, int team);
typedef int (*Player_GetTeam_t)(void* player);
typedef bool (*Player_SetScore_t)(void* player, int score);
typedef int (*Player_GetScore_t)(void* player);
typedef int (*Player_GetSkin_t)(void* player);
typedef bool (*Player_SetColor_t)(void* player, uint32_t color);
typedef uint32_t (*Player_GetColor_t)(void* player);
typedef uint32_t (*Player_GetDefaultColor_t)(void* player);
typedef int (*Player_GetDrunkLevel_t)(void* player);
typedef bool (*Player_GiveWeapon_t)(void* player, int weapon, int ammo);
typedef bool (*Player_RemoveWeapon_t)(void* player, int weapon);
typedef int (*Player_GetMoney_t)(void* player);
typedef bool (*Player_ResetMoney_t)(void* player);
typedef int (*Player_SetName_t)(void* player, const char* name);
typedef int (*Player_GetName_t)(void* player, struct CAPIStringView* name);
typedef int (*Player_GetState_t)(void* player);
typedef int (*Player_GetPing_t)(void* player);
typedef int (*Player_GetWeapon_t)(void* player);
typedef bool (*Player_SetTime_t)(void* player, int hour, int minute);
typedef bool (*Player_GetTime_t)(void* player, int* hour, int* minute);
typedef bool (*Player_ToggleClock_t)(void* player, bool enable);
typedef bool (*Player_HasClock_t)(void* player);
typedef bool (*Player_ForceClassSelection_t)(void* player);
typedef int (*Player_GetWantedLevel_t)(void* player);
typedef bool (*Player_SetFightingStyle_t)(void* player, int style);
typedef int (*Player_GetFightingStyle_t)(void* player);
typedef bool (*Player_SetVelocity_t)(void* player, float x, float y, float z);
typedef bool (*Player_GetVelocity_t)(void* player, float* x, float* y, float* z);
typedef bool (*Player_GetCameraPos_t)(void* player, float* x, float* y, float* z);
typedef float (*Player_GetDistanceFromPoint_t)(void* player, float x, float y, float z);
typedef int (*Player_GetInterior_t)(void* player);
typedef bool (*Player_SetPos_t)(void* player, float x, float y, float z);
typedef bool (*Player_GetPos_t)(void* player, float* x, float* y, float* z);
typedef int (*Player_GetVirtualWorld_t)(void* player);
typedef bool (*Player_IsNPC_t)(void* player);
typedef bool (*Player_IsStreamedIn_t)(void* player, void* other);
typedef bool (*Player_PlayGameSound_t)(void* player, int sound, float x, float y, float z);
typedef bool (*Player_SpectatePlayer_t)(void* player, void* target, int mode);
typedef bool (*Player_SpectateVehicle_t)(void* player, void* target, int mode);
typedef bool (*Player_SetVirtualWorld_t)(void* player, int vw);
typedef bool (*Player_SetWorldBounds_t)(void* player, float xMax, float xMin, float yMax, float yMin);
typedef bool (*Player_ClearWorldBounds_t)(void* player);
typedef bool (*Player_GetWorldBounds_t)(void* player, float* xmax, float* xmin, float* ymax, float* ymin);
typedef bool (*Player_ClearAnimations_t)(void* player, int syncType);
typedef bool (*Player_GetLastShotVectors_t)(void* player, float* origin_x, float* origin_y, float* origin_z, float* hit_x, float* hit_y, float* hit_z);
typedef void* (*Player_GetCameraTargetPlayer_t)(void* player);
typedef void* (*Player_GetCameraTargetActor_t)(void* player);
typedef void* (*Player_GetCameraTargetObject_t)(void* player);
typedef void* (*Player_GetCameraTargetVehicle_t)(void* player);
typedef bool (*Player_PutInVehicle_t)(void* player, void* vehicle, int seat);
typedef bool (*Player_RemoveBuilding_t)(void* player, int model, float x, float y, float z, float radius);
typedef int (*Player_GetBuildingsRemoved_t)(void* player);
typedef bool (*Player_RemoveFromVehicle_t)(void* player, bool force);
typedef bool (*Player_RemoveMapIcon_t)(void* player, int icon);
typedef bool (*Player_SetMapIcon_t)(void* player, int iconID, float x, float y, float z, int type, uint32_t color, int style);
typedef bool (*Player_ResetWeapons_t)(void* player);
typedef bool (*Player_SetAmmo_t)(void* player, uint8_t id, uint32_t ammo);
typedef bool (*Player_SetArmedWeapon_t)(void* player, uint8_t weapon);
typedef bool (*Player_SetChatBubble_t)(void* player, const char* text, uint32_t color, float drawdistance, int expiretime);
typedef bool (*Player_SetPosFindZ_t)(void* player, float x, float y, float z);
typedef bool (*Player_SetSkillLevel_t)(void* player, uint8_t weapon, int level);
typedef bool (*Player_SetSpecialAction_t)(void* player, uint32_t action);
typedef bool (*Player_ShowNameTagForPlayer_t)(void* player, void* other, bool enable);
typedef bool (*Player_ToggleControllable_t)(void* player, bool enable);
typedef bool (*Player_ToggleSpectating_t)(void* player, bool enable);
typedef bool (*Player_ApplyAnimation_t)(void* player, const char* animlib, const char* animname, float delta, bool loop, bool lockX, bool lockY, bool freeze, uint32_t time, int sync);
typedef bool (*Player_GetAnimationName_t)(int index, struct CAPIStringView* lib, struct CAPIStringView* name);
typedef bool (*Player_EditAttachedObject_t)(void* player, int index);
typedef bool (*Player_EnableCameraTarget_t)(void* player, bool enable);
typedef bool (*Player_EnableStuntBonus_t)(void* player, bool enable);
typedef int (*Player_GetPlayerAmmo_t)(void* player);
typedef int (*Player_GetAnimationIndex_t)(void* player);
typedef float (*Player_GetFacingAngle_t)(void* player);
typedef int (*Player_GetIp_t)(void* player, struct CAPIStringView* ip);
typedef int (*Player_GetSpecialAction_t)(void* player);
typedef int (*Player_GetVehicleID_t)(void* player);
typedef int (*Player_GetVehicleSeat_t)(void* player);
typedef bool (*Player_GetWeaponData_t)(void* player, int slot, int* weaponid, int* ammo);
typedef int (*Player_GetWeaponState_t)(void* player);
typedef bool (*Player_InterpolateCameraPos_t)(void* player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut);
typedef bool (*Player_InterpolateCameraLookAt_t)(void* player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut);
typedef bool (*Player_IsPlayerAttachedObjectSlotUsed_t)(void* player, int index);
typedef bool (*Player_AttachCameraToObject_t)(void* player, void* object);
typedef bool (*Player_AttachCameraToPlayerObject_t)(void* player, void* object);
typedef float (*Player_GetCameraAspectRatio_t)(void* player);
typedef bool (*Player_GetCameraFrontVector_t)(void* player, float* x, float* y, float* z);
typedef int (*Player_GetCameraMode_t)(void* player);
typedef bool (*Player_GetKeys_t)(void* player, int* keys, int* updown, int* leftright);
typedef void* (*Player_GetSurfingVehicle_t)(void* player);
typedef void* (*Player_GetSurfingObject_t)(void* player);
typedef void* (*Player_GetTargetPlayer_t)(void* player);
typedef void* (*Player_GetTargetActor_t)(void* player);
typedef bool (*Player_IsInVehicle_t)(void* player, void* targetVehicle);
typedef bool (*Player_IsInAnyVehicle_t)(void* player);
typedef bool (*Player_IsInRangeOfPoint_t)(void* player, float range, float x, float y, float z);
typedef bool (*Player_PlayCrimeReport_t)(void* player, void* suspect, int crime);
typedef bool (*Player_RemoveAttachedObject_t)(void* player, int index);
typedef bool (*Player_SetAttachedObject_t)(void* player, int index, int modelid, int bone, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ, uint32_t materialcolor1, uint32_t materialcolor2);
typedef bool (*Player_GetAttachedObject_t)(void* player, int index, int* modelid, int* bone, float* offsetX, float* offsetY, float* offsetZ, float* rotationX, float* rotationY, float* rotationZ, float* scaleX, float* scaleY, float* scaleZ, int* materialcolor1, int* materialcolor2);
typedef bool (*Player_SetFacingAngle_t)(void* player, float angle);
typedef bool (*Player_SetMarkerForPlayer_t)(void* player, void* other, uint32_t color);
typedef uint32_t (*Player_GetMarkerForPlayer_t)(void* player, void* other);
typedef bool (*Player_AllowTeleport_t)(void* player, bool allow);
typedef bool (*Player_IsTeleportAllowed_t)(void* player);
typedef bool (*Player_DisableRemoteVehicleCollisions_t)(void* player, bool disable);
typedef float (*Player_GetCameraZoom_t)(void* player);
typedef bool (*Player_SelectTextDraw_t)(void* player, uint32_t hoverColour);
typedef bool (*Player_CancelSelectTextDraw_t)(void* player);
typedef bool (*Player_SendClientCheck_t)(void* player, int actionType, int address, int offset, int count);
typedef bool (*Player_Spawn_t)(void* player);
typedef bool (*Player_GPCI_t)(void* player, struct CAPIStringView* gpci);
typedef bool (*Player_IsAdmin_t)(void* player);
typedef bool (*Player_Kick_t)(void* player);
typedef bool (*Player_ShowGameText_t)(void* player, const char* text, int time, int style);
typedef bool (*Player_HideGameText_t)(void* player, int style);
typedef bool (*Player_HasGameText_t)(void* player, int style);
typedef bool (*Player_GetGameText_t)(void* player, int style, struct CAPIStringView* message, int* time, int* remaining);
typedef bool (*Player_Ban_t)(void* player);
typedef bool (*Player_BanEx_t)(void* player, const char* reason);
typedef bool (*Player_SendDeathMessage_t)(void* player, void* killer, void* killee, int weapon);
typedef bool (*Player_SendMessageToPlayer_t)(void* player, void* sender, const char* message);
typedef int (*Player_GetVersion_t)(void* player, struct CAPIStringView* version);
typedef int (*Player_GetSkillLevel_t)(void* player, int skill);
typedef float (*Player_GetZAim_t)(void* player);
typedef bool (*Player_GetSurfingOffsets_t)(void* player, float* offsetX, float* offsetY, float* offsetZ);
typedef bool (*Player_GetRotationQuat_t)(void* player, float* x, float* y, float* z, float* w);
typedef int (*Player_GetPlayerSpectateID_t)(void* player);
typedef int (*Player_GetSpectateType_t)(void* player);
typedef uint32_t (*Player_GetRawIp_t)(void* player);
typedef bool (*Player_SetGravity_t)(void* player, float gravity);
typedef float (*Player_GetGravity_t)(void* player);
typedef bool (*Player_SetAdmin_t)(void* player, bool set);
typedef bool (*Player_IsSpawned_t)(void* player);
typedef bool (*Player_IsControllable_t)(void* player);
typedef bool (*Player_IsCameraTargetEnabled_t)(void* player);
typedef bool (*Player_ToggleGhostMode_t)(void* player, bool toggle);
typedef bool (*Player_GetGhostMode_t)(void* player);
typedef bool (*Player_AllowWeapons_t)(void* player, bool allow);
typedef bool (*Player_AreWeaponsAllowed_t)(void* player);
typedef bool (*Player_IsPlayerUsingOfficialClient_t)(void* player);
typedef int (*Player_GetAnimationFlags_t)(void* player);
typedef bool (*Player_IsInDriveByMode_t)(void* player);
typedef bool (*Player_IsCuffed_t)(void* player);
typedef bool (*Player_IsInModShop_t)(void* player);
typedef int (*Player_GetSirenState_t)(void* player);
typedef int (*Player_GetLandingGearState_t)(void* player);
typedef uint32_t (*Player_GetHydraReactorAngle_t)(void* player);
typedef float (*Player_GetTrainSpeed_t)(void* player);
typedef bool (*Player_IsPlayerUsingOmp_t)(void* player);


// Component function type definitions
typedef void* (*Component_Create_t)(uint64_t uid, const char* name, struct ComponentVersion version, void* onReadyCB, void* onResetCB, void* onFreeCB);


// Config function type definitions
typedef bool (*Config_GetAsBool_t)(const char* cvar);
typedef int (*Config_GetAsInt_t)(const char* cvar);
typedef float (*Config_GetAsFloat_t)(const char* cvar);
typedef int (*Config_GetAsString_t)(const char* cvar, struct CAPIStringView* output);


// Core function type definitions
typedef uint32_t (*Core_TickCount_t)();
typedef int (*Core_MaxPlayers_t)();
typedef bool (*Core_Log_t)(const char* text);
typedef bool (*Core_IsAdminTeleportAllowed_t)();
typedef bool (*Core_AllowAdminTeleport_t)(bool allow);
typedef bool (*Core_AreAllAnimationsEnabled_t)();
typedef bool (*Core_EnableAllAnimations_t)(bool allow);
typedef bool (*Core_IsAnimationLibraryValid_t)(const char* name);
typedef bool (*Core_AreInteriorWeaponsAllowed_t)();
typedef bool (*Core_AllowInteriorWeapons_t)(bool allow);
typedef bool (*Core_BlockIpAddress_t)(const char* ipAddress, int timeMS);
typedef bool (*Core_UnBlockIpAddress_t)(const char* ipAddress);
typedef bool (*Core_DisableEntryExitMarkers_t)();
typedef bool (*Core_DisableNameTagsLOS_t)();
typedef bool (*Core_EnableZoneNames_t)(bool enable);
typedef bool (*Core_ShowGameTextForAll_t)(const char* msg, int time, int style);
typedef bool (*Core_HideGameTextForAll_t)(int style);
typedef int (*Core_NetworkStats_t)(struct CAPIStringView* output);
typedef int (*Core_ServerTickRate_t)();
typedef bool (*Core_GetWeaponName_t)(int weaponid, struct CAPIStringView* output);
typedef bool (*Core_SetChatRadius_t)(float globalChatRadius);
typedef bool (*Core_SetMarkerRadius_t)(float playerMarkerRadius);
typedef bool (*Core_SendRconCommand_t)(const char* command);
typedef bool (*Core_SetDeathDropAmount_t)(int amount);
typedef bool (*Core_GameMode_t)(const char* string);
typedef bool (*Core_SetGravity_t)(float gravity);
typedef float (*Core_GetGravity_t)();
typedef bool (*Core_SetNameTagsDrawDistance_t)(float distance);
typedef bool (*Core_SetWeather_t)(int weatherid);
typedef bool (*Core_SetWorldTime_t)(int hour);
typedef bool (*Core_ShowNameTags_t)(bool show);
typedef bool (*Core_ShowPlayerMarkers_t)(int mode);
typedef bool (*Core_UsePedAnims_t)();
typedef int (*Core_GetWeather_t)();
typedef int (*Core_GetWorldTime_t)();
typedef bool (*Core_ToggleChatTextReplacement_t)(bool enable);
typedef bool (*Core_IsChatTextReplacementToggled_t)();
typedef bool (*Core_IsNickNameValid_t)(const char* name);
typedef bool (*Core_AllowNickNameCharacter_t)(int character, bool allow);
typedef bool (*Core_IsNickNameCharacterAllowed_t)(int character);
typedef bool (*Core_ClearBanList_t)();
typedef bool (*Core_IsIpAddressBanned_t)(const char* ip);
typedef int (*Core_GetWeaponSlot_t)(uint8_t weapon);
typedef bool (*Core_AddRule_t)(const char* name, const char* value);
typedef bool (*Core_IsValidRule_t)(const char* name);
typedef bool (*Core_RemoveRule_t)(const char* name);


// NPC function type definitions
typedef bool (*NPC_Connect_t)(const char* name, const char* script);


// CustomModel function type definitions
typedef bool (*CustomModel_AddCharModel_t)(int baseid, int newid, const char* dff, const char* textureLibrary);
typedef bool (*CustomModel_AddSimpleModel_t)(int virtualWorld, int baseid, int newid, const char* dff, const char* textureLibrary);
typedef bool (*CustomModel_AddSimpleModelTimed_t)(int virtualWorld, int baseid, int newid, const char* dff, const char* textureLibrary, int timeOn, int timeOff);
typedef bool (*CustomModel_RedirectDownload_t)(void* player, const char* url);
typedef int (*CustomModel_FindModelFileNameFromCRC_t)(int crc, struct CAPIStringView* output);
typedef bool (*CustomModel_IsValid_t)(int modelId);
typedef bool (*CustomModel_GetPath_t)(int modelId, struct CAPIStringView* dffPath, struct CAPIStringView* txdPath);


// Dialog function type definitions
typedef bool (*Dialog_Show_t)(void* player, int dialog, int style, const char* title, const char* body, const char* button1, const char* button2);
typedef bool (*Dialog_Hide_t)(void* player);


// Event function type definitions
typedef bool (*Event_AddHandler_t)(const char* name, int priority, void* callback);
typedef bool (*Event_RemoveHandler_t)(const char* name, int priority, void* callback);
typedef bool (*Event_RemoveAllHandlers_t)(const char* name, int priority);


// GangZone function type definitions
typedef void* (*GangZone_Create_t)(float minx, float miny, float maxx, float maxy, int* id);
typedef bool (*GangZone_Destroy_t)(void* gangzone);
typedef void* (*GangZone_FromID_t)(int gangzoneid);
typedef int (*GangZone_GetID_t)(void* gangzone);
typedef bool (*GangZone_ShowForPlayer_t)(void* player, void* gangzone, uint32_t color);
typedef bool (*GangZone_ShowForAll_t)(void* gangzone, uint32_t color);
typedef bool (*GangZone_HideForPlayer_t)(void* player, void* gangzone);
typedef bool (*GangZone_HideForAll_t)(void* gangzone);
typedef bool (*GangZone_FlashForPlayer_t)(void* player, void* gangzone, uint32_t color);
typedef bool (*GangZone_FlashForAll_t)(void* gangzone, uint32_t color);
typedef bool (*GangZone_StopFlashForPlayer_t)(void* player, void* gangzone);
typedef bool (*GangZone_StopFlashForAll_t)(void* gangzone);
typedef bool (*GangZone_IsValid_t)(void* gangzone);
typedef bool (*GangZone_IsPlayerIn_t)(void* player, void* gangzone);
typedef bool (*GangZone_IsVisibleForPlayer_t)(void* player, void* gangzone);
typedef int (*GangZone_GetColorForPlayer_t)(void* player, void* gangzone);
typedef int (*GangZone_GetFlashColorForPlayer_t)(void* player, void* gangzone);
typedef bool (*GangZone_IsFlashingForPlayer_t)(void* player, void* gangzone);
typedef bool (*GangZone_GetPos_t)(void* gangzone, float* minx, float* miny, float* maxx, float* maxy);
typedef bool (*GangZone_UseCheck_t)(void* gangzone, bool enable);


// Menu function type definitions
typedef void* (*Menu_Create_t)(const char* title, uint32_t columns, float x, float y, float column1Width, float column2Width, int* id);
typedef bool (*Menu_Destroy_t)(void* menu);
typedef void* (*Menu_FromID_t)(int menuid);
typedef int (*Menu_GetID_t)(void* menu);
typedef int (*Menu_AddItem_t)(void* menu, uint8_t column, const char* text);
typedef bool (*Menu_SetColumnHeader_t)(void* menu, uint8_t column, const char* headerTitle);
typedef bool (*Menu_ShowForPlayer_t)(void* menu, void* player);
typedef bool (*Menu_HideForPlayer_t)(void* menu, void* player);
typedef bool (*Menu_Disable_t)(void* menu);
typedef bool (*Menu_DisableRow_t)(void* menu, uint8_t row);
typedef bool (*Menu_IsValid_t)(void* menu);
typedef bool (*Menu_IsDisabled_t)(void* menu);
typedef bool (*Menu_IsRowDisabled_t)(void* menu, int row);
typedef int (*Menu_GetColumns_t)(void* menu);
typedef int (*Menu_GetItems_t)(void* menu, int column);
typedef bool (*Menu_GetPos_t)(void* menu, float* x, float* y);
typedef bool (*Menu_GetColumnWidth_t)(void* menu, float* column1Width, float* column2Width);
typedef bool (*Menu_GetColumnHeader_t)(void* menu, int column, struct CAPIStringView* header);
typedef bool (*Menu_GetItem_t)(void* menu, int column, int row, struct CAPIStringView* item);


// Object function type definitions
typedef void* (*Object_Create_t)(int modelid, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float drawDistance, int* id);
typedef bool (*Object_Destroy_t)(void* object);
typedef void* (*Object_FromID_t)(int objectid);
typedef int (*Object_GetID_t)(void* object);
typedef bool (*Object_AttachToVehicle_t)(void* object, void* vehicle, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ);
typedef bool (*Object_AttachToObject_t)(void* object, void* objAttachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, bool syncRotation);
typedef bool (*Object_AttachToPlayer_t)(void* object, void* player, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ);
typedef bool (*Object_SetPos_t)(void* object, float x, float y, float z);
typedef bool (*Object_GetPos_t)(void* object, float* x, float* y, float* z);
typedef bool (*Object_SetRot_t)(void* object, float rotationX, float rotationY, float rotationZ);
typedef bool (*Object_GetRot_t)(void* object, float* rotationX, float* rotationY, float* rotationZ);
typedef int (*Object_GetModel_t)(void* object);
typedef bool (*Object_SetNoCameraCollision_t)(void* object);
typedef bool (*Object_IsValid_t)(void* object);
typedef int (*Object_Move_t)(void* object, float x, float y, float z, float speed, float rotationX, float rotationY, float rotationZ);
typedef bool (*Object_Stop_t)(void* object);
typedef bool (*Object_IsMoving_t)(void* object);
typedef bool (*Object_BeginEditing_t)(void* player, void* object);
typedef bool (*Object_BeginSelecting_t)(void* player);
typedef bool (*Object_EndEditing_t)(void* player);
typedef bool (*Object_SetMaterial_t)(void* object, int materialIndex, int modelId, const char* textureLibrary, const char* textureName, uint32_t materialColor);
typedef bool (*Object_SetMaterialText_t)(void* object, const char* text, int materialIndex, int materialSize, const char* fontface, int fontsize, bool bold, uint32_t fontColor, uint32_t backgroundColor, int textalignment);
typedef bool (*Object_SetDefaultCameraCollision_t)(bool disable);
typedef float (*Object_GetDrawDistance_t)(void* object);
typedef float (*Object_GetMoveSpeed_t)(void* object);
typedef bool (*Object_GetMovingTargetPos_t)(void* object, float* targetX, float* targetY, float* targetZ);
typedef bool (*Object_GetMovingTargetRot_t)(void* object, float* rotationX, float* rotationY, float* rotationZ);
typedef bool (*Object_GetAttachedData_t)(void* object, int* parentVehicle, int* parentObject, int* parentPlayer);
typedef bool (*Object_GetAttachedOffset_t)(void* object, float* offsetX, float* offsetY, float* offsetZ, float* rotationX, float* rotationY, float* rotationZ);
typedef bool (*Object_GetSyncRotation_t)(void* object);
typedef bool (*Object_IsMaterialSlotUsed_t)(void* object, int materialIndex);
typedef bool (*Object_GetMaterial_t)(void* object, int materialIndex, int* modelid, struct CAPIStringView* textureLibrary, struct CAPIStringView* textureName, int* materialColor);
typedef bool (*Object_GetMaterialText_t)(void* object, int materialIndex, struct CAPIStringView* text, int* materialSize, struct CAPIStringView* fontFace, int* fontSize, bool* bold, int* fontColor, int* backgroundColor, int* textAlignment);
typedef bool (*Object_IsObjectNoCameraCollision_t)(void* object);
typedef uint8_t (*Object_GetType_t)(void* player, int objectid);


// PlayerObject function type definitions
typedef void* (*PlayerObject_Create_t)(void* player, int modelid, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float drawDistance, int* id);
typedef bool (*PlayerObject_Destroy_t)(void* player, void* object);
typedef void* (*PlayerObject_FromID_t)(void* player, int objectid);
typedef int (*PlayerObject_GetID_t)(void* player, void* object);
typedef bool (*PlayerObject_AttachToVehicle_t)(void* player, void* object, void* vehicle, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ);
typedef bool (*PlayerObject_AttachToPlayer_t)(void* player, void* object, void* playerAttachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ);
typedef bool (*PlayerObject_AttachToObject_t)(void* player, void* object, void* attachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ);
typedef bool (*PlayerObject_SetPos_t)(void* player, void* object, float x, float y, float z);
typedef bool (*PlayerObject_GetPos_t)(void* player, void* object, float* x, float* y, float* z);
typedef bool (*PlayerObject_SetRot_t)(void* player, void* object, float rotationX, float rotationY, float rotationZ);
typedef bool (*PlayerObject_GetRot_t)(void* player, void* object, float* rotationX, float* rotationY, float* rotationZ);
typedef int (*PlayerObject_GetModel_t)(void* player, void* object);
typedef bool (*PlayerObject_SetNoCameraCollision_t)(void* player, void* object);
typedef bool (*PlayerObject_IsValid_t)(void* player, void* object);
typedef int (*PlayerObject_Move_t)(void* player, void* object, float x, float y, float z, float speed, float rotationX, float rotationY, float rotationZ);
typedef bool (*PlayerObject_Stop_t)(void* player, void* object);
typedef bool (*PlayerObject_IsMoving_t)(void* player, void* object);
typedef bool (*PlayerObject_BeginEditing_t)(void* player, void* object);
typedef bool (*PlayerObject_SetMaterial_t)(void* player, void* object, int materialIndex, int modelId, const char* textureLibrary, const char* textureName, uint32_t materialColor);
typedef bool (*PlayerObject_SetMaterialText_t)(void* player, void* object, const char* text, int materialIndex, int materialSize, const char* fontface, int fontsize, bool bold, uint32_t fontColor, uint32_t backgroundColor, int textalignment);
typedef float (*PlayerObject_GetDrawDistance_t)(void* player, void* object);
typedef float (*PlayerObject_GetMoveSpeed_t)(void* player, void* object);
typedef bool (*PlayerObject_GetMovingTargetPos_t)(void* player, void* object, float* targetX, float* targetY, float* targetZ);
typedef bool (*PlayerObject_GetMovingTargetRot_t)(void* player, void* object, float* rotationX, float* rotationY, float* rotationZ);
typedef bool (*PlayerObject_GetAttachedData_t)(void* player, void* object, int* parentVehicle, int* parentObject, int* parentPlayer);
typedef bool (*PlayerObject_GetAttachedOffset_t)(void* player, void* object, float* offsetX, float* offsetY, float* offsetZ, float* rotationX, float* rotationY, float* rotationZ);
typedef bool (*PlayerObject_GetSyncRotation_t)(void* player, void* object);
typedef bool (*PlayerObject_IsMaterialSlotUsed_t)(void* player, void* object, int materialIndex);
typedef bool (*PlayerObject_GetMaterial_t)(void* player, void* object, int materialIndex, int* modelid, struct CAPIStringView* textureLibrary, struct CAPIStringView* textureName, int* materialColor);
typedef bool (*PlayerObject_GetMaterialText_t)(void* player, void* object, int materialIndex, struct CAPIStringView* text, int* materialSize, struct CAPIStringView* fontFace, int* fontSize, bool* bold, int* fontColor, int* backgroundColor, int* textAlignment);
typedef bool (*PlayerObject_IsNoCameraCollision_t)(void* player, void* object);


// Pickup function type definitions
typedef void* (*Pickup_Create_t)(int model, int type, float x, float y, float z, int virtualWorld, int* id);
typedef bool (*Pickup_AddStatic_t)(int model, int type, float x, float y, float z, int virtualWorld);
typedef bool (*Pickup_Destroy_t)(void* pickup);
typedef void* (*Pickup_FromID_t)(int pickupid);
typedef int (*Pickup_GetID_t)(void* pickup);
typedef bool (*Pickup_IsValid_t)(void* pickup);
typedef bool (*Pickup_IsStreamedIn_t)(void* player, void* pickup);
typedef bool (*Pickup_GetPos_t)(void* pickup, float* x, float* y, float* z);
typedef int (*Pickup_GetModel_t)(void* pickup);
typedef int (*Pickup_GetType_t)(void* pickup);
typedef int (*Pickup_GetVirtualWorld_t)(void* pickup);
typedef bool (*Pickup_SetPos_t)(void* pickup, float x, float y, float z, bool update);
typedef bool (*Pickup_SetModel_t)(void* pickup, int model, bool update);
typedef bool (*Pickup_SetType_t)(void* pickup, int type, bool update);
typedef bool (*Pickup_SetVirtualWorld_t)(void* pickup, int virtualworld);
typedef bool (*Pickup_ShowForPlayer_t)(void* player, void* pickup);
typedef bool (*Pickup_HideForPlayer_t)(void* player, void* pickup);
typedef bool (*Pickup_IsHiddenForPlayer_t)(void* player, void* pickup);


// All function type definitions
typedef bool (*All_SendClientMessage_t)(uint32_t color, const char* text);
typedef bool (*All_CreateExplosion_t)(float x, float y, float z, int type, float radius);
typedef bool (*All_SendDeathMessage_t)(void* killer, void* killee, int weapon);
typedef bool (*All_EnableStuntBonus_t)(bool enable);


// Recording function type definitions
typedef bool (*Recording_Start_t)(void* player, int type, const char* file);
typedef bool (*Recording_Stop_t)(void* player);


// TextDraw function type definitions
typedef void* (*TextDraw_Create_t)(float x, float y, const char* text, int* id);
typedef bool (*TextDraw_Destroy_t)(void* textdraw);
typedef void* (*TextDraw_FromID_t)(int textdrawid);
typedef int (*TextDraw_GetID_t)(void* textdraw);
typedef bool (*TextDraw_IsValid_t)(void* textdraw);
typedef bool (*TextDraw_IsVisibleForPlayer_t)(void* player, void* textdraw);
typedef bool (*TextDraw_SetLetterSize_t)(void* textdraw, float sizeX, float sizeY);
typedef bool (*TextDraw_SetTextSize_t)(void* textdraw, float sizeX, float sizeY);
typedef bool (*TextDraw_SetAlignment_t)(void* textdraw, int alignment);
typedef bool (*TextDraw_SetColor_t)(void* textdraw, uint32_t color);
typedef bool (*TextDraw_SetUseBox_t)(void* textdraw, bool use);
typedef bool (*TextDraw_SetBoxColor_t)(void* textdraw, uint32_t color);
typedef bool (*TextDraw_SetShadow_t)(void* textdraw, int size);
typedef bool (*TextDraw_SetOutline_t)(void* textdraw, int size);
typedef bool (*TextDraw_SetBackgroundColor_t)(void* textdraw, uint32_t color);
typedef bool (*TextDraw_SetFont_t)(void* textdraw, int font);
typedef bool (*TextDraw_SetSetProportional_t)(void* textdraw, bool set);
typedef bool (*TextDraw_SetSelectable_t)(void* textdraw, bool set);
typedef bool (*TextDraw_ShowForPlayer_t)(void* player, void* textdraw);
typedef bool (*TextDraw_HideForPlayer_t)(void* player, void* textdraw);
typedef bool (*TextDraw_ShowForAll_t)(void* textdraw);
typedef bool (*TextDraw_HideForAll_t)(void* textdraw);
typedef bool (*TextDraw_SetString_t)(void* textdraw, const char* text);
typedef bool (*TextDraw_SetPreviewModel_t)(void* textdraw, int model);
typedef bool (*TextDraw_SetPreviewRot_t)(void* textdraw, float rotationX, float rotationY, float rotationZ, float zoom);
typedef bool (*TextDraw_SetPreviewVehCol_t)(void* textdraw, int color1, int color2);
typedef bool (*TextDraw_SetPos_t)(void* textdraw, float x, float y);
typedef bool (*TextDraw_GetString_t)(void* textdraw, struct CAPIStringView* text);
typedef bool (*TextDraw_GetLetterSize_t)(void* textdraw, float* sizeX, float* sizeY);
typedef bool (*TextDraw_GetTextSize_t)(void* textdraw, float* sizeX, float* sizeY);
typedef bool (*TextDraw_GetPos_t)(void* textdraw, float* x, float* y);
typedef int (*TextDraw_GetColor_t)(void* textdraw);
typedef int (*TextDraw_GetBoxColor_t)(void* textdraw);
typedef int (*TextDraw_GetBackgroundColor_t)(void* textdraw);
typedef int (*TextDraw_GetShadow_t)(void* textdraw);
typedef int (*TextDraw_GetOutline_t)(void* textdraw);
typedef int (*TextDraw_GetFont_t)(void* textdraw);
typedef bool (*TextDraw_IsBox_t)(void* textdraw);
typedef bool (*TextDraw_IsProportional_t)(void* textdraw);
typedef bool (*TextDraw_IsSelectable_t)(void* textdraw);
typedef int (*TextDraw_GetAlignment_t)(void* textdraw);
typedef int (*TextDraw_GetPreviewModel_t)(void* textdraw);
typedef bool (*TextDraw_GetPreviewRot_t)(void* textdraw, float* x, float* y, float* z, float* zoom);
typedef bool (*TextDraw_GetPreviewVehColor_t)(void* textdraw, int* color1, int* color2);
typedef bool (*TextDraw_SetStringForPlayer_t)(void* textdraw, void* player, const char* text);


// PlayerTextDraw function type definitions
typedef void* (*PlayerTextDraw_Create_t)(void* player, float x, float y, const char* text, int* id);
typedef bool (*PlayerTextDraw_Destroy_t)(void* player, void* textdraw);
typedef void* (*PlayerTextDraw_FromID_t)(void* player, int textdrawid);
typedef int (*PlayerTextDraw_GetID_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_IsValid_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_IsVisible_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_SetLetterSize_t)(void* player, void* textdraw, float x, float y);
typedef bool (*PlayerTextDraw_SetTextSize_t)(void* player, void* textdraw, float x, float y);
typedef bool (*PlayerTextDraw_SetAlignment_t)(void* player, void* textdraw, int alignment);
typedef bool (*PlayerTextDraw_SetColor_t)(void* player, void* textdraw, uint32_t color);
typedef bool (*PlayerTextDraw_UseBox_t)(void* player, void* textdraw, bool use);
typedef bool (*PlayerTextDraw_SetBoxColor_t)(void* player, void* textdraw, uint32_t color);
typedef bool (*PlayerTextDraw_SetShadow_t)(void* player, void* textdraw, int size);
typedef bool (*PlayerTextDraw_SetOutline_t)(void* player, void* textdraw, int size);
typedef bool (*PlayerTextDraw_SetBackgroundColor_t)(void* player, void* textdraw, uint32_t color);
typedef bool (*PlayerTextDraw_SetFont_t)(void* player, void* textdraw, int font);
typedef bool (*PlayerTextDraw_SetProportional_t)(void* player, void* textdraw, bool set);
typedef bool (*PlayerTextDraw_SetSelectable_t)(void* player, void* textdraw, bool set);
typedef bool (*PlayerTextDraw_Show_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_Hide_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_SetString_t)(void* player, void* textdraw, const char* text);
typedef bool (*PlayerTextDraw_SetPreviewModel_t)(void* player, void* textdraw, int model);
typedef bool (*PlayerTextDraw_SetPreviewRot_t)(void* player, void* textdraw, float rx, float ry, float rz, float zoom);
typedef bool (*PlayerTextDraw_SetPreviewVehCol_t)(void* player, void* textdraw, int color1, int color2);
typedef bool (*PlayerTextDraw_SetPos_t)(void* player, void* textdraw, float x, float y);
typedef bool (*PlayerTextDraw_GetString_t)(void* player, void* textdraw, struct CAPIStringView* text);
typedef bool (*PlayerTextDraw_GetLetterSize_t)(void* player, void* textdraw, float* x, float* y);
typedef bool (*PlayerTextDraw_GetTextSize_t)(void* player, void* textdraw, float* x, float* y);
typedef bool (*PlayerTextDraw_GetPos_t)(void* player, void* textdraw, float* x, float* y);
typedef int (*PlayerTextDraw_GetColor_t)(void* player, void* textdraw);
typedef int (*PlayerTextDraw_GetBoxColor_t)(void* player, void* textdraw);
typedef int (*PlayerTextDraw_GetBackgroundColor_t)(void* player, void* textdraw);
typedef int (*PlayerTextDraw_GetShadow_t)(void* player, void* textdraw);
typedef int (*PlayerTextDraw_GetOutline_t)(void* player, void* textdraw);
typedef int (*PlayerTextDraw_GetFont_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_IsBox_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_IsProportional_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_IsSelectable_t)(void* player, void* textdraw);
typedef int (*PlayerTextDraw_GetAlignment_t)(void* player, void* textdraw);
typedef int (*PlayerTextDraw_GetPreviewModel_t)(void* player, void* textdraw);
typedef bool (*PlayerTextDraw_GetPreviewRot_t)(void* player, void* textdraw, float* rx, float* ry, float* rz, float* zoom);
typedef bool (*PlayerTextDraw_GetPreviewVehColor_t)(void* player, void* textdraw, int* color1, int* color2);


// TextLabel function type definitions
typedef void* (*TextLabel_Create_t)(const char* text, uint32_t color, float x, float y, float z, float drawDistance, int virtualWorld, bool los, int* id);
typedef bool (*TextLabel_Destroy_t)(void* textlabel);
typedef void* (*TextLabel_FromID_t)(int textlabelid);
typedef int (*TextLabel_GetID_t)(void* textlabel);
typedef bool (*TextLabel_AttachToPlayer_t)(void* textlabel, void* player, float offsetX, float offsetY, float offsetZ);
typedef bool (*TextLabel_AttachToVehicle_t)(void* textlabel, void* vehicle, float offsetX, float offsetY, float offsetZ);
typedef bool (*TextLabel_UpdateText_t)(void* textlabel, uint32_t color, const char* text);
typedef bool (*TextLabel_IsValid_t)(void* textlabel);
typedef bool (*TextLabel_IsStreamedIn_t)(void* player, void* textlabel);
typedef bool (*TextLabel_GetText_t)(void* textlabel, struct CAPIStringView* output);
typedef uint32_t (*TextLabel_GetColor_t)(void* textlabel);
typedef bool (*TextLabel_GetPos_t)(void* textlabel, float* x, float* y, float* z);
typedef bool (*TextLabel_SetDrawDistance_t)(void* textlabel, float distance);
typedef float (*TextLabel_GetDrawDistance_t)(void* textlabel);
typedef bool (*TextLabel_GetLOS_t)(void* textlabel);
typedef bool (*TextLabel_SetLOS_t)(void* textlabel, bool status);
typedef int (*TextLabel_GetVirtualWorld_t)(void* textlabel);
typedef bool (*TextLabel_SetVirtualWorld_t)(void* textlabel, int world);
typedef bool (*TextLabel_GetAttachedData_t)(void* textlabel, int* attached_player, int* attached_vehicle);


// PlayerTextLabel function type definitions
typedef void* (*PlayerTextLabel_Create_t)(void* player, const char* text, uint32_t color, float x, float y, float z, float drawDistance, void* attachedPlayer, void* attachedVehicle, bool los, int* id);
typedef bool (*PlayerTextLabel_Destroy_t)(void* player, void* textlabel);
typedef void* (*PlayerTextLabel_FromID_t)(void* player, int textlabelid);
typedef int (*PlayerTextLabel_GetID_t)(void* player, void* textlabel);
typedef bool (*PlayerTextLabel_UpdateText_t)(void* player, void* textlabel, uint32_t color, const char* text);
typedef bool (*PlayerTextLabel_IsValid_t)(void* player, void* textlabel, bool* valid);
typedef bool (*PlayerTextLabel_GetText_t)(void* player, void* textlabel, struct CAPIStringView* output);
typedef bool (*PlayerTextLabel_GetColor_t)(void* player, void* textlabel, uint32_t* color);
typedef bool (*PlayerTextLabel_GetPos_t)(void* player, void* textlabel, float* x, float* y, float* z);
typedef bool (*PlayerTextLabel_SetDrawDistance_t)(void* player, void* textlabel, float distance);
typedef float (*PlayerTextLabel_GetDrawDistance_t)(void* player, void* textlabel);
typedef bool (*PlayerTextLabel_GetLOS_t)(void* player, void* textlabel);
typedef bool (*PlayerTextLabel_SetLOS_t)(void* player, void* textlabel, bool status);
typedef int (*PlayerTextLabel_GetVirtualWorld_t)(void* player);
typedef bool (*PlayerTextLabel_GetAttachedData_t)(void* player, void* textlabel, int* attached_player, int* attached_vehicle);


// Vehicle function type definitions
typedef void* (*Vehicle_Create_t)(int modelid, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, bool addSiren, int* id);
typedef bool (*Vehicle_Destroy_t)(void* vehicle);
typedef void* (*Vehicle_FromID_t)(int vehicleid);
typedef int (*Vehicle_GetID_t)(void* vehicle);
typedef int (*Vehicle_GetMaxPassengerSeats_t)(int modelid);
typedef bool (*Vehicle_IsStreamedIn_t)(void* vehicle, void* player);
typedef bool (*Vehicle_GetPos_t)(void* vehicle, float* x, float* y, float* z);
typedef bool (*Vehicle_SetPos_t)(void* vehicle, float x, float y, float z);
typedef float (*Vehicle_GetZAngle_t)(void* vehicle);
typedef bool (*Vehicle_GetRotationQuat_t)(void* vehicle, float* w, float* x, float* y, float* z);
typedef float (*Vehicle_GetDistanceFromPoint_t)(void* vehicle, float x, float y, float z);
typedef bool (*Vehicle_SetZAngle_t)(void* vehicle, float angle);
typedef bool (*Vehicle_SetParamsForPlayer_t)(void* vehicle, void* player, int objective, int doors);
typedef bool (*Vehicle_UseManualEngineAndLights_t)();
typedef bool (*Vehicle_SetParamsEx_t)(void* vehicle, int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective);
typedef bool (*Vehicle_GetParamsEx_t)(void* vehicle, int* engine, int* lights, int* alarm, int* doors, int* bonnet, int* boot, int* objective);
typedef int (*Vehicle_GetParamsSirenState_t)(void* vehicle);
typedef bool (*Vehicle_SetParamsCarDoors_t)(void* vehicle, int frontLeft, int frontRight, int rearLeft, int rearRight);
typedef bool (*Vehicle_GetParamsCarDoors_t)(void* vehicle, int* frontLeft, int* frontRight, int* rearLeft, int* rearRight);
typedef bool (*Vehicle_SetParamsCarWindows_t)(void* vehicle, int frontLeft, int frontRight, int rearLeft, int rearRight);
typedef bool (*Vehicle_GetParamsCarWindows_t)(void* vehicle, int* frontLeft, int* frontRight, int* rearLeft, int* rearRight);
typedef bool (*Vehicle_SetToRespawn_t)(void* vehicle);
typedef bool (*Vehicle_LinkToInterior_t)(void* vehicle, int interiorid);
typedef bool (*Vehicle_AddComponent_t)(void* vehicle, int componentid);
typedef bool (*Vehicle_RemoveComponent_t)(void* vehicle, int componentid);
typedef bool (*Vehicle_ChangeColor_t)(void* vehicle, int color1, int color2);
typedef bool (*Vehicle_ChangePaintjob_t)(void* vehicle, int paintjobid);
typedef bool (*Vehicle_SetHealth_t)(void* vehicle, float health);
typedef float (*Vehicle_GetHealth_t)(void* vehicle);
typedef bool (*Vehicle_AttachTrailer_t)(void* trailer, void* vehicle);
typedef bool (*Vehicle_DetachTrailer_t)(void* vehicle);
typedef bool (*Vehicle_IsTrailerAttached_t)(void* vehicle);
typedef void* (*Vehicle_GetTrailer_t)(void* vehicle);
typedef bool (*Vehicle_SetNumberPlate_t)(void* vehicle, const char* numberPlate);
typedef int (*Vehicle_GetModel_t)(void* vehicle);
typedef int (*Vehicle_GetComponentInSlot_t)(void* vehicle, int slot);
typedef int (*Vehicle_GetComponentType_t)(int componentid);
typedef bool (*Vehicle_CanHaveComponent_t)(int modelid, int componentid);
typedef bool (*Vehicle_GetRandomColorPair_t)(int modelid, int* color1, int* color2, int* color3, int* color4);
typedef int (*Vehicle_ColorIndexToColor_t)(int colorIndex, int alpha);
typedef bool (*Vehicle_Repair_t)(void* vehicle);
typedef bool (*Vehicle_GetVelocity_t)(void* vehicle, float* x, float* y, float* z);
typedef bool (*Vehicle_SetVelocity_t)(void* vehicle, float x, float y, float z);
typedef bool (*Vehicle_SetAngularVelocity_t)(void* vehicle, float x, float y, float z);
typedef bool (*Vehicle_GetDamageStatus_t)(void* vehicle, int* panels, int* doors, int* lights, int* tires);
typedef bool (*Vehicle_UpdateDamageStatus_t)(void* vehicle, int panels, int doors, int lights, int tires);
typedef bool (*Vehicle_GetModelInfo_t)(int vehiclemodel, int infotype, float* x, float* y, float* z);
typedef bool (*Vehicle_SetVirtualWorld_t)(void* vehicle, int virtualWorld);
typedef int (*Vehicle_GetVirtualWorld_t)(void* vehicle);
typedef int (*Vehicle_GetLandingGearState_t)(void* vehicle);
typedef bool (*Vehicle_IsValid_t)(void* vehicle);
typedef void* (*Vehicle_AddStatic_t)(int modelid, float x, float y, float z, float angle, int color1, int color2, int* id);
typedef void* (*Vehicle_AddStaticEx_t)(int modelid, float x, float y, float z, float angle, int color1, int color2, int respawnDelay, bool addSiren, int* id);
typedef bool (*Vehicle_EnableFriendlyFire_t)();
typedef bool (*Vehicle_GetSpawnInfo_t)(void* vehicle, float* x, float* y, float* z, float* rotation, int* color1, int* color2);
typedef bool (*Vehicle_SetSpawnInfo_t)(void* vehicle, int modelid, float x, float y, float z, float rotation, int color1, int color2, int respawn_time, int interior);
typedef int (*Vehicle_GetModelCount_t)(int modelid);
typedef int (*Vehicle_GetModelsUsed_t)();
typedef int (*Vehicle_GetPaintjob_t)(void* vehicle);
typedef bool (*Vehicle_GetColor_t)(void* vehicle, int* color1, int* color2);
typedef int (*Vehicle_GetInterior_t)(void* vehicle);
typedef bool (*Vehicle_GetNumberPlate_t)(void* vehicle, struct CAPIStringView* numberPlate);
typedef bool (*Vehicle_SetRespawnDelay_t)(void* vehicle, int respawn_delay);
typedef int (*Vehicle_GetRespawnDelay_t)(void* vehicle);
typedef void* (*Vehicle_GetCab_t)(void* vehicle);
typedef void* (*Vehicle_GetTower_t)(void* vehicle);
typedef int (*Vehicle_GetOccupiedTick_t)(void* vehicle);
typedef int (*Vehicle_GetRespawnTick_t)(void* vehicle);
typedef bool (*Vehicle_HasBeenOccupied_t)(void* vehicle);
typedef bool (*Vehicle_IsOccupied_t)(void* vehicle);
typedef bool (*Vehicle_IsDead_t)(void* vehicle);
typedef bool (*Vehicle_SetParamsSirenState_t)(void* vehicle, bool siren_state);
typedef bool (*Vehicle_ToggleSirenEnabled_t)(void* vehicle, bool status);
typedef bool (*Vehicle_IsSirenEnabled_t)(void* vehicle);
typedef void* (*Vehicle_GetLastDriver_t)(void* vehicle);
typedef void* (*Vehicle_GetDriver_t)(void* vehicle);
typedef int (*Vehicle_GetSirenState_t)(void* vehicle);
typedef uint32_t (*Vehicle_GetHydraReactorAngle_t)(void* vehicle);
typedef float (*Vehicle_GetTrainSpeed_t)(void* vehicle);
typedef bool (*Vehicle_GetMatrix_t)(void* vehicle, float* rightX, float* rightY, float* rightZ, float* upX, float* upY, float* upZ, float* atX, float* atY, float* atZ);
typedef void* (*Vehicle_GetOccupant_t)(void* vehicle, int seat);
typedef int (*Vehicle_CountOccupants_t)(void* vehicle);


// Actor event type and arguments definitions
struct EventArgs_onPlayerGiveDamageActor {
    int size;
    struct {
        void** player;
        void** actor;
        float* amount;
        int* weapon;
        int* part;
    } *list;
};
typedef bool (*EventCallback_onPlayerGiveDamageActor)(struct EventArgs_onPlayerGiveDamageActor args);

struct EventArgs_onActorStreamIn {
    int size;
    struct {
        void** actor;
        void** forPlayer;
    } *list;
};
typedef bool (*EventCallback_onActorStreamIn)(struct EventArgs_onActorStreamIn args);

struct EventArgs_onActorStreamOut {
    int size;
    struct {
        void** actor;
        void** forPlayer;
    } *list;
};
typedef bool (*EventCallback_onActorStreamOut)(struct EventArgs_onActorStreamOut args);


// Checkpoint event type and arguments definitions
struct EventArgs_onPlayerEnterCheckpoint {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerEnterCheckpoint)(struct EventArgs_onPlayerEnterCheckpoint args);

struct EventArgs_onPlayerLeaveCheckpoint {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerLeaveCheckpoint)(struct EventArgs_onPlayerLeaveCheckpoint args);

struct EventArgs_onPlayerEnterRaceCheckpoint {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerEnterRaceCheckpoint)(struct EventArgs_onPlayerEnterRaceCheckpoint args);

struct EventArgs_onPlayerLeaveRaceCheckpoint {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerLeaveRaceCheckpoint)(struct EventArgs_onPlayerLeaveRaceCheckpoint args);


// Class event type and arguments definitions
struct EventArgs_onPlayerRequestClass {
    int size;
    struct {
        void** player;
        int* classId;
    } *list;
};
typedef bool (*EventCallback_onPlayerRequestClass)(struct EventArgs_onPlayerRequestClass args);


// Console event type and arguments definitions
struct EventArgs_onConsoleText {
    int size;
    struct {
        struct CAPIStringView* command;
        struct CAPIStringView* parameters;
    } *list;
};
typedef bool (*EventCallback_onConsoleText)(struct EventArgs_onConsoleText args);

struct EventArgs_onRconLoginAttempt {
    int size;
    struct {
        struct CAPIStringView* address;
        struct CAPIStringView* password;
        bool* success;
    } *list;
};
typedef bool (*EventCallback_onRconLoginAttempt)(struct EventArgs_onRconLoginAttempt args);


// Core event type and arguments definitions
struct EventArgs_onTick {
    int size;
    struct {
        int* elapsed;
    } *list;
};
typedef bool (*EventCallback_onTick)(struct EventArgs_onTick args);


// CustomModel event type and arguments definitions
struct EventArgs_onPlayerFinishedDownloading {
    int size;
    struct {
        void** player;
        int* vw;
    } *list;
};
typedef bool (*EventCallback_onPlayerFinishedDownloading)(struct EventArgs_onPlayerFinishedDownloading args);

struct EventArgs_onPlayerRequestDownload {
    int size;
    struct {
        void** player;
        int* type;
        int* checksum;
    } *list;
};
typedef bool (*EventCallback_onPlayerRequestDownload)(struct EventArgs_onPlayerRequestDownload args);


// Dialog event type and arguments definitions
struct EventArgs_onDialogResponse {
    int size;
    struct {
        void** player;
        int* dialogId;
        int* response;
        int* listItem;
        struct CAPIStringView* inputText;
    } *list;
};
typedef bool (*EventCallback_onDialogResponse)(struct EventArgs_onDialogResponse args);


// GangZone event type and arguments definitions
struct EventArgs_onPlayerEnterGangZone {
    int size;
    struct {
        void** player;
        void** zone;
    } *list;
};
typedef bool (*EventCallback_onPlayerEnterGangZone)(struct EventArgs_onPlayerEnterGangZone args);

struct EventArgs_onPlayerLeaveGangZone {
    int size;
    struct {
        void** player;
        void** zone;
    } *list;
};
typedef bool (*EventCallback_onPlayerLeaveGangZone)(struct EventArgs_onPlayerLeaveGangZone args);

struct EventArgs_onPlayerClickGangZone {
    int size;
    struct {
        void** player;
        void** zone;
    } *list;
};
typedef bool (*EventCallback_onPlayerClickGangZone)(struct EventArgs_onPlayerClickGangZone args);


// Menu event type and arguments definitions
struct EventArgs_onPlayerSelectedMenuRow {
    int size;
    struct {
        void** player;
        int* row;
    } *list;
};
typedef bool (*EventCallback_onPlayerSelectedMenuRow)(struct EventArgs_onPlayerSelectedMenuRow args);

struct EventArgs_onPlayerExitedMenu {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerExitedMenu)(struct EventArgs_onPlayerExitedMenu args);


// Object event type and arguments definitions
struct EventArgs_onObjectMove {
    int size;
    struct {
        void** object;
    } *list;
};
typedef bool (*EventCallback_onObjectMove)(struct EventArgs_onObjectMove args);

struct EventArgs_onPlayerObjectMove {
    int size;
    struct {
        void** player;
        void** object;
    } *list;
};
typedef bool (*EventCallback_onPlayerObjectMove)(struct EventArgs_onPlayerObjectMove args);

struct EventArgs_onPlayerEditObject {
    int size;
    struct {
        void** player;
        void** object;
        int* response;
        float* offsetX;
        float* offsetY;
        float* offsetZ;
        float* rotationX;
        float* rotationY;
        float* rotationZ;
    } *list;
};
typedef bool (*EventCallback_onPlayerEditObject)(struct EventArgs_onPlayerEditObject args);

struct EventArgs_onPlayerEditPlayerObject {
    int size;
    struct {
        void** player;
        void** object;
        int* response;
        float* offsetX;
        float* offsetY;
        float* offsetZ;
        float* rotationX;
        float* rotationY;
        float* rotationZ;
    } *list;
};
typedef bool (*EventCallback_onPlayerEditPlayerObject)(struct EventArgs_onPlayerEditPlayerObject args);

struct EventArgs_onPlayerEditAttachedObject {
    int size;
    struct {
        void** player;
        bool* saved;
        int* index;
        int* model;
        int* bone;
        float* offsetX;
        float* offsetY;
        float* offsetZ;
        float* rotationX;
        float* rotationY;
        float* rotationZ;
        float* scaleX;
        float* scaleY;
        float* scaleZ;
    } *list;
};
typedef bool (*EventCallback_onPlayerEditAttachedObject)(struct EventArgs_onPlayerEditAttachedObject args);

struct EventArgs_onPlayerSelectObject {
    int size;
    struct {
        void** player;
        void** object;
        int* model;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerSelectObject)(struct EventArgs_onPlayerSelectObject args);

struct EventArgs_onPlayerSelectPlayerObject {
    int size;
    struct {
        void** player;
        void** object;
        int* model;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerSelectPlayerObject)(struct EventArgs_onPlayerSelectPlayerObject args);


// Pickup event type and arguments definitions
struct EventArgs_onPlayerPickUpPickup {
    int size;
    struct {
        void** player;
        void** pickup;
    } *list;
};
typedef bool (*EventCallback_onPlayerPickUpPickup)(struct EventArgs_onPlayerPickUpPickup args);


// TextDraw event type and arguments definitions
struct EventArgs_onPlayerCancelTextDrawSelection {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerCancelTextDrawSelection)(struct EventArgs_onPlayerCancelTextDrawSelection args);

struct EventArgs_onPlayerCancelPlayerTextDrawSelection {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerCancelPlayerTextDrawSelection)(struct EventArgs_onPlayerCancelPlayerTextDrawSelection args);

struct EventArgs_onPlayerClickTextDraw {
    int size;
    struct {
        void** player;
        void** textdraw;
    } *list;
};
typedef bool (*EventCallback_onPlayerClickTextDraw)(struct EventArgs_onPlayerClickTextDraw args);

struct EventArgs_onPlayerClickPlayerTextDraw {
    int size;
    struct {
        void** player;
        void** textdraw;
    } *list;
};
typedef bool (*EventCallback_onPlayerClickPlayerTextDraw)(struct EventArgs_onPlayerClickPlayerTextDraw args);


// Player event type and arguments definitions
struct EventArgs_onPlayerConnect {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerConnect)(struct EventArgs_onPlayerConnect args);

struct EventArgs_onPlayerSpawn {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerSpawn)(struct EventArgs_onPlayerSpawn args);

struct EventArgs_onPlayerCommandText {
    int size;
    struct {
        void** player;
        struct CAPIStringView* command;
    } *list;
};
typedef bool (*EventCallback_onPlayerCommandText)(struct EventArgs_onPlayerCommandText args);

struct EventArgs_onPlayerKeyStateChange {
    int size;
    struct {
        void** player;
        int* newKeys;
        int* oldKeys;
    } *list;
};
typedef bool (*EventCallback_onPlayerKeyStateChange)(struct EventArgs_onPlayerKeyStateChange args);

struct EventArgs_onIncomingConnection {
    int size;
    struct {
        void** player;
        struct CAPIStringView* ipAddress;
        int* port;
    } *list;
};
typedef bool (*EventCallback_onIncomingConnection)(struct EventArgs_onIncomingConnection args);

struct EventArgs_onPlayerDisconnect {
    int size;
    struct {
        void** player;
        int* reason;
    } *list;
};
typedef bool (*EventCallback_onPlayerDisconnect)(struct EventArgs_onPlayerDisconnect args);

struct EventArgs_onPlayerRequestSpawn {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerRequestSpawn)(struct EventArgs_onPlayerRequestSpawn args);

struct EventArgs_onPlayerStreamIn {
    int size;
    struct {
        void** player;
        void** forPlayer;
    } *list;
};
typedef bool (*EventCallback_onPlayerStreamIn)(struct EventArgs_onPlayerStreamIn args);

struct EventArgs_onPlayerStreamOut {
    int size;
    struct {
        void** player;
        void** forPlayer;
    } *list;
};
typedef bool (*EventCallback_onPlayerStreamOut)(struct EventArgs_onPlayerStreamOut args);

struct EventArgs_onPlayerText {
    int size;
    struct {
        void** player;
        struct CAPIStringView* text;
    } *list;
};
typedef bool (*EventCallback_onPlayerText)(struct EventArgs_onPlayerText args);

struct EventArgs_onPlayerShotMissed {
    int size;
    struct {
        void** player;
        int* weapon;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerShotMissed)(struct EventArgs_onPlayerShotMissed args);

struct EventArgs_onPlayerShotPlayer {
    int size;
    struct {
        void** player;
        void** target;
        int* weapon;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerShotPlayer)(struct EventArgs_onPlayerShotPlayer args);

struct EventArgs_onPlayerShotVehicle {
    int size;
    struct {
        void** player;
        void** target;
        int* weapon;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerShotVehicle)(struct EventArgs_onPlayerShotVehicle args);

struct EventArgs_onPlayerShotObject {
    int size;
    struct {
        void** player;
        void** target;
        int* weapon;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerShotObject)(struct EventArgs_onPlayerShotObject args);

struct EventArgs_onPlayerShotPlayerObject {
    int size;
    struct {
        void** player;
        void** target;
        int* weapon;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerShotPlayerObject)(struct EventArgs_onPlayerShotPlayerObject args);

struct EventArgs_onPlayerDeath {
    int size;
    struct {
        void** player;
        void** killer;
        int* reason;
    } *list;
};
typedef bool (*EventCallback_onPlayerDeath)(struct EventArgs_onPlayerDeath args);

struct EventArgs_onPlayerTakeDamage {
    int size;
    struct {
        void** player;
        void** from;
        float* amount;
        int* weapon;
        int* bodypart;
    } *list;
};
typedef bool (*EventCallback_onPlayerTakeDamage)(struct EventArgs_onPlayerTakeDamage args);

struct EventArgs_onPlayerGiveDamage {
    int size;
    struct {
        void** player;
        void** to;
        float* amount;
        int* weapon;
        int* bodypart;
    } *list;
};
typedef bool (*EventCallback_onPlayerGiveDamage)(struct EventArgs_onPlayerGiveDamage args);

struct EventArgs_onPlayerInteriorChange {
    int size;
    struct {
        void** player;
        int* newInterior;
        int* oldInterior;
    } *list;
};
typedef bool (*EventCallback_onPlayerInteriorChange)(struct EventArgs_onPlayerInteriorChange args);

struct EventArgs_onPlayerStateChange {
    int size;
    struct {
        void** player;
        int* newState;
        int* oldState;
    } *list;
};
typedef bool (*EventCallback_onPlayerStateChange)(struct EventArgs_onPlayerStateChange args);

struct EventArgs_onPlayerClickMap {
    int size;
    struct {
        void** player;
        float* x;
        float* y;
        float* z;
    } *list;
};
typedef bool (*EventCallback_onPlayerClickMap)(struct EventArgs_onPlayerClickMap args);

struct EventArgs_onPlayerClickPlayer {
    int size;
    struct {
        void** player;
        void** clicked;
        int* source;
    } *list;
};
typedef bool (*EventCallback_onPlayerClickPlayer)(struct EventArgs_onPlayerClickPlayer args);

struct EventArgs_onClientCheckResponse {
    int size;
    struct {
        void** player;
        int* actionType;
        int* address;
        int* result;
    } *list;
};
typedef bool (*EventCallback_onClientCheckResponse)(struct EventArgs_onClientCheckResponse args);

struct EventArgs_onPlayerUpdate {
    int size;
    struct {
        void** player;
    } *list;
};
typedef bool (*EventCallback_onPlayerUpdate)(struct EventArgs_onPlayerUpdate args);


// Vehicle event type and arguments definitions
struct EventArgs_onVehicleStreamIn {
    int size;
    struct {
        void** vehicle;
        void** player;
    } *list;
};
typedef bool (*EventCallback_onVehicleStreamIn)(struct EventArgs_onVehicleStreamIn args);

struct EventArgs_onVehicleStreamOut {
    int size;
    struct {
        void** vehicle;
        void** player;
    } *list;
};
typedef bool (*EventCallback_onVehicleStreamOut)(struct EventArgs_onVehicleStreamOut args);

struct EventArgs_onVehicleDeath {
    int size;
    struct {
        void** vehicle;
        void** player;
    } *list;
};
typedef bool (*EventCallback_onVehicleDeath)(struct EventArgs_onVehicleDeath args);

struct EventArgs_onPlayerEnterVehicle {
    int size;
    struct {
        void** player;
        void** vehicle;
        bool* passenger;
    } *list;
};
typedef bool (*EventCallback_onPlayerEnterVehicle)(struct EventArgs_onPlayerEnterVehicle args);

struct EventArgs_onPlayerExitVehicle {
    int size;
    struct {
        void** player;
        void** vehicle;
    } *list;
};
typedef bool (*EventCallback_onPlayerExitVehicle)(struct EventArgs_onPlayerExitVehicle args);

struct EventArgs_onVehicleDamageStatusUpdate {
    int size;
    struct {
        void** vehicle;
        void** player;
    } *list;
};
typedef bool (*EventCallback_onVehicleDamageStatusUpdate)(struct EventArgs_onVehicleDamageStatusUpdate args);

struct EventArgs_onVehiclePaintJob {
    int size;
    struct {
        void** player;
        void** vehicle;
        int* paintJob;
    } *list;
};
typedef bool (*EventCallback_onVehiclePaintJob)(struct EventArgs_onVehiclePaintJob args);

struct EventArgs_onVehicleMod {
    int size;
    struct {
        void** player;
        void** vehicle;
        int* component;
    } *list;
};
typedef bool (*EventCallback_onVehicleMod)(struct EventArgs_onVehicleMod args);

struct EventArgs_onVehicleRespray {
    int size;
    struct {
        void** player;
        void** vehicle;
        int* color1;
        int* color2;
    } *list;
};
typedef bool (*EventCallback_onVehicleRespray)(struct EventArgs_onVehicleRespray args);

struct EventArgs_onEnterExitModShop {
    int size;
    struct {
        void** player;
        int* enterexit;
        int* interiorId;
    } *list;
};
typedef bool (*EventCallback_onEnterExitModShop)(struct EventArgs_onEnterExitModShop args);

struct EventArgs_onVehicleSpawn {
    int size;
    struct {
        void** vehicle;
    } *list;
};
typedef bool (*EventCallback_onVehicleSpawn)(struct EventArgs_onVehicleSpawn args);

struct EventArgs_onUnoccupiedVehicleUpdate {
    int size;
    struct {
        void** vehicle;
        void** player;
        int* seat;
        float* posX;
        float* posY;
        float* posZ;
        float* velocityX;
        float* velocityY;
        float* velocityZ;
    } *list;
};
typedef bool (*EventCallback_onUnoccupiedVehicleUpdate)(struct EventArgs_onUnoccupiedVehicleUpdate args);

struct EventArgs_onTrailerUpdate {
    int size;
    struct {
        void** player;
        void** trailer;
    } *list;
};
typedef bool (*EventCallback_onTrailerUpdate)(struct EventArgs_onTrailerUpdate args);

struct EventArgs_onVehicleSirenStateChange {
    int size;
    struct {
        void** player;
        void** vehicle;
        int* sirenState;
    } *list;
};
typedef bool (*EventCallback_onVehicleSirenStateChange)(struct EventArgs_onVehicleSirenStateChange args);


// Actor functions
struct Actor_t {
    Actor_Create_t Create;
    Actor_Destroy_t Destroy;
    Actor_FromID_t FromID;
    Actor_GetID_t GetID;
    Actor_IsStreamedInFor_t IsStreamedInFor;
    Actor_SetVirtualWorld_t SetVirtualWorld;
    Actor_GetVirtualWorld_t GetVirtualWorld;
    Actor_ApplyAnimation_t ApplyAnimation;
    Actor_ClearAnimations_t ClearAnimations;
    Actor_SetPos_t SetPos;
    Actor_GetPos_t GetPos;
    Actor_SetFacingAngle_t SetFacingAngle;
    Actor_GetFacingAngle_t GetFacingAngle;
    Actor_SetHealth_t SetHealth;
    Actor_GetHealth_t GetHealth;
    Actor_SetInvulnerable_t SetInvulnerable;
    Actor_IsInvulnerable_t IsInvulnerable;
    Actor_IsValid_t IsValid;
    Actor_SetSkin_t SetSkin;
    Actor_GetSkin_t GetSkin;
    Actor_GetAnimation_t GetAnimation;
    Actor_GetSpawnInfo_t GetSpawnInfo;
};

// Checkpoint functions
struct Checkpoint_t {
    Checkpoint_Set_t Set;
    Checkpoint_Disable_t Disable;
    Checkpoint_IsPlayerIn_t IsPlayerIn;
    Checkpoint_IsActive_t IsActive;
    Checkpoint_Get_t Get;
};

// RaceCheckpoint functions
struct RaceCheckpoint_t {
    RaceCheckpoint_Set_t Set;
    RaceCheckpoint_Disable_t Disable;
    RaceCheckpoint_IsPlayerIn_t IsPlayerIn;
    RaceCheckpoint_IsActive_t IsActive;
    RaceCheckpoint_Get_t Get;
};

// Class functions
struct Class_t {
    Class_Add_t Add;
    Class_FromID_t FromID;
    Class_GetID_t GetID;
    Class_Count_t Count;
    Class_GetData_t GetData;
    Class_Edit_t Edit;
};

// Player functions
struct Player_t {
    Player_SetSpawnInfo_t SetSpawnInfo;
    Player_GetSpawnInfo_t GetSpawnInfo;
    Player_GetNetworkStats_t GetNetworkStats;
    Player_NetStatsBytesReceived_t NetStatsBytesReceived;
    Player_NetStatsBytesSent_t NetStatsBytesSent;
    Player_NetStatsConnectionStatus_t NetStatsConnectionStatus;
    Player_NetStatsGetConnectedTime_t NetStatsGetConnectedTime;
    Player_NetStatsGetIpPort_t NetStatsGetIpPort;
    Player_NetStatsMessagesReceived_t NetStatsMessagesReceived;
    Player_NetStatsMessagesRecvPerSecond_t NetStatsMessagesRecvPerSecond;
    Player_NetStatsMessagesSent_t NetStatsMessagesSent;
    Player_NetStatsPacketLossPercent_t NetStatsPacketLossPercent;
    Player_GetCustomSkin_t GetCustomSkin;
    Player_GetDialog_t GetDialog;
    Player_GetDialogData_t GetDialogData;
    Player_GetMenu_t GetMenu;
    Player_GetSurfingPlayerObject_t GetSurfingPlayerObject;
    Player_GetCameraTargetPlayerObject_t GetCameraTargetPlayerObject;
    Player_FromID_t FromID;
    Player_GetID_t GetID;
    Player_SendClientMessage_t SendClientMessage;
    Player_SetCameraPos_t SetCameraPos;
    Player_SetDrunkLevel_t SetDrunkLevel;
    Player_SetInterior_t SetInterior;
    Player_SetWantedLevel_t SetWantedLevel;
    Player_SetWeather_t SetWeather;
    Player_GetWeather_t GetWeather;
    Player_SetSkin_t SetSkin;
    Player_SetShopName_t SetShopName;
    Player_GiveMoney_t GiveMoney;
    Player_SetCameraLookAt_t SetCameraLookAt;
    Player_SetCameraBehind_t SetCameraBehind;
    Player_CreateExplosion_t CreateExplosion;
    Player_PlayAudioStream_t PlayAudioStream;
    Player_StopAudioStream_t StopAudioStream;
    Player_ToggleWidescreen_t ToggleWidescreen;
    Player_IsWidescreenToggled_t IsWidescreenToggled;
    Player_SetHealth_t SetHealth;
    Player_GetHealth_t GetHealth;
    Player_SetArmor_t SetArmor;
    Player_GetArmor_t GetArmor;
    Player_SetTeam_t SetTeam;
    Player_GetTeam_t GetTeam;
    Player_SetScore_t SetScore;
    Player_GetScore_t GetScore;
    Player_GetSkin_t GetSkin;
    Player_SetColor_t SetColor;
    Player_GetColor_t GetColor;
    Player_GetDefaultColor_t GetDefaultColor;
    Player_GetDrunkLevel_t GetDrunkLevel;
    Player_GiveWeapon_t GiveWeapon;
    Player_RemoveWeapon_t RemoveWeapon;
    Player_GetMoney_t GetMoney;
    Player_ResetMoney_t ResetMoney;
    Player_SetName_t SetName;
    Player_GetName_t GetName;
    Player_GetState_t GetState;
    Player_GetPing_t GetPing;
    Player_GetWeapon_t GetWeapon;
    Player_SetTime_t SetTime;
    Player_GetTime_t GetTime;
    Player_ToggleClock_t ToggleClock;
    Player_HasClock_t HasClock;
    Player_ForceClassSelection_t ForceClassSelection;
    Player_GetWantedLevel_t GetWantedLevel;
    Player_SetFightingStyle_t SetFightingStyle;
    Player_GetFightingStyle_t GetFightingStyle;
    Player_SetVelocity_t SetVelocity;
    Player_GetVelocity_t GetVelocity;
    Player_GetCameraPos_t GetCameraPos;
    Player_GetDistanceFromPoint_t GetDistanceFromPoint;
    Player_GetInterior_t GetInterior;
    Player_SetPos_t SetPos;
    Player_GetPos_t GetPos;
    Player_GetVirtualWorld_t GetVirtualWorld;
    Player_IsNPC_t IsNPC;
    Player_IsStreamedIn_t IsStreamedIn;
    Player_PlayGameSound_t PlayGameSound;
    Player_SpectatePlayer_t SpectatePlayer;
    Player_SpectateVehicle_t SpectateVehicle;
    Player_SetVirtualWorld_t SetVirtualWorld;
    Player_SetWorldBounds_t SetWorldBounds;
    Player_ClearWorldBounds_t ClearWorldBounds;
    Player_GetWorldBounds_t GetWorldBounds;
    Player_ClearAnimations_t ClearAnimations;
    Player_GetLastShotVectors_t GetLastShotVectors;
    Player_GetCameraTargetPlayer_t GetCameraTargetPlayer;
    Player_GetCameraTargetActor_t GetCameraTargetActor;
    Player_GetCameraTargetObject_t GetCameraTargetObject;
    Player_GetCameraTargetVehicle_t GetCameraTargetVehicle;
    Player_PutInVehicle_t PutInVehicle;
    Player_RemoveBuilding_t RemoveBuilding;
    Player_GetBuildingsRemoved_t GetBuildingsRemoved;
    Player_RemoveFromVehicle_t RemoveFromVehicle;
    Player_RemoveMapIcon_t RemoveMapIcon;
    Player_SetMapIcon_t SetMapIcon;
    Player_ResetWeapons_t ResetWeapons;
    Player_SetAmmo_t SetAmmo;
    Player_SetArmedWeapon_t SetArmedWeapon;
    Player_SetChatBubble_t SetChatBubble;
    Player_SetPosFindZ_t SetPosFindZ;
    Player_SetSkillLevel_t SetSkillLevel;
    Player_SetSpecialAction_t SetSpecialAction;
    Player_ShowNameTagForPlayer_t ShowNameTagForPlayer;
    Player_ToggleControllable_t ToggleControllable;
    Player_ToggleSpectating_t ToggleSpectating;
    Player_ApplyAnimation_t ApplyAnimation;
    Player_GetAnimationName_t GetAnimationName;
    Player_EditAttachedObject_t EditAttachedObject;
    Player_EnableCameraTarget_t EnableCameraTarget;
    Player_EnableStuntBonus_t EnableStuntBonus;
    Player_GetPlayerAmmo_t GetPlayerAmmo;
    Player_GetAnimationIndex_t GetAnimationIndex;
    Player_GetFacingAngle_t GetFacingAngle;
    Player_GetIp_t GetIp;
    Player_GetSpecialAction_t GetSpecialAction;
    Player_GetVehicleID_t GetVehicleID;
    Player_GetVehicleSeat_t GetVehicleSeat;
    Player_GetWeaponData_t GetWeaponData;
    Player_GetWeaponState_t GetWeaponState;
    Player_InterpolateCameraPos_t InterpolateCameraPos;
    Player_InterpolateCameraLookAt_t InterpolateCameraLookAt;
    Player_IsPlayerAttachedObjectSlotUsed_t IsPlayerAttachedObjectSlotUsed;
    Player_AttachCameraToObject_t AttachCameraToObject;
    Player_AttachCameraToPlayerObject_t AttachCameraToPlayerObject;
    Player_GetCameraAspectRatio_t GetCameraAspectRatio;
    Player_GetCameraFrontVector_t GetCameraFrontVector;
    Player_GetCameraMode_t GetCameraMode;
    Player_GetKeys_t GetKeys;
    Player_GetSurfingVehicle_t GetSurfingVehicle;
    Player_GetSurfingObject_t GetSurfingObject;
    Player_GetTargetPlayer_t GetTargetPlayer;
    Player_GetTargetActor_t GetTargetActor;
    Player_IsInVehicle_t IsInVehicle;
    Player_IsInAnyVehicle_t IsInAnyVehicle;
    Player_IsInRangeOfPoint_t IsInRangeOfPoint;
    Player_PlayCrimeReport_t PlayCrimeReport;
    Player_RemoveAttachedObject_t RemoveAttachedObject;
    Player_SetAttachedObject_t SetAttachedObject;
    Player_GetAttachedObject_t GetAttachedObject;
    Player_SetFacingAngle_t SetFacingAngle;
    Player_SetMarkerForPlayer_t SetMarkerForPlayer;
    Player_GetMarkerForPlayer_t GetMarkerForPlayer;
    Player_AllowTeleport_t AllowTeleport;
    Player_IsTeleportAllowed_t IsTeleportAllowed;
    Player_DisableRemoteVehicleCollisions_t DisableRemoteVehicleCollisions;
    Player_GetCameraZoom_t GetCameraZoom;
    Player_SelectTextDraw_t SelectTextDraw;
    Player_CancelSelectTextDraw_t CancelSelectTextDraw;
    Player_SendClientCheck_t SendClientCheck;
    Player_Spawn_t Spawn;
    Player_GPCI_t GPCI;
    Player_IsAdmin_t IsAdmin;
    Player_Kick_t Kick;
    Player_ShowGameText_t ShowGameText;
    Player_HideGameText_t HideGameText;
    Player_HasGameText_t HasGameText;
    Player_GetGameText_t GetGameText;
    Player_Ban_t Ban;
    Player_BanEx_t BanEx;
    Player_SendDeathMessage_t SendDeathMessage;
    Player_SendMessageToPlayer_t SendMessageToPlayer;
    Player_GetVersion_t GetVersion;
    Player_GetSkillLevel_t GetSkillLevel;
    Player_GetZAim_t GetZAim;
    Player_GetSurfingOffsets_t GetSurfingOffsets;
    Player_GetRotationQuat_t GetRotationQuat;
    Player_GetPlayerSpectateID_t GetPlayerSpectateID;
    Player_GetSpectateType_t GetSpectateType;
    Player_GetRawIp_t GetRawIp;
    Player_SetGravity_t SetGravity;
    Player_GetGravity_t GetGravity;
    Player_SetAdmin_t SetAdmin;
    Player_IsSpawned_t IsSpawned;
    Player_IsControllable_t IsControllable;
    Player_IsCameraTargetEnabled_t IsCameraTargetEnabled;
    Player_ToggleGhostMode_t ToggleGhostMode;
    Player_GetGhostMode_t GetGhostMode;
    Player_AllowWeapons_t AllowWeapons;
    Player_AreWeaponsAllowed_t AreWeaponsAllowed;
    Player_IsPlayerUsingOfficialClient_t IsPlayerUsingOfficialClient;
    Player_GetAnimationFlags_t GetAnimationFlags;
    Player_IsInDriveByMode_t IsInDriveByMode;
    Player_IsCuffed_t IsCuffed;
    Player_IsInModShop_t IsInModShop;
    Player_GetSirenState_t GetSirenState;
    Player_GetLandingGearState_t GetLandingGearState;
    Player_GetHydraReactorAngle_t GetHydraReactorAngle;
    Player_GetTrainSpeed_t GetTrainSpeed;
    Player_IsPlayerUsingOmp_t IsPlayerUsingOmp;
};

// Component functions
struct Component_t {
    Component_Create_t Create;
};

// Config functions
struct Config_t {
    Config_GetAsBool_t GetAsBool;
    Config_GetAsInt_t GetAsInt;
    Config_GetAsFloat_t GetAsFloat;
    Config_GetAsString_t GetAsString;
};

// Core functions
struct Core_t {
    Core_TickCount_t TickCount;
    Core_MaxPlayers_t MaxPlayers;
    Core_Log_t Log;
    Core_IsAdminTeleportAllowed_t IsAdminTeleportAllowed;
    Core_AllowAdminTeleport_t AllowAdminTeleport;
    Core_AreAllAnimationsEnabled_t AreAllAnimationsEnabled;
    Core_EnableAllAnimations_t EnableAllAnimations;
    Core_IsAnimationLibraryValid_t IsAnimationLibraryValid;
    Core_AreInteriorWeaponsAllowed_t AreInteriorWeaponsAllowed;
    Core_AllowInteriorWeapons_t AllowInteriorWeapons;
    Core_BlockIpAddress_t BlockIpAddress;
    Core_UnBlockIpAddress_t UnBlockIpAddress;
    Core_DisableEntryExitMarkers_t DisableEntryExitMarkers;
    Core_DisableNameTagsLOS_t DisableNameTagsLOS;
    Core_EnableZoneNames_t EnableZoneNames;
    Core_ShowGameTextForAll_t ShowGameTextForAll;
    Core_HideGameTextForAll_t HideGameTextForAll;
    Core_NetworkStats_t NetworkStats;
    Core_ServerTickRate_t ServerTickRate;
    Core_GetWeaponName_t GetWeaponName;
    Core_SetChatRadius_t SetChatRadius;
    Core_SetMarkerRadius_t SetMarkerRadius;
    Core_SendRconCommand_t SendRconCommand;
    Core_SetDeathDropAmount_t SetDeathDropAmount;
    Core_GameMode_t GameMode;
    Core_SetGravity_t SetGravity;
    Core_GetGravity_t GetGravity;
    Core_SetNameTagsDrawDistance_t SetNameTagsDrawDistance;
    Core_SetWeather_t SetWeather;
    Core_SetWorldTime_t SetWorldTime;
    Core_ShowNameTags_t ShowNameTags;
    Core_ShowPlayerMarkers_t ShowPlayerMarkers;
    Core_UsePedAnims_t UsePedAnims;
    Core_GetWeather_t GetWeather;
    Core_GetWorldTime_t GetWorldTime;
    Core_ToggleChatTextReplacement_t ToggleChatTextReplacement;
    Core_IsChatTextReplacementToggled_t IsChatTextReplacementToggled;
    Core_IsNickNameValid_t IsNickNameValid;
    Core_AllowNickNameCharacter_t AllowNickNameCharacter;
    Core_IsNickNameCharacterAllowed_t IsNickNameCharacterAllowed;
    Core_ClearBanList_t ClearBanList;
    Core_IsIpAddressBanned_t IsIpAddressBanned;
    Core_GetWeaponSlot_t GetWeaponSlot;
    Core_AddRule_t AddRule;
    Core_IsValidRule_t IsValidRule;
    Core_RemoveRule_t RemoveRule;
};

// NPC functions
struct NPC_t {
    NPC_Connect_t Connect;
};

// CustomModel functions
struct CustomModel_t {
    CustomModel_AddCharModel_t AddCharModel;
    CustomModel_AddSimpleModel_t AddSimpleModel;
    CustomModel_AddSimpleModelTimed_t AddSimpleModelTimed;
    CustomModel_RedirectDownload_t RedirectDownload;
    CustomModel_FindModelFileNameFromCRC_t FindModelFileNameFromCRC;
    CustomModel_IsValid_t IsValid;
    CustomModel_GetPath_t GetPath;
};

// Dialog functions
struct Dialog_t {
    Dialog_Show_t Show;
    Dialog_Hide_t Hide;
};

// Event functions
struct Event_t {
    Event_AddHandler_t AddHandler;
    Event_RemoveHandler_t RemoveHandler;
    Event_RemoveAllHandlers_t RemoveAllHandlers;
};

// GangZone functions
struct GangZone_t {
    GangZone_Create_t Create;
    GangZone_Destroy_t Destroy;
    GangZone_FromID_t FromID;
    GangZone_GetID_t GetID;
    GangZone_ShowForPlayer_t ShowForPlayer;
    GangZone_ShowForAll_t ShowForAll;
    GangZone_HideForPlayer_t HideForPlayer;
    GangZone_HideForAll_t HideForAll;
    GangZone_FlashForPlayer_t FlashForPlayer;
    GangZone_FlashForAll_t FlashForAll;
    GangZone_StopFlashForPlayer_t StopFlashForPlayer;
    GangZone_StopFlashForAll_t StopFlashForAll;
    GangZone_IsValid_t IsValid;
    GangZone_IsPlayerIn_t IsPlayerIn;
    GangZone_IsVisibleForPlayer_t IsVisibleForPlayer;
    GangZone_GetColorForPlayer_t GetColorForPlayer;
    GangZone_GetFlashColorForPlayer_t GetFlashColorForPlayer;
    GangZone_IsFlashingForPlayer_t IsFlashingForPlayer;
    GangZone_GetPos_t GetPos;
    GangZone_UseCheck_t UseCheck;
};

// Menu functions
struct Menu_t {
    Menu_Create_t Create;
    Menu_Destroy_t Destroy;
    Menu_FromID_t FromID;
    Menu_GetID_t GetID;
    Menu_AddItem_t AddItem;
    Menu_SetColumnHeader_t SetColumnHeader;
    Menu_ShowForPlayer_t ShowForPlayer;
    Menu_HideForPlayer_t HideForPlayer;
    Menu_Disable_t Disable;
    Menu_DisableRow_t DisableRow;
    Menu_IsValid_t IsValid;
    Menu_IsDisabled_t IsDisabled;
    Menu_IsRowDisabled_t IsRowDisabled;
    Menu_GetColumns_t GetColumns;
    Menu_GetItems_t GetItems;
    Menu_GetPos_t GetPos;
    Menu_GetColumnWidth_t GetColumnWidth;
    Menu_GetColumnHeader_t GetColumnHeader;
    Menu_GetItem_t GetItem;
};

// Object functions
struct Object_t {
    Object_Create_t Create;
    Object_Destroy_t Destroy;
    Object_FromID_t FromID;
    Object_GetID_t GetID;
    Object_AttachToVehicle_t AttachToVehicle;
    Object_AttachToObject_t AttachToObject;
    Object_AttachToPlayer_t AttachToPlayer;
    Object_SetPos_t SetPos;
    Object_GetPos_t GetPos;
    Object_SetRot_t SetRot;
    Object_GetRot_t GetRot;
    Object_GetModel_t GetModel;
    Object_SetNoCameraCollision_t SetNoCameraCollision;
    Object_IsValid_t IsValid;
    Object_Move_t Move;
    Object_Stop_t Stop;
    Object_IsMoving_t IsMoving;
    Object_BeginEditing_t BeginEditing;
    Object_BeginSelecting_t BeginSelecting;
    Object_EndEditing_t EndEditing;
    Object_SetMaterial_t SetMaterial;
    Object_SetMaterialText_t SetMaterialText;
    Object_SetDefaultCameraCollision_t SetDefaultCameraCollision;
    Object_GetDrawDistance_t GetDrawDistance;
    Object_GetMoveSpeed_t GetMoveSpeed;
    Object_GetMovingTargetPos_t GetMovingTargetPos;
    Object_GetMovingTargetRot_t GetMovingTargetRot;
    Object_GetAttachedData_t GetAttachedData;
    Object_GetAttachedOffset_t GetAttachedOffset;
    Object_GetSyncRotation_t GetSyncRotation;
    Object_IsMaterialSlotUsed_t IsMaterialSlotUsed;
    Object_GetMaterial_t GetMaterial;
    Object_GetMaterialText_t GetMaterialText;
    Object_IsObjectNoCameraCollision_t IsObjectNoCameraCollision;
    Object_GetType_t GetType;
};

// PlayerObject functions
struct PlayerObject_t {
    PlayerObject_Create_t Create;
    PlayerObject_Destroy_t Destroy;
    PlayerObject_FromID_t FromID;
    PlayerObject_GetID_t GetID;
    PlayerObject_AttachToVehicle_t AttachToVehicle;
    PlayerObject_AttachToPlayer_t AttachToPlayer;
    PlayerObject_AttachToObject_t AttachToObject;
    PlayerObject_SetPos_t SetPos;
    PlayerObject_GetPos_t GetPos;
    PlayerObject_SetRot_t SetRot;
    PlayerObject_GetRot_t GetRot;
    PlayerObject_GetModel_t GetModel;
    PlayerObject_SetNoCameraCollision_t SetNoCameraCollision;
    PlayerObject_IsValid_t IsValid;
    PlayerObject_Move_t Move;
    PlayerObject_Stop_t Stop;
    PlayerObject_IsMoving_t IsMoving;
    PlayerObject_BeginEditing_t BeginEditing;
    PlayerObject_SetMaterial_t SetMaterial;
    PlayerObject_SetMaterialText_t SetMaterialText;
    PlayerObject_GetDrawDistance_t GetDrawDistance;
    PlayerObject_GetMoveSpeed_t GetMoveSpeed;
    PlayerObject_GetMovingTargetPos_t GetMovingTargetPos;
    PlayerObject_GetMovingTargetRot_t GetMovingTargetRot;
    PlayerObject_GetAttachedData_t GetAttachedData;
    PlayerObject_GetAttachedOffset_t GetAttachedOffset;
    PlayerObject_GetSyncRotation_t GetSyncRotation;
    PlayerObject_IsMaterialSlotUsed_t IsMaterialSlotUsed;
    PlayerObject_GetMaterial_t GetMaterial;
    PlayerObject_GetMaterialText_t GetMaterialText;
    PlayerObject_IsNoCameraCollision_t IsNoCameraCollision;
};

// Pickup functions
struct Pickup_t {
    Pickup_Create_t Create;
    Pickup_AddStatic_t AddStatic;
    Pickup_Destroy_t Destroy;
    Pickup_FromID_t FromID;
    Pickup_GetID_t GetID;
    Pickup_IsValid_t IsValid;
    Pickup_IsStreamedIn_t IsStreamedIn;
    Pickup_GetPos_t GetPos;
    Pickup_GetModel_t GetModel;
    Pickup_GetType_t GetType;
    Pickup_GetVirtualWorld_t GetVirtualWorld;
    Pickup_SetPos_t SetPos;
    Pickup_SetModel_t SetModel;
    Pickup_SetType_t SetType;
    Pickup_SetVirtualWorld_t SetVirtualWorld;
    Pickup_ShowForPlayer_t ShowForPlayer;
    Pickup_HideForPlayer_t HideForPlayer;
    Pickup_IsHiddenForPlayer_t IsHiddenForPlayer;
};

// All functions
struct All_t {
    All_SendClientMessage_t SendClientMessage;
    All_CreateExplosion_t CreateExplosion;
    All_SendDeathMessage_t SendDeathMessage;
    All_EnableStuntBonus_t EnableStuntBonus;
};

// Recording functions
struct Recording_t {
    Recording_Start_t Start;
    Recording_Stop_t Stop;
};

// TextDraw functions
struct TextDraw_t {
    TextDraw_Create_t Create;
    TextDraw_Destroy_t Destroy;
    TextDraw_FromID_t FromID;
    TextDraw_GetID_t GetID;
    TextDraw_IsValid_t IsValid;
    TextDraw_IsVisibleForPlayer_t IsVisibleForPlayer;
    TextDraw_SetLetterSize_t SetLetterSize;
    TextDraw_SetTextSize_t SetTextSize;
    TextDraw_SetAlignment_t SetAlignment;
    TextDraw_SetColor_t SetColor;
    TextDraw_SetUseBox_t SetUseBox;
    TextDraw_SetBoxColor_t SetBoxColor;
    TextDraw_SetShadow_t SetShadow;
    TextDraw_SetOutline_t SetOutline;
    TextDraw_SetBackgroundColor_t SetBackgroundColor;
    TextDraw_SetFont_t SetFont;
    TextDraw_SetSetProportional_t SetSetProportional;
    TextDraw_SetSelectable_t SetSelectable;
    TextDraw_ShowForPlayer_t ShowForPlayer;
    TextDraw_HideForPlayer_t HideForPlayer;
    TextDraw_ShowForAll_t ShowForAll;
    TextDraw_HideForAll_t HideForAll;
    TextDraw_SetString_t SetString;
    TextDraw_SetPreviewModel_t SetPreviewModel;
    TextDraw_SetPreviewRot_t SetPreviewRot;
    TextDraw_SetPreviewVehCol_t SetPreviewVehCol;
    TextDraw_SetPos_t SetPos;
    TextDraw_GetString_t GetString;
    TextDraw_GetLetterSize_t GetLetterSize;
    TextDraw_GetTextSize_t GetTextSize;
    TextDraw_GetPos_t GetPos;
    TextDraw_GetColor_t GetColor;
    TextDraw_GetBoxColor_t GetBoxColor;
    TextDraw_GetBackgroundColor_t GetBackgroundColor;
    TextDraw_GetShadow_t GetShadow;
    TextDraw_GetOutline_t GetOutline;
    TextDraw_GetFont_t GetFont;
    TextDraw_IsBox_t IsBox;
    TextDraw_IsProportional_t IsProportional;
    TextDraw_IsSelectable_t IsSelectable;
    TextDraw_GetAlignment_t GetAlignment;
    TextDraw_GetPreviewModel_t GetPreviewModel;
    TextDraw_GetPreviewRot_t GetPreviewRot;
    TextDraw_GetPreviewVehColor_t GetPreviewVehColor;
    TextDraw_SetStringForPlayer_t SetStringForPlayer;
};

// PlayerTextDraw functions
struct PlayerTextDraw_t {
    PlayerTextDraw_Create_t Create;
    PlayerTextDraw_Destroy_t Destroy;
    PlayerTextDraw_FromID_t FromID;
    PlayerTextDraw_GetID_t GetID;
    PlayerTextDraw_IsValid_t IsValid;
    PlayerTextDraw_IsVisible_t IsVisible;
    PlayerTextDraw_SetLetterSize_t SetLetterSize;
    PlayerTextDraw_SetTextSize_t SetTextSize;
    PlayerTextDraw_SetAlignment_t SetAlignment;
    PlayerTextDraw_SetColor_t SetColor;
    PlayerTextDraw_UseBox_t UseBox;
    PlayerTextDraw_SetBoxColor_t SetBoxColor;
    PlayerTextDraw_SetShadow_t SetShadow;
    PlayerTextDraw_SetOutline_t SetOutline;
    PlayerTextDraw_SetBackgroundColor_t SetBackgroundColor;
    PlayerTextDraw_SetFont_t SetFont;
    PlayerTextDraw_SetProportional_t SetProportional;
    PlayerTextDraw_SetSelectable_t SetSelectable;
    PlayerTextDraw_Show_t Show;
    PlayerTextDraw_Hide_t Hide;
    PlayerTextDraw_SetString_t SetString;
    PlayerTextDraw_SetPreviewModel_t SetPreviewModel;
    PlayerTextDraw_SetPreviewRot_t SetPreviewRot;
    PlayerTextDraw_SetPreviewVehCol_t SetPreviewVehCol;
    PlayerTextDraw_SetPos_t SetPos;
    PlayerTextDraw_GetString_t GetString;
    PlayerTextDraw_GetLetterSize_t GetLetterSize;
    PlayerTextDraw_GetTextSize_t GetTextSize;
    PlayerTextDraw_GetPos_t GetPos;
    PlayerTextDraw_GetColor_t GetColor;
    PlayerTextDraw_GetBoxColor_t GetBoxColor;
    PlayerTextDraw_GetBackgroundColor_t GetBackgroundColor;
    PlayerTextDraw_GetShadow_t GetShadow;
    PlayerTextDraw_GetOutline_t GetOutline;
    PlayerTextDraw_GetFont_t GetFont;
    PlayerTextDraw_IsBox_t IsBox;
    PlayerTextDraw_IsProportional_t IsProportional;
    PlayerTextDraw_IsSelectable_t IsSelectable;
    PlayerTextDraw_GetAlignment_t GetAlignment;
    PlayerTextDraw_GetPreviewModel_t GetPreviewModel;
    PlayerTextDraw_GetPreviewRot_t GetPreviewRot;
    PlayerTextDraw_GetPreviewVehColor_t GetPreviewVehColor;
};

// TextLabel functions
struct TextLabel_t {
    TextLabel_Create_t Create;
    TextLabel_Destroy_t Destroy;
    TextLabel_FromID_t FromID;
    TextLabel_GetID_t GetID;
    TextLabel_AttachToPlayer_t AttachToPlayer;
    TextLabel_AttachToVehicle_t AttachToVehicle;
    TextLabel_UpdateText_t UpdateText;
    TextLabel_IsValid_t IsValid;
    TextLabel_IsStreamedIn_t IsStreamedIn;
    TextLabel_GetText_t GetText;
    TextLabel_GetColor_t GetColor;
    TextLabel_GetPos_t GetPos;
    TextLabel_SetDrawDistance_t SetDrawDistance;
    TextLabel_GetDrawDistance_t GetDrawDistance;
    TextLabel_GetLOS_t GetLOS;
    TextLabel_SetLOS_t SetLOS;
    TextLabel_GetVirtualWorld_t GetVirtualWorld;
    TextLabel_SetVirtualWorld_t SetVirtualWorld;
    TextLabel_GetAttachedData_t GetAttachedData;
};

// PlayerTextLabel functions
struct PlayerTextLabel_t {
    PlayerTextLabel_Create_t Create;
    PlayerTextLabel_Destroy_t Destroy;
    PlayerTextLabel_FromID_t FromID;
    PlayerTextLabel_GetID_t GetID;
    PlayerTextLabel_UpdateText_t UpdateText;
    PlayerTextLabel_IsValid_t IsValid;
    PlayerTextLabel_GetText_t GetText;
    PlayerTextLabel_GetColor_t GetColor;
    PlayerTextLabel_GetPos_t GetPos;
    PlayerTextLabel_SetDrawDistance_t SetDrawDistance;
    PlayerTextLabel_GetDrawDistance_t GetDrawDistance;
    PlayerTextLabel_GetLOS_t GetLOS;
    PlayerTextLabel_SetLOS_t SetLOS;
    PlayerTextLabel_GetVirtualWorld_t GetVirtualWorld;
    PlayerTextLabel_GetAttachedData_t GetAttachedData;
};

// Vehicle functions
struct Vehicle_t {
    Vehicle_Create_t Create;
    Vehicle_Destroy_t Destroy;
    Vehicle_FromID_t FromID;
    Vehicle_GetID_t GetID;
    Vehicle_GetMaxPassengerSeats_t GetMaxPassengerSeats;
    Vehicle_IsStreamedIn_t IsStreamedIn;
    Vehicle_GetPos_t GetPos;
    Vehicle_SetPos_t SetPos;
    Vehicle_GetZAngle_t GetZAngle;
    Vehicle_GetRotationQuat_t GetRotationQuat;
    Vehicle_GetDistanceFromPoint_t GetDistanceFromPoint;
    Vehicle_SetZAngle_t SetZAngle;
    Vehicle_SetParamsForPlayer_t SetParamsForPlayer;
    Vehicle_UseManualEngineAndLights_t UseManualEngineAndLights;
    Vehicle_SetParamsEx_t SetParamsEx;
    Vehicle_GetParamsEx_t GetParamsEx;
    Vehicle_GetParamsSirenState_t GetParamsSirenState;
    Vehicle_SetParamsCarDoors_t SetParamsCarDoors;
    Vehicle_GetParamsCarDoors_t GetParamsCarDoors;
    Vehicle_SetParamsCarWindows_t SetParamsCarWindows;
    Vehicle_GetParamsCarWindows_t GetParamsCarWindows;
    Vehicle_SetToRespawn_t SetToRespawn;
    Vehicle_LinkToInterior_t LinkToInterior;
    Vehicle_AddComponent_t AddComponent;
    Vehicle_RemoveComponent_t RemoveComponent;
    Vehicle_ChangeColor_t ChangeColor;
    Vehicle_ChangePaintjob_t ChangePaintjob;
    Vehicle_SetHealth_t SetHealth;
    Vehicle_GetHealth_t GetHealth;
    Vehicle_AttachTrailer_t AttachTrailer;
    Vehicle_DetachTrailer_t DetachTrailer;
    Vehicle_IsTrailerAttached_t IsTrailerAttached;
    Vehicle_GetTrailer_t GetTrailer;
    Vehicle_SetNumberPlate_t SetNumberPlate;
    Vehicle_GetModel_t GetModel;
    Vehicle_GetComponentInSlot_t GetComponentInSlot;
    Vehicle_GetComponentType_t GetComponentType;
    Vehicle_CanHaveComponent_t CanHaveComponent;
    Vehicle_GetRandomColorPair_t GetRandomColorPair;
    Vehicle_ColorIndexToColor_t ColorIndexToColor;
    Vehicle_Repair_t Repair;
    Vehicle_GetVelocity_t GetVelocity;
    Vehicle_SetVelocity_t SetVelocity;
    Vehicle_SetAngularVelocity_t SetAngularVelocity;
    Vehicle_GetDamageStatus_t GetDamageStatus;
    Vehicle_UpdateDamageStatus_t UpdateDamageStatus;
    Vehicle_GetModelInfo_t GetModelInfo;
    Vehicle_SetVirtualWorld_t SetVirtualWorld;
    Vehicle_GetVirtualWorld_t GetVirtualWorld;
    Vehicle_GetLandingGearState_t GetLandingGearState;
    Vehicle_IsValid_t IsValid;
    Vehicle_AddStatic_t AddStatic;
    Vehicle_AddStaticEx_t AddStaticEx;
    Vehicle_EnableFriendlyFire_t EnableFriendlyFire;
    Vehicle_GetSpawnInfo_t GetSpawnInfo;
    Vehicle_SetSpawnInfo_t SetSpawnInfo;
    Vehicle_GetModelCount_t GetModelCount;
    Vehicle_GetModelsUsed_t GetModelsUsed;
    Vehicle_GetPaintjob_t GetPaintjob;
    Vehicle_GetColor_t GetColor;
    Vehicle_GetInterior_t GetInterior;
    Vehicle_GetNumberPlate_t GetNumberPlate;
    Vehicle_SetRespawnDelay_t SetRespawnDelay;
    Vehicle_GetRespawnDelay_t GetRespawnDelay;
    Vehicle_GetCab_t GetCab;
    Vehicle_GetTower_t GetTower;
    Vehicle_GetOccupiedTick_t GetOccupiedTick;
    Vehicle_GetRespawnTick_t GetRespawnTick;
    Vehicle_HasBeenOccupied_t HasBeenOccupied;
    Vehicle_IsOccupied_t IsOccupied;
    Vehicle_IsDead_t IsDead;
    Vehicle_SetParamsSirenState_t SetParamsSirenState;
    Vehicle_ToggleSirenEnabled_t ToggleSirenEnabled;
    Vehicle_IsSirenEnabled_t IsSirenEnabled;
    Vehicle_GetLastDriver_t GetLastDriver;
    Vehicle_GetDriver_t GetDriver;
    Vehicle_GetSirenState_t GetSirenState;
    Vehicle_GetHydraReactorAngle_t GetHydraReactorAngle;
    Vehicle_GetTrainSpeed_t GetTrainSpeed;
    Vehicle_GetMatrix_t GetMatrix;
    Vehicle_GetOccupant_t GetOccupant;
    Vehicle_CountOccupants_t CountOccupants;
};

// All APIs
struct OMPAPI_t {
    struct Actor_t Actor;
    struct Checkpoint_t Checkpoint;
    struct RaceCheckpoint_t RaceCheckpoint;
    struct Class_t Class;
    struct Player_t Player;
    struct Component_t Component;
    struct Config_t Config;
    struct Core_t Core;
    struct NPC_t NPC;
    struct CustomModel_t CustomModel;
    struct Dialog_t Dialog;
    struct Event_t Event;
    struct GangZone_t GangZone;
    struct Menu_t Menu;
    struct Object_t Object;
    struct PlayerObject_t PlayerObject;
    struct Pickup_t Pickup;
    struct All_t All;
    struct Recording_t Recording;
    struct TextDraw_t TextDraw;
    struct PlayerTextDraw_t PlayerTextDraw;
    struct TextLabel_t TextLabel;
    struct PlayerTextLabel_t PlayerTextLabel;
    struct Vehicle_t Vehicle;
};

static bool omp_initialize_capi(struct OMPAPI_t* ompapi) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    void* capi_lib = LIBRARY_OPEN("./components/$CAPI.dll");
#else
    void* capi_lib = LIBRARY_OPEN("./components/$CAPI.so");
#endif

    // Check if library was loaded successfully
    if (!capi_lib)
    {
        return false;
    }

    // Verify one of the core components are available
    ompapi->Core.TickCount = (Core_TickCount_t)LIBRARY_GET_ADDR(capi_lib, "Core_TickCount");

    // Verify that at least one function was loaded successfully
    if (!ompapi->Actor.Create)
    {
        return false;
    }

    // Retrieve Actor functions
    ompapi->Actor.Create = (Actor_Create_t)LIBRARY_GET_ADDR(capi_lib, "Actor_Create");
    ompapi->Actor.Destroy = (Actor_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "Actor_Destroy");
    ompapi->Actor.FromID = (Actor_FromID_t)LIBRARY_GET_ADDR(capi_lib, "Actor_FromID");
    ompapi->Actor.GetID = (Actor_GetID_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetID");
    ompapi->Actor.IsStreamedInFor = (Actor_IsStreamedInFor_t)LIBRARY_GET_ADDR(capi_lib, "Actor_IsStreamedInFor");
    ompapi->Actor.SetVirtualWorld = (Actor_SetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Actor_SetVirtualWorld");
    ompapi->Actor.GetVirtualWorld = (Actor_GetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetVirtualWorld");
    ompapi->Actor.ApplyAnimation = (Actor_ApplyAnimation_t)LIBRARY_GET_ADDR(capi_lib, "Actor_ApplyAnimation");
    ompapi->Actor.ClearAnimations = (Actor_ClearAnimations_t)LIBRARY_GET_ADDR(capi_lib, "Actor_ClearAnimations");
    ompapi->Actor.SetPos = (Actor_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "Actor_SetPos");
    ompapi->Actor.GetPos = (Actor_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetPos");
    ompapi->Actor.SetFacingAngle = (Actor_SetFacingAngle_t)LIBRARY_GET_ADDR(capi_lib, "Actor_SetFacingAngle");
    ompapi->Actor.GetFacingAngle = (Actor_GetFacingAngle_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetFacingAngle");
    ompapi->Actor.SetHealth = (Actor_SetHealth_t)LIBRARY_GET_ADDR(capi_lib, "Actor_SetHealth");
    ompapi->Actor.GetHealth = (Actor_GetHealth_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetHealth");
    ompapi->Actor.SetInvulnerable = (Actor_SetInvulnerable_t)LIBRARY_GET_ADDR(capi_lib, "Actor_SetInvulnerable");
    ompapi->Actor.IsInvulnerable = (Actor_IsInvulnerable_t)LIBRARY_GET_ADDR(capi_lib, "Actor_IsInvulnerable");
    ompapi->Actor.IsValid = (Actor_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "Actor_IsValid");
    ompapi->Actor.SetSkin = (Actor_SetSkin_t)LIBRARY_GET_ADDR(capi_lib, "Actor_SetSkin");
    ompapi->Actor.GetSkin = (Actor_GetSkin_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetSkin");
    ompapi->Actor.GetAnimation = (Actor_GetAnimation_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetAnimation");
    ompapi->Actor.GetSpawnInfo = (Actor_GetSpawnInfo_t)LIBRARY_GET_ADDR(capi_lib, "Actor_GetSpawnInfo");

    // Retrieve Checkpoint functions
    ompapi->Checkpoint.Set = (Checkpoint_Set_t)LIBRARY_GET_ADDR(capi_lib, "Checkpoint_Set");
    ompapi->Checkpoint.Disable = (Checkpoint_Disable_t)LIBRARY_GET_ADDR(capi_lib, "Checkpoint_Disable");
    ompapi->Checkpoint.IsPlayerIn = (Checkpoint_IsPlayerIn_t)LIBRARY_GET_ADDR(capi_lib, "Checkpoint_IsPlayerIn");
    ompapi->Checkpoint.IsActive = (Checkpoint_IsActive_t)LIBRARY_GET_ADDR(capi_lib, "Checkpoint_IsActive");
    ompapi->Checkpoint.Get = (Checkpoint_Get_t)LIBRARY_GET_ADDR(capi_lib, "Checkpoint_Get");

    // Retrieve RaceCheckpoint functions
    ompapi->RaceCheckpoint.Set = (RaceCheckpoint_Set_t)LIBRARY_GET_ADDR(capi_lib, "RaceCheckpoint_Set");
    ompapi->RaceCheckpoint.Disable = (RaceCheckpoint_Disable_t)LIBRARY_GET_ADDR(capi_lib, "RaceCheckpoint_Disable");
    ompapi->RaceCheckpoint.IsPlayerIn = (RaceCheckpoint_IsPlayerIn_t)LIBRARY_GET_ADDR(capi_lib, "RaceCheckpoint_IsPlayerIn");
    ompapi->RaceCheckpoint.IsActive = (RaceCheckpoint_IsActive_t)LIBRARY_GET_ADDR(capi_lib, "RaceCheckpoint_IsActive");
    ompapi->RaceCheckpoint.Get = (RaceCheckpoint_Get_t)LIBRARY_GET_ADDR(capi_lib, "RaceCheckpoint_Get");

    // Retrieve Class functions
    ompapi->Class.Add = (Class_Add_t)LIBRARY_GET_ADDR(capi_lib, "Class_Add");
    ompapi->Class.FromID = (Class_FromID_t)LIBRARY_GET_ADDR(capi_lib, "Class_FromID");
    ompapi->Class.GetID = (Class_GetID_t)LIBRARY_GET_ADDR(capi_lib, "Class_GetID");
    ompapi->Class.Count = (Class_Count_t)LIBRARY_GET_ADDR(capi_lib, "Class_Count");
    ompapi->Class.GetData = (Class_GetData_t)LIBRARY_GET_ADDR(capi_lib, "Class_GetData");
    ompapi->Class.Edit = (Class_Edit_t)LIBRARY_GET_ADDR(capi_lib, "Class_Edit");

    // Retrieve Player functions
    ompapi->Player.SetSpawnInfo = (Player_SetSpawnInfo_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetSpawnInfo");
    ompapi->Player.GetSpawnInfo = (Player_GetSpawnInfo_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSpawnInfo");
    ompapi->Player.GetNetworkStats = (Player_GetNetworkStats_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetNetworkStats");
    ompapi->Player.NetStatsBytesReceived = (Player_NetStatsBytesReceived_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsBytesReceived");
    ompapi->Player.NetStatsBytesSent = (Player_NetStatsBytesSent_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsBytesSent");
    ompapi->Player.NetStatsConnectionStatus = (Player_NetStatsConnectionStatus_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsConnectionStatus");
    ompapi->Player.NetStatsGetConnectedTime = (Player_NetStatsGetConnectedTime_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsGetConnectedTime");
    ompapi->Player.NetStatsGetIpPort = (Player_NetStatsGetIpPort_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsGetIpPort");
    ompapi->Player.NetStatsMessagesReceived = (Player_NetStatsMessagesReceived_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsMessagesReceived");
    ompapi->Player.NetStatsMessagesRecvPerSecond = (Player_NetStatsMessagesRecvPerSecond_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsMessagesRecvPerSecond");
    ompapi->Player.NetStatsMessagesSent = (Player_NetStatsMessagesSent_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsMessagesSent");
    ompapi->Player.NetStatsPacketLossPercent = (Player_NetStatsPacketLossPercent_t)LIBRARY_GET_ADDR(capi_lib, "Player_NetStatsPacketLossPercent");
    ompapi->Player.GetCustomSkin = (Player_GetCustomSkin_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCustomSkin");
    ompapi->Player.GetDialog = (Player_GetDialog_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetDialog");
    ompapi->Player.GetDialogData = (Player_GetDialogData_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetDialogData");
    ompapi->Player.GetMenu = (Player_GetMenu_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetMenu");
    ompapi->Player.GetSurfingPlayerObject = (Player_GetSurfingPlayerObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSurfingPlayerObject");
    ompapi->Player.GetCameraTargetPlayerObject = (Player_GetCameraTargetPlayerObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraTargetPlayerObject");
    ompapi->Player.FromID = (Player_FromID_t)LIBRARY_GET_ADDR(capi_lib, "Player_FromID");
    ompapi->Player.GetID = (Player_GetID_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetID");
    ompapi->Player.SendClientMessage = (Player_SendClientMessage_t)LIBRARY_GET_ADDR(capi_lib, "Player_SendClientMessage");
    ompapi->Player.SetCameraPos = (Player_SetCameraPos_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetCameraPos");
    ompapi->Player.SetDrunkLevel = (Player_SetDrunkLevel_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetDrunkLevel");
    ompapi->Player.SetInterior = (Player_SetInterior_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetInterior");
    ompapi->Player.SetWantedLevel = (Player_SetWantedLevel_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetWantedLevel");
    ompapi->Player.SetWeather = (Player_SetWeather_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetWeather");
    ompapi->Player.GetWeather = (Player_GetWeather_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetWeather");
    ompapi->Player.SetSkin = (Player_SetSkin_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetSkin");
    ompapi->Player.SetShopName = (Player_SetShopName_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetShopName");
    ompapi->Player.GiveMoney = (Player_GiveMoney_t)LIBRARY_GET_ADDR(capi_lib, "Player_GiveMoney");
    ompapi->Player.SetCameraLookAt = (Player_SetCameraLookAt_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetCameraLookAt");
    ompapi->Player.SetCameraBehind = (Player_SetCameraBehind_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetCameraBehind");
    ompapi->Player.CreateExplosion = (Player_CreateExplosion_t)LIBRARY_GET_ADDR(capi_lib, "Player_CreateExplosion");
    ompapi->Player.PlayAudioStream = (Player_PlayAudioStream_t)LIBRARY_GET_ADDR(capi_lib, "Player_PlayAudioStream");
    ompapi->Player.StopAudioStream = (Player_StopAudioStream_t)LIBRARY_GET_ADDR(capi_lib, "Player_StopAudioStream");
    ompapi->Player.ToggleWidescreen = (Player_ToggleWidescreen_t)LIBRARY_GET_ADDR(capi_lib, "Player_ToggleWidescreen");
    ompapi->Player.IsWidescreenToggled = (Player_IsWidescreenToggled_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsWidescreenToggled");
    ompapi->Player.SetHealth = (Player_SetHealth_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetHealth");
    ompapi->Player.GetHealth = (Player_GetHealth_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetHealth");
    ompapi->Player.SetArmor = (Player_SetArmor_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetArmor");
    ompapi->Player.GetArmor = (Player_GetArmor_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetArmor");
    ompapi->Player.SetTeam = (Player_SetTeam_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetTeam");
    ompapi->Player.GetTeam = (Player_GetTeam_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetTeam");
    ompapi->Player.SetScore = (Player_SetScore_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetScore");
    ompapi->Player.GetScore = (Player_GetScore_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetScore");
    ompapi->Player.GetSkin = (Player_GetSkin_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSkin");
    ompapi->Player.SetColor = (Player_SetColor_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetColor");
    ompapi->Player.GetColor = (Player_GetColor_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetColor");
    ompapi->Player.GetDefaultColor = (Player_GetDefaultColor_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetDefaultColor");
    ompapi->Player.GetDrunkLevel = (Player_GetDrunkLevel_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetDrunkLevel");
    ompapi->Player.GiveWeapon = (Player_GiveWeapon_t)LIBRARY_GET_ADDR(capi_lib, "Player_GiveWeapon");
    ompapi->Player.RemoveWeapon = (Player_RemoveWeapon_t)LIBRARY_GET_ADDR(capi_lib, "Player_RemoveWeapon");
    ompapi->Player.GetMoney = (Player_GetMoney_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetMoney");
    ompapi->Player.ResetMoney = (Player_ResetMoney_t)LIBRARY_GET_ADDR(capi_lib, "Player_ResetMoney");
    ompapi->Player.SetName = (Player_SetName_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetName");
    ompapi->Player.GetName = (Player_GetName_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetName");
    ompapi->Player.GetState = (Player_GetState_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetState");
    ompapi->Player.GetPing = (Player_GetPing_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetPing");
    ompapi->Player.GetWeapon = (Player_GetWeapon_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetWeapon");
    ompapi->Player.SetTime = (Player_SetTime_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetTime");
    ompapi->Player.GetTime = (Player_GetTime_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetTime");
    ompapi->Player.ToggleClock = (Player_ToggleClock_t)LIBRARY_GET_ADDR(capi_lib, "Player_ToggleClock");
    ompapi->Player.HasClock = (Player_HasClock_t)LIBRARY_GET_ADDR(capi_lib, "Player_HasClock");
    ompapi->Player.ForceClassSelection = (Player_ForceClassSelection_t)LIBRARY_GET_ADDR(capi_lib, "Player_ForceClassSelection");
    ompapi->Player.GetWantedLevel = (Player_GetWantedLevel_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetWantedLevel");
    ompapi->Player.SetFightingStyle = (Player_SetFightingStyle_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetFightingStyle");
    ompapi->Player.GetFightingStyle = (Player_GetFightingStyle_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetFightingStyle");
    ompapi->Player.SetVelocity = (Player_SetVelocity_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetVelocity");
    ompapi->Player.GetVelocity = (Player_GetVelocity_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetVelocity");
    ompapi->Player.GetCameraPos = (Player_GetCameraPos_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraPos");
    ompapi->Player.GetDistanceFromPoint = (Player_GetDistanceFromPoint_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetDistanceFromPoint");
    ompapi->Player.GetInterior = (Player_GetInterior_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetInterior");
    ompapi->Player.SetPos = (Player_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetPos");
    ompapi->Player.GetPos = (Player_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetPos");
    ompapi->Player.GetVirtualWorld = (Player_GetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetVirtualWorld");
    ompapi->Player.IsNPC = (Player_IsNPC_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsNPC");
    ompapi->Player.IsStreamedIn = (Player_IsStreamedIn_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsStreamedIn");
    ompapi->Player.PlayGameSound = (Player_PlayGameSound_t)LIBRARY_GET_ADDR(capi_lib, "Player_PlayGameSound");
    ompapi->Player.SpectatePlayer = (Player_SpectatePlayer_t)LIBRARY_GET_ADDR(capi_lib, "Player_SpectatePlayer");
    ompapi->Player.SpectateVehicle = (Player_SpectateVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Player_SpectateVehicle");
    ompapi->Player.SetVirtualWorld = (Player_SetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetVirtualWorld");
    ompapi->Player.SetWorldBounds = (Player_SetWorldBounds_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetWorldBounds");
    ompapi->Player.ClearWorldBounds = (Player_ClearWorldBounds_t)LIBRARY_GET_ADDR(capi_lib, "Player_ClearWorldBounds");
    ompapi->Player.GetWorldBounds = (Player_GetWorldBounds_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetWorldBounds");
    ompapi->Player.ClearAnimations = (Player_ClearAnimations_t)LIBRARY_GET_ADDR(capi_lib, "Player_ClearAnimations");
    ompapi->Player.GetLastShotVectors = (Player_GetLastShotVectors_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetLastShotVectors");
    ompapi->Player.GetCameraTargetPlayer = (Player_GetCameraTargetPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraTargetPlayer");
    ompapi->Player.GetCameraTargetActor = (Player_GetCameraTargetActor_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraTargetActor");
    ompapi->Player.GetCameraTargetObject = (Player_GetCameraTargetObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraTargetObject");
    ompapi->Player.GetCameraTargetVehicle = (Player_GetCameraTargetVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraTargetVehicle");
    ompapi->Player.PutInVehicle = (Player_PutInVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Player_PutInVehicle");
    ompapi->Player.RemoveBuilding = (Player_RemoveBuilding_t)LIBRARY_GET_ADDR(capi_lib, "Player_RemoveBuilding");
    ompapi->Player.GetBuildingsRemoved = (Player_GetBuildingsRemoved_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetBuildingsRemoved");
    ompapi->Player.RemoveFromVehicle = (Player_RemoveFromVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Player_RemoveFromVehicle");
    ompapi->Player.RemoveMapIcon = (Player_RemoveMapIcon_t)LIBRARY_GET_ADDR(capi_lib, "Player_RemoveMapIcon");
    ompapi->Player.SetMapIcon = (Player_SetMapIcon_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetMapIcon");
    ompapi->Player.ResetWeapons = (Player_ResetWeapons_t)LIBRARY_GET_ADDR(capi_lib, "Player_ResetWeapons");
    ompapi->Player.SetAmmo = (Player_SetAmmo_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetAmmo");
    ompapi->Player.SetArmedWeapon = (Player_SetArmedWeapon_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetArmedWeapon");
    ompapi->Player.SetChatBubble = (Player_SetChatBubble_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetChatBubble");
    ompapi->Player.SetPosFindZ = (Player_SetPosFindZ_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetPosFindZ");
    ompapi->Player.SetSkillLevel = (Player_SetSkillLevel_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetSkillLevel");
    ompapi->Player.SetSpecialAction = (Player_SetSpecialAction_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetSpecialAction");
    ompapi->Player.ShowNameTagForPlayer = (Player_ShowNameTagForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Player_ShowNameTagForPlayer");
    ompapi->Player.ToggleControllable = (Player_ToggleControllable_t)LIBRARY_GET_ADDR(capi_lib, "Player_ToggleControllable");
    ompapi->Player.ToggleSpectating = (Player_ToggleSpectating_t)LIBRARY_GET_ADDR(capi_lib, "Player_ToggleSpectating");
    ompapi->Player.ApplyAnimation = (Player_ApplyAnimation_t)LIBRARY_GET_ADDR(capi_lib, "Player_ApplyAnimation");
    ompapi->Player.GetAnimationName = (Player_GetAnimationName_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetAnimationName");
    ompapi->Player.EditAttachedObject = (Player_EditAttachedObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_EditAttachedObject");
    ompapi->Player.EnableCameraTarget = (Player_EnableCameraTarget_t)LIBRARY_GET_ADDR(capi_lib, "Player_EnableCameraTarget");
    ompapi->Player.EnableStuntBonus = (Player_EnableStuntBonus_t)LIBRARY_GET_ADDR(capi_lib, "Player_EnableStuntBonus");
    ompapi->Player.GetPlayerAmmo = (Player_GetPlayerAmmo_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetPlayerAmmo");
    ompapi->Player.GetAnimationIndex = (Player_GetAnimationIndex_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetAnimationIndex");
    ompapi->Player.GetFacingAngle = (Player_GetFacingAngle_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetFacingAngle");
    ompapi->Player.GetIp = (Player_GetIp_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetIp");
    ompapi->Player.GetSpecialAction = (Player_GetSpecialAction_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSpecialAction");
    ompapi->Player.GetVehicleID = (Player_GetVehicleID_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetVehicleID");
    ompapi->Player.GetVehicleSeat = (Player_GetVehicleSeat_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetVehicleSeat");
    ompapi->Player.GetWeaponData = (Player_GetWeaponData_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetWeaponData");
    ompapi->Player.GetWeaponState = (Player_GetWeaponState_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetWeaponState");
    ompapi->Player.InterpolateCameraPos = (Player_InterpolateCameraPos_t)LIBRARY_GET_ADDR(capi_lib, "Player_InterpolateCameraPos");
    ompapi->Player.InterpolateCameraLookAt = (Player_InterpolateCameraLookAt_t)LIBRARY_GET_ADDR(capi_lib, "Player_InterpolateCameraLookAt");
    ompapi->Player.IsPlayerAttachedObjectSlotUsed = (Player_IsPlayerAttachedObjectSlotUsed_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsPlayerAttachedObjectSlotUsed");
    ompapi->Player.AttachCameraToObject = (Player_AttachCameraToObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_AttachCameraToObject");
    ompapi->Player.AttachCameraToPlayerObject = (Player_AttachCameraToPlayerObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_AttachCameraToPlayerObject");
    ompapi->Player.GetCameraAspectRatio = (Player_GetCameraAspectRatio_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraAspectRatio");
    ompapi->Player.GetCameraFrontVector = (Player_GetCameraFrontVector_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraFrontVector");
    ompapi->Player.GetCameraMode = (Player_GetCameraMode_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraMode");
    ompapi->Player.GetKeys = (Player_GetKeys_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetKeys");
    ompapi->Player.GetSurfingVehicle = (Player_GetSurfingVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSurfingVehicle");
    ompapi->Player.GetSurfingObject = (Player_GetSurfingObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSurfingObject");
    ompapi->Player.GetTargetPlayer = (Player_GetTargetPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetTargetPlayer");
    ompapi->Player.GetTargetActor = (Player_GetTargetActor_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetTargetActor");
    ompapi->Player.IsInVehicle = (Player_IsInVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsInVehicle");
    ompapi->Player.IsInAnyVehicle = (Player_IsInAnyVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsInAnyVehicle");
    ompapi->Player.IsInRangeOfPoint = (Player_IsInRangeOfPoint_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsInRangeOfPoint");
    ompapi->Player.PlayCrimeReport = (Player_PlayCrimeReport_t)LIBRARY_GET_ADDR(capi_lib, "Player_PlayCrimeReport");
    ompapi->Player.RemoveAttachedObject = (Player_RemoveAttachedObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_RemoveAttachedObject");
    ompapi->Player.SetAttachedObject = (Player_SetAttachedObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetAttachedObject");
    ompapi->Player.GetAttachedObject = (Player_GetAttachedObject_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetAttachedObject");
    ompapi->Player.SetFacingAngle = (Player_SetFacingAngle_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetFacingAngle");
    ompapi->Player.SetMarkerForPlayer = (Player_SetMarkerForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetMarkerForPlayer");
    ompapi->Player.GetMarkerForPlayer = (Player_GetMarkerForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetMarkerForPlayer");
    ompapi->Player.AllowTeleport = (Player_AllowTeleport_t)LIBRARY_GET_ADDR(capi_lib, "Player_AllowTeleport");
    ompapi->Player.IsTeleportAllowed = (Player_IsTeleportAllowed_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsTeleportAllowed");
    ompapi->Player.DisableRemoteVehicleCollisions = (Player_DisableRemoteVehicleCollisions_t)LIBRARY_GET_ADDR(capi_lib, "Player_DisableRemoteVehicleCollisions");
    ompapi->Player.GetCameraZoom = (Player_GetCameraZoom_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetCameraZoom");
    ompapi->Player.SelectTextDraw = (Player_SelectTextDraw_t)LIBRARY_GET_ADDR(capi_lib, "Player_SelectTextDraw");
    ompapi->Player.CancelSelectTextDraw = (Player_CancelSelectTextDraw_t)LIBRARY_GET_ADDR(capi_lib, "Player_CancelSelectTextDraw");
    ompapi->Player.SendClientCheck = (Player_SendClientCheck_t)LIBRARY_GET_ADDR(capi_lib, "Player_SendClientCheck");
    ompapi->Player.Spawn = (Player_Spawn_t)LIBRARY_GET_ADDR(capi_lib, "Player_Spawn");
    ompapi->Player.GPCI = (Player_GPCI_t)LIBRARY_GET_ADDR(capi_lib, "Player_GPCI");
    ompapi->Player.IsAdmin = (Player_IsAdmin_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsAdmin");
    ompapi->Player.Kick = (Player_Kick_t)LIBRARY_GET_ADDR(capi_lib, "Player_Kick");
    ompapi->Player.ShowGameText = (Player_ShowGameText_t)LIBRARY_GET_ADDR(capi_lib, "Player_ShowGameText");
    ompapi->Player.HideGameText = (Player_HideGameText_t)LIBRARY_GET_ADDR(capi_lib, "Player_HideGameText");
    ompapi->Player.HasGameText = (Player_HasGameText_t)LIBRARY_GET_ADDR(capi_lib, "Player_HasGameText");
    ompapi->Player.GetGameText = (Player_GetGameText_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetGameText");
    ompapi->Player.Ban = (Player_Ban_t)LIBRARY_GET_ADDR(capi_lib, "Player_Ban");
    ompapi->Player.BanEx = (Player_BanEx_t)LIBRARY_GET_ADDR(capi_lib, "Player_BanEx");
    ompapi->Player.SendDeathMessage = (Player_SendDeathMessage_t)LIBRARY_GET_ADDR(capi_lib, "Player_SendDeathMessage");
    ompapi->Player.SendMessageToPlayer = (Player_SendMessageToPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Player_SendMessageToPlayer");
    ompapi->Player.GetVersion = (Player_GetVersion_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetVersion");
    ompapi->Player.GetSkillLevel = (Player_GetSkillLevel_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSkillLevel");
    ompapi->Player.GetZAim = (Player_GetZAim_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetZAim");
    ompapi->Player.GetSurfingOffsets = (Player_GetSurfingOffsets_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSurfingOffsets");
    ompapi->Player.GetRotationQuat = (Player_GetRotationQuat_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetRotationQuat");
    ompapi->Player.GetPlayerSpectateID = (Player_GetPlayerSpectateID_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetPlayerSpectateID");
    ompapi->Player.GetSpectateType = (Player_GetSpectateType_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSpectateType");
    ompapi->Player.GetRawIp = (Player_GetRawIp_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetRawIp");
    ompapi->Player.SetGravity = (Player_SetGravity_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetGravity");
    ompapi->Player.GetGravity = (Player_GetGravity_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetGravity");
    ompapi->Player.SetAdmin = (Player_SetAdmin_t)LIBRARY_GET_ADDR(capi_lib, "Player_SetAdmin");
    ompapi->Player.IsSpawned = (Player_IsSpawned_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsSpawned");
    ompapi->Player.IsControllable = (Player_IsControllable_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsControllable");
    ompapi->Player.IsCameraTargetEnabled = (Player_IsCameraTargetEnabled_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsCameraTargetEnabled");
    ompapi->Player.ToggleGhostMode = (Player_ToggleGhostMode_t)LIBRARY_GET_ADDR(capi_lib, "Player_ToggleGhostMode");
    ompapi->Player.GetGhostMode = (Player_GetGhostMode_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetGhostMode");
    ompapi->Player.AllowWeapons = (Player_AllowWeapons_t)LIBRARY_GET_ADDR(capi_lib, "Player_AllowWeapons");
    ompapi->Player.AreWeaponsAllowed = (Player_AreWeaponsAllowed_t)LIBRARY_GET_ADDR(capi_lib, "Player_AreWeaponsAllowed");
    ompapi->Player.IsPlayerUsingOfficialClient = (Player_IsPlayerUsingOfficialClient_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsPlayerUsingOfficialClient");
    ompapi->Player.GetAnimationFlags = (Player_GetAnimationFlags_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetAnimationFlags");
    ompapi->Player.IsInDriveByMode = (Player_IsInDriveByMode_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsInDriveByMode");
    ompapi->Player.IsCuffed = (Player_IsCuffed_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsCuffed");
    ompapi->Player.IsInModShop = (Player_IsInModShop_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsInModShop");
    ompapi->Player.GetSirenState = (Player_GetSirenState_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetSirenState");
    ompapi->Player.GetLandingGearState = (Player_GetLandingGearState_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetLandingGearState");
    ompapi->Player.GetHydraReactorAngle = (Player_GetHydraReactorAngle_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetHydraReactorAngle");
    ompapi->Player.GetTrainSpeed = (Player_GetTrainSpeed_t)LIBRARY_GET_ADDR(capi_lib, "Player_GetTrainSpeed");
    ompapi->Player.IsPlayerUsingOmp = (Player_IsPlayerUsingOmp_t)LIBRARY_GET_ADDR(capi_lib, "Player_IsPlayerUsingOmp");

    // Retrieve Component functions
    ompapi->Component.Create = (Component_Create_t)LIBRARY_GET_ADDR(capi_lib, "Component_Create");

    // Retrieve Config functions
    ompapi->Config.GetAsBool = (Config_GetAsBool_t)LIBRARY_GET_ADDR(capi_lib, "Config_GetAsBool");
    ompapi->Config.GetAsInt = (Config_GetAsInt_t)LIBRARY_GET_ADDR(capi_lib, "Config_GetAsInt");
    ompapi->Config.GetAsFloat = (Config_GetAsFloat_t)LIBRARY_GET_ADDR(capi_lib, "Config_GetAsFloat");
    ompapi->Config.GetAsString = (Config_GetAsString_t)LIBRARY_GET_ADDR(capi_lib, "Config_GetAsString");

    // Retrieve Core functions
    ompapi->Core.TickCount = (Core_TickCount_t)LIBRARY_GET_ADDR(capi_lib, "Core_TickCount");
    ompapi->Core.MaxPlayers = (Core_MaxPlayers_t)LIBRARY_GET_ADDR(capi_lib, "Core_MaxPlayers");
    ompapi->Core.Log = (Core_Log_t)LIBRARY_GET_ADDR(capi_lib, "Core_Log");
    ompapi->Core.IsAdminTeleportAllowed = (Core_IsAdminTeleportAllowed_t)LIBRARY_GET_ADDR(capi_lib, "Core_IsAdminTeleportAllowed");
    ompapi->Core.AllowAdminTeleport = (Core_AllowAdminTeleport_t)LIBRARY_GET_ADDR(capi_lib, "Core_AllowAdminTeleport");
    ompapi->Core.AreAllAnimationsEnabled = (Core_AreAllAnimationsEnabled_t)LIBRARY_GET_ADDR(capi_lib, "Core_AreAllAnimationsEnabled");
    ompapi->Core.EnableAllAnimations = (Core_EnableAllAnimations_t)LIBRARY_GET_ADDR(capi_lib, "Core_EnableAllAnimations");
    ompapi->Core.IsAnimationLibraryValid = (Core_IsAnimationLibraryValid_t)LIBRARY_GET_ADDR(capi_lib, "Core_IsAnimationLibraryValid");
    ompapi->Core.AreInteriorWeaponsAllowed = (Core_AreInteriorWeaponsAllowed_t)LIBRARY_GET_ADDR(capi_lib, "Core_AreInteriorWeaponsAllowed");
    ompapi->Core.AllowInteriorWeapons = (Core_AllowInteriorWeapons_t)LIBRARY_GET_ADDR(capi_lib, "Core_AllowInteriorWeapons");
    ompapi->Core.BlockIpAddress = (Core_BlockIpAddress_t)LIBRARY_GET_ADDR(capi_lib, "Core_BlockIpAddress");
    ompapi->Core.UnBlockIpAddress = (Core_UnBlockIpAddress_t)LIBRARY_GET_ADDR(capi_lib, "Core_UnBlockIpAddress");
    ompapi->Core.DisableEntryExitMarkers = (Core_DisableEntryExitMarkers_t)LIBRARY_GET_ADDR(capi_lib, "Core_DisableEntryExitMarkers");
    ompapi->Core.DisableNameTagsLOS = (Core_DisableNameTagsLOS_t)LIBRARY_GET_ADDR(capi_lib, "Core_DisableNameTagsLOS");
    ompapi->Core.EnableZoneNames = (Core_EnableZoneNames_t)LIBRARY_GET_ADDR(capi_lib, "Core_EnableZoneNames");
    ompapi->Core.ShowGameTextForAll = (Core_ShowGameTextForAll_t)LIBRARY_GET_ADDR(capi_lib, "Core_ShowGameTextForAll");
    ompapi->Core.HideGameTextForAll = (Core_HideGameTextForAll_t)LIBRARY_GET_ADDR(capi_lib, "Core_HideGameTextForAll");
    ompapi->Core.NetworkStats = (Core_NetworkStats_t)LIBRARY_GET_ADDR(capi_lib, "Core_NetworkStats");
    ompapi->Core.ServerTickRate = (Core_ServerTickRate_t)LIBRARY_GET_ADDR(capi_lib, "Core_ServerTickRate");
    ompapi->Core.GetWeaponName = (Core_GetWeaponName_t)LIBRARY_GET_ADDR(capi_lib, "Core_GetWeaponName");
    ompapi->Core.SetChatRadius = (Core_SetChatRadius_t)LIBRARY_GET_ADDR(capi_lib, "Core_SetChatRadius");
    ompapi->Core.SetMarkerRadius = (Core_SetMarkerRadius_t)LIBRARY_GET_ADDR(capi_lib, "Core_SetMarkerRadius");
    ompapi->Core.SendRconCommand = (Core_SendRconCommand_t)LIBRARY_GET_ADDR(capi_lib, "Core_SendRconCommand");
    ompapi->Core.SetDeathDropAmount = (Core_SetDeathDropAmount_t)LIBRARY_GET_ADDR(capi_lib, "Core_SetDeathDropAmount");
    ompapi->Core.GameMode = (Core_GameMode_t)LIBRARY_GET_ADDR(capi_lib, "Core_GameMode");
    ompapi->Core.SetGravity = (Core_SetGravity_t)LIBRARY_GET_ADDR(capi_lib, "Core_SetGravity");
    ompapi->Core.GetGravity = (Core_GetGravity_t)LIBRARY_GET_ADDR(capi_lib, "Core_GetGravity");
    ompapi->Core.SetNameTagsDrawDistance = (Core_SetNameTagsDrawDistance_t)LIBRARY_GET_ADDR(capi_lib, "Core_SetNameTagsDrawDistance");
    ompapi->Core.SetWeather = (Core_SetWeather_t)LIBRARY_GET_ADDR(capi_lib, "Core_SetWeather");
    ompapi->Core.SetWorldTime = (Core_SetWorldTime_t)LIBRARY_GET_ADDR(capi_lib, "Core_SetWorldTime");
    ompapi->Core.ShowNameTags = (Core_ShowNameTags_t)LIBRARY_GET_ADDR(capi_lib, "Core_ShowNameTags");
    ompapi->Core.ShowPlayerMarkers = (Core_ShowPlayerMarkers_t)LIBRARY_GET_ADDR(capi_lib, "Core_ShowPlayerMarkers");
    ompapi->Core.UsePedAnims = (Core_UsePedAnims_t)LIBRARY_GET_ADDR(capi_lib, "Core_UsePedAnims");
    ompapi->Core.GetWeather = (Core_GetWeather_t)LIBRARY_GET_ADDR(capi_lib, "Core_GetWeather");
    ompapi->Core.GetWorldTime = (Core_GetWorldTime_t)LIBRARY_GET_ADDR(capi_lib, "Core_GetWorldTime");
    ompapi->Core.ToggleChatTextReplacement = (Core_ToggleChatTextReplacement_t)LIBRARY_GET_ADDR(capi_lib, "Core_ToggleChatTextReplacement");
    ompapi->Core.IsChatTextReplacementToggled = (Core_IsChatTextReplacementToggled_t)LIBRARY_GET_ADDR(capi_lib, "Core_IsChatTextReplacementToggled");
    ompapi->Core.IsNickNameValid = (Core_IsNickNameValid_t)LIBRARY_GET_ADDR(capi_lib, "Core_IsNickNameValid");
    ompapi->Core.AllowNickNameCharacter = (Core_AllowNickNameCharacter_t)LIBRARY_GET_ADDR(capi_lib, "Core_AllowNickNameCharacter");
    ompapi->Core.IsNickNameCharacterAllowed = (Core_IsNickNameCharacterAllowed_t)LIBRARY_GET_ADDR(capi_lib, "Core_IsNickNameCharacterAllowed");
    ompapi->Core.ClearBanList = (Core_ClearBanList_t)LIBRARY_GET_ADDR(capi_lib, "Core_ClearBanList");
    ompapi->Core.IsIpAddressBanned = (Core_IsIpAddressBanned_t)LIBRARY_GET_ADDR(capi_lib, "Core_IsIpAddressBanned");
    ompapi->Core.GetWeaponSlot = (Core_GetWeaponSlot_t)LIBRARY_GET_ADDR(capi_lib, "Core_GetWeaponSlot");
    ompapi->Core.AddRule = (Core_AddRule_t)LIBRARY_GET_ADDR(capi_lib, "Core_AddRule");
    ompapi->Core.IsValidRule = (Core_IsValidRule_t)LIBRARY_GET_ADDR(capi_lib, "Core_IsValidRule");
    ompapi->Core.RemoveRule = (Core_RemoveRule_t)LIBRARY_GET_ADDR(capi_lib, "Core_RemoveRule");

    // Retrieve NPC functions
    ompapi->NPC.Connect = (NPC_Connect_t)LIBRARY_GET_ADDR(capi_lib, "NPC_Connect");

    // Retrieve CustomModel functions
    ompapi->CustomModel.AddCharModel = (CustomModel_AddCharModel_t)LIBRARY_GET_ADDR(capi_lib, "CustomModel_AddCharModel");
    ompapi->CustomModel.AddSimpleModel = (CustomModel_AddSimpleModel_t)LIBRARY_GET_ADDR(capi_lib, "CustomModel_AddSimpleModel");
    ompapi->CustomModel.AddSimpleModelTimed = (CustomModel_AddSimpleModelTimed_t)LIBRARY_GET_ADDR(capi_lib, "CustomModel_AddSimpleModelTimed");
    ompapi->CustomModel.RedirectDownload = (CustomModel_RedirectDownload_t)LIBRARY_GET_ADDR(capi_lib, "CustomModel_RedirectDownload");
    ompapi->CustomModel.FindModelFileNameFromCRC = (CustomModel_FindModelFileNameFromCRC_t)LIBRARY_GET_ADDR(capi_lib, "CustomModel_FindModelFileNameFromCRC");
    ompapi->CustomModel.IsValid = (CustomModel_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "CustomModel_IsValid");
    ompapi->CustomModel.GetPath = (CustomModel_GetPath_t)LIBRARY_GET_ADDR(capi_lib, "CustomModel_GetPath");

    // Retrieve Dialog functions
    ompapi->Dialog.Show = (Dialog_Show_t)LIBRARY_GET_ADDR(capi_lib, "Dialog_Show");
    ompapi->Dialog.Hide = (Dialog_Hide_t)LIBRARY_GET_ADDR(capi_lib, "Dialog_Hide");

    // Retrieve Event functions
    ompapi->Event.AddHandler = (Event_AddHandler_t)LIBRARY_GET_ADDR(capi_lib, "Event_AddHandler");
    ompapi->Event.RemoveHandler = (Event_RemoveHandler_t)LIBRARY_GET_ADDR(capi_lib, "Event_RemoveHandler");
    ompapi->Event.RemoveAllHandlers = (Event_RemoveAllHandlers_t)LIBRARY_GET_ADDR(capi_lib, "Event_RemoveAllHandlers");

    // Retrieve GangZone functions
    ompapi->GangZone.Create = (GangZone_Create_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_Create");
    ompapi->GangZone.Destroy = (GangZone_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_Destroy");
    ompapi->GangZone.FromID = (GangZone_FromID_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_FromID");
    ompapi->GangZone.GetID = (GangZone_GetID_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_GetID");
    ompapi->GangZone.ShowForPlayer = (GangZone_ShowForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_ShowForPlayer");
    ompapi->GangZone.ShowForAll = (GangZone_ShowForAll_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_ShowForAll");
    ompapi->GangZone.HideForPlayer = (GangZone_HideForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_HideForPlayer");
    ompapi->GangZone.HideForAll = (GangZone_HideForAll_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_HideForAll");
    ompapi->GangZone.FlashForPlayer = (GangZone_FlashForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_FlashForPlayer");
    ompapi->GangZone.FlashForAll = (GangZone_FlashForAll_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_FlashForAll");
    ompapi->GangZone.StopFlashForPlayer = (GangZone_StopFlashForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_StopFlashForPlayer");
    ompapi->GangZone.StopFlashForAll = (GangZone_StopFlashForAll_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_StopFlashForAll");
    ompapi->GangZone.IsValid = (GangZone_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_IsValid");
    ompapi->GangZone.IsPlayerIn = (GangZone_IsPlayerIn_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_IsPlayerIn");
    ompapi->GangZone.IsVisibleForPlayer = (GangZone_IsVisibleForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_IsVisibleForPlayer");
    ompapi->GangZone.GetColorForPlayer = (GangZone_GetColorForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_GetColorForPlayer");
    ompapi->GangZone.GetFlashColorForPlayer = (GangZone_GetFlashColorForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_GetFlashColorForPlayer");
    ompapi->GangZone.IsFlashingForPlayer = (GangZone_IsFlashingForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_IsFlashingForPlayer");
    ompapi->GangZone.GetPos = (GangZone_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_GetPos");
    ompapi->GangZone.UseCheck = (GangZone_UseCheck_t)LIBRARY_GET_ADDR(capi_lib, "GangZone_UseCheck");

    // Retrieve Menu functions
    ompapi->Menu.Create = (Menu_Create_t)LIBRARY_GET_ADDR(capi_lib, "Menu_Create");
    ompapi->Menu.Destroy = (Menu_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "Menu_Destroy");
    ompapi->Menu.FromID = (Menu_FromID_t)LIBRARY_GET_ADDR(capi_lib, "Menu_FromID");
    ompapi->Menu.GetID = (Menu_GetID_t)LIBRARY_GET_ADDR(capi_lib, "Menu_GetID");
    ompapi->Menu.AddItem = (Menu_AddItem_t)LIBRARY_GET_ADDR(capi_lib, "Menu_AddItem");
    ompapi->Menu.SetColumnHeader = (Menu_SetColumnHeader_t)LIBRARY_GET_ADDR(capi_lib, "Menu_SetColumnHeader");
    ompapi->Menu.ShowForPlayer = (Menu_ShowForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Menu_ShowForPlayer");
    ompapi->Menu.HideForPlayer = (Menu_HideForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Menu_HideForPlayer");
    ompapi->Menu.Disable = (Menu_Disable_t)LIBRARY_GET_ADDR(capi_lib, "Menu_Disable");
    ompapi->Menu.DisableRow = (Menu_DisableRow_t)LIBRARY_GET_ADDR(capi_lib, "Menu_DisableRow");
    ompapi->Menu.IsValid = (Menu_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "Menu_IsValid");
    ompapi->Menu.IsDisabled = (Menu_IsDisabled_t)LIBRARY_GET_ADDR(capi_lib, "Menu_IsDisabled");
    ompapi->Menu.IsRowDisabled = (Menu_IsRowDisabled_t)LIBRARY_GET_ADDR(capi_lib, "Menu_IsRowDisabled");
    ompapi->Menu.GetColumns = (Menu_GetColumns_t)LIBRARY_GET_ADDR(capi_lib, "Menu_GetColumns");
    ompapi->Menu.GetItems = (Menu_GetItems_t)LIBRARY_GET_ADDR(capi_lib, "Menu_GetItems");
    ompapi->Menu.GetPos = (Menu_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "Menu_GetPos");
    ompapi->Menu.GetColumnWidth = (Menu_GetColumnWidth_t)LIBRARY_GET_ADDR(capi_lib, "Menu_GetColumnWidth");
    ompapi->Menu.GetColumnHeader = (Menu_GetColumnHeader_t)LIBRARY_GET_ADDR(capi_lib, "Menu_GetColumnHeader");
    ompapi->Menu.GetItem = (Menu_GetItem_t)LIBRARY_GET_ADDR(capi_lib, "Menu_GetItem");

    // Retrieve Object functions
    ompapi->Object.Create = (Object_Create_t)LIBRARY_GET_ADDR(capi_lib, "Object_Create");
    ompapi->Object.Destroy = (Object_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "Object_Destroy");
    ompapi->Object.FromID = (Object_FromID_t)LIBRARY_GET_ADDR(capi_lib, "Object_FromID");
    ompapi->Object.GetID = (Object_GetID_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetID");
    ompapi->Object.AttachToVehicle = (Object_AttachToVehicle_t)LIBRARY_GET_ADDR(capi_lib, "Object_AttachToVehicle");
    ompapi->Object.AttachToObject = (Object_AttachToObject_t)LIBRARY_GET_ADDR(capi_lib, "Object_AttachToObject");
    ompapi->Object.AttachToPlayer = (Object_AttachToPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Object_AttachToPlayer");
    ompapi->Object.SetPos = (Object_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "Object_SetPos");
    ompapi->Object.GetPos = (Object_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetPos");
    ompapi->Object.SetRot = (Object_SetRot_t)LIBRARY_GET_ADDR(capi_lib, "Object_SetRot");
    ompapi->Object.GetRot = (Object_GetRot_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetRot");
    ompapi->Object.GetModel = (Object_GetModel_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetModel");
    ompapi->Object.SetNoCameraCollision = (Object_SetNoCameraCollision_t)LIBRARY_GET_ADDR(capi_lib, "Object_SetNoCameraCollision");
    ompapi->Object.IsValid = (Object_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "Object_IsValid");
    ompapi->Object.Move = (Object_Move_t)LIBRARY_GET_ADDR(capi_lib, "Object_Move");
    ompapi->Object.Stop = (Object_Stop_t)LIBRARY_GET_ADDR(capi_lib, "Object_Stop");
    ompapi->Object.IsMoving = (Object_IsMoving_t)LIBRARY_GET_ADDR(capi_lib, "Object_IsMoving");
    ompapi->Object.BeginEditing = (Object_BeginEditing_t)LIBRARY_GET_ADDR(capi_lib, "Object_BeginEditing");
    ompapi->Object.BeginSelecting = (Object_BeginSelecting_t)LIBRARY_GET_ADDR(capi_lib, "Object_BeginSelecting");
    ompapi->Object.EndEditing = (Object_EndEditing_t)LIBRARY_GET_ADDR(capi_lib, "Object_EndEditing");
    ompapi->Object.SetMaterial = (Object_SetMaterial_t)LIBRARY_GET_ADDR(capi_lib, "Object_SetMaterial");
    ompapi->Object.SetMaterialText = (Object_SetMaterialText_t)LIBRARY_GET_ADDR(capi_lib, "Object_SetMaterialText");
    ompapi->Object.SetDefaultCameraCollision = (Object_SetDefaultCameraCollision_t)LIBRARY_GET_ADDR(capi_lib, "Object_SetDefaultCameraCollision");
    ompapi->Object.GetDrawDistance = (Object_GetDrawDistance_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetDrawDistance");
    ompapi->Object.GetMoveSpeed = (Object_GetMoveSpeed_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetMoveSpeed");
    ompapi->Object.GetMovingTargetPos = (Object_GetMovingTargetPos_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetMovingTargetPos");
    ompapi->Object.GetMovingTargetRot = (Object_GetMovingTargetRot_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetMovingTargetRot");
    ompapi->Object.GetAttachedData = (Object_GetAttachedData_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetAttachedData");
    ompapi->Object.GetAttachedOffset = (Object_GetAttachedOffset_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetAttachedOffset");
    ompapi->Object.GetSyncRotation = (Object_GetSyncRotation_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetSyncRotation");
    ompapi->Object.IsMaterialSlotUsed = (Object_IsMaterialSlotUsed_t)LIBRARY_GET_ADDR(capi_lib, "Object_IsMaterialSlotUsed");
    ompapi->Object.GetMaterial = (Object_GetMaterial_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetMaterial");
    ompapi->Object.GetMaterialText = (Object_GetMaterialText_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetMaterialText");
    ompapi->Object.IsObjectNoCameraCollision = (Object_IsObjectNoCameraCollision_t)LIBRARY_GET_ADDR(capi_lib, "Object_IsObjectNoCameraCollision");
    ompapi->Object.GetType = (Object_GetType_t)LIBRARY_GET_ADDR(capi_lib, "Object_GetType");

    // Retrieve PlayerObject functions
    ompapi->PlayerObject.Create = (PlayerObject_Create_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_Create");
    ompapi->PlayerObject.Destroy = (PlayerObject_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_Destroy");
    ompapi->PlayerObject.FromID = (PlayerObject_FromID_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_FromID");
    ompapi->PlayerObject.GetID = (PlayerObject_GetID_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetID");
    ompapi->PlayerObject.AttachToVehicle = (PlayerObject_AttachToVehicle_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_AttachToVehicle");
    ompapi->PlayerObject.AttachToPlayer = (PlayerObject_AttachToPlayer_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_AttachToPlayer");
    ompapi->PlayerObject.AttachToObject = (PlayerObject_AttachToObject_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_AttachToObject");
    ompapi->PlayerObject.SetPos = (PlayerObject_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_SetPos");
    ompapi->PlayerObject.GetPos = (PlayerObject_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetPos");
    ompapi->PlayerObject.SetRot = (PlayerObject_SetRot_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_SetRot");
    ompapi->PlayerObject.GetRot = (PlayerObject_GetRot_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetRot");
    ompapi->PlayerObject.GetModel = (PlayerObject_GetModel_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetModel");
    ompapi->PlayerObject.SetNoCameraCollision = (PlayerObject_SetNoCameraCollision_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_SetNoCameraCollision");
    ompapi->PlayerObject.IsValid = (PlayerObject_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_IsValid");
    ompapi->PlayerObject.Move = (PlayerObject_Move_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_Move");
    ompapi->PlayerObject.Stop = (PlayerObject_Stop_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_Stop");
    ompapi->PlayerObject.IsMoving = (PlayerObject_IsMoving_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_IsMoving");
    ompapi->PlayerObject.BeginEditing = (PlayerObject_BeginEditing_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_BeginEditing");
    ompapi->PlayerObject.SetMaterial = (PlayerObject_SetMaterial_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_SetMaterial");
    ompapi->PlayerObject.SetMaterialText = (PlayerObject_SetMaterialText_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_SetMaterialText");
    ompapi->PlayerObject.GetDrawDistance = (PlayerObject_GetDrawDistance_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetDrawDistance");
    ompapi->PlayerObject.GetMoveSpeed = (PlayerObject_GetMoveSpeed_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetMoveSpeed");
    ompapi->PlayerObject.GetMovingTargetPos = (PlayerObject_GetMovingTargetPos_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetMovingTargetPos");
    ompapi->PlayerObject.GetMovingTargetRot = (PlayerObject_GetMovingTargetRot_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetMovingTargetRot");
    ompapi->PlayerObject.GetAttachedData = (PlayerObject_GetAttachedData_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetAttachedData");
    ompapi->PlayerObject.GetAttachedOffset = (PlayerObject_GetAttachedOffset_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetAttachedOffset");
    ompapi->PlayerObject.GetSyncRotation = (PlayerObject_GetSyncRotation_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetSyncRotation");
    ompapi->PlayerObject.IsMaterialSlotUsed = (PlayerObject_IsMaterialSlotUsed_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_IsMaterialSlotUsed");
    ompapi->PlayerObject.GetMaterial = (PlayerObject_GetMaterial_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetMaterial");
    ompapi->PlayerObject.GetMaterialText = (PlayerObject_GetMaterialText_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_GetMaterialText");
    ompapi->PlayerObject.IsNoCameraCollision = (PlayerObject_IsNoCameraCollision_t)LIBRARY_GET_ADDR(capi_lib, "PlayerObject_IsNoCameraCollision");

    // Retrieve Pickup functions
    ompapi->Pickup.Create = (Pickup_Create_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_Create");
    ompapi->Pickup.AddStatic = (Pickup_AddStatic_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_AddStatic");
    ompapi->Pickup.Destroy = (Pickup_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_Destroy");
    ompapi->Pickup.FromID = (Pickup_FromID_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_FromID");
    ompapi->Pickup.GetID = (Pickup_GetID_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_GetID");
    ompapi->Pickup.IsValid = (Pickup_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_IsValid");
    ompapi->Pickup.IsStreamedIn = (Pickup_IsStreamedIn_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_IsStreamedIn");
    ompapi->Pickup.GetPos = (Pickup_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_GetPos");
    ompapi->Pickup.GetModel = (Pickup_GetModel_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_GetModel");
    ompapi->Pickup.GetType = (Pickup_GetType_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_GetType");
    ompapi->Pickup.GetVirtualWorld = (Pickup_GetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_GetVirtualWorld");
    ompapi->Pickup.SetPos = (Pickup_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_SetPos");
    ompapi->Pickup.SetModel = (Pickup_SetModel_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_SetModel");
    ompapi->Pickup.SetType = (Pickup_SetType_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_SetType");
    ompapi->Pickup.SetVirtualWorld = (Pickup_SetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_SetVirtualWorld");
    ompapi->Pickup.ShowForPlayer = (Pickup_ShowForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_ShowForPlayer");
    ompapi->Pickup.HideForPlayer = (Pickup_HideForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_HideForPlayer");
    ompapi->Pickup.IsHiddenForPlayer = (Pickup_IsHiddenForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Pickup_IsHiddenForPlayer");

    // Retrieve All functions
    ompapi->All.SendClientMessage = (All_SendClientMessage_t)LIBRARY_GET_ADDR(capi_lib, "All_SendClientMessage");
    ompapi->All.CreateExplosion = (All_CreateExplosion_t)LIBRARY_GET_ADDR(capi_lib, "All_CreateExplosion");
    ompapi->All.SendDeathMessage = (All_SendDeathMessage_t)LIBRARY_GET_ADDR(capi_lib, "All_SendDeathMessage");
    ompapi->All.EnableStuntBonus = (All_EnableStuntBonus_t)LIBRARY_GET_ADDR(capi_lib, "All_EnableStuntBonus");

    // Retrieve Recording functions
    ompapi->Recording.Start = (Recording_Start_t)LIBRARY_GET_ADDR(capi_lib, "Recording_Start");
    ompapi->Recording.Stop = (Recording_Stop_t)LIBRARY_GET_ADDR(capi_lib, "Recording_Stop");

    // Retrieve TextDraw functions
    ompapi->TextDraw.Create = (TextDraw_Create_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_Create");
    ompapi->TextDraw.Destroy = (TextDraw_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_Destroy");
    ompapi->TextDraw.FromID = (TextDraw_FromID_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_FromID");
    ompapi->TextDraw.GetID = (TextDraw_GetID_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetID");
    ompapi->TextDraw.IsValid = (TextDraw_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_IsValid");
    ompapi->TextDraw.IsVisibleForPlayer = (TextDraw_IsVisibleForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_IsVisibleForPlayer");
    ompapi->TextDraw.SetLetterSize = (TextDraw_SetLetterSize_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetLetterSize");
    ompapi->TextDraw.SetTextSize = (TextDraw_SetTextSize_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetTextSize");
    ompapi->TextDraw.SetAlignment = (TextDraw_SetAlignment_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetAlignment");
    ompapi->TextDraw.SetColor = (TextDraw_SetColor_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetColor");
    ompapi->TextDraw.SetUseBox = (TextDraw_SetUseBox_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetUseBox");
    ompapi->TextDraw.SetBoxColor = (TextDraw_SetBoxColor_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetBoxColor");
    ompapi->TextDraw.SetShadow = (TextDraw_SetShadow_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetShadow");
    ompapi->TextDraw.SetOutline = (TextDraw_SetOutline_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetOutline");
    ompapi->TextDraw.SetBackgroundColor = (TextDraw_SetBackgroundColor_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetBackgroundColor");
    ompapi->TextDraw.SetFont = (TextDraw_SetFont_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetFont");
    ompapi->TextDraw.SetSetProportional = (TextDraw_SetSetProportional_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetSetProportional");
    ompapi->TextDraw.SetSelectable = (TextDraw_SetSelectable_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetSelectable");
    ompapi->TextDraw.ShowForPlayer = (TextDraw_ShowForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_ShowForPlayer");
    ompapi->TextDraw.HideForPlayer = (TextDraw_HideForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_HideForPlayer");
    ompapi->TextDraw.ShowForAll = (TextDraw_ShowForAll_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_ShowForAll");
    ompapi->TextDraw.HideForAll = (TextDraw_HideForAll_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_HideForAll");
    ompapi->TextDraw.SetString = (TextDraw_SetString_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetString");
    ompapi->TextDraw.SetPreviewModel = (TextDraw_SetPreviewModel_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetPreviewModel");
    ompapi->TextDraw.SetPreviewRot = (TextDraw_SetPreviewRot_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetPreviewRot");
    ompapi->TextDraw.SetPreviewVehCol = (TextDraw_SetPreviewVehCol_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetPreviewVehCol");
    ompapi->TextDraw.SetPos = (TextDraw_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetPos");
    ompapi->TextDraw.GetString = (TextDraw_GetString_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetString");
    ompapi->TextDraw.GetLetterSize = (TextDraw_GetLetterSize_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetLetterSize");
    ompapi->TextDraw.GetTextSize = (TextDraw_GetTextSize_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetTextSize");
    ompapi->TextDraw.GetPos = (TextDraw_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetPos");
    ompapi->TextDraw.GetColor = (TextDraw_GetColor_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetColor");
    ompapi->TextDraw.GetBoxColor = (TextDraw_GetBoxColor_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetBoxColor");
    ompapi->TextDraw.GetBackgroundColor = (TextDraw_GetBackgroundColor_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetBackgroundColor");
    ompapi->TextDraw.GetShadow = (TextDraw_GetShadow_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetShadow");
    ompapi->TextDraw.GetOutline = (TextDraw_GetOutline_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetOutline");
    ompapi->TextDraw.GetFont = (TextDraw_GetFont_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetFont");
    ompapi->TextDraw.IsBox = (TextDraw_IsBox_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_IsBox");
    ompapi->TextDraw.IsProportional = (TextDraw_IsProportional_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_IsProportional");
    ompapi->TextDraw.IsSelectable = (TextDraw_IsSelectable_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_IsSelectable");
    ompapi->TextDraw.GetAlignment = (TextDraw_GetAlignment_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetAlignment");
    ompapi->TextDraw.GetPreviewModel = (TextDraw_GetPreviewModel_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetPreviewModel");
    ompapi->TextDraw.GetPreviewRot = (TextDraw_GetPreviewRot_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetPreviewRot");
    ompapi->TextDraw.GetPreviewVehColor = (TextDraw_GetPreviewVehColor_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_GetPreviewVehColor");
    ompapi->TextDraw.SetStringForPlayer = (TextDraw_SetStringForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "TextDraw_SetStringForPlayer");

    // Retrieve PlayerTextDraw functions
    ompapi->PlayerTextDraw.Create = (PlayerTextDraw_Create_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_Create");
    ompapi->PlayerTextDraw.Destroy = (PlayerTextDraw_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_Destroy");
    ompapi->PlayerTextDraw.FromID = (PlayerTextDraw_FromID_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_FromID");
    ompapi->PlayerTextDraw.GetID = (PlayerTextDraw_GetID_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetID");
    ompapi->PlayerTextDraw.IsValid = (PlayerTextDraw_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_IsValid");
    ompapi->PlayerTextDraw.IsVisible = (PlayerTextDraw_IsVisible_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_IsVisible");
    ompapi->PlayerTextDraw.SetLetterSize = (PlayerTextDraw_SetLetterSize_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetLetterSize");
    ompapi->PlayerTextDraw.SetTextSize = (PlayerTextDraw_SetTextSize_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetTextSize");
    ompapi->PlayerTextDraw.SetAlignment = (PlayerTextDraw_SetAlignment_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetAlignment");
    ompapi->PlayerTextDraw.SetColor = (PlayerTextDraw_SetColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetColor");
    ompapi->PlayerTextDraw.UseBox = (PlayerTextDraw_UseBox_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_UseBox");
    ompapi->PlayerTextDraw.SetBoxColor = (PlayerTextDraw_SetBoxColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetBoxColor");
    ompapi->PlayerTextDraw.SetShadow = (PlayerTextDraw_SetShadow_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetShadow");
    ompapi->PlayerTextDraw.SetOutline = (PlayerTextDraw_SetOutline_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetOutline");
    ompapi->PlayerTextDraw.SetBackgroundColor = (PlayerTextDraw_SetBackgroundColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetBackgroundColor");
    ompapi->PlayerTextDraw.SetFont = (PlayerTextDraw_SetFont_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetFont");
    ompapi->PlayerTextDraw.SetProportional = (PlayerTextDraw_SetProportional_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetProportional");
    ompapi->PlayerTextDraw.SetSelectable = (PlayerTextDraw_SetSelectable_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetSelectable");
    ompapi->PlayerTextDraw.Show = (PlayerTextDraw_Show_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_Show");
    ompapi->PlayerTextDraw.Hide = (PlayerTextDraw_Hide_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_Hide");
    ompapi->PlayerTextDraw.SetString = (PlayerTextDraw_SetString_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetString");
    ompapi->PlayerTextDraw.SetPreviewModel = (PlayerTextDraw_SetPreviewModel_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetPreviewModel");
    ompapi->PlayerTextDraw.SetPreviewRot = (PlayerTextDraw_SetPreviewRot_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetPreviewRot");
    ompapi->PlayerTextDraw.SetPreviewVehCol = (PlayerTextDraw_SetPreviewVehCol_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetPreviewVehCol");
    ompapi->PlayerTextDraw.SetPos = (PlayerTextDraw_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_SetPos");
    ompapi->PlayerTextDraw.GetString = (PlayerTextDraw_GetString_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetString");
    ompapi->PlayerTextDraw.GetLetterSize = (PlayerTextDraw_GetLetterSize_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetLetterSize");
    ompapi->PlayerTextDraw.GetTextSize = (PlayerTextDraw_GetTextSize_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetTextSize");
    ompapi->PlayerTextDraw.GetPos = (PlayerTextDraw_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetPos");
    ompapi->PlayerTextDraw.GetColor = (PlayerTextDraw_GetColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetColor");
    ompapi->PlayerTextDraw.GetBoxColor = (PlayerTextDraw_GetBoxColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetBoxColor");
    ompapi->PlayerTextDraw.GetBackgroundColor = (PlayerTextDraw_GetBackgroundColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetBackgroundColor");
    ompapi->PlayerTextDraw.GetShadow = (PlayerTextDraw_GetShadow_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetShadow");
    ompapi->PlayerTextDraw.GetOutline = (PlayerTextDraw_GetOutline_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetOutline");
    ompapi->PlayerTextDraw.GetFont = (PlayerTextDraw_GetFont_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetFont");
    ompapi->PlayerTextDraw.IsBox = (PlayerTextDraw_IsBox_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_IsBox");
    ompapi->PlayerTextDraw.IsProportional = (PlayerTextDraw_IsProportional_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_IsProportional");
    ompapi->PlayerTextDraw.IsSelectable = (PlayerTextDraw_IsSelectable_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_IsSelectable");
    ompapi->PlayerTextDraw.GetAlignment = (PlayerTextDraw_GetAlignment_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetAlignment");
    ompapi->PlayerTextDraw.GetPreviewModel = (PlayerTextDraw_GetPreviewModel_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetPreviewModel");
    ompapi->PlayerTextDraw.GetPreviewRot = (PlayerTextDraw_GetPreviewRot_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetPreviewRot");
    ompapi->PlayerTextDraw.GetPreviewVehColor = (PlayerTextDraw_GetPreviewVehColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextDraw_GetPreviewVehColor");

    // Retrieve TextLabel functions
    ompapi->TextLabel.Create = (TextLabel_Create_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_Create");
    ompapi->TextLabel.Destroy = (TextLabel_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_Destroy");
    ompapi->TextLabel.FromID = (TextLabel_FromID_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_FromID");
    ompapi->TextLabel.GetID = (TextLabel_GetID_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetID");
    ompapi->TextLabel.AttachToPlayer = (TextLabel_AttachToPlayer_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_AttachToPlayer");
    ompapi->TextLabel.AttachToVehicle = (TextLabel_AttachToVehicle_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_AttachToVehicle");
    ompapi->TextLabel.UpdateText = (TextLabel_UpdateText_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_UpdateText");
    ompapi->TextLabel.IsValid = (TextLabel_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_IsValid");
    ompapi->TextLabel.IsStreamedIn = (TextLabel_IsStreamedIn_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_IsStreamedIn");
    ompapi->TextLabel.GetText = (TextLabel_GetText_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetText");
    ompapi->TextLabel.GetColor = (TextLabel_GetColor_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetColor");
    ompapi->TextLabel.GetPos = (TextLabel_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetPos");
    ompapi->TextLabel.SetDrawDistance = (TextLabel_SetDrawDistance_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_SetDrawDistance");
    ompapi->TextLabel.GetDrawDistance = (TextLabel_GetDrawDistance_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetDrawDistance");
    ompapi->TextLabel.GetLOS = (TextLabel_GetLOS_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetLOS");
    ompapi->TextLabel.SetLOS = (TextLabel_SetLOS_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_SetLOS");
    ompapi->TextLabel.GetVirtualWorld = (TextLabel_GetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetVirtualWorld");
    ompapi->TextLabel.SetVirtualWorld = (TextLabel_SetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_SetVirtualWorld");
    ompapi->TextLabel.GetAttachedData = (TextLabel_GetAttachedData_t)LIBRARY_GET_ADDR(capi_lib, "TextLabel_GetAttachedData");

    // Retrieve PlayerTextLabel functions
    ompapi->PlayerTextLabel.Create = (PlayerTextLabel_Create_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_Create");
    ompapi->PlayerTextLabel.Destroy = (PlayerTextLabel_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_Destroy");
    ompapi->PlayerTextLabel.FromID = (PlayerTextLabel_FromID_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_FromID");
    ompapi->PlayerTextLabel.GetID = (PlayerTextLabel_GetID_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetID");
    ompapi->PlayerTextLabel.UpdateText = (PlayerTextLabel_UpdateText_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_UpdateText");
    ompapi->PlayerTextLabel.IsValid = (PlayerTextLabel_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_IsValid");
    ompapi->PlayerTextLabel.GetText = (PlayerTextLabel_GetText_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetText");
    ompapi->PlayerTextLabel.GetColor = (PlayerTextLabel_GetColor_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetColor");
    ompapi->PlayerTextLabel.GetPos = (PlayerTextLabel_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetPos");
    ompapi->PlayerTextLabel.SetDrawDistance = (PlayerTextLabel_SetDrawDistance_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_SetDrawDistance");
    ompapi->PlayerTextLabel.GetDrawDistance = (PlayerTextLabel_GetDrawDistance_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetDrawDistance");
    ompapi->PlayerTextLabel.GetLOS = (PlayerTextLabel_GetLOS_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetLOS");
    ompapi->PlayerTextLabel.SetLOS = (PlayerTextLabel_SetLOS_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_SetLOS");
    ompapi->PlayerTextLabel.GetVirtualWorld = (PlayerTextLabel_GetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetVirtualWorld");
    ompapi->PlayerTextLabel.GetAttachedData = (PlayerTextLabel_GetAttachedData_t)LIBRARY_GET_ADDR(capi_lib, "PlayerTextLabel_GetAttachedData");

    // Retrieve Vehicle functions
    ompapi->Vehicle.Create = (Vehicle_Create_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_Create");
    ompapi->Vehicle.Destroy = (Vehicle_Destroy_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_Destroy");
    ompapi->Vehicle.FromID = (Vehicle_FromID_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_FromID");
    ompapi->Vehicle.GetID = (Vehicle_GetID_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetID");
    ompapi->Vehicle.GetMaxPassengerSeats = (Vehicle_GetMaxPassengerSeats_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetMaxPassengerSeats");
    ompapi->Vehicle.IsStreamedIn = (Vehicle_IsStreamedIn_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_IsStreamedIn");
    ompapi->Vehicle.GetPos = (Vehicle_GetPos_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetPos");
    ompapi->Vehicle.SetPos = (Vehicle_SetPos_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetPos");
    ompapi->Vehicle.GetZAngle = (Vehicle_GetZAngle_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetZAngle");
    ompapi->Vehicle.GetRotationQuat = (Vehicle_GetRotationQuat_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetRotationQuat");
    ompapi->Vehicle.GetDistanceFromPoint = (Vehicle_GetDistanceFromPoint_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetDistanceFromPoint");
    ompapi->Vehicle.SetZAngle = (Vehicle_SetZAngle_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetZAngle");
    ompapi->Vehicle.SetParamsForPlayer = (Vehicle_SetParamsForPlayer_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetParamsForPlayer");
    ompapi->Vehicle.UseManualEngineAndLights = (Vehicle_UseManualEngineAndLights_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_UseManualEngineAndLights");
    ompapi->Vehicle.SetParamsEx = (Vehicle_SetParamsEx_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetParamsEx");
    ompapi->Vehicle.GetParamsEx = (Vehicle_GetParamsEx_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetParamsEx");
    ompapi->Vehicle.GetParamsSirenState = (Vehicle_GetParamsSirenState_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetParamsSirenState");
    ompapi->Vehicle.SetParamsCarDoors = (Vehicle_SetParamsCarDoors_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetParamsCarDoors");
    ompapi->Vehicle.GetParamsCarDoors = (Vehicle_GetParamsCarDoors_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetParamsCarDoors");
    ompapi->Vehicle.SetParamsCarWindows = (Vehicle_SetParamsCarWindows_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetParamsCarWindows");
    ompapi->Vehicle.GetParamsCarWindows = (Vehicle_GetParamsCarWindows_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetParamsCarWindows");
    ompapi->Vehicle.SetToRespawn = (Vehicle_SetToRespawn_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetToRespawn");
    ompapi->Vehicle.LinkToInterior = (Vehicle_LinkToInterior_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_LinkToInterior");
    ompapi->Vehicle.AddComponent = (Vehicle_AddComponent_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_AddComponent");
    ompapi->Vehicle.RemoveComponent = (Vehicle_RemoveComponent_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_RemoveComponent");
    ompapi->Vehicle.ChangeColor = (Vehicle_ChangeColor_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_ChangeColor");
    ompapi->Vehicle.ChangePaintjob = (Vehicle_ChangePaintjob_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_ChangePaintjob");
    ompapi->Vehicle.SetHealth = (Vehicle_SetHealth_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetHealth");
    ompapi->Vehicle.GetHealth = (Vehicle_GetHealth_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetHealth");
    ompapi->Vehicle.AttachTrailer = (Vehicle_AttachTrailer_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_AttachTrailer");
    ompapi->Vehicle.DetachTrailer = (Vehicle_DetachTrailer_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_DetachTrailer");
    ompapi->Vehicle.IsTrailerAttached = (Vehicle_IsTrailerAttached_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_IsTrailerAttached");
    ompapi->Vehicle.GetTrailer = (Vehicle_GetTrailer_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetTrailer");
    ompapi->Vehicle.SetNumberPlate = (Vehicle_SetNumberPlate_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetNumberPlate");
    ompapi->Vehicle.GetModel = (Vehicle_GetModel_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetModel");
    ompapi->Vehicle.GetComponentInSlot = (Vehicle_GetComponentInSlot_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetComponentInSlot");
    ompapi->Vehicle.GetComponentType = (Vehicle_GetComponentType_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetComponentType");
    ompapi->Vehicle.CanHaveComponent = (Vehicle_CanHaveComponent_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_CanHaveComponent");
    ompapi->Vehicle.GetRandomColorPair = (Vehicle_GetRandomColorPair_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetRandomColorPair");
    ompapi->Vehicle.ColorIndexToColor = (Vehicle_ColorIndexToColor_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_ColorIndexToColor");
    ompapi->Vehicle.Repair = (Vehicle_Repair_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_Repair");
    ompapi->Vehicle.GetVelocity = (Vehicle_GetVelocity_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetVelocity");
    ompapi->Vehicle.SetVelocity = (Vehicle_SetVelocity_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetVelocity");
    ompapi->Vehicle.SetAngularVelocity = (Vehicle_SetAngularVelocity_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetAngularVelocity");
    ompapi->Vehicle.GetDamageStatus = (Vehicle_GetDamageStatus_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetDamageStatus");
    ompapi->Vehicle.UpdateDamageStatus = (Vehicle_UpdateDamageStatus_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_UpdateDamageStatus");
    ompapi->Vehicle.GetModelInfo = (Vehicle_GetModelInfo_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetModelInfo");
    ompapi->Vehicle.SetVirtualWorld = (Vehicle_SetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetVirtualWorld");
    ompapi->Vehicle.GetVirtualWorld = (Vehicle_GetVirtualWorld_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetVirtualWorld");
    ompapi->Vehicle.GetLandingGearState = (Vehicle_GetLandingGearState_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetLandingGearState");
    ompapi->Vehicle.IsValid = (Vehicle_IsValid_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_IsValid");
    ompapi->Vehicle.AddStatic = (Vehicle_AddStatic_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_AddStatic");
    ompapi->Vehicle.AddStaticEx = (Vehicle_AddStaticEx_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_AddStaticEx");
    ompapi->Vehicle.EnableFriendlyFire = (Vehicle_EnableFriendlyFire_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_EnableFriendlyFire");
    ompapi->Vehicle.GetSpawnInfo = (Vehicle_GetSpawnInfo_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetSpawnInfo");
    ompapi->Vehicle.SetSpawnInfo = (Vehicle_SetSpawnInfo_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetSpawnInfo");
    ompapi->Vehicle.GetModelCount = (Vehicle_GetModelCount_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetModelCount");
    ompapi->Vehicle.GetModelsUsed = (Vehicle_GetModelsUsed_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetModelsUsed");
    ompapi->Vehicle.GetPaintjob = (Vehicle_GetPaintjob_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetPaintjob");
    ompapi->Vehicle.GetColor = (Vehicle_GetColor_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetColor");
    ompapi->Vehicle.GetInterior = (Vehicle_GetInterior_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetInterior");
    ompapi->Vehicle.GetNumberPlate = (Vehicle_GetNumberPlate_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetNumberPlate");
    ompapi->Vehicle.SetRespawnDelay = (Vehicle_SetRespawnDelay_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetRespawnDelay");
    ompapi->Vehicle.GetRespawnDelay = (Vehicle_GetRespawnDelay_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetRespawnDelay");
    ompapi->Vehicle.GetCab = (Vehicle_GetCab_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetCab");
    ompapi->Vehicle.GetTower = (Vehicle_GetTower_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetTower");
    ompapi->Vehicle.GetOccupiedTick = (Vehicle_GetOccupiedTick_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetOccupiedTick");
    ompapi->Vehicle.GetRespawnTick = (Vehicle_GetRespawnTick_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetRespawnTick");
    ompapi->Vehicle.HasBeenOccupied = (Vehicle_HasBeenOccupied_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_HasBeenOccupied");
    ompapi->Vehicle.IsOccupied = (Vehicle_IsOccupied_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_IsOccupied");
    ompapi->Vehicle.IsDead = (Vehicle_IsDead_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_IsDead");
    ompapi->Vehicle.SetParamsSirenState = (Vehicle_SetParamsSirenState_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_SetParamsSirenState");
    ompapi->Vehicle.ToggleSirenEnabled = (Vehicle_ToggleSirenEnabled_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_ToggleSirenEnabled");
    ompapi->Vehicle.IsSirenEnabled = (Vehicle_IsSirenEnabled_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_IsSirenEnabled");
    ompapi->Vehicle.GetLastDriver = (Vehicle_GetLastDriver_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetLastDriver");
    ompapi->Vehicle.GetDriver = (Vehicle_GetDriver_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetDriver");
    ompapi->Vehicle.GetSirenState = (Vehicle_GetSirenState_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetSirenState");
    ompapi->Vehicle.GetHydraReactorAngle = (Vehicle_GetHydraReactorAngle_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetHydraReactorAngle");
    ompapi->Vehicle.GetTrainSpeed = (Vehicle_GetTrainSpeed_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetTrainSpeed");
    ompapi->Vehicle.GetMatrix = (Vehicle_GetMatrix_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetMatrix");
    ompapi->Vehicle.GetOccupant = (Vehicle_GetOccupant_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_GetOccupant");
    ompapi->Vehicle.CountOccupants = (Vehicle_CountOccupants_t)LIBRARY_GET_ADDR(capi_lib, "Vehicle_CountOccupants");

    return true;
};

#endif

#endif /* OMPCAPI_H */
