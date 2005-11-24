/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/Interface.h,v 1.176 2005/11/24 17:44:08 wjpalenstijn Exp $
 *
 */

/**
 * @file Interface.h
 * Declaration of Interface class, central interconnect for various GemRB parts
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "InterfaceDesc.h"
#include "../../includes/SClassID.h"
#include "Cache.h"
#include "GlobalTimer.h"


class PluginMgr;
class Video;
class ResourceMgr;
class StringMgr;
class Container;
class Factory;
class ImageMgr;
class Font;
class EventMgr;
class WindowMgr;
class ScriptEngine;
class Console;
class SoundMgr;
class TextArea;
class SaveGameIterator;
class Variables;
class Item;
class Spell;
class MusicMgr;
class TableMgr;
class SymbolMgr;
class ITMExtHeader;
class SPLExtHeader;
class DataFileMgr;
class Game;
class WorldMap;
class WorldMapArray;
class GameControl;
class OpcodeMgr;
class Window;
class CREItem;
class Store;
class Actor;
struct Effect;
class EffectRef;
class Map;
class ScriptedAnimation;
class Control;

typedef struct Table {
	TableMgr * tm;
	char ResRef[8];
	bool free;
} Table;

typedef struct Symbol {
	SymbolMgr * sm;
	char ResRef[8];
	bool free;
} Symbol;

typedef struct SlotType {
	ieDword slottype;
	ieDword slottip;
	ieDword slotid;
	ieDword sloteffects;
	ieResRef slotresref;
} SlotType;

#ifdef WIN32

#include <windows.h>

#ifdef GEM_BUILD_DLL
#define GEM_EXPORT __declspec(dllexport)
#else
#define GEM_EXPORT __declspec(dllimport)
#endif

#else
#define GEM_EXPORT
#endif

// Colors of modal window shadow
// !!! Keep these synchronized with GUIDefines.py !!!
#define MODAL_SHADOW_NONE	0
#define MODAL_SHADOW_GRAY	1
#define MODAL_SHADOW_BLACK	2

#define WINDOW_INVALID   -1
#define WINDOW_INVISIBLE 0
#define WINDOW_VISIBLE   1
#define WINDOW_GRAYED    2
#define WINDOW_FRONT     3

#define QF_NORMAL        0
#define QF_QUITGAME      1
#define QF_EXITGAME      2
#define QF_CHANGESCRIPT  4
#define QF_LOADGAME      8
#define QF_ENTERGAME     16

#define AP_UNUSABLE      0
#define AP_ATTACKED      1
#define AP_HIT           2
#define AP_WOUNDED       3
#define AP_DEAD          4
#define AP_NOTARGET      5
#define AP_ENDROUND      6
#define AP_ENEMY         7
#define AP_TRAP          8
#define AP_SPELLCAST     9

/**
 * @class Interface
 * Central interconnect for all GemRB parts, driving functions and utility functions possibly belonging to a better place
 */

