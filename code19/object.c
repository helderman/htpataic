#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "toggle.h"
static const char *tags0[] = { "east", "west", "north", "south", NULL};
static const char *tags1[] = { "field", NULL};
static const char *tags2[] = { "cave", NULL};
static const char *tags3[] = { "silver", "coin", "silver coin", NULL};
static const char *tags4[] = { "gold", "coin", "gold coin", NULL};
static const char *tags5[] = { "guard", "burly guard", NULL};
static const char *tags6[] = { "yourself", NULL};
static bool condition7(void)  { return guard->health == 0 || silver->location == guard; }
static const char *tags7[] = { "east", "entrance", NULL};
static bool condition8(void)  { return guard->health > 0 && silver->location != guard; }
static const char *tags8[] = { "east", "entrance", NULL};
static const char *tags9[] = { "west", "exit", NULL};
static const char *tags10[] = { "west", "north", "south", "forest", NULL};
static const char *tags11[] = { "east", "north", "rock", NULL};
static const char *tags12[] = { "backroom", NULL};
static const char *tags13[] = { "east", "west", "south", "rock", NULL};
static const char *tags14[] = { "south", "door", "doorway", NULL};
static const char *tags15[] = { "south", "door", "doorway", NULL};
static const char *tags16[] = { "north", "door", "doorway", NULL};
static const char *tags17[] = { "north", "door", "doorway", NULL};
static const char *tags18[] = { "box", "wooden box", NULL};
static const char *tags19[] = { "box", "wooden box", NULL};
static const char *tags20[] = { "box", "wooden box", NULL};
static const char *tags21[] = { "key", "tiny key", NULL};
static const char *tags22[] = { "lamp", NULL};
static const char *tags23[] = { "lamp", NULL};

static bool alwaysTrue(void) { return true; }

