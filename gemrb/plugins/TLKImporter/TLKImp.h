/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/TLKImporter/TLKImp.h,v 1.14 2004/08/03 22:58:37 guidoj Exp $
 *
 */

#ifndef TLKIMP_H
#define TLKIMP_H

#include "../Core/StringMgr.h"

class TLKImp : public StringMgr {
private:
	DataStream* str;
	bool autoFree;

	//Data
	ieDword StrRefCount, Offset;
public:
	TLKImp(void);
	~TLKImp(void);
	bool Open(DataStream* stream, bool autoFree = true);
	char* GetString(ieStrRef strref, unsigned long flags = 0);
	StringBlock GetStringBlock(ieStrRef strref, unsigned long flags = 0);
private:
	/** replaces tags in dest, don't exceed Length */
	bool ResolveTags(char* dest, char* source, int Length);
	/** returns the needed length in Length, 
		if there was no token, returns false */
	bool GetNewStringLength(char* string, int& Length);
	/**returns the decoded length of the built-in token
	   if dest is not NULL it also returns the decoded value
	   */
	int BuiltinToken(char* Token, char* dest);
 	int GenderStrRef(int slot, int malestrref, int femalestrref);

public:
	void release(void)
	{
		delete this;
	}
};

#endif