class GEM_EXPORT Interface : public InterfaceDesc
{
private:
	PluginMgr * plugin;
	Video * video;
	ResourceMgr * key;
public:
	StringMgr *strings;
	GlobalTimer * timer;
private:
	Cache ItemCache;
	Cache SpellCache;
	Cache EffectCache;
	Factory * factory;
	ImageMgr * pal256;
	ImageMgr * pal32;
	ImageMgr * pal16;
	std::vector<Font*> fonts;
	EventMgr * evntmgr;
	WindowMgr * windowmgr;
	Window* ModalWindow;
	char WindowPack[10];
	ScriptEngine * guiscript;
	SoundMgr * soundmgr;
	OpcodeMgr * opcodemgr;
	SaveGameIterator *sgiterator;
	/** Windows Array */
	std::vector<Window*> windows;
	std::vector<int> topwin;
	Variables * vars;
	Variables * tokens;
	MusicMgr * music;
	std::vector<Table> tables;
	std::vector<Symbol> symbols;
	DataFileMgr * INIparty;
	DataFileMgr * INIbeasts;
	DataFileMgr * INIquests;
	Game * game;
	WorldMapArray* worldmap;
	int GameFeatures;
	ieResRef ButtonFont;
	ieResRef CursorBam;
	ieResRef TooltipFont;
	ieResRef TooltipBackResRef;
	ieResRef *DefSound; //default sounds 
	int DSCount;
	Color TooltipColor;
	int TooltipMargin;
	ieResRef Palette16;
	ieResRef Palette32;
	ieResRef Palette256;
	ieDword* slotmatrix; //itemtype vs slottype
	SlotType* slottypes;
	int ItemTypes;
	int tooltip_x;
	int tooltip_y;
	// the control owning the tooltip
	Control* tooltip_ctrl;
	// Currently dragged item or NULL
	CREItem* DraggedItem;
	// Current Store
	Store* CurrentStore;
	// Index of current container
	Container* CurrentContainer;
	bool UseContainer;
public:
	int SaveAsOriginal; //if true, saves files in compatible mode
	int QuitFlag;
	int LoadGameIndex;
	int SlotTypes; //this is the same as the inventory size
	ieResRef GlobalScript;
	ieResRef WorldMapName;
	Sprite2D **Cursors;
	int CursorCount;
	Sprite2D *FogSprites[32];
	Sprite2D **TooltipBack;
	Sprite2D *WindowFrames[4];
public:
	Interface(int iargc, char **iargv);
	~Interface(void);
	int Init(void);
	//TODO: Core Methods in Interface Class
	int SetFeature(int value, int position);
	int HasFeature(int position) const;
	bool IsAvailable(SClass_ID filetype);
	void * GetInterface(SClass_ID filetype);
	const char * TypeExt(SClass_ID type);
	Video * GetVideoDriver() const;
	ResourceMgr * GetResourceMgr() const;
	char * GetString(ieStrRef strref, ieDword options = 0);
	void FreeInterface(void * ptr);
	Factory * GetFactory() const;
	/** No descriptions */
	Color * GetPalette(int index, int colors);
	/** Returns a preloaded Font */
	Font * GetFont(const char *) const;
	Font * GetFont(unsigned int index) const;
	/** Returns the button font */
	Font * GetButtonFont() const;
	/** Returns the Event Manager */
	EventMgr * GetEventMgr() const;
	/** Returns the Window Manager */
	WindowMgr * GetWindowMgr() const;
	/** Get GUI Script Manager */
	ScriptEngine * GetGUIScriptEngine() const;
	/** Returns actor */
	Actor *GetCreature(DataStream *stream);
	/** Returns a PC index, by loading a creature */
	int LoadCreature(char *ResRef, int InParty, bool character=false);
	/** Sets a stat for the creature in actor index Slot */
	int SetCreatureStat(unsigned int Slot, unsigned int StatID, int StatValue, int Mod);
	/** returns the stat of a creature (mod:1-modified, 0-base) */
	int GetCreatureStat(unsigned int Slot, unsigned int StatID, int Mod);
	/** Loads a WindowPack (CHUI file) in the Window Manager */
	bool LoadWindowPack(const char *name);
	/** Loads a Window in the Window Manager */
	int LoadWindow(unsigned short WindowID);
	/** Creates a Window in the Window Manager */
#ifdef WIN32
#ifdef CreateWindow
#undef CreateWindow
#endif
#endif
	int CreateWindow(unsigned short WindowID, int XPos, int YPos, unsigned int Width, unsigned int Height, char* Background);
	/** Sets a Window on the Top */
	void SetOnTop(int Index);
	/** Add a window to the Window List */
	void AddWindow(Window * win);
	/** Get a Control on a Window */
	int GetControl(unsigned short WindowIndex, unsigned long ControlID);
	/** Adjust the scrolling of the control (if applicable) */
	int AdjustScrolling(unsigned short WindowIndex, unsigned short ControlIndex, short x, short y);
	/** Set the Text of a Control */
	int SetText(unsigned short WindowIndex, unsigned short ControlIndex, const char * string);
	/** Set the Tooltip text of a Control */
	int SetTooltip(unsigned short WindowIndex, unsigned short ControlIndex, const char * string);
	/** sets tooltip to be displayed */
	void DisplayTooltip(int x, int y, Control* ctrl);
	/** Actually draws tooltip on the screen. Called from SDLVideoDriver */
	void DrawTooltip();
	/** returns the textarea of the main game screen */
	TextArea *GetMessageTextArea();
	/** displays any string in the textarea */
	void DisplayString(const char *txt);
	/** displays a string constant in the textarea */
	void DisplayConstantString(int stridx, unsigned int color);
	/** displays a string constant followed by a number in the textarea */
	void DisplayConstantStringValue(int stridx, unsigned int color, ieDword value);
	/** displays a string constant in the textarea, starting with speaker's name */
	void DisplayConstantStringName(int stridx, unsigned int color, Scriptable *speaker);
	/** displays a string in the textarea, starting with speaker's name */
	void DisplayStringName(int stridx, unsigned int color, Scriptable *speaker);
	/** returns the Window Visible Flag */
	int GetVisible(unsigned short WindowIndex);
	/** Set a Window Visible Flag */
	int SetVisible(unsigned short WindowIndex, int visible);
	/** Show a Window in Modal Mode */
	int ShowModal(unsigned short WindowIndex, int Shadow);
	/** Set the Status of a Control in a Window */
	int SetControlStatus(unsigned short WindowIndex, unsigned short ControlIndex, unsigned long Status);
	/** Get a Window from the Loaded Window List */
	Window * GetWindow(unsigned short WindowIndex);
	/** Removes a Loaded Window */
	int DelWindow(unsigned short WindowIndex);
	/** Redraws all window */
	void RedrawAll();
	/** Refreshes any control associated with the variable name with value*/
	void RedrawControls(char *varname, unsigned int value);
	/** Popup the Console */
	void PopupConsole();
	/** Draws the Console */
	void DrawConsole();
	/** Get the Sound Manager */
	SoundMgr * GetSoundMgr();
	/** Get the SaveGameIterator */
	SaveGameIterator * GetSaveGameIterator();
	/** Get the Variables Dictionary */
	Variables * GetDictionary();
	/** Get the Token Dictionary */
	Variables * GetTokenDictionary();
	/** Get the Music Manager */
	MusicMgr * GetMusicMgr();
	/** Loads a 2DA Table, returns -1 on error or the Table Index on success */
	int LoadTable(const char * ResRef);
	/** Gets the index of a loaded table, returns -1 on error */
	int GetTableIndex(const char * ResRef);
	/** Gets a Loaded Table by its index, returns NULL on error */
	TableMgr * GetTable(unsigned int index);
	/** Frees a Loaded Table, returns false on error, true on success */
	bool DelTable(unsigned int index);
	/** Loads an IDS Table, returns -1 on error or the Symbol Table Index on success */
	int LoadSymbol(const char * ResRef);
	/** Gets the index of a loaded Symbol Table, returns -1 on error */
	int GetSymbolIndex(const char * ResRef);
	/** Gets a Loaded Symbol Table by its index, returns NULL on error */
	SymbolMgr * GetSymbol(unsigned int index);
	/** Frees a Loaded Symbol Table, returns false on error, true on success */
	bool DelSymbol(unsigned int index);
	/** Plays a Movie */
	int PlayMovie(char * ResRef);
	/** Generates traditional random number xdy+z */
	int Roll(int dice, int size, int add);
	/** Returns true on successful saving throw */
	bool SavingThrow(int Save, int Bonus);
	/** Loads a Game Compiled Script */
	int LoadScript(const char * ResRef);
	/** Enables/Disables the CutScene Mode */
	void SetCutSceneMode(bool active);
	/** returns true if in cutscene mode */
	bool InCutSceneMode();
	/** Updates the Game Script Engine State */
	void GSUpdate(bool update_scripts)
	{
		if(update_scripts) {
			timer->Update();
		}
		else {
			timer->Freeze();
		}
	}
	/** Get the Party INI Interpreter */
	DataFileMgr * GetPartyINI()
	{
		return INIparty;
	}
	DataFileMgr * GetBeastsINI()
	{
		return INIbeasts;
	}
	DataFileMgr * GetQuestsINI()
	{
		return INIquests;
	}
	/** Gets the Game class */
	Game * GetGame()
	{
		return game;
	}
	/** Gets the WorldMap class, returns the current worldmap or the first worldmap containing the area*/
	WorldMap * GetWorldMap(const char *area = NULL);
	GameControl *GetGameControl();

	void QuitGame(bool backtomain);
	void LoadGame(int index);
	/*reads the filenames of the sounds folder into a list */
	int GetCharSounds(TextArea *ta);
	int QuerySlotType(int idx) const;
	int QuerySlottip(int idx) const;
	int QuerySlotID(int idx) const;
	int QuerySlotEffects(int idx) const;
	const char * QuerySlotResRef(int idx) const;
	/*returns true if an itemtype is acceptable for a slottype */
	int CanUseItemType(int itype, int slottype) const;
	/*removes single file from cache*/
	void RemoveFromCache(const ieResRef resref);
	/*removes all files from directory*/
	void DelTree(const char *path, bool onlysaved);
	/*returns true if the file should be saved */
	bool SavedExtension(const char *filename);
	/*handles the load screen*/
	void LoadProgress(int percent);

	void DragItem(CREItem* item);
	CREItem* GetDraggedItem() { return DraggedItem; }
	CREItem *ReadItem(DataStream *str);
	bool ResolveRandomItem(CREItem *itm);
	Item* GetItem(const ieResRef resname);
	void FreeItem(Item *itm, const ieResRef name, bool free=false);
	Spell* GetSpell(const ieResRef resname);
	void FreeSpell(Spell *spl, const ieResRef name, bool free=false);
	Effect* GetEffect(const ieResRef resname);
	void FreeEffect(Effect *eff, const ieResRef name, bool free=false);
	ieStrRef GetRumour(const ieResRef resname);
	Container *GetCurrentContainer();
	int CloseCurrentContainer();
	void SetCurrentContainer(Actor *actor, Container *arg, bool flag=false);
	Store *GetCurrentStore();
	int CloseCurrentStore();
	Store *SetCurrentStore(const ieResRef resname);
	// FIXME: due to Win32 we have to allocate/release all common
	// memory from Interface. Yes, it is ugly.
	ITMExtHeader *GetITMExt(int count);
	SPLExtHeader *GetSPLExt(int count);
	Effect *GetFeatures(int count);
	void FreeITMExt(ITMExtHeader *p, Effect *e);
	void FreeSPLExt(SPLExtHeader *p, Effect *e);
	WorldMapArray *NewWorldMapArray(int count);
	void DoTheStoreHack(Store *s);
	void MoveViewportTo(int x, int y, bool center);
	/** plays stock gui sound referenced by index */
	void PlaySound(int idx);
	/** returns true if resource exists */
	bool Exists(const char *ResRef, SClass_ID type);
	/** creates a vvc/bam animation object at point */
	ScriptedAnimation* GetScriptedAnimation( const char *ResRef, Point &p);
	/** returns the first selected PC */
	Actor *GetFirstSelectedPC();
	/** returns a single sprite (not cached) from a BAM resource */
	Sprite2D* GetBAMSprite(const ieResRef ResRef, int cycle, int frame);
	/** returns a cursor sprite (not cached) */
	Sprite2D *GetCursorSprite();
	/** returns 0 for unmovable, -1 for movable items, otherwise it
	returns gold value! */
	int CanMoveItem(CREItem *item);
	int GetMaximumAbility();
	int GetStrengthBonus(int column, int value, int ex);
	int GetIntelligenceBonus(int column, int value);
	int GetDexterityBonus(int column, int value);
	int GetConstitutionBonus(int column, int value);
	int GetCharismaBonus(int column, int value);

	/** applies the spell on the target */
	void ApplySpell(const ieResRef resname, Actor *target, Actor *caster, int level);
	/** applies the spell on the area or on a scriptable object */
	void ApplySpellPoint(const ieResRef resname, Scriptable *target, Point &pos, Actor *caster, int level);
	/** applies a single effect on the target */
	void ApplyEffect(const ieResRef resname, Actor *target, Actor *caster, int level);

	/** dumps an area object to the cache */
	int SwapoutArea(Map *map);
	/** saves the game object to the destination folder  */
	int WriteGame(const char *folder);
	/** saves the worldmap object to the destination folder  */
	int WriteWorldMap(const char *folder);
	/** saves the .are and .sto files to the destination folder */
	int CompressSave(const char *folder);
	/** receives an autopause reason, returns 1 if pause was triggered by this call, -1 if it was already triggered */
	int Autopause(ieDword reason);
	/** registers engine opcodes */
	void RegisterOpcodes(int count, EffectRef *opcodes);

private:
	bool LoadConfig(void);
	bool LoadConfig(const char *filename);
	bool LoadGemRBINI();
	bool LoadINI(const char * filename);
	bool InitItemTypes();
	bool ReadStrrefs();
	bool ReadRandomItems();
	bool ReadItemTable(const ieResRef item, const char *Prefix);
	bool ReadAbilityTables();
	bool ReadAbilityTable(const ieResRef name, ieWord *mem, int cols, int rows);
	/** handles the QuitFlag bits (main loop events) */
	void HandleFlags();
	/** Creates a game control, closes all other windows */
	GameControl* StartGameControl();

public:
	char GameData[12];
	char GameOverride[12];
	char GameSounds[12];
	char GameScripts[12];
	ieResRef GameNameResRef;
	ieResRef GoldResRef; //MISC07.itm
	Variables *RtRows;
	char UserDir[_MAX_PATH];
	int argc;
	char **argv;
	char GameName[_MAX_PATH];
	char GameType[_MAX_PATH];
	char GemRBPath[_MAX_PATH];
	char PluginsPath[_MAX_PATH];
	char CachePath[_MAX_PATH];
	char GUIScriptsPath[_MAX_PATH];
	char GamePath[_MAX_PATH];
	char SavePath[_MAX_PATH];
	char INIConfig[_MAX_PATH];
	char CD1[_MAX_PATH];
	char CD2[_MAX_PATH];
	char CD3[_MAX_PATH];
	char CD4[_MAX_PATH];
	char CD5[_MAX_PATH];
	char CD6[_MAX_PATH];
	int Width, Height, Bpp, ForceStereo;
	unsigned int TooltipDelay;
	unsigned int FogOfWar;
	bool FullScreen, CaseSensitive, GameOnCD, SkipIntroVideos, DrawFPS;
	/** The Main program loop */
	void Main(void);
	/** Draws the Visible windows in the Windows Array */
	void DrawWindows(void);
	/** Sends a termination signal to the Video Driver */
	bool Quit(void);
	/** CheatKey support */
	void EnableCheatKeys(int Flag)
	{
		CheatFlag=(Flag > 0);
	}

	bool CheatEnabled()
	{
		return CheatFlag;
	}

	/** Next Script Name */
	char NextScript[64];
	/** Console is on Screen */
	bool ConsolePopped;
	/** Cheats enabled? */
	bool CheatFlag;
	/** The Console Object */
	Console * console;

#ifdef _DEBUG
	int FileStreamPtrCount;
	int CachedFileStreamPtrCount;
#endif
};

#ifdef GEM_BUILD_DLL

#ifndef INTERFACE
extern Interface* core;
#ifdef WIN32
extern HANDLE hConsole;
#endif
#endif

#else
#ifdef WIN32
GEM_EXPORT Interface * core;
GEM_EXPORT HANDLE hConsole;
#else
extern Interface * core;
#endif
#endif

#endif