OBJECT objs[] = {
	{	/* 0 = gossipEWNS */
		alwaysTrue,
		NULL,
		tags0,
		NULL,
		NULL,
		NULL,
		"You see nothing special.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "It's just a compass direction.",
		99,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 1 = field */
		alwaysTrue,
		 "an open field",
		tags1,
		NULL,
		NULL,
		NULL,
		 "The field is a nice and quiet place under a clear blue sky.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "A lot of tourists go there.",
		99,
		 9999,
		0,
		 100,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 2 = cave */
		alwaysTrue,
		 "a little cave",
		tags2,
		NULL,
		NULL,
		NULL,
		 "The cave is just a cold, damp, rocky chamber.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "It's dark in there; bring a lamp!",
		99,
		 9999,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 3 = silver */
		alwaysTrue,
		 "a silver coin",
		tags3,
		 field,
		NULL,
		NULL,
		 "The coin has an eagle on the obverse.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "Money makes the world go round...",
		 1,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 4 = gold */
		alwaysTrue,
		 "a gold coin",
		tags4,
		 openBox,
		NULL,
		NULL,
		 "The shiny coin seems to be a rare and priceless artefact.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "Money makes the world go round...",
		 1,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 5 = guard */
		alwaysTrue,
		 "a burly guard",
		tags5,
		 field,
		NULL,
		NULL,
		 "The guard is a really big fellow.\n",
		 "He has",
		"You can't get much closer than this.\n",
		 "Easy to bribe...",
		99,
		 20,
		 100,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 6 = player */
		alwaysTrue,
		 "yourself",
		tags6,
		 field,
		NULL,
		NULL,
		 "You would need a mirror to look at yourself.\n",
		 "You have",
		"You can't get much closer than this.\n",
		 "You're not from around here, are you?",
		99,
		 20,
		 100,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 7 = intoCave */
		condition7,
		 "a cave entrance to the east",
		tags7,
		 field,
		 cave,
		 cave,
		 "The entrance is just a narrow opening in a small outcrop.\n",
		"You see",
		 "You walk into the cave.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		 isAlreadyOpen,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 8 = intoCaveBlocked */
		condition8,
		 "a cave entrance to the east",
		tags8,
		 field,
		NULL,
		 cave,
		 "The entrance is just a narrow opening in a small outcrop.\n",
		"You see",
		 "The guard stops you from walking into the cave.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		 isAlreadyOpen,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 9 = exitCave */
		alwaysTrue,
		 "an exit to the west",
		tags9,
		 cave,
		 field,
		 field,
		 "Sunlight pours in through an opening in the cave's wall.\n",
		"You see",
		 "You walk out of the cave.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		 isAlreadyOpen,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 10 = wallField */
		alwaysTrue,
		 "dense forest all around",
		tags10,
		 field,
		NULL,
		NULL,
		 "The field is surrounded by trees and undergrowth.\n",
		"You see",
		 "Dense forest is blocking the way.\n",
		 "You cannot go there, it is impenetrable.",
		99,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 11 = wallCave */
		alwaysTrue,
		 "solid rock all around",
		tags11,
		 cave,
		NULL,
		NULL,
		 "Carved in stone is a secret password 'abccb'.\n",
		"You see",
		 "Solid rock is blocking the way.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 12 = backroom */
		alwaysTrue,
		 "a backroom",
		tags12,
		NULL,
		NULL,
		NULL,
		 "The room is dusty and messy.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "There is something of value to be found there.",
		99,
		 9999,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 13 = wallBackroom */
		alwaysTrue,
		 "solid rock all around",
		tags13,
		 backroom,
		NULL,
		NULL,
		 "Trendy wallpaper covers the rock walls.\n",
		"You see",
		 "Solid rock is blocking the way.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 14 = openDoorToBackroom */
		alwaysTrue,
		 "an open door to the south",
		tags14,
		NULL,
		 backroom,
		 backroom,
		 "The door is open.\n",
		"You see",
		 "You walk through the door into a backroom.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		 isAlreadyOpen,
		 toggleBackdoor,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 15 = closedDoorToBackroom */
		alwaysTrue,
		 "a closed door to the south",
		tags15,
		 cave,
		NULL,
		 backroom,
		 "The door is closed.\n",
		"You see",
		 "The door is closed.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		 toggleBackdoor,
		 isAlreadyClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 16 = openDoorToCave */
		alwaysTrue,
		 "an open door to the north",
		tags16,
		NULL,
		 cave,
		 cave,
		 "The door is open.\n",
		"You see",
		 "You walk through the door into the cave.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		 isAlreadyOpen,
		 toggleBackdoor,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 17 = closedDoorToCave */
		alwaysTrue,
		 "a closed door to the north",
		tags17,
		 backroom,
		NULL,
		 cave,
		 "The door is closed.\n",
		"You see",
		 "The door is closed.\n",
		"I know nothing about that.",
		99,
		0,
		0,
		0,
		 toggleBackdoor,
		 isAlreadyClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 18 = openBox */
		alwaysTrue,
		 "a wooden box",
		tags18,
		NULL,
		NULL,
		NULL,
		 "The box is open.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "You need a key to open it.",
		 5,
		 10,
		0,
		0,
		 isAlreadyOpen,
		 toggleBox,
		 isStillOpen,
		 isAlreadyOpen
	},
	{	/* 19 = closedBox */
		alwaysTrue,
		 "a wooden box",
		tags19,
		NULL,
		NULL,
		NULL,
		 "The box is closed.\n",
		"You see",
		"You can't get much closer than this.\n",
		"I know nothing about that.",
		 5,
		0,
		0,
		0,
		 toggleBox,
		 isAlreadyClosed,
		 toggleBoxLock,
		 isAlreadyUnlocked
	},
	{	/* 20 = lockedBox */
		alwaysTrue,
		 "a wooden box",
		tags20,
		 backroom,
		NULL,
		NULL,
		 "The box is closed.\n",
		"You see",
		"You can't get much closer than this.\n",
		"I know nothing about that.",
		 5,
		0,
		0,
		0,
		 isStillLocked,
		 isAlreadyClosed,
		 isAlreadyLocked,
		 toggleBoxLock
	},
	{	/* 21 = keyForBox */
		alwaysTrue,
		 "a tiny key",
		tags21,
		 cave,
		NULL,
		NULL,
		 "The key is really small and shiny.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "A small key opens a small lock.",
		 1,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 22 = lampOff */
		alwaysTrue,
		 "a lamp",
		tags22,
		 field,
		NULL,
		NULL,
		 "The lamp is off.\n",
		"You see",
		"You can't get much closer than this.\n",
		 "Essential in dark areas.",
		 5,
		0,
		0,
		0,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	},
	{	/* 23 = lampOn */
		alwaysTrue,
		 "a lamp",
		tags23,
		NULL,
		NULL,
		NULL,
		 "The lamp is on.\n",
		"You see",
		"You can't get much closer than this.\n",
		"I know nothing about that.",
		 5,
		0,
		0,
		 100,
		cannotBeOpened,
		cannotBeClosed,
		cannotBeLocked,
		cannotBeUnlocked
	}
};
