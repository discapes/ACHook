#pragma once
#include "geom.h"

typedef vec Vector3;
// Created with ReClass.NET 1.2 by KN4CK3R

class animstate
{
public:
	int anim; //0x0000
	int frame; //0x0004
	int range; //0x0008
	int basetime; //0x000C
	float speed; //0x0010
}; //Size: 0x0014

class poshist
{
public:
	int nextupdate; //0x0000
	int curpos; //0x0004
	int numpos; //0x0008
	Vector3 pos[7]; //0x000C
}; //Size: 0x0060

class playerent
{
public:
	char pad_0000[4]; //0x0000
	Vector3 o; //0x0004 physent
	Vector3 vel; //0x0010
	Vector3 vel_t; //0x001C
	Vector3 deltapos; //0x0028
	Vector3 newpos; //0x0034
	float yaw; //0x0040
	float pitch; //0x0044
	float roll; //0x0048
	float pitchvel; //0x004C
	float maxspeed; //0x0050
	int timeinair; //0x0054
	float radius; //0x0058
	float eyeheight; //0x005C
	float maxeyeheight; //0x0060
	float aboveeye; //0x0064
	bool inwater; //0x0068
	bool onfloor; //0x0069
	bool onladder; //0x006A
	bool jumpnext; //0x006B
	bool crouching; //0x006C
	bool crounchedinair; //0x006D
	bool trycrouch; //0x006E
	bool cancollide; //0x006F
	bool stuck; //0x0070
	bool scoping; //0x0071
	bool shoot; //0x0072
	char pad_0073[1]; //0x0073
	int lastjump; //0x0074
	float lastjumpheight; //0x0078
	int lastsplash; //0x007C
	char move; //0x0080
	char strafe; //0x0081
	unsigned char state; //0x0082
	unsigned char type; //0x0083
	float eyeheightvel; //0x0084
	int lastpos; //0x0088
	bool k_left; //0x008C dynent
	bool k_right; //0x008D
	bool k_up; //0x008E
	bool k_down; //0x008F
	class animstate prev[2]; //0x0090
	class animstate current[2]; //0x00B8
	int lastanimswitchtime[2]; //0x00E0
	void* lastmodel[2]; //0x00E8
	int lastrendered; //0x00F0
	char pad_00F4[4]; //0x00F4
	int health; //0x00F8 playerstate
	int armor; //0x00FC
	int primary; //0x0100
	int nextprimary; //0x0104
	int gunselect; //0x0108
	bool akimbo; //0x010C
	int ammo[10]; //0x010D
	int mag[10]; //0x0135
	int gunwait[10]; //0x015D
	int pstatshots[10]; //0x0185
	int pstatdamage[10]; //0x01AD
	char pad_01D5[3]; //0x01D5
	int curskin; //0x01D8
	int nextskin[2]; //0x01DC
	int clientnum; //0x01E4
	int lastupdate; //0x01E8
	int plag; //0x01EC
	int ping; //0x01F0
	unsigned int address; //0x01F4
	int lifesequence; //0x01F8
	int frags; //0x01FC
	int flagscore; //0x0200
	int deaths; //0x0204
	int points; //0x0208
	int tks; //0x020C
	int lastaction; //0x0210
	int lastmove; //0x0214
	int lastpain; //0x0218
	int lastvoicecom; //0x021C
	int lastdeath; //0x0220
	bool attacking; //0x0224 missing int clientrole
	char name[260]; //0x0225
	char pad_0329[3]; //0x0329
	int team; //0x032C
	int weaponchanging; //0x0330
	int nextweapon; //0x0334
	int spectatemode; //0x0338
	int followplayercn; //0x033C
	int eardamagemillis; //0x0340
	float maxroll; //0x0344
	float maxrolleffect; //0x0348
	float movroll; //0x034C
	float effroll; //0x0350
	class weapon* weapons[7]; //0x0354 should be 10
	class weapon* prevweaponsel; //0x0370
	class weapon* weaponsel; //0x0374
	class weapon* nextweaponsel; //0x0378
	class weapon* primeweap; //0x037C
	class weapon* nextprimeweap; //0x0380
	class weapon* lastattackweapon; //0x0384
	class poshist history; //0x0388
	char* skin_noteam; //0x03E8
	char* skin_cla; //0x03EC
	char* skin_rvsf; //0x03F0
	float deltayaw; //0x03F4
	float deltapitch; //0x03F8
	float newyaw; //0x03FC
	float newpitch; //0x0400
	int smoothmillis; //0x0404
	Vector3 head; //0x0408
	bool ignored; //0x0414
	bool muted; //0x0415
	bool nocorpse; //0x0416
}; //Size: 0x0417

class weapon
{
public:
	char pad_0000[4]; //0x0000
	int type; //0x0004
	class playerent* owner; //0x0008
	class guninfo* info; //0x000C
	int* ammo; //0x0010
	int* mag; //0x0014
	int* gunwait; //0x0018
	int shots; //0x001C
	int reloading; //0x0020
	int lastaction; //0x0024
}; //Size: 0x0028

class guninfo
{
public:
	char modelname[23]; //0x0000
	char title[42]; //0x0017
	short sound; //0x0041
	short reload; //0x0043
	short reloadtime; //0x0045
	short attackdelay; //0x0047
	short damage; //0x0049
	short piercing; //0x004B
	short projspeed; //0x004D
	short part; //0x004F
	short spread; //0x0051
	short recoil; //0x0053
	short magsize; //0x0055
	short mdl_kick_rot; //0x0057
	short mdl_kick_back; //0x0059
	short recoilincrease; //0x005B
	short recoilbase; //0x005D
	short maxrecoil; //0x005F
	short recoilbackfade; //0x0061
	short pushfactor; //0x0063
	char pad_0065[3]; //0x0065
	bool isauto; //0x0068
}; //Size: 0x0069