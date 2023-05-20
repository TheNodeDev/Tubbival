//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

struct ICommandLine {
public:
	virtual void		CreateCmdLine(const char* commandline) = 0;
	virtual void		CreateCmdLine(int argc, char** argv) = 0;
	/**
	 * Gets the command line parameters
	 * */
	virtual const char* GetCmdLine(void) const = 0;
	virtual	const char* CheckParm(const char* psz, const char** ppszValue = 0) const = 0;
	/**
	 * Remove the given command line parameter
	 * */
	virtual void		RemoveParm(const char* parm) = 0;
	/**
	 * Appends a command line parameter
	 * */
	virtual void		AppendParm(const char* pszParm, const char* pszValues) = 0;
	virtual const char* ParmValue(const char* psz, const char* pDefaultVal = 0) const = 0;
	virtual int			ParmValue(const char* psz, int nDefaultVal) const = 0;
	virtual float		ParmValue(const char* psz, float flDefaultVal) const = 0;
	/**
	 * Returns the count of the parameters
	 * */
	virtual int			ParmCount() const = 0;
	/**
	 * Returns the position of a parameter
	 * */
	virtual int			FindParm(const char* psz) const = 0;
	/**
	 * Gets the parameter on position nIndex
	 * */
	virtual const char* GetParm(int nIndex) const = 0;
	/**
	 * Set the parameter at nIndex to pNewParam
	 * */
	virtual void SetParm(int nIndex, char const* pNewParm) = 0;
};